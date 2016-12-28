// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

#include "assets/sspl.h"
#include "assets/ssen1.h"
#include "assets/ssen2.h"
#include "assets/ssen3.h"
#include "assets/ssplend1.h"
#include "assets/ssplend2.h"

// Enemies

// Each enemy is R2 R2 L1 L2, so actual frame is (ent << 2) + (facing [0/2]) + (frame [0/1])

const unsigned char * const spr_enems [] = {
	// 16x24
	spr_enems1_00_a, spr_enems1_01_a, spr_enems1_00_b, spr_enems1_01_b,
	spr_enems1_02_a, spr_enems1_03_a, spr_enems1_02_b, spr_enems1_03_b,
	spr_enems1_04_a, spr_enems1_05_a, spr_enems1_04_b, spr_enems1_05_b,
	spr_enems1_06_a, spr_enems1_07_a, spr_enems1_06_b, spr_enems1_07_b,

	// 16x16
	spr_enems2_00_a, spr_enems2_01_a, spr_enems2_00_b, spr_enems2_01_b,
	spr_enems2_02_a, spr_enems2_03_a, spr_enems2_02_b, spr_enems2_03_b,
	spr_enems2_04_a, spr_enems2_05_a, spr_enems2_04_b, spr_enems2_05_b,
	spr_enems2_06_a, spr_enems2_07_a, spr_enems2_06_b, spr_enems2_07_b,
	spr_enems2_08_a, spr_enems2_09_a, spr_enems2_08_b, spr_enems2_09_b,
	spr_enems2_0A_a, spr_enems2_0B_a, spr_enems2_0A_b, spr_enems2_0B_b,
	spr_enems2_0C_a, spr_enems2_0D_a, spr_enems2_0C_b, spr_enems2_0D_b,
	spr_enems2_0E_a, spr_enems2_0F_a, spr_enems2_0E_b, spr_enems2_0F_b,

	// 16x16, but special
	spr_enems3_00, spr_enems3_01, 0, 0, // # 12 C
	spr_enems3_02, spr_enems3_03, 0, 0, // # 13 D
	spr_enems3_04, spr_enems3_05, 0, 0, // # 14 E
	spr_enems3_06, spr_enems3_07, 0, 0, // # 15 F

	// And the WC (index = 64)
	spr_enems3_08,

	// And the almighty Zurully (index = 65) 
	spr_enems3_09 
};

// Player is: (right, then the same thing for left)
// Standing, Run1, Run2, Run3, Run4, Jump, Fall, Butt1,
// Niao, Butt2, Hit
// + 11 for left, + 22 for nude.

const unsigned char * const spr_player [] = {
	spr_player_00_a, spr_player_01_a, spr_player_02_a, spr_player_03_a, 
	spr_player_04_a, spr_player_05_a, spr_player_06_a, spr_player_07_a, 
	spr_player_08_a, spr_player_09_a, spr_player_0A_a, 

	spr_player_00_b, spr_player_01_b, spr_player_02_b, spr_player_03_b, 
	spr_player_04_b, spr_player_05_b, spr_player_06_b, spr_player_07_b, 
	spr_player_08_b, spr_player_09_b, spr_player_0A_b, 

	spr_player_0B_a, spr_player_0C_a, spr_player_0D_a, spr_player_0E_a, 
	spr_player_0F_a, spr_player_10_a, spr_player_11_a, spr_player_12_a, 
	spr_player_13_a, spr_player_14_a, spr_player_15_a, 

	spr_player_0B_b, spr_player_0C_b, spr_player_0D_b, spr_player_0E_b, 
	spr_player_0F_b, spr_player_10_b, spr_player_11_b, spr_player_12_b, 
	spr_player_13_b, spr_player_14_b, spr_player_15_b
};

// Ending routines.
// 0 1 2 3 -> dance
// 4 5 6 7 -> turn
const unsigned char * const spr_player_ending [] = {
	spr_player_ending1_00, spr_player_ending1_01, spr_player_ending1_00, spr_player_ending1_02,
	spr_player_ending1_00, spr_player_ending2_00_a, spr_player_ending1_03, spr_player_ending2_00_b
};
