// Config.h

#define PLAYER_MAX_VY_CAYENDO	112	
#define PLAYER_G				7	

#define PLAYER_VY_INICIAL_SALTO	24	
#define PLAYER_MAX_VY_SALTANDO	80	
#define PLAYER_INCR_SALTO 		16	

#define PLAYER_MAX_VX			48		// Velocidad m�xima horizontal (192/64 = 3 p�xels/frame)
#define PLAYER_AX				4		// Aceleraci�n horizontal (24/64 = 0,375 p�xels/frame^2)
#define PLAYER_RX				8		// Fricci�n horizontal (32/64 = 0,5 p�xels/frame^2)

#define PLAYER_LIFE				9		// Vida m�xima (con la que empieza, adem�s)
#define PLAYER_REFILL			1		// Recarga de vida.

#define PLAYER_INI_X			1		// NO TOCAR ESTO, que el motor s�lo puede empezar desde
#define PLAYER_INI_Y			1		// Arriba del todo a la izquierda, para ahorrar c�digo.									

#define PLAYER_NUM_OBJETOS		24		// N�mero de objetos para terminar el juego
