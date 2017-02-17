	// Iterator is on rdt
	
	//if (cl (prx, pry, en_x [rdt], en_y [rdt]) && !pkilled) {
	// Inline for speed	
	if (prx + 4 >= en_x [rdt] && prx <= en_x [rdt] + 12 && pry + (ens >= 16 ? 12 : 20) >= en_y [rdt] && pry <= en_y [rdt] + 12) {
		switch (ent) {
			case 3:
				// buzzer ?
				if (!en_r [rdt]) {
					en_r [rdt] = 1;
					
					// Grab object or regain clothes or win level
					switch (ens) {
						case 0:
							game_res = 1; do_game_loop = 0;
							prx = en_x [rdt] + 4; pry = en_y [rdt];
							break;
						case 4:
							// Claro, tontopolla, pones 1, pero lo multiplica por 4!
							// Set hotspot
							pcheckpoint = en_x [rdt] + 4;
							break;
						case 48:
							pobjs ++;
							break;
						case 52:
							pen = 1; penhit = ticks;
							break;
					}
					
					opscore = 1;
					bcd_score_add_5_2 (2, 5);
					sfx_play (SFX_GET_ITEM, SC_LEVEL);
					DISABLE_SFX_NEXT_FRAME;
				}
				break;
			case 6:
				// Bloco ?
				break;
			case 7: 	
				// Frogo is different, but most code is the same
				// He won't collide if player has gotten all the objects
				if (pobjs >= PLAYER_MAX_ITEMS) break;
			case 1:
			case 2:
			case 4:
			case 5:
				// Collide from top w/ pbutt on?
				if (pbutt && pry < en_y [rdt] && ent != 2 && (ent != 4 || ens != (FIREBALL << 2))) {
					pvy = -PLAYER_VY_JUMP_BUTT;
					phasbounced = 1;
					// en_jc == 1 when just changed direction.
					// This prevents the player throwing enemies out of their trajectories.
					if (!en_jc) en_my [rdt] = ABS (en_my [rdt]); // DOWN!
					opscore = 1;
					bcd_score_add_5_2 (0, 5);
					sfx_play (SFX_JUMP, SC_PLAYER);
					sfx_play (SFX_BUTT_HIT, SC_LEVEL);
					DISABLE_SFX_NEXT_FRAME;
				} else {
					player_kill ((signed char) (prx - en_x [rdt]));
					sfx_play (SFX_ENEMY_HIT, SC_PLAYER);
					DISABLE_SFX_NEXT_FRAME;
				}
				break;
		}
	} 
