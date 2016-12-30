            // Gyrosaws
            // Clockwise is L U R D, place here:
            // ···
            // ·Xv
            // ·<o with SPEED = 1

            // Counter-clockwise is L D R U, place here:
            // ·<o
            // ·X^
            // ··· with SPEED = 0

            // en_r is state.
            // en_mx is counter.
            // en_my = 1 means "clockwise" 
            
            if (half_life) {
                delta = (en_my [rdt] ? (en_r [rdt] >> 1) : (((en_r [rdt] + 1) & 3) >> 1)) ? GYROSAW_V : -GYROSAW_V;
                if (en_r [rdt] & 1) en_y [rdt] += delta; else en_rx += delta;
                en_mx [rdt] = (en_mx [rdt] + GYROSAW_V) & 31; if (!en_mx [rdt]) en_r [rdt] = (en_r [rdt] + 1) & 3;
            }
            en_cell = ens + half_life;
