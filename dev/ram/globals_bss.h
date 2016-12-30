// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

// 50 or 60 depending on TV system
unsigned char ticks, halfticks;                

// Update list for VBlank updates
static unsigned char update_list [UPDATE_LIST_SIZE * 3 + 1];

// Fade in / fade out
signed char fader;

// Level
unsigned char level, last_level;
unsigned char game_res;
unsigned char safe_landing;

// Attributes table buffer
unsigned char attr_table [64];

// Enems
unsigned char en_t [MAX_ENEMS];
unsigned char en_r [MAX_ENEMS];
signed int en_x [MAX_ENEMS];
unsigned char en_y [MAX_ENEMS];
signed char en_mx [MAX_ENEMS], en_my [MAX_ENEMS];
unsigned char en_cell;
unsigned char en_slot [MAX_ENEMS];

// Player
unsigned char plives, opscore, pobjs, opobjs;

// I could calculate these from the values in ROM in runtime
// but I need to save every cycle and there's plenty of free RAM.
unsigned char en_x1 [MAX_ENEMS], en_y1 [MAX_ENEMS];
unsigned char en_x2 [MAX_ENEMS], en_y2 [MAX_ENEMS];

unsigned char en_n_pant, en_ct_aux;

// BCD score for fast whatever
unsigned char bcd_score [5];

// Palette cycle
unsigned char pal_cycle [3];

// Frame counter for frame skip
unsigned char fskip_counter;

// Current level
unsigned char cur_level;

// Start with...
unsigned char pobjs_starter;
