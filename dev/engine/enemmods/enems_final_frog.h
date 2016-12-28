			// Not much to do uh?

			en_cell = ens + (pobjs >= PLAYER_MAX_ITEMS);

			// But some animation is due
			if (ens == 56) {
				if (pobjs < PLAYER_MAX_ITEMS) {
					en_y [rdt] = en_y1 [rdt] + half_life;
				} else {
					en_y [rdt] = en_y1 [rdt] + ((frame_counter >> 3) & 1);
				}
			}
