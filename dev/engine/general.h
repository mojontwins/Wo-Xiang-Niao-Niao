// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

void enter_screen (const unsigned char *pal, void (*func) (void)) {
	scroll (0, 0);
	
	cls ();
	reset_attributes ();
	(*func) ();
	//write_attr_table (NAMETABLE_A);
	
	pal_bg (pal);
	ppu_on_all ();
	fade_in ();
}

void exit_cleanly (void) {
	set_vram_update (0);
	oam_hide_rest (0);
	music_stop ();
	fade_out ();
	ppu_off ();	
}

void wait_time_or_input (void) {
	rda = (pad_poll (0) != 0);
	while (game_time) {
		ticker ++; if (ticker == ticks) {
			ticker = 0;
			game_time --;
		}

		if (pad_poll (0)) {
			if (!rda) break;
		} else {
			rda = 0;
		}

		ppu_wait_nmi ();
	}
}

void wait_time_or_input_split (void) {
	while (game_time) {
		ticker ++; if (ticker == ticks) {
			ticker = 0; game_time --;
		}
		if (rda) if (pad_poll (0)) break;
		split (cam_pos & 0x01ff,0);
		ppu_wait_nmi ();
	}
}

void do_screen (unsigned char seconds) {
	game_time = seconds; ticker = 0;
	wait_time_or_input ();
	exit_cleanly ();
}

signed int add_sign (signed int sign, signed int value) {
	return sign == 0 ? 0 : sign < 0 ? -value : value;
}

signed int saturate (signed int v, signed int max) {
	return v >= 0 ? (v > max ? max : v) : (v < -max ? -max : v);
}

// Only called once, inline for speed. And obfuscation. Pichude.
/*
unsigned char cl (signed int x1, unsigned char y1, signed int x2, unsigned char y2) {
	return x1 + 4 >= x2 && x1 <= x2 + 12 && y1 + 12 >= y2 && y1 <= y2 + 12;
}
*/

void cm_two_points (void) {
	// Collide map, two points
	// with vertical adjust.
	/*
	rdx = cx1 >> 1;
	at1 = *(map_ptr + (rdx << 3) + (rdx << 1) + ((cy1 < 2) ? 0 : cy1 - 2));
	at1 = behs [(cx1 & 1) ? (at1 & 15) : (at1 >> 4)];
	
	rdx = cx2 >> 1;
	at2 = *(map_ptr + (rdx << 3) + (rdx << 1) + ((cy2 < 2) ? 0 : cy2 - 2));
	at2 = behs [(cx2 & 1) ? (at2 & 15) : (at2 >> 4)];
	*/
	rdx = cx1 >> 1;
	if (cy1 > 11) at1 = 0; else {
		if (cy1 < 2) cy1 = 2; 
		at1 = *(map_ptr + (rdx << 3) + (rdx << 1) + cy1 - 2);
		at1 = behs [(cx1 & 1) ? (at1 & 15) : (at1 >> 4)];	
	}

	rdx = cx2 >> 1;
	if (cy2 > 11) at2 = 0; else {
		if (cy2 < 2) cy2 = 2;
		at2 = *(map_ptr + (rdx << 3) + (rdx << 1) + cy2 - 2);
		at2 = behs [(cx2 & 1) ? (at2 & 15) : (at2 >> 4)];	
	}
}
