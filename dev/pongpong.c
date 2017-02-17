// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

//#define DEBUG
#define NESDEV

// Shiru's

#include "neslib.h"

// Some needed stuff...

#include "definitions.h"

// Main const includes

#include "assets/palettes.h"
#include "assets/metasprites.h"
#include "assets/map.h"
#include "assets/enems.h"
#include "assets/tspals.h"
#include "assets/precalcs.h"
#include "assets/precalc_attr_bits.h"
#include "assets/title.h"
#include "assets/ending.h"

// Some variables

#pragma bss-name (push,"ZEROPAGE")
#pragma data-name(push,"ZEROPAGE")

#include "ram/globals_zp.h"

#pragma bss-name (push,"BSS")
#pragma data-name(push,"BSS")

#include "ram/globals_bss.h"

// Engine functions

#include "engine/mybcd.h"
#include "engine/printer.h"
#include "engine/screens.h"
#include "engine/general.h"
#include "engine/scroll.h"
#include "engine/player.h"
#include "engine/enems.h"
#include "engine/camera.h"
#include "engine/game.h"

// Functions

void main (void) {
	is_ntsc = !!ppu_system ();
	ticks = is_ntsc ? 60 : 50;
	halfticks = ticks >> 1;
	last_level = 0;

	bank_bg (0);
	bank_spr (1);
	pal_bright (0);
	pal_cycle_init ();

	while (1) {
		// title screen
		game_title ();

		pcheckpoint = pobjs_starter = 0;
		plives = 3;
		gpit = 5; while (gpit --) bcd_score [gpit] = 16;

		while (1) {
			level = cur_level;
			game_cycle ();

			if (game_res == 1) {
				pcheckpoint = 0;
				pobjs_starter = 0;
				if (!(level & 1)) {
					if (pobjs > PLAYER_MAX_ITEMS) {
						level = 8; game_cycle ();
						pobjs_starter = pobjs;
						game_bonus ();
					}
				} 
				cur_level ++;
				if (cur_level == 8) {
					game_ending ();
					break; 
				}
			} else {
				if (plives) plives --; else {
					game_over ();
					break;
				}
			}
		}
		last_level = cur_level;
	}
}
