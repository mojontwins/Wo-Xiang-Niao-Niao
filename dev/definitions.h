// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

#define COMM_POOL                ((unsigned char*)0x0300)    // Mapper 113 stuff.

#define UPDATE_LIST_SIZE        32
#define MSB(x)                    ((x)>>8)
#define LSB(x)                    ((x)&0xff)
#define SPRITE_ADJUST            -1
#define TOP_ADJUST                4
#define FIX_BITS                4
#define FADE_DELAY                 1

#define SGNI(n)                    ((n)<0?-1:1)
#define SGNC(a,b,c)                ((a)<(b)?-(c):(c))
#define SATURATE_Z(n)            ((n)<0?0:(n))
#define SATURATE(v,max)            ((v)>=0?((v)>(max)?(max):(v)):((v)<-(max)?-(max):(v)))
#define ABS(n)                    ((n)<0?-(n):(n))
#define DELTA(a,b)                ((a)<(b)?(b)-(a):(a)-(b))
#define CL(x1,y1,x2,y2)            ((x1)+4>=(x2)&&(x1)<=(x2)+12&&(y1)+12>=(y2)&&(y1)<=(y2)+12)
#define SUBSTR_SAT(a,b)            ((a)>(b)?(a)-(b):0)
#define DISABLE_SFX_NEXT_FRAME    *((unsigned char*)0x01bf)=1;

#define DIGIT(n)                ((n)+16)
#define NAMETABLE_A_X_Y(x,y)    (NAMETABLE_A+(x)+((y)<<5))

// Map

#define COLUMN_SIZE                10
#define MAP_W                    128

// Enemies

#define MAX_ENEMS                48
#define ENEM_SPRITE_SLOTS        6
#define ENEM_PROCESS_MAX        6        // 3 enemies per virtual "screen"
#define ENEMS_PER_SCREEN        3         // I know it's not needed, but I like to read.
#define SLOT_EMPTY                0xff
#define NO_SLOT                    0xff

// Animation cells

#define PCELL_STANDING            0
#define PCELL_WALK_BASE            1
#define PCELL_ASCENDING            5
#define PCELL_DESCENDING        6
#define PCELL_BUTT                7
#define PCELL_BUTT_UP             9
#define PCELL_KILLED            10
#define PCELL_NIAO_NIAO            8

// Player movement values

#define PLAYER_VY_FALLING_MAX    64
#define PLAYER_G                4
#define PLAYER_VY_JUMP_INITIAL    16
#define PLAYER_VY_JUMP_MAX        64    
#define PLAYER_VY_JUMP_BUTT        96
#define PLAYER_VY_JUMP_A_STEPS  16
#define PLAYER_VY_SINK            2
#define PLAYER_AY_JUMP             8    
#define PLAYER_VX_MAX            32    
#define PLAYER_AX                4    
#define PLAYER_RX                4
#define PLAYER_AX_SLIP            1
#define PLAYER_RX_SLIP            0
#define PLAYER_VX_MIN (PLAYER_AX << 2)
#define PLAYER_V_REBOUND        56
#define PLAYER_MAX_ITEMS        8        // Might be more. But you need 8.

// Some defines for enemies

#define FANTY_A                 1
#define FANTY_MAXV                 12

#define PEZON_WAIT                50
#define PEZON_THRUST            96
#define PEZON_THRUST_ALT        120
#define FIREBALL                10         // Pezons with this tile are fireballs and use PEZON_THRUST_ALT
#define PEZON_VY_FALLING_MAX    64
#define PEZON_G                    4

#define GYROSAW_V                2

#define BLOCO_VY_IDLE            1
#define BLOCO_VY_FALL            4

// Facing

#define PFACING_LEFT             11
#define PFACING_RIGHT            0

// Camera

#define CAMERA_MIN                 96
#define CAMERA_MAX                160

// Screen times in seconds

#define ENDING_SCREEN_TIME        60
#define GAME_OVER_SCREEN_TIME    10
#define LEVEL_SCREEN_TIME        10

// Sound channels

#define SC_PLAYER                0
#define SC_ENEMS                1
#define SC_LEVEL                1

// SFX

#define SFX_JUMP                1            
#define SFX_ENEMY_HIT            3
#define SFX_CHOF                7
#define SFX_GET_ITEM            2
#define SFX_BUTT_FALL            8
#define SFX_BUTT_HIT            9
#define SFX_SHOOT                5
#define SFX_FART                6
#define SFX_START                0
#define SFX_EXTRA_1                4
#define SFX_BLOCO                10

// OGT

#define MUSIC_FANFARE_START        0
#define MUSIC_INGAME            1
#define MUSIC_BONUS                3
#define MUSIC_CLEAR                4
#define MUSIC_NIAONIAO            5
