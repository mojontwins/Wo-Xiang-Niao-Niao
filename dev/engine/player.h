// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

void player_init (void) {
	// KISS for now, expand "when" needed.
	py = 64 << FIX_BITS;
	pry = 16;

	prx = pcheckpoint ? pcheckpoint : 16;
	px = prx << FIX_BITS;
	
	prx_advance = prx + 64;
	pvx = 0; pvy = 0;
	pgotten = 0; ppossee = 0; pkilled = 0;
	phit = penhit = 0;
	pfacing = 0; pfr = 0;
	pj = pjb = 0;
	do_game_loop = 1;
	pen = 1;
	psoff = 0;
}

void player_kill (signed char sign) {
	if (sign == 0) sign = -1; // Patchy patch
	pvx = add_sign (sign, PLAYER_VX_MAX);
	pvy = -PLAYER_VY_JUMP_MAX;
	if (pen) {
		pen = 0;
		penhit = ticks; 
	} else if (!penhit) {
		pkilled = 1;
	}
}

void player_move (void) {
	if (!game_res) {
		// Invalidate controls if pkilled
		pad = pkilled ? 0 : pad0;

		// ========
		// Vertical
		// ========

		// Gravity
		if (!pgotten) {
			if (pvy < PLAYER_VY_FALLING_MAX) pvy += PLAYER_G; else pvy = PLAYER_VY_FALLING_MAX;
		}

		// Move
		py = py + pvy;
		if (py < 0) py = 0;
		if (py > 3072) {
			sfx_play (SFX_CHOF, SC_LEVEL);
			pkilled = 1;
		}
		if (py > 3584) {
			do_game_loop = 0;
		}

		pry = py >> FIX_BITS;
		
		// Collide
		// cm_two_points handles 2-point collision. Just give two points 
		// (cx1, cy1), (cx2, cy2), and then check at1 and at2
		if (!pkilled) {
			cx1 = prx >> 4;
			cx2 = (prx + 7) >> 4;

			if (pvy < 0) {
				cy1 = cy2 = pry >> 4;
				cm_two_points ();
				if ((at1 & 8) || (at2 & 8)) {
					pgotten = pvy = 0;
					pry = (cy1 + 1) << 4;
					py = pry << FIX_BITS;
				} else if ((at1 & 2) || (at2 & 2)) {
					if (pctj > 2) pj = 0;
				}
			} else if (pvy + pgtmy > 0) {
				cy1 = cy2 = (pry + 15) >> 4;
				cm_two_points ();
				if (((pry - 1) & 15) < 4 && ((at1 & 12) || (at2 & 12))) {
					pgotten = pvy = 0;
					pry = (cy1 - 1) << 4;
					py = pry << FIX_BITS;
				} else if ((at1 & 2) || (at2 & 2)) {
					pvy = PLAYER_VY_SINK;
				}
			}
			cy1 = cy2 = (pry + 16) >> 4;
			cm_two_points ();
			ppossee = ((at1 & 14) || (at2 & 14));
			pslip = (ppossee && ((at1 & 16) || (at2 & 16)));

			if (pad & PAD_A) {
				if (!pjb) {
					pjb = 1;
					if (!pj) {
						if (pgotten || ppossee || phit) {
							pj = 1; pctj = 0; 
							pvy = -PLAYER_VY_JUMP_INITIAL;
							sfx_play (SFX_JUMP, SC_PLAYER);
						}
					} 
				}
				if (pj) {
					rda = PLAYER_AY_JUMP - (pctj >> 2) - (pctj >> 3);
					pvy -= (rda > 1 ? rda : 1);
					if (pvy < -PLAYER_VY_JUMP_MAX) pvy = -PLAYER_VY_JUMP_MAX;
					pctj ++; if (pctj == PLAYER_VY_JUMP_A_STEPS) pj = 0;
				}
			} else {
				pjb = 0;
				pj = 0;
			}

			if (ppossee || phit) pbutt = 0; else {
				if (pad & PAD_B) {
					if (pbutt == 0) {
						pbutt = 1; pj = 0;
						sfx_play (SFX_BUTT_FALL, SC_PLAYER);
					}
				}
			}

			// ==========
			// Horizontal
			// ==========

			if (pad & PAD_LEFT) {
				pfacing = PFACING_LEFT;
				ppressingh = 1;
				if (pvx > -PLAYER_VX_MAX) pvx -= (pslip ? PLAYER_AX_SLIP : PLAYER_AX);
			} else if (pad & PAD_RIGHT) {
				pfacing = PFACING_RIGHT;
				ppressingh = 1;
				if (pvx < PLAYER_VX_MAX) pvx += (pslip ? PLAYER_AX_SLIP : PLAYER_AX);
			} else {
				ppressingh = 0;
				if (pvx > 0) {
					pvx -= (pslip ? PLAYER_RX_SLIP : PLAYER_RX); if (pvx < 0) pvx = 0;
				} else if (pvx < 0) {
					pvx += (pslip ? PLAYER_RX_SLIP : PLAYER_RX); if (pvx > 0) pvx = 0;
				}
			}
		}

		// Move
		px += pvx;
		if (px > 0xff80) px = 0;				// Negative values. Cheesy but seems to work.
		if (px > 0xff00) px = 0xff00;

		prx = px >> FIX_BITS;

		if (!pkilled) {
			// Collide
			cy1 = pry >> 4;
			cy2 = (pry + 15) >> 4;
			if (pvx < 0) {
				cx1 = cx2 = prx >> 4;
				cm_two_points ();
				if ((at1 & 8) || (at2 & 8)) {
					pvx = 0;
					prx = (cx1 + 1) << 4;
					px = prx << FIX_BITS;
				}
			} else if (pvx > 0) {
				cx1 = cx2 = (prx + 7) >> 4;
				cm_two_points ();
				if ((at1 & 8) || (at2 & 8)) {
					pvx = 0;
					prx = ((cx1 - 1) << 4) + 8;
					px = prx << FIX_BITS;
				}
			}
		}

		// More so
		// ...
		if (penhit) {
			penhit --; 
			if (penhit) psoff = 22 - psoff; else psoff = pen ? 0 : 22;
		}

		if (pvx) {
			pidlt = 0;
		} else {
			if (pidlt < ticks) pidlt ++;
		}
	}

	// Calc cell
	if (game_res) {
		pfr = PCELL_NIAO_NIAO; pfacing = 0;
	} else if (pkilled || (!pen && penhit > halfticks)) {
		pfr = PCELL_KILLED;
	} else if (ppossee || pgotten) {
		if (ABS (pvx) > PLAYER_VX_MIN && (!pslip || ppressingh)) {
			pfr = PCELL_WALK_BASE + ((prx >> 4) & 3);
		} else pfr = PCELL_STANDING;
	} else if (pbutt) {
		pfr = (pvy > 0) ? PCELL_BUTT : PCELL_BUTT_UP;
	} else if (pvy < 0) {
		pfr = PCELL_ASCENDING;
	} else if (pvy > 0) {
		pfr = PCELL_DESCENDING;
	}

	// Move sprite
	rdxi = prx - cam_pos;
	rdy = pry + SPRITE_ADJUST;

	if (rdxi < 4 || rdxi > 244) rdy = 240;

	oam_meta_spr (
		rdxi, rdy,
		4,										// Right after sprite #0
		spr_player [psoff + pfacing + pfr]
	);
}
