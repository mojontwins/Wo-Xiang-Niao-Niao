            // Blocos
    
            // en_r is state.
            // en_y1 is original position.

            // New approach

            if (!en_r [rdt]) {
                // Still not up?
                if (en_y [rdt] > en_y1 [rdt]) en_y [rdt] -= BLOCO_VY_IDLE;

                // Collision?
                if (prx + 6 >= en_x [rdt] && prx <= en_x [rdt] + 14) {
                    if (pry + 15 >= en_y [rdt] && pry + 12 <= en_y [rdt]) {
                        en_r [rdt] = 1;
                    }
                }
            }

            if (en_r [rdt]) {
                // Falling. Is player still on and not jumping?
                if (
                    !(prx + 6 >= en_x [rdt] && prx <= en_x [rdt] + 14) ||
                    !(pry + 16 >= en_y [rdt] && pry + 12 <= en_y [rdt]) ||
                    pj
                ) {
                    en_r [rdt] = 0;
                } else {
                    // move both player and bloco
                    en_y [rdt] += BLOCO_VY_FALL;
                    pry = en_y [rdt] - 16;
                    py = pry << FIX_BITS;
                    pvy = 0;
                    pgotten = 1; pgtmy = BLOCO_VY_FALL << FIX_BITS;
                }
            }
            
            en_cell = ens + en_r [rdt];
