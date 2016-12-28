void bcd_score_inc (void) {
	*gp_gen -= 10; *(gp_gen + 1) = (* (gp_gen + 1)) + 1;
}

void bcd_score_add_5_2 (unsigned char d1, unsigned char d2) {
	// This adds a bcd number "d1d2" to our 5-digits stored number at bcd_score
	gp_gen = bcd_score;
	// Unrolled.
	// d0, carry over d1
	*gp_gen += d2; if (*gp_gen >= 26) bcd_score_inc ();
	// d1, carry over d2
	++gp_gen;
	*gp_gen += d1; if (*gp_gen >= 26) bcd_score_inc ();
	// d2, carry over d3
	++gp_gen;
	if (*gp_gen >= 26) bcd_score_inc ();
	// d3, carry over d4
	++gp_gen;
	if (*gp_gen >= 26) bcd_score_inc ();
}
