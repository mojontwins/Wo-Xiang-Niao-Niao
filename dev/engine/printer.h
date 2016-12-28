// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

void cls (void) {
	vram_adr (NAMETABLE_A);
	vram_fill (0, 2048);		// Both Nametables A & B (0x2000, 0x2400)
}

void fade_out (void) {
	for (fader = 4; fader > -1; fader --) {
		pal_bright (fader);
		delay (FADE_DELAY);
	}	
}

void fade_in (void) {
	for (fader = 0; fader < 5; fader ++) {
		pal_bright (fader);
		delay (FADE_DELAY);
	}	
}

void pal_split_wait (void) {
	pal_bright (gpit);
	split (cam_pos & 0x01ff,0);
	ppu_wait_nmi ();
}

void reset_attributes (void) {
	gpit = 64; while (gpit --) attr_table [gpit] = 0;
}

void write_attr_table (unsigned int nt) {
	vram_adr (nt + 960);
	vram_write (attr_table, 64);
}

void draw_tile (void) {
	// Draws metatile rdt at rdx, rdy. rdx = 0->31, metatile coordinates
	gp_addr = (rdx > 15 ? NAMETABLE_B : NAMETABLE_A) + ((rdx & 15) << 1) + (rdy << 6);
	rdc = rdt << 2;
	vram_adr (gp_addr); vram_put (rdc ++); vram_put (rdc ++);
	vram_adr (gp_addr + 1); vram_put (rdc ++); vram_put (rdc);
	rdc = ((rdx & 15) >> 1) + ((rdy >> 1) << 3);
	rdb = (rdx & 1) + ((rdy & 1) << 1);
	rda = (attr_table [rdc] & bitmasks [rdb]) | (ts_pals [rdt - 16] << (rdb << 1));
	attr_table [rdc] = rda;
}

void draw_tile_rep_strip (void) {
	// Draws a strip of rdt @ rdy
	for (rdx = 0; rdx < 32; rdx ++) draw_tile ();
}

void write_gp_addr_horz (void) {
	*gp_ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
	*gp_ul ++ = LSB (gp_addr);
}

void p_t2 (unsigned char x, unsigned char y, unsigned char n) {
	gp_addr = NAMETABLE_A_X_Y (x, y);
	write_gp_addr_horz ();
	*gp_ul ++ = 2;
	*gp_ul ++ = DIGIT (n / 10);
	*gp_ul ++ = DIGIT (n % 10);
}

void p_t2d (unsigned char x, unsigned char y, unsigned char n) {
	vram_adr (NAMETABLE_A_X_Y (x, y));
	vram_put (DIGIT (n / 10));
	vram_put (DIGIT (n % 10));
}

void p_score (void) {
	// Prints BCD score at 7, 1
	gp_addr = NAMETABLE_A + 0x47;
	write_gp_addr_horz ();
	*gp_ul ++ = 5;
	gp_gen = bcd_score + 4;
	*gp_ul ++ = *gp_gen --;
	*gp_ul ++ = *gp_gen --;
	*gp_ul ++ = *gp_gen --;
	*gp_ul ++ = *gp_gen --;
	*gp_ul ++ = *gp_gen --;
}

void p_score_d (void) {
	gp_gen = bcd_score + 4;
	vram_put (*gp_gen --);
	vram_put (*gp_gen --);
	vram_put (*gp_gen --);
	vram_put (*gp_gen --);
	vram_put (*gp_gen --);
}

/*
void p_s (unsigned char x, unsigned char y, unsigned char *s) {
	vram_adr (NAMETABLE_A_X_Y (x, y));
	while (rda = *s ++) vram_put (rda - 32);
}
*/
void p_s (unsigned char x, unsigned char y, unsigned char *s) {
	vram_adr (NAMETABLE_A_X_Y (x, y));
	while (rda = *s ++) {
		if (rda == '%') {
			y ++; vram_adr (NAMETABLE_A_X_Y (x, y));
		} else vram_put (rda - 32);
	}
}

void pal_cycle_init (void) {
	pal_cycle [0] = 0x18;
	pal_cycle [1] = 0x28;
	pal_cycle [2] = 0x38;
}

void pal_cycle_do (void) {
	if ((frame_counter & 15) == 0) {
		gpit = pal_cycle [2]; 
		pal_cycle [2] = pal_cycle [1]; 	pal_col (15, pal_cycle [2]);
		pal_cycle [1] = pal_cycle [0]; 	pal_col (14, pal_cycle [1]);
		pal_cycle [0] = gpit; 			pal_col (13, pal_cycle [0]);
	}
}

#ifdef DEBUG
unsigned char hex_digit (unsigned char n) {
	if (n < 10) return n + 16;
	return n + 23;
}

void debug_pt_hex (unsigned char x, unsigned char y, unsigned char n) {
	gp_addr = NAMETABLE_A_X_Y (x, y);
	write_gp_addr_horz ();
	*gp_ul ++ = 2;
	*gp_ul ++ = hex_digit (n >> 4);
	*gp_ul ++ = hex_digit (n & 0x0f);
}

void debug_pt_hex_d (unsigned char x, unsigned char y, unsigned char n) {
	vram_adr (NAMETABLE_A_X_Y (x, y));
	vram_put (hex_digit (n >> 4));
	vram_put (hex_digit (n & 0x0f));
}
#endif
