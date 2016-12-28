// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

// Pad control
unsigned char pad0, pad;						

// Game counters
unsigned char half_life;
unsigned char frame_counter;

// General all-purpose, all-around vars
unsigned char i, gpit, gpjt, scit;			
unsigned char *gp_gen, *gp_aux, *gp_ul;
unsigned int gp_addr;
unsigned char rda, rdb, rdc, rdd;
unsigned char rdx, rdy, rdt, rdct;
signed int rdxi;

// Counts ticks
unsigned char ticker, game_time;

// Collision
unsigned char cx1, cy1, cx2, cy2, at1, at2;
unsigned char *behs;

// Scroller
unsigned char col_idx; 		// Column to draw (0x00 - 0xff)
unsigned int col_adr;		// VRAM address to draw to (patterns)
unsigned int col_attr_adr;	// VRAM address to draw to (attributes)
unsigned char *col_ptr; 	// Points to current column
unsigned char *map_ptr;		// Contains map + (level offset)
unsigned char col_ctr;		// Column counter, counts 0 1 2 3
unsigned char col_offs;		// Offset in metatile. 0 or 2.
unsigned char *mtile_pattern_offsets;	// Precalculates starting pattern of each metatile
unsigned char *mtile_palettes;

// Camera
signed int cam_pos, cam_pos_old;

// Sprite system
unsigned char oam_index;

// Enems
signed int enf_x [ENEM_SPRITE_SLOTS];
signed int enf_y [ENEM_SPRITE_SLOTS];
signed int enf_vx [ENEM_SPRITE_SLOTS];
signed int enf_vy [ENEM_SPRITE_SLOTS];
unsigned char en_rx, en_facing, en_fr, ent, ens, slot;
unsigned char en_jc;
unsigned char orda;
signed char delta;

// Teh player
unsigned int px;
signed int prx, prx_advance;
signed int py;
unsigned char pry;
unsigned char pgtmy;
unsigned char pgotten, ppossee, phit, pslip;
unsigned char pfacing, pfr, pkilled;
unsigned char pidlt;
signed int pvx, pvy;
unsigned char pj, pctj, pjb, pbutt;
unsigned char pen, penhit;
unsigned char do_game_loop;

unsigned char psoff;

unsigned int pcheckpoint;

unsigned char is_ntsc;

unsigned char autoscroll;
