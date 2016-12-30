// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

const unsigned char bitmasks [] = { 0xfc, 0xf3, 0xcf, 0x3f };

const char jitter [] = {
    0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1
};

// Pattern offset of first pattern in each metatile for each tileset

const unsigned char mtile_pattrn_offsets_0 [] = {
    0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0x58, 0x5c, 0x60, 0x70, 0x68, 0x6c, 0x7c, 0x74, 0x78, 0xbc
};

const unsigned char mtile_pattrn_offsets_1 [] = {
    0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0x58, 0x5c, 0x60, 0xbc, 0x68, 0x6c, 0x7c, 0x74, 0x78, 0x70 
};

const unsigned char mtile_pattrn_offsets_2 [] = {
    0x40, 0x84, 0x88, 0x8c, 0x90, 0x54, 0x98, 0x9c, 0xa0, 0xa4, 0x68, 0x6c, 0xb0, 0x70, 0x78, 0xbc
};

const unsigned char mtile_pattrn_offsets_3 [] = {
    0x40, 0x84, 0x88, 0x8c, 0x90, 0x54, 0x98, 0x9c, 0xa0, 0xa4, 0x68, 0x6c, 0xb0, 0xbc, 0x78, 0x70
};

const unsigned char mtile_pattrn_offsets_4 [] = {
    0x40, 0xe0, 0xe4, 0xb8, 0x94, 0x54, 0x98, 0x9c, 0x60, 0x64, 0xa8, 0x70, 0xb0, 0x80, 0x78, 0xbc
};

const unsigned char mtile_pattrn_offsets_5 [] = {
    0x40, 0xe0, 0xe4, 0xb8, 0x94, 0x54, 0x98, 0x9c, 0x60, 0x64, 0xa8, 0xbc, 0xb0, 0x80, 0x78, 0x70
};

const unsigned char mtile_pattrn_offsets_6 [] = {
    0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0xe8, 0xec, 0xf0, 0xf4, 0x68, 0x70, 0x7c, 0x74, 0x78, 0xbc
};

const unsigned char mtile_pattrn_offsets_7 [] = {
    0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0xe8, 0xec, 0xf0, 0xf4, 0x68, 0xbc, 0x7c, 0x74, 0x78, 0x70
};

// Bonus stage
const unsigned char mtile_pattrn_offsets_8 [] = {
    0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0xec, 0x9c, 0x60, 0x64, 0x68, 0x6c, 0xb4, 0x7c, 0x78, 0xbc
};

// Tile behaviours. Add these numbers to combine:
// 2 sinks
// 4 platform
// 8 obstacle
// 16 slippery.

const unsigned char behs_0 [] = {
    0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 4, 4, 8, 8, 0, 8
};

const unsigned char behs_1 [] = {
    0, 0, 0, 0, 0, 0, 8, 8, 0, 8, 4, 4, 8, 8, 0, 0
};

const unsigned char behs_2 [] = {
    0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 4, 4, 8, 0, 0, 8
};

const unsigned char behs_3 [] = {
    0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 4, 4, 8, 8, 0, 0
};

const unsigned char behs_4 [] = {
    0, 0, 0, 0, 8, 0, 8, 8, 0, 0,20, 0, 8,24, 0, 8
};

const unsigned char behs_5 [] = {
    0, 0, 0, 0, 8, 0, 8, 8, 0, 0,20, 8, 8,24, 0, 0
};

const unsigned char behs_6 [] = {
    0, 0, 0, 0, 0, 0, 8, 8, 2, 2, 4, 0, 8, 8, 0, 8
};

const unsigned char behs_7 [] = {
    0, 0, 0, 0, 0, 0, 8, 8, 2, 2, 4, 8, 8, 8, 0, 0
};

const unsigned char behs_8 [] = {
    0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 4, 4, 0, 8, 0, 8
};

// World arrays

const unsigned char * const world_mpos [] = {
    mtile_pattrn_offsets_0, mtile_pattrn_offsets_1, mtile_pattrn_offsets_2, mtile_pattrn_offsets_3,
    mtile_pattrn_offsets_4, mtile_pattrn_offsets_5, mtile_pattrn_offsets_6, mtile_pattrn_offsets_7,
    mtile_pattrn_offsets_8
};

const unsigned char * const world_behs [] = {
    behs_0, behs_1, behs_2, behs_3, behs_4, behs_5, behs_6, behs_7, 
    behs_8
};

const unsigned char * const world_pals [] = {
    pal_bg_0, pal_bg_4, pal_bg_1, pal_bg_5, pal_bg_2, pal_bg_6, pal_bg_3, pal_bg_7,
    pal_bg_8
};

const unsigned char titlechars [] = {
    0xa0, 0xa0, 0xa0, 0x00, 0x00, 0xa0, 0xa0, 0xa0
};

// Load dynamic enems. Screen arrays, 16 screens:

const unsigned char enems_half [] = {
    0, 3, 0, 3, 0, 3, 0, 3, 
    0, 3, 0, 3, 0, 3, 0, 3
};

const unsigned char enems_offs [] = {
    0, 3, 6, 9, 12, 15, 18, 21, 
    24, 27, 30, 33, 36, 39, 42, 45
};
