    // Iterator is on rdt

    en_rx = LSB (en_x [rdt]);
    switch (ent) {
        case 1:
            #include "enems_linear.h"
            break;
        case 2:
            #include "enems_gyrosaw.h"
            break;
        case 3:
            #include "enems_buzzer.h"
            break;
        case 4:
            #include "enems_pezon.h"
            break;
        /*
        case 5:
            #include "enems_fanty.h"
            break;
        */
        case 6: 
            #include "enems_bloco.h"
            break;
        case 7:
            #include "enems_final_frog.h"
            break;
    }

    //*((unsigned char *)(en_x + rdt + rdt + 1)) = en_rx;        // I've never been this dirty before! Update LSB.
    if (ent < 3) en_x [rdt] = en_x [rdt] & 0xff00 | en_rx;
