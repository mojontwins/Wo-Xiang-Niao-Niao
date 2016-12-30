void screen_game_over (void) {
    p_s (10, 14, " GAME OVER!%%SCORE\\");
    rdx = 17; rdy = 16; p_score_d ();
}

void screen_win (void) {
    vram_unrle (ending);
}

void screen_title (void) {
    vram_adr (NAMETABLE_A);
    vram_unrle (title);
    
    if (last_level) {
        p_s (8, 16, "START  TO BEGIN%%SELECT TO CONTINUE");
    } else {
        p_s (10, 17, "PRESS START!");
    }     
    p_s (9, 25, "@ 2016 XIN XIN");
}

void screen_level (void) {
    if (level < 8) {
        p_s (11, 14, "LEVEL: "); /*p_t2d (18, 14, level + 1);*/
        vram_put (DIGIT (1 + (level >> 1)));
        vram_put (13);
        vram_put (DIGIT (1 + (level & 1)));
        p_s (12, 16, "LIVES"); p_t2d (18, 16, plives);
    } else {
        p_s (10, 15, "BONUS STAGE!");
    }
}

void screen_bonus (void) {
    if (pobjs == 8) {
        rdb = 14; p_s (12, 16, "PERFECT!");
    } else rdb = 15;

    p_s (10, rdb, "GOT    BEES!"); 
    p_t2d (14, rdb, pobjs_starter);

}
