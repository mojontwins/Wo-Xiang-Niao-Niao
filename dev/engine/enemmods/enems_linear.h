            // Move?
        
            if (en_r [rdt] == 0 || (frame_counter & en_r [rdt]) == 0) {
                en_rx += en_mx [rdt];
                en_y [rdt] += en_my [rdt];
                if (en_rx == en_x1 [rdt] || en_rx == en_x2 [rdt]) en_mx [rdt] = -en_mx [rdt];
                if (en_y [rdt] == en_y1 [rdt] || en_y [rdt] == en_y2 [rdt]) {
                    en_my [rdt] = -en_my [rdt]; en_jc = 1;
                }
            }
        
            en_facing = (en_mx [rdt] ? ((en_mx [rdt] > 0) ? 0 : 2) : ((en_my [rdt] > 0) ? 0 : 2));
            en_fr = (en_mx [rdt] ? ((en_rx >> 3) & 1) : ((en_y [rdt] >> 3) & 1));

            en_cell = ens + en_facing + en_fr;
            