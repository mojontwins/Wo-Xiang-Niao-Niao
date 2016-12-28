// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

void game_init (void) {
	map_ptr = (unsigned char *) (map + (level >> 1) * COLUMN_SIZE * MAP_W);
	pal_bg (world_pals [level]);
	pal_spr (level == 8 ? pal_fg_2 : (((level >> 1) & 1) ? pal_fg_1 : pal_fg_0));
	mtile_pattern_offsets = (unsigned char *) world_mpos [level];
	mtile_palettes = (unsigned char *) precalc_attr_bits + ((level >> 1) << 6);
	behs = (unsigned char *) world_behs [level];

	enems_init_level ();
	player_init ();
	cam_pos = prx - 120; if (cam_pos < 0) cam_pos = 0;	

	if (!pcheckpoint) pobjs = pobjs_starter; 
	opobjs = 99;
}

void game_loop (void) {
	game_res = 0;
	opscore = 0;
	fskip_counter = 0;
	autoscroll = ((level & 1) || level == 8);

	scroll_prepare_screen ();

	// Paint level, score & lives
	vram_adr (NAMETABLE_A + 0x47); p_score_d ();
	p_t2d (20, 2, plives);
	p_t2d (29, 2, pobjs);
	scroll_init ();

	ppu_on_all ();

	set_vram_update (update_list);
	scroll_draw_screen ();

	gpit = 0; while (gpit ++ < 4) pal_split_wait ();

	music_play (MUSIC_INGAME + (level & 1));

	while (do_game_loop) {
		gp_ul = update_list;			// Reset pointer to update list
		
		// NTSC magic
		if (is_ntsc) { fskip_counter ++; if (fskip_counter == 6) fskip_counter = 0;	}

		split (cam_pos & 0x01ff, 0);	// Wait until sprite 0 hit then set scroll

		if (fskip_counter != 5) {
			half_life = 1 - half_life;		// Main flip-flop
			frame_counter ++;				// Increase frame counter
		
			oam_index = 28;					// Reset OAM index; skip sprite #0 & player
			pad0 = pad_poll (0);			// Read pads here.

			// Cheat. Remove
			if ((pad0 & (PAD_SELECT | PAD_UP | PAD_A)) == (PAD_SELECT | PAD_UP | PAD_A)) {
				game_res = 1; do_game_loop = 0;
				//pobjs = PLAYER_MAX_ITEMS;
			}
			if ((pad0 & (PAD_SELECT | PAD_DOWN)) == (PAD_SELECT | PAD_DOWN)) {
				pobjs = 9;
			}
			// End of cheat
			if (pobjs != opobjs) { p_t2 (29, 2, pobjs); opobjs = pobjs; }
			if (prx <= cam_pos + 4)	{ if (safe_landing) prx = cam_pos + 4; else player_kill (1); }

			camera_do ();
			scroll_to ();
			enems_move ();
			player_move ();
			
			if (3 == (level >> 1)) pal_cycle_do ();
			
			//*((unsigned char*)0x2001) = 0x1f;

			oam_hide_rest (oam_index);
		}

		if (opscore) {
			p_score ();
			opscore = 0; 
		}
		
		*gp_ul = NT_UPD_EOF;	
		ppu_wait_nmi ();
		
		//*((unsigned char*)0x2001) = 0x1e;
	}

	music_stop ();
	set_vram_update (0);

	if (game_res) {
		ticker = ticks + ticks; while (--ticker) {
			split (cam_pos & 0x01ff,0);
			ppu_wait_nmi ();
		}
	}

	gpit = 4; while (gpit --) pal_split_wait ();
	oam_hide_rest (0);
	ppu_off ();
}

void game_over () {
	enter_screen (pal_bg_0, screen_game_over);
	do_screen (GAME_OVER_SCREEN_TIME);
}

void game_ending () {
	enter_screen (pal_bg_0, screen_win);
	music_play (MUSIC_FANFARE_START);
	ticker = 0; rda = 0; rdb = 0; rdc = 0; 
	pal_spr (pal_fg_0);
	while (1) {
		if (ticker < ticks) ticker ++; else {
			if (pad_poll (0)) break;
		}
		
		rdc = (rdc + 1) & 7; if (!rdc) {
			rdb = (rdb + 1) & 3; if (!rdb) {
				rda = rand8 () & 1;
			}
		}

		oam_meta_spr (124, 111, 4, spr_player_ending [(rda << 2) + rdb]);
		ppu_wait_nmi ();
	}
	exit_cleanly ();
}

void game_title () {
	enter_screen (pal_bg_t0, screen_title);
	rda = 0x31;

	while (1) {
		pad0 = pad_poll (0);
		if (pad0 & PAD_START) {
			cur_level = 0; break;
		} else if (pad0 & PAD_SELECT) {
			cur_level = last_level & 0xfe; break;
		} else if ((pad0 & (PAD_A | PAD_B)) == (PAD_A | PAD_B)) {
			cur_level = 8; break;
		}
		pal_col (3, rda);
		oam_hide_rest (0);
		ppu_wait_nmi ();		
		rda ++; if (rda == 0x3d) rda = 0x31;
	}
	music_play (MUSIC_FANFARE_START);
	game_time = 4; ticker = 0; wait_time_or_input ();
	exit_cleanly ();
}

void game_level () {
	enter_screen (pal_bg_0, screen_level);
	do_screen (LEVEL_SCREEN_TIME);
}

void game_bonus () {
	enter_screen (pal_bg_0, screen_bonus);
	do_screen (LEVEL_SCREEN_TIME);
}

void game_cycle () {
	game_level ();
	game_init ();
	game_loop ();
}