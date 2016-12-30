			if ((rdt & 1) == half_life) {
				if (prx < en_x [rdt]) { enf_vx [slot] -= FANTY_A; if (enf_vx [slot] < -FANTY_MAXV) enf_vx [slot] = -FANTY_MAXV; }
				else if (prx > en_x [rdt]) { enf_vx [slot] += FANTY_A; if (enf_vx [slot] > FANTY_MAXV) enf_vx [slot] = FANTY_MAXV; }
				if (pry < en_y [rdt]) { enf_vy [slot] -= FANTY_A; if (enf_vy [slot] < -FANTY_MAXV) enf_vy [slot] = -FANTY_MAXV; }
				else if (pry > en_y [rdt]) { enf_vy [slot] += FANTY_A; if (enf_vy [slot] > FANTY_MAXV) enf_vy [slot] = FANTY_MAXV; }
			}
			
			enf_x [slot] += enf_vx [slot]; 
			if (enf_x [slot] < 0) enf_x [slot] = 0;
			if (enf_x [slot] > 3840) enf_x [slot] = 3840;

			enf_y [slot] += enf_vy [slot]; 
			if (enf_y [slot] < 0) enf_y [slot] = 0;
			if (enf_y [slot] > 2816) enf_y [slot] = 2816;
		
			en_facing = (en_x [gpit] > prx) ? 0 : 2;
			en_fr = (en_x [gpit] >> 3) & 1;

			en_cell = ens + en_facing + en_fr;

			// Update pixel positions
			if (ent >= 4) {
				en_rx = enf_x [slot] >> FIX_BITS;
				en_y [rdt] = enf_y [slot] >> FIX_BITS;
			}
			