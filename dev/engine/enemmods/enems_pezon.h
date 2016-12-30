            switch (en_r [rdt]) {
                case 0:
                    // Idling
                    if (en_mx [rdt]) {
                        en_mx [rdt] --; 
                    } else {
                        en_r [rdt] = 1;
                        en_y [rdt] = en_y1 [rdt];
                        enf_y [slot] = en_y [rdt] << FIX_BITS;
                        enf_vy [slot] = (ens == (FIREBALL << 2) ? -PEZON_THRUST_ALT : -PEZON_THRUST);
                    }
                    en_cell = ens;
                    break;
                case 1:
                    // Jumping
                    enf_vy [slot] += PEZON_G;
                    if (enf_vy [slot] > PEZON_VY_FALLING_MAX) enf_vy [slot] = PEZON_VY_FALLING_MAX;
                    enf_y [slot] += enf_vy [slot];
                    
                    en_y [rdt] = enf_y [slot] >> FIX_BITS;

                    
                    if (en_y [rdt] >= en_y1 [rdt]) {
                        en_r [rdt] = 0;
                        enf_y [slot] = 242 << FIX_BITS;
                        en_y [rdt] = 242;
                        en_mx [rdt] = en_my [rdt];
                        if (ens == (FIREBALL << 2)) en_mx [rdt] -= (rand8 () & 15);
                    }

                    en_cell = ens + (enf_vy [slot] >= -16);

                    break;
            }
