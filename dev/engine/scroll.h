// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

/*
	Map is divided in columns. Each column is 25 bytes.

	First 10 bytes are 2x10 metatiles, column-ordered, as in:

	0x00 0x0a
	0x01 0x0b
	0x02 0x0c
	0x03 0x0d
	0x04 0x0e
	0x05 0x0f
	0x06 0x10
	0x07 0x11
	0x08 0x12
	0x09 0x13

	(2 metatiles per byte)

	Next 4 bytes are 5 attributes for such metatiles, ordered top->bottom

	Each 16x16 metatile is composed by 2x2 tiles:

 	(t << 2)      (t << 2 + 2)
 	(t << 2 + 1)  (t << 2 + 3)

 	Each frame, 1/4 of the tiles and all of the attributes are sent to 
 	the nametable via NMI update.
*/

void scroll_init (void) {
	col_ctr = 0;
}

void scroll_paint_chunk (void) {
	// Globals needed:
	//	col_idx			- Column index.
	//	map_ptr			- Is map + level offset (points to the beginning of strip)
	//	gp_ul			- Pointer to the update list

	// Calculate memory address of current column [col_idx * 10]
	col_ptr = map_ptr + (col_idx << 3) + (col_idx << 1);

	// VRAM address
	rdb = (col_idx << 2) & 63;		// Column # is directly based upon col_idx!
	rdc = rdb & 31;

	// which nametable?
	if (rdb < 32) {
		col_adr = NAMETABLE_A + (TOP_ADJUST << 5) + rdc;
		col_attr_adr = NAMETABLE_A + ((TOP_ADJUST >> 2) << 3) + 0x03c0 + (rdc >> 2);
	} else {
		col_adr = NAMETABLE_B + (TOP_ADJUST << 5) + rdc;
		col_attr_adr = NAMETABLE_B + ((TOP_ADJUST >> 2) << 3) + 0x03c0 + (rdc >> 2);
	}

	gp_gen = col_ptr;

	if (col_ctr != 4) {
		gp_addr = col_adr + col_ctr;

		// metatile offset
		col_offs = (col_ctr & 1) << 1;

		// fill in 10 metatiles...
		
		// starting address
		*gp_ul++ = MSB (gp_addr) | NT_UPD_VERT;
		*gp_ul++ = LSB (gp_addr);

		// 20 sequential writes
		*gp_ul++ = 20;

		// write 1 column of 10 metatiles, unrolled
		if (col_ctr >> 1) {
			// Read metatile from map. This is pattern number
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs;
			*gp_ul ++ = rda ++;					// Write fist pattern
			*gp_ul ++ = rda;					// Write next pattern

			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) & 15] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
		} else {
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
			rda = mtile_pattern_offsets [(*gp_gen ++) >> 4] + col_offs; *gp_ul ++ = rda ++; *gp_ul ++ = rda;
		}

	} else {
		// And now, the attributes
		
		gp_addr = col_attr_adr;
		scit = 5; while (scit --) {
			rda = (*gp_gen ++); rdb = (rda & 15); rdc = (rda >> 4);
			rdt = mtile_palettes [16+rdb] + mtile_palettes [rdc];
			rda = (*gp_gen ++); rdb = (rda & 15); rdc = (rda >> 4);
			rdt += mtile_palettes [48+rdb] + mtile_palettes [32+rdc];
			*gp_ul ++ = MSB (gp_addr);
			*gp_ul ++ = LSB (gp_addr);
			*gp_ul ++ = rdt;
			gp_addr += 8;
		}

		// Recreate the above calculating!

	}
	// Next pattern column to process
	//col_ctr = (col_ctr + 1) & 3;
	col_ctr ++; if (col_ctr == 5) col_ctr = 0;

	// Don't update SFX if set!
}

void scroll_draw_one_chunk_completely (void) {
	col_ctr = 0;
	gp_ul = update_list;
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	*gp_ul = NT_UPD_EOF;
	ppu_wait_nmi ();
	gp_ul = update_list;
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	*gp_ul = NT_UPD_EOF;
	ppu_wait_nmi ();
}

void scroll_to (void) {
	// Updates nametables upon direction
	if (cam_pos > cam_pos_old) {
		col_idx = (cam_pos >> 5) + 9;
		scroll_paint_chunk ();
	} else if (cam_pos < cam_pos_old) {
		col_idx = (cam_pos >> 5) - 1;
		scroll_paint_chunk ();
	}

	cam_pos_old = cam_pos;
}

/*
void scroll_draw_screen (void) {
	// Redraw
	cx1 = cam_pos >> 5; cx2 = cx1 + 8;
	for (col_idx = cx1; col_idx <= cx2; col_idx ++) {
		scroll_draw_one_chunk_completely ();
	}
}
*/
void scroll_draw_screen (void) {
	// Redraw
	cx1 = (cam_pos >> 5); if (cx1) cx1 --;
	cx2 = cx1 + 10;
	for (col_idx = cx1; col_idx <= cx2; col_idx ++) {
		scroll_draw_one_chunk_completely ();
	}
}

void scroll_prepare_screen (void) {
	// Fills top and bottom stripes with tiles accross both nametables
	reset_attributes ();

	vram_inc (1);
	
	rdt = 30; rdy = 1;
	draw_tile_rep_strip ();
	rdt = 63; for (rdy = 12; rdy < 15; rdy ++) draw_tile_rep_strip ();
	
	vram_inc (0);

	write_attr_table (NAMETABLE_A);
	write_attr_table (NAMETABLE_B);

	// Setup top lines for status
	p_s (1, 2, "SCORE\\00000  LIVES\\00  BEES\\00");
	vram_adr (NAMETABLE_A + 95);
	vram_put (59);	// This tile has a non-zero dot at the bottom right minux 1 pixel (avoid PPU bug in x=255!)

	// Add sprite 0 for sprite 0-based split
	oam_spr (254, 22, 255, 0x20, 0);
}
