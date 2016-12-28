// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

void enems_fp_create (void) {
	// Creates floating point dynamic versions of enems from screen rdb

	if (rdb > 0xf) return;		// Don't!

	rdc = enems_half [rdb]; rdt = enems_offs [rdb];
	gpit = ENEMS_PER_SCREEN; while (gpit --) {
		// This can be optimized for THIS game as there's only one type of 
		// Baddie which needs fp variables, which is ent = 4.
		// Original:
		/*
		ent = (en_t [rdt] >> 4) & 7;
		enf_vx [rdc] = enf_vy [rdc] = 0;
		enf_x [rdc] = LSB (en_x [rdt]) << FIX_BITS;
		enf_y [rdc] = ((ent == 4) ? 241 : en_y [rdt]) << FIX_BITS;
		*/
		// Shaved for this game:
		enf_vx [rdc] = enf_vy [rdc] = 0;
		enf_x [rdc] = LSB (en_x [rdt]) << FIX_BITS;
		enf_y [rdc] = 241 << FIX_BITS;

		rdc ++; rdt ++;	
	}
}

void enems_init_level (void) {
	// Copies (expands & prepares) ROM data to RAM.
	// ROM format is T XY1 XY2 S

	gp_gen = (unsigned char *) enems_ROM + (level >> 1) * MAX_ENEMS * 4;

	en_n_pant = 0; en_ct_aux = 0; rdct = 0;
	for (gpit = 0; gpit < MAX_ENEMS; gpit ++) {
		en_slot [gpit] = rdct ++; if (rdct == 6) rdct = 0;

		// Read type
		en_t [gpit] = *gp_gen ++;

		// Read XY1
		rda = *gp_gen ++;
		en_x [gpit] = (en_n_pant << 8) + (rda & 0xf0);
		en_y [gpit] = rda << 4;

		// Read XY2
		rdb = *gp_gen ++;

		// Read S
		rdc = *gp_gen ++;

		// General
		en_x1 [gpit] = LSB (en_x [gpit]);
		en_y1 [gpit] = en_y [gpit];
		en_x2 [gpit] = rdb & 0xf0;
		en_y2 [gpit] = rdb << 4;

		rdt = (en_t [gpit] >> 4) & 7;
		if (rdt != 3 || !pcheckpoint) en_r [gpit] = 0; else if (en_r [gpit]) en_x [gpit] = 4096;

		switch (rdt) {
			case 0:
				en_y [gpit] = 241;
				break;
			case 1:
				// Linear sprites
				if (rdc > 128) {
					en_r [gpit] = rdc - 128; rdc = 1;
				} else en_r [gpit] = 0;
				en_mx [gpit] = add_sign (en_x2 [gpit] - en_x1 [gpit], rdc);
				en_my [gpit] = add_sign (en_y2 [gpit] - en_y1 [gpit], rdc);
				break;
			case 2:
				// Gyrosaws
				en_mx [gpit] = 0; 		// Counter
				en_my [gpit] = rdc; 	// clockwise = 1; counter-clockwise = 0
				break;
			case 4:
				en_y1 [gpit] = en_y [gpit]; en_y [gpit] = 241;
				en_my [gpit] = PEZON_WAIT + (rdc << 3);
				en_mx [gpit] = en_my [gpit];
				break;
			case 6:
				en_y1 [gpit] = en_y [gpit];
				break;
		}

		// Keep up
		en_ct_aux ++; if (en_ct_aux == 3) { en_ct_aux = 0; en_n_pant ++; }
	}

	// Create for the first two screens.
	rdb = MSB (cam_pos); enems_fp_create ();
	//rdb = MSB (cam_pos) + 1; enems_fp_create ();
	orda = MSB (cam_pos);
}

void enems_move (void) {
	// Update enemies from current "virtual" screen and the next.
	rda = MSB (cam_pos); 

	// Need to reset this.
	pgtmy = pgotten = 0;

	// Enemies with fixed point maths have to be created dinamically as the map scrolls.
	// Half those arrays changes when the virtual screen changes.
	if (rda > orda) {
		// Next screen, update the half not updated last time
		// Creates enems from "next" screen
		rdb = rda + 1;
		enems_fp_create ();
	} else if (rda < orda) {
		// Previous screen, update the same half which was updated last time
		// Creates enems from "current" screen
		rdb = rda;
		enems_fp_create ();
	}
	orda = rda;

	rda = rda + rda + rda; rdb = rda <= MAX_ENEMS - ENEM_PROCESS_MAX ? rda + ENEM_PROCESS_MAX : MAX_ENEMS;
	for (rdt = rda; rdt < rdb; rdt ++) {
		ens = (en_t [rdt] & 0x0f) << 2;
		ent = (en_t [rdt] >> 4) & 0x07;
		slot = en_slot [rdt];
		en_jc = 0;

		// Update
		#include "enemmods/enems_update.h"

		// Collision
		if ((rdt & 1) != half_life) {
			#include "enemmods/enems_collision.h"
		}

		if (en_x [rdt] >= cam_pos && en_x [rdt] < cam_pos + 240) {
			if (ent == 4) {
				oam_index = oam_meta_spr (
					en_x [rdt] - cam_pos, en_y1 [rdt] + SPRITE_ADJUST,
					oam_index,
					spr_enems [53]
				);
			}
			// Add to OAM
			oam_index = oam_meta_spr (
				en_x [rdt] - cam_pos, en_y [rdt] + SPRITE_ADJUST,
				oam_index,
				spr_enems [en_cell]
			);
		}
	}
}
