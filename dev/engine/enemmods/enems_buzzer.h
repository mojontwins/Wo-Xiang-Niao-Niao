        if (ens == 0) {
            en_cell = 64;
        } else {
            if (en_r [rdt]) {
                if (en_y [rdt]) en_y [rdt] --; else en_x [rdt] = 4096;
            } else {
                en_rx = en_x1 [rdt] + jitter [frame_counter & 0x0f];
                en_y [rdt] = en_y1 [rdt] + jitter [0x0f - (frame_counter & 0x0f)];
            }

            en_cell = (ens == 4) ? 65 : (ens + ((ens == 48) & half_life));
        }
