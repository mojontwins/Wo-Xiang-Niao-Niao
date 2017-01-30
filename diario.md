20160201
========

Soy King Disperso. 

Llevo tiempo queriendo hacer esto, y voy a ver si lo puedo hacer rápido: juego fácil, rápido y divertido construido como si fuese un hack chino de Sir Ababol para NES. Y poco más. Me inventé un título y lo traduje a chino, y ahora se me ha olvidado qué significaba, lo que hace que esto sea aún mejor.

He hecho algunos gráficos y un poco de mapa. Si consigo montar eso con el motor de SA tal cual, tendré el primer hito. Luego tendré que cambiar mucho el gameplay.

Vamos al lío.

~~

Como siempre, montar un proyecto nuevo es mucho trabajo (muchas cosas que hay que dejar listas antes de ponerse a compilar, pero que, por suerte, sólo hay que hacer una vez). Ahora mismo lo tengo todo patas arriba porque, además, he decidido hacerlo todo con las últimas versiones de cc65/neslib que tengo para así ahorrar algún que otro ciclo y algún que otro byte.

Pero creo que ya vale por hoy... Y por unos cuantos días. Este proyecto es mi on - hold - rellenador. Pero es que he hecho unos tiles y unos sprites la mar de chulos.

~~

Ideas apunten (antes de echar el cierre por hoy): Aunque el area de scroll mapeado efectiva es de 10 tiles de alto, el resto de la pantalla la rellenaré con tiles a través de las dos nametables: las primeras lineas, por encima del area de juego, serán cielo. Las lineas inferiores, por debajo del area de juego, tierra. Si pre-relleno las dos nametables con esta mierda, luego scrollearán con la parte del mapaque sí se actualiza y dará todo el pegow.

Luego haré que el ATTR por arriba siempre salga 0 para que podamos "salirnos" del mapa por arriba - O, mejor aún (aunque creo que esto era así, me acaba de venir el flash): ATTR(x, y) con y < 0 vale lo mismo que ATTR(x,0). Así, del tirón.

Intentaré hacerlo como con Super Uwol, en un #define, aunque aquí la expresión es algo más compleja.

Sea x en metatiles, hay que mirar en la columna # x / 2 del mapa. Esto tiene su orden paranoia. La función original en Sir Ababol es esta:

	unsigned char __fastcall__ attr (unsigned char x, unsigned char y) {
		// This function gets called a lot, but I can't think on a way to 
		// make this run faster :-/
		
		if (y > 10) y = 0;		// Don't ask ... :~)
		if (y > 9) return 0;
		
		// Calculate address in map data.
		precalc1 = (x >> 1);
		work_idx = (unsigned char *) (map_plus_offset + (precalc1 << 4) + (precalc1 << 3) + precalc1);
		work_idx += (x & 1) + (y << 1);
		
		// Get metatile
		t = (*work_idx);
		
		// Return metatile behaviour
		return behaviours [t];
	}

Pues sí, estaba hecho: si y > 10 -> y = 0. Al ser "y" un unsigned char, bajando de 0 se pasa a 0xff, etc. Si nos hemos salido por abajo, según los valores de las ecuaciones de movimiento, y no puede ser otro que 10, ya que justo ahí se detecta el cambio de tira (aunque en este juego NO HAY cambio de tira y eso nos lo podemos fumar).

Luego precalcula x / 2, y a partir de ahí multiplica por 25 para obtener el número de columna. A eso último suma el desplazamiento dentro de la columna.

No sé si hacer un inline con esto no será un poco overkill. La expresión podría ser bastante heavy. De hecho, no me sale.

El __fastcall__ es una cagada porque la función es en C. Si la hiciese en ensamblador, a lo mejor, pero aún no me atrevo a hacer ese tipo de kung fu. O puedo dejarlo para más adelante, por si acaso saliese. 

En el paso de parámetros se pierde bastante tiempo. Como el motor de movimiento lo voy a cambiar porque usa el modelo antiguo y lento de pasar a tiles y comprobar los tiles dependiendo si estamos alineados o no (MK1), quizá pueda fumarme el paso de parámetros. Si hago que siempre quiera comprobar los atributos sobre tx, ty (por ejemplo), precalculando tx y ty (que tengo que hacerlo), llamo a calc_attr () sin atributos y obtengo el resultado.

En todas las colisiones, que yo recuerde, se comprueban dos puntos. Puedo hacer así:

	void attr (void) {
		precalc1 = (tx1 >> 1);
		at1 = behaviours [*((unsigned char*) (map_plus_offset + (precalc1 << 4) + (precalc1 << 3) + precalc1 + (tx1 & 1) + (ty1 << 1)))];
		precalc1 = (tx2 >> 1);
		at2 = behaviours [*((unsigned char*) (map_plus_offset + (precalc1 << 4) + (precalc1 << 3) + precalc1 + (tx2 & 1) + (ty2 << 1)))];
	}

Me ahorro todo el paso de parámetros y luego sólo tengo que usar at1 y at2 en las comprobaciones. Creo que así lo aceleraré bastante.

El scroll también lo voy a acelerar. Incluso siguiendo el mismo paradigma, usando las escritras secuenciales que tiene ahora neslib seguro que ahorro un montón de ciclos. De hecho, podría plantearme dejarme de zarandajas y ordenes raros y pintar las tiras enteras de arriba a abajo, que sería más rápido. Con los atributos precalculados y almacenados en el mapa, podría ser trivial.

No, si al final me fliparé y terminaré reescribiéndolo todo XD

20160202
========

No teman, animalicos, no voy a terminar reescribiéndolo todo. La gestión de los enemigos, el cálculo del bloque del mapa y demás zarandajas las reaprovecharé. Pero como uno es como es, pasa de hacer los metatiles y el charset a mano, así que por usar mi amado mkts.exe voy a tener que cambiar cosas sí o sí.

Además, por querer usar los últimos cc65 y neslib, tardo menos empezando el proyecto de 0 y cortando/pegando lo que necesite.

Por lo pronto muevo el código original a /dev/ref. Ref de referencia, no de refrito, desagradable.

~~

(Hoy no estoy podiendo hacer nada)

Hito #1: 1st compile: Inicialización, paletas, assets.

Lo primero que se suele hacer y estilar en estos casos: generar una ROM que básicamente no haga nada, pero que tenga todas las cosas cargadas y un bucle tonto.

~~

Hito #2: Scroller.

Bueno, este hito tiene más tomate. Por lo pronto voy a hacer la función que pinta una columna. Luego más shyte. Apunto por aquí toda la mierda que me salga, que me saldrá un montón de ella. Toda ella. Estos son los subhitos:

- Pintar una columna, pero de forma menos atravesada (*). Para esto tengo que cambiar el conversor de mapas para que guarde las columnas en un formato más fácil, por columnas, por filas. Es un momento...
- Pintar toda la pantalla actual (trivial, copypaste).
- Scroll left/right (supuestamente trivial y copypaste).

(*) El atravesamiento tenía bastante que ver con varias cosas, entre ellas mi atravesamiento propio, y además el que la estructura para actualizar la nametable durante VBlank sólo permitía accesos "aleatorios" escribiendo tres bytes (2 addres, 1 pattern #). Ahora neslib permite hacer tiras horizontales o verticales, así que...

Para mayor velocidad y simplicidad de código, voy a meter en mkts un modo de metatiles 2x2 ordenados por columna, en vez de por filas.

Me apunto esto que lo necesitaré pronto:

	rdb = (col_idx << 2) & 63;		// Column # is directly based upon col_idx!
	rdc = rdb & 31;

	// which nametable?
	if (rdb < 32) {
		col_adr = NAMETABLE_A + (TOP_ADJUST << 5) + rdc;
		col_attr_adr = NAMETABLE_A + (TOP_ADJUST >> 2) << 3 + 0x03c0 + (rdc >> 2);
	} else {
		col_adr = NAMETABLE_B + (TOP_ADJUST << 5) + rdc;
		col_attr_adr = NAMETABLE_B + (TOP_ADJUST >> 2) << 3 + 0x03c0 + (rdc >> 2);
	}

~~

¡Scroll funcionando como un puto tiro!

20160203
========

He perdido algo de tiempo (más del que pensaba, la verdad) en hacer un split del scroll. También he medido cuánta frame me queda y me queda un pasote, así que por ahora va guay todo.

Tengo que pensar en los enemigos. Varias cosas así, al batiburral:

- Of course que los lineales van dentro.
- Dejamos espacio para las plataformas móviles pero por ahora no.
- Sea lo que sea, no deben poder salir de la "pantalla" en la que están creados, o me jode el invento. Limitar por LSB a 0..240
- Implementar motor de disparos sencillo.
- Punto fijo para las cosas que quiera hacer, supongo.
- El enemigo de trayectorias random durante X frames es una mierda pero puede funcionar. 
- Por ahora mejor paso de programar cosas que precisen colisión con el escenario.
- Sigue buscando tu regalo.
- Tortilla.

- Mierda, los necesito con colisión. Quiero hacer que la tía del culo pegue saltos.

Bueno, antes de seguir voy a ver cómo se manejaba Sir Ababol con los enemigos y a escribir aquí todos los datos que encuentre, porque seguro que encuentro una forma mejor de almacenar los enemigos en ROM y copiarlos a RAM para las pantallas actuales. 

El juego original copia todos los enemigos de la tira actual. Estamos hablando de 48 enemigos, que con nada que necesiten ya hacen que la memoria necesaria escale. Por suerte no tengo más buffers.

Imaginando que necesito, así, a voleo, x, y, mx, my, x1, y1, x2, y2 - esto ya son 8 bytes, o 384 para toda la tira (nivel). Lo bueno es que con esos 8 bytes ya tengo para todo.

Creo que el juego original usaba valores de 16 bits para las X de los enenmigos, pero teniendo en cuenta que los enemigos no pueden cambiar de pantalla lo veo un gasto inútil. Por supuesto, era más fácil comparar X con CamX para saber si el enemigo estaba en la pantalla, pero no pasa nada por complicar esto un poco más. Veamos:

Tenía que ser CamX <= X < CamX + 256

Teniendo en cuenta que "X" era en realidad (n_pant << 8) + x ... tengo que coger papel y lápiz, porque la solución trivial (enX = (n_pant << 8) + x) no me gusta mucho. Pero antes voy a ver cómo se hacía todo antes y lo voy documentando aquí.

- Tengo una array sprite_assign de 8 espacios que inicializo a 0xff
- La función activate_enemy activa el enemigo número t. Lo que hace es buscar un espacio libre (0xff) en sprite_assign y asigna t a ese espacio. Luego asigna el índice de ese espacio al array enem_spr, sólo si el sprite no estaba ya activo (enem_spr [t] != 0xff). La búsqueda de huecos libres en sprite_assign se hace sólo sobre los seis primeros espacios.
- La función deactivate_enemy hace exactamente lo contrario: pone un 0xff en enem_spr [t] y un 0xff en el hueco que ocupaba el sprite en sprite_assign (el valor original en denem_spr [t]).
- La función assign_enemies es la que maneja todo el cotarro. Se encarga de definir qué enemigos deberían verse en la pantalla y cuáles no. Para ello crea o elimina enemigos al vuelo.

La función assign_enemies
=========================

Tiene varias partes:

- La primera parte recorre los 6 enemigos referenciados en las primeras seis posiciones de sprite_assign y comprueba que no se hayan salido de la pantalla mirando cam_pos y su coordenada X. En efecto, las coordenadas X son enteros absolutos. En el caso de salirse de la pantalla se los carga con deactivate_enemy.
- La segunda parte es la que crea sprites nuevos, de ser necesario. Para ello primero hace una primera criba muy inteligente de los 48 posibles candidatos: sólo podrá haber seis visibles a lo más: los que estén en las "pantallas" MSB (cam_pos) y siguiente. Como los enemigos están ordenados por pantallas, sólo hay que multiplicar cam_pos * 3 y procesar los seis enemigos a partir de ahí en la tabla de enemigos. Para cada uno de ellos, se compara X con cam_pos y se llama a activate_enemy si quedan dentro del área visible.
- La tercera parte crea los sprites en la OAM para los seis enemigos potencialmente visibles. Como ahora mis metasprites tienen tamaños variables, tendré que modificar levemente esta parte.

Me gustaría ahorrarme todas las matemáticas de 16 bits implicando la posición X de los enemigos en el motor para ganar ciclos. Lo que pasa es que esto complica la comparación tan sencilla que se hacía originalmente con cam_pos.

Estoy seguro de que el cansancio me está impidiendo ver la solución probablemente trivial al problema. La requete-lame es coger y precalcular el valor de 16 bits o coordenada X absoluta a partir de la relativa...

Si "t" es el índice del enemigo, t / 3 es el número de pantalla que ocupa. Por tanto, su coordenada X absoluta es ((t / 3) << 8) + Xr, siendo Xr la coordenada X realtiva dentro de la pantalla.

De ahí arriba lo que no mola es dividir entre tres. Cosas de tener 3 enemigos por pantalla.  Dejar espacio para 4 puede ser overkill con tan poca RAM aunque simplicaría los calculos.

No sé qué hacer. Voy a desconectar un rato, que siempre vienen las soluciones del tirona (¿un lookup table de 48 posiciones? 0, 0, 0, 1, 1, 1, 2, 2, 2 ...) 

Escribo unas cosas antes de parar: "teniendo resuelto el cálculo de n_pant para un enemigo t", la posición donde habría que colocar el sprite sería:

	X - cam_pos
	((n_pant << 8) + Xr) - ((MSB (cam_pos) << 8) + LSB (cam_pos)).

Aquí sabemos algunas cosas, como que si un enemigo está activo es que su n_pant es MSB(cam_pos) o MSB (cam_pos + 1). Esto es bastante interesante. 

Joder, no doy con la solución.
	
~~

Leyendo por ahí y pensando un poco me doy cuenta de que lo mejor es dejar la coordenada X "absoluta" de 16 bits. Lo que sí puedo hacer, en la rutina que mueve a los enemigos, es quedarme con el LSB y utilizar sólo eso para todos los cálculos, para luego volver a colocarle el MSB. Clever. Y si uso *(&(x[t]) + 1) lo puedo manipular directamente, aunque eso es ya un poco heavy peavy y no ahorraría gran cosa en ciclos y tal. Tan fácil como sacar un xr = LSB (x[t]) al principio de cada tile y luego hacer un *(x + 1 + t + t) = xr al final del bucle (actualiza el LSB directamente en la zona de RAM que ocupa el array).

Creo que esta será la dirección que tome. Ahora voy a analizar el formato de los datos en ROM a ver si puedo ahorrar algo. En MK1 NES, última versión estoy almacenando en ROM los valores T XY1 XY2 y P, con T codificando tipo/comportamiento, XY1 y XY2 coordenadas a nivel de metatile, y P las propiedades (por ejemplo, la velocidad).

Por cierto, teniendo 12 gráficos de enemigos diferentes sólo necesito hacer esto:

	T = CBBBAAAA

Donde AAAA es el # de gráfico, BBB describe el tipo de movimiento (quitando los lineares me quedan 6 más, el 0 no cuenta) y C vale 1 si el enemigo dispara proyectiles (lo dejo por ahora es estado "reservado y ya lo pondré si cabe"). De hacerlo, el sistema de proyectiles debe ser global y utilizable también por el jugador.

~~

Sigo apuntando cosas que luego me darán que pensar: como el escenario que se ve es mayor que "el que existe", voy a considerar que las pantallas son en realidad de 15 tiles de alto, solo que empiezan en el tile Y=2. Todo esto quedará reflejado en las funciones que cree para la colisión, que tendrán en cuenta el offset al leer del mapa y rellenarán con el valor de mapY=0 en las posiciones que se salgan.

Tendré que tener todo esto en cuenta para dejarlo ya pre-ajustado en el conversor de enemigos, porque cuantos más cálculos me ahorre en la ROM, mejor.

~~

Voy a colocar unos enemigos de prueba (lineales) y a escribir el conversor. Voy a hacer una pequeña modificación a col_incog.exe para que permita meter números en HEX, que vendrá bien, pero por ahora no será necesario, ya que los enemigos de prueba tienen CBBB = 1 (no disparan y llevan el tipo de movimiento 1), así que serán 16 + ID del gráfico, fácil de calcular al vuelow.

Hablando de ahorros: 3 tiras de 16 pantallas (48 en total) en el original ocupaban 1296 bytes. Ahora, si los cálculos no me fallan, ocuparán 4*16*3*4 = 768 bytes, lo que está bastante mejor - siempre que el código de "expandir" esos datos mientras se copian a RAM no ocupe demasiado, claro.

~~

Algunos enemigos añadidos y conversor modificado con offsets y para no generar hotspots. Voy a programar el siguiente hito:

Hito #3: Enemigos

- Programar al rutina de copia/expansión de ROM a RAM para el nivel actual.
- Programar la rutina de movimiento preparada para varios tipos, pero implementando solo el tipo 1 (lineal).
- Integrar con el sistema de sprites.

~~

Mientras estoy en ello, tengo que pensar algo de una vez para las velocidades de los enemigos que no sea un pifostio y me permita tener actualizaciones cada 2 o cada 4 frames y cosas así...

Veamos. Establezcamos estas velocidades:

	1/8 1/4 1/2 0 1 2 4.

Tengo que codificar las 1/X de alguna manera que me permita manejar todo esto de una forma buena. Por un lado, 1/X hace que se actualice cuando (frame_counter & (X-1)) == 0

Puedo codificarlos como 0x80 + N en el propio colocador. Voy a poner uno y así pruebo.

Las velocidades son, pues:

	8	8 pixels por frame
	4 	4 pixels por frame
	2 	2 pixels por frame
	1 	1 pixel por frame
	129 1 pixel cada 2 frames (129 - 128 = 1)
	131 1 pixel cada 4 frames (131 - 128 = 3)
	135 1 pixel cada 8 frames (135 - 128 = 7)
	...

~~

Ahí estamos - hay cosas raras, pero ahí estamos :-P. Los incrementos fraccionales funcionan, pero creo que me estoy haciendo la picha un lío con el tema de la coordenada relativa temporal del enemigo para los cálculos en el eje X y su actualización. Pero ahí estamos, casi casi. Pero tengo menos de 15 minutos para irme, así que...

--> lo tengo aislado. Esto es lo que lo está peyendo todo

	*(en_x + gpit + gpit + 1) = en_rx;		// I've never been this dirty before! Update LSB.

Me estoy cargando el array. Algo falla. Bocadillo de caballa. Pero ¿qué? No lo sé. Ya averiguaré que falla (¿Pensaba que los números en este ordenador eran MSB LSB?). Por ahora hago esto, y va:

	en_x [gpit] = en_x [gpit] & 0xff00 | en_rx;

Pasemos a otro tema. Voy a ver cómo vamos de tiempo de frame y meto la rutina básica de plataformeo para el personaje principal.

~~

Hito #4: Personaje principal

La rutina que empleaba en Sir Ababol era la de "la vieja escuela". Paso, prefiero la colision liviana por puntos, que además voy a optimizar haciendo una rutina de ATTR que pille los dos puntos indicados de forma específica y así ahorrarme todo el paso de parámetros (y muchos ciclos).

Lo haré además de forma que los distintos ejes se puedan cambiar al vuelo para poder hacer el truco y generar, con la misma ROM, varios posibles juegos diferentes.

Lo primero que tengo que hacer es sacar la fórmula para el attr, dados x e y en coordenadas de tile. Teniendo en cuenta que el mapa se divide en "chunks", tenemos que:

	01 0A
	02 0B
	03 0C
	04 0D
	05 0E
	06 0F
	07 10
	08 11
	09 12

Sería (x >> 1) * 25 + (x & 1) * 10 + y. Urm. Muchas multipicaciones feas...

	rda = (x >> 1);

	gp_gen = map_ptr + (rda << 4) + (rda << 3) + rda + ((x & 1) ? 10 : 0) + y

Yuh, overkill, pero asín es esto. Lo que gano en el scroller lo pierdo aquí. Qué se le va a hacer. Para otro juego lo hago de otra forma y no intercalo tiles y atributos, y me busco números más amigos de las potencias de dos. Por ahora, vamos a tirar con esto.

20160204
========

Hoy le voy a poder dedicar muy poco tiempo a esto, pero algo es algo. Vamos a ver si al menos puedo tener lo más mínimo para el movimiento (que caiga y pare al tocar tile, vaya, lo de siempre).

Lo dejo ya. Muy poco. Tengo lo que quería, pero hay un problema con o bien la colisión vertical o bien la detección de atributos del mapa. Con mas tiempo y tranquilidad lo mirow.

Defitivamente es la función que obtiene el comportamiento de los tiles del mapa. Seguro que me he equivocao con la fórmula, o algow. Lo pensaré más mejor.

~~

Resuelto. Era el array de behs. Como el primer tile empieza en el caracter 64, en el mapa los tengo ya precalculados. El primer metatile es el 16. Se me había olvidad colocar 16 ceros al principio de behs (es lo más rápido). Ahora sí va bien :)

20160206
========

No lo apunté, pero ayer en un ratito dejé listo el movimiento del juegador. Hoy he terminado de redondearlo y he metido colisiones contra los malos y lógica del bucle del juego. Ahora me dispongo a meter las abejitas que se supone que tenemos que coger. Estos bichos son fijos pero tendrán un "jitter" (como las camisetas de Super Uwol, vaya).

El número de sprite enemigo es el 12. El tipo de "enemigo" (para ahorrar código lo pongo todo aquí) será el 7, por lo que el valor que tendré que usar para crearlos en el colocador es

	CBBBAAAA = 01111100 = 0x7C = 124

Voy a poner uno y tal a ver.

~~

Todo perfecto, marcadores funcionando y tal, pero se me acaban los 32K y no hago más que pensar que el overhead de tener 2 tiles por byte no sería tanto. Creo que antes de seguir me voy a poner a hacer pruebas. Así el mapa se reduciría de 12800 a 7680 bytes, lo que me da 5Kb más para darle más age al juego.

Probaré.

~~

Veamos, vamos a organizarnos un poco. Necesito las siguientes tareas previas:

1.- Rediseñar el tileset, dividirlo en dos.
1.- Dibujar el nuevo mapa.
2.- Hacer el nuevo conversor (diseñar el formato, aunque es tontería... no creo que haya problemas).
3.- Modificar la rutina de scroll - ojete, poder cambiar la "tira" o el "offset" de los tiles que se pintan.
4.- Para que esto siga siendo rápido y bonito, los comportamientos de los tiles de todas las tiras de 16 tienen que ser equivalentes.

El nuevo formato, igualmente por columnas de 10 tiles de alto. Esta vez, un byte por cada dos tiles en horizontal, más 5 bytes con los atributos. Esto hacen 10 + 5 bytes en total por columna.

En cada columna, se pilla el nibble izquierdo o derecho dependiendo de qué columna estemos pintando. El resto sería igual. O sea, sólo cambia la "extracción del metatile del mapa" y, en apariencia, no es demasiado compleja.

20160207
========

Más rápido de lo que pensaba, he hecho la transición. Aunque he metido varias optimizaciones y he añadido precálculos por todos lados está claro que el proceso será bastante más lento. Aún no he medido el tiempo de frame que me queda ahora mismo porque pienso que todavía podría precalcular u optimizar alguna cosa más. Le daré más pensadas ahora que no puedo ponerme a ello, he visto que macerando las cosas offline a veces se me ocurren geniales ideas (como la de precalcular los 16 posibles inicios de metatile en # de patrón para no tener que calcular nada una vez extraído el nibble del byte correcto del tile del mapa que quiero pintar).

Si todo va bien, meteré más tipos de enemigos. Otra cosa que tengo que hacer es buscar una forma mejor de extraer los dígitos decimales de la puntuación para añadirlos al display. Estoy empeñado en ejecutar esta actualización justo antes de esperar al split, pero ahora mismo no me da tiempo. Lo intentaré un par de veces más y si veo que sigue saltando, lo muevo después del split y busco otra cosa que colocar antes.

¡ENHORABUENA! ¡¡HE TERMINADO REESCRIBIÉNDOLO TODO!!

~~

He estado leyendo y es lo que yo me temía: como el 6502 de la NES está capado y no tiene BCD, no hay otra que hacer el BCD tú mismo almacenando cada dígito en una posición de RAM e implementando tu función de suma pseudo-BCD si quieres evitar las divisiones.

Mira, hace tiempo que tenía que haber hecho esto, así que voy al lío. Tengo código en asm para hacerlo, pero voy a probar a dejarlo en C para no complicar porque creo que me dará tiempo.

~~

Sencillo, aunque tengo que optimizar un par de cosas tontas. Pero es genial: ahora me cabe en el poquísimo tiempo que hay desde que acaba la rutina del NMI y aún no ha ocurrido el "sprite 0 hit" que controla el split. 

Ahora tengo que hacer estas tareas de limpieza tonta:

- Quitar la variable "pscore" y usar una bandera normal 0/1 para indicar que ha cambiado y que hay que volver a pintarlo.
- Quitar la función p_5d que pinta un valor de 16 bits en decimal (con las consiguientes divisiones y módulos) por algo que pinte directamente el valor del buffer bcd (directo a VRAM, se llama siempre con la PPU apagada).
- Otra cosa que se me había ocurrido para ahorrar algunos ciclos pero que ahora no puedo recordar. Ya me vendrá.

Tengo que ir metiendo ya la música, aunque sea la de Chase o algo tonto que haga, para que no me de una sorpresa nada agradable en el futuro.

Voy a hacer una lista de sonidos que necesito y a rapiñarlos del pool murciano, veamos:

	- Salto 						"Jump 3" (tocado, -1o)
	- Enemy hit 					"Kill"
	- Chof (agua)					"Door"
	- Coger mosca					"Item" (tocado, -1o)
	- Caer con el culo 				"Fiuuu" (tocado, -1o)
	- Botar con el culo 			"Assplossion" (recortado) + "Jump 3"
	- Disparo (tentativo) 			"Laser 2"
	- Pedo (movimiento choco)		"Wrong"
	- Start 						"Select"
	- ???? 1 						"Invisibility"

Voy a meter los sonidos y la música de Chase y ver qué tiempo de frame queda, de media.

~~

Mierda, me da la impresión de que al sonar más de un sonido a la vez pierdo ya el frame en NTSC. Porca miseria. Tendría que haber empezado desde el principio con la música.

A ver de dónde saco castaña.

~~

He cambiado el sitio donde llamo al split. Se ve que, en NTSC, cuando hay un loop de la canción el tiempo que tarda el NMI en terminar es bastante mayor, así que se junta todo y no da tiempo.

Bueno, así se pierde más tiempo en los frames, pero bueno, a ver si así va todo guay. No debería afectarme mucho si quiero añadir complejidad al juego, porque lo que incrementa es el tiempo de NMI y no el tiempo antes de esperar a que este ocurra...

En teoría seguimos yendo bien.

~~

Chrum se está despertando, pero yo debería ir pensando en ver qué añadir:

- Más movimientos de enemigos. Sierras, podrían funcionar bien, pero tengo que trabajar en un código más sencillo. Fantys, de los más sencillos - a lo mejor no quedan bien del todo porque estarían limitados a la pantalla donde están creados -> si los pongo de los que llevan estados esto se notará menos. Si el jugador sale de la pantalla para ellos dejaría de existir y se les vería volviendo a su sitio. Saltadores: saltan al azar a izquierda o a derecha, siempre que no se vayan a salir de la pantalla. El problema de esto es que precisaría una rutina equivalente (o casi) a la que mueve al jugador. [**].
- Motor jetpac y motor choco, para ir cambiando.
- El set de sprites normal en el que no se le vea el totete a la prota.

[**] Tengo que crear un sistema de coordenadas de punto fijo y de colisiones con el escenario unificada. Vendrá bien.

Pensaré en todo, churum está despertándose.

~

Quizá pueda codificar de alguna manera qué cosas necesito (generales) en el valor de 3 bits que indica el tipo de movimiento, en plan:

	111
	|||
	||+- Alt
	|+-- Colisión
	+--- Fixed Point

Así, por ejemplo, en el bucle que controla los enemigos, si el bit 2 está a 1 haré automáticamente la conversión de fixed point -> integer al final del bucle. Si el bit 1 está a 1, habrá colisión. Pero quizá.... No sé.

Lo de las sierras, he pensado que puedo liarla parda porque las sierras originales de MK1 necesitan el truco del sprite que oculta (o sea, poner un sprite de mayor prioridad (antes en la OAM) pero con el bit de "baja prioridad" levantado, de forma que se pinte antes de los importantes, pero detrás del escenario, efectivamente ocultando parte de los sprites importantes - el truco de SMB3) y ya es mucha tela marinera. Lo que haré será esta variación muy sencilla:

	  ···
	  ·X·
	  ··o 

Donde X es el tile, o el enemigo, y · la trayectoria, en el sentido de las agujas del reloj o el contrario.

Simplificando, dos modos, cuatro estados.

	Modo clockwise: L U R D.
	- Si state & 1 = 0: Horizontal.
	- Si state & 1 = 1: Vertical.
	- Si state >> 1 = 0: Decrementando
	- Si state >> 1 = 1: Incrementando

	Modo counter-clockwise: L D R U.
	- Si state & 1 = 0: Horizontal.
	- Si state & 1 = 1: Vertical.
	- Si state == 0 || state == 3: Decrementando
	- Si state == 1 || state == 2: Incrementando;

	o lo que es lo mismo:
	- Si ((state + 1) & 3) >> 1 == 0: Decrementando
	- Si ((state + 1) & 3) >> 1 == 1: Incrementando

Todo esto se simplifica en este pseudocódigo:

	rda = cw ? (state >> 1) : (((state + 1) & 3) >> 1);
	d = rda ? V : -V;
	if (state & 1) y += d; else x += d;

A lo que habría que añadir el cambio de estados. Siempre se avanza 32 pixels desde la posición inicial, así que podríamos llevar la cuenta:

	ct = (ct + V) & 31; if (!ct) state = (state + 1) & 3;

Creo que es la forma más compacta de programar algo así, y daría de la leche de juego. Será lo próximo a lo que le de fran. Además, no necesita ni punto fijo ni colisión, lo que me lleva al problema de la falta de bits. O sea, 000 no puede ser porque eso es "vacío", 001 ya está pillado, x1x no, porque no necesita FP, y 1xx tampoco, porque no necesita colisión.

Por otro lado, no tiene sentido hacerlo con cualquier tipo de sprite, así que a lo mejor lo puedo fijar de otra manera, combinando con el número de sprite.

EN plan, si tipo = 000, y sprite != 0000, entonces -> este tipo de casos especiales. O yo qué sé.

Tengo que pensar otra cosa. O eso, o usar el bit que reservo para "dispara o no". Juer, me crecen los enanows. Otra de pensar.

PENSAWR!!!

También podría pensar qué quiero y qué es posible, y luego pensar en cómo codificarlo todo. Quizá así me fuese mejor.

Pero ahora voy a fregal.

20160208
========

Veamos, esto lo tengo que resolver ya. Parece mentira que cosas tan tontas me ocupen tanto tiempo. Cómo codificar todo lo que quiero extraer de los enemigos en un sólo byte. Hagámoslo como se hacen las cosas de verdad, con un análisis de requisitos (siempre pienso en quesitos cuando escribo esta palabra):

- Debe poder representar fácilmente el "enemigo no existe". Por ejemplo, con el valor "0".
- Debe poder indicarse qué cells de sprite usará, de 0 a 15.
- Los enemigos lineales deben poder o no disparar (tentativo).
- Quiero fantys (sin colisión, FP), saltadores (FP), cuchillas, lineales, pezones (FP).

Estoy pensando que podría gastar 48 bytes en otro array "en_attrs" y rellenar este y en_t de la siguiente forma:

	- en_t -> AFCDXTTT
	- en_attrs -> XXXXSSSS

Donde:

	A -> Activo. Siempre a 1, menos cuando el enemigo no existe (en ese caso, todo en_t == 0).
	F -> Fixed Point. Inicializar valores al crear y actualizar al finalizar.
	C -> Collision. Realizar colisión.
	D -> Dispara.
	TTT -> Tipo de rutina de movimiento
	SSSS -> # de gráfico.

Creo que si lo estructuro así el tema irá sobre ruedas. Lo que tengo que ver es si no me voy a quedar sin memoria con los nuevos arrays que necesito (enf_x, enf_y, enf_vx, enf_vy, en_attrs son 96+96+96+96+48 = ¡¡432 bytes!!). Voy a crear los arrays antes de montar más historias a ver si me queda suficiente RAM. Si no tendré que inventarme algo:

pre-idea: hacer que enf_x, enf_y, enf_vx y enf_vy sean sólo arrays de 6 elementos y crear al vuelo cuando un enemigo de este tipo empiece a ser procesado (sea de los seis que están activos) - No sé si esto será viable tal y como está montada la gaita. Lo miraré y lo pensaré.

De hecho lo voy a mirar antes que nada porque si es viable es la mejor forma. Hay que ser conservadores con la memoria: puede que tenga esos 432 bytes, pero ¿no los necesitaré para otras cosas en el futuro?

~~

No lo voy a poder enganchar directamente, pero está claro que siempre se actualizan 6 enemigos (pantalla actual de cam_pos y siguiente), y es tontería estar guardándolos todos. Aquí el problema radica, principalmente, en saber cuándo inicializar los valores de un enemigo y en saber cuándo queda este libre.

Hay que tener en cuenta que esto se va solapando. A medida que se avanza, si se pasa de n_pant a n_pant + 1, los tres primeros enemigos quedan libres y podrían ser usados por los nuevos enemigos de la pantalla que entra. La sección de enems_move que asigna sprites al vuelo (y hace que se actualicen) procesa de seis en seis, según la pantalla actual. ¿Cómo detectar un cambio? Más pensar, más pensar. Qué de pensar lleva esto, coñor.

Aunque luego está el tema de que un enemigo no se mueve SI NO SE VE. Con esto no había contado yo. Creo que tengo que modificar esto. Lo suyo es que, aunque no se vea, se mueva si está en el "radio de acción" (en la pantalla donde está la cámara o en la siguiente). Voy a darle una vuelta, porque a lo mejor ahí veo el quid. 

En Sir Ababol el bucle de crear sprites y el bucle de mover enemigos están separados, y por eso va bien. Aquí los junté, pero creo que los junté demasiado. A lo mejor puedo hacerlo de otra manera... Veamos...

~~

Espérate porque creo que la mierda esta de los slots no se usa para nada - es que si es así, soy la banana más grande de la historia de Wichita...

Joder, creo que esto era porque cuando hice Sir Ababol no sabía controlar los sprites de la OAM de forma dinámica y lo tenía todo por putos slots... Joder, por eso se llama "en_slot" el array. Esto es más grande que barcelona. Voy a cambiar algunas cosas.

~~~

Joder, lo he quitado, he salvado toneladas de memoria, me he quitado ciclos de procesador, y he arreglado lo de que a veces no se mueven cuando deberían. La leche en polvo, esto es la puta hostia. Lo flipo conmigo. Vaya cagada, primosaurio. En serio. La leche.

Ahora a ver cómo resuelvo el tema de, esta vez sí, asignar dinámicamente los arrays de punto fijo a los enemigos que lo necesiten. Seguramente de una forma parecida a la que asignaba los "slots" para sprites que no estaba usando XD

A ver, que puede ser fácil. En rda tengo el número de pantalla, o sea, MSB (cam_pos). Imaginamos que guardo un on_pant con el valor "anterior" de MSB (cam_pos). Cuando estos valores sean diferentes, es que hemos cambiado de pantalla. 

Teniendo en cuenta que al principio del juego MSB(cam_pos) es PAR, tenemos que al cambiar de pantalla MSB(cam_pos) sería IMPAR. Los tres enemigos al principio de los arrays tendrían que ser sustituidos por tres enemigos nuevos. Al siguiente cambio de pantalla, MSB(cam_pos) vuelve a ser PAR y los tres enemigos entrantes deberían escribirse en los tres slots ultimos.

Si ahora vamos a la izquierda, al cambia MSB (cam_pos) volvería a ser IMPAR ... Nah, el PAR / IMPAR no me sirve. Tengo que considerar el desplazamiento a la izquierda y a la derecha.

Si recordamos "última mitad" que se introdujo... 0 (1ª) o 1 (2ª)

Al principio del juego la última mitad es la 1 -> tocaría la 0 si nos movemos a la derecha.
Seguimos avanzando -> tocaría la 1.
Pero si retrocedemos -> ¡La 1 de nuevo!

O sea, siendo last_half la ultima mitad, rda la posición actual (pantalla) y orda la posición anterior, tenemos que:

if (rda > orda) update (1 - last_half);
if (rda < orda) update (last_half);

Es un tanto complejo de ver, menos mal que llevo diarios. Creo que así puede funcionar y ahorraré bastante mandanga. Por supuesto lo más rápido sería tenerlos todos creados y tal, pero haciendo cuentas, ahora mismo los enemigos se llevan esta RAM:

	en_t 		48 bytes
	en_attr 	48 bytes
	en_r 		48 bytes
	en_x 		96 bytes
	en_y 		48 bytes
	en_mx 		48 bytes
	en_my 		48 bytes
	en_slot 	48 bytes <- lo dejo porque lo necesitaré.

	9 x 48 = 432 bytes. Es un pepino. 

Además, así puedo crear los arrays en ZP, con lo que ahorro ciclos.

Esto va a costar. Voy a ello. Además, no podré probarlo hasta que meta un fanty o algo. Jodó, son demasiadas cosas que hacer. Vamos al lío.

~~

Creo que por ahora voy a pasar de los atributos y de las mierdas, y a hacerlo como siempre.

	1 -> lineal
	2 -> saw
	3 -> buzzer
	4 -> fanty
	5 -> pezon
	6 -> jumper

	Si >= 4 -> fp.
	Si >= 6 -> colision.

Y a tomar por culo.

~~ 

Cosas: 

- Me vuelve a renquear esto de vez en cuando, aunque no he establecido cuando. Seguramente alguno de los añadidos que he metido sea ya pasarse. Voy a mirar el tiempo de frame. 
- El fanty se para al borde de su pantalla, y esto queda muy raro. ¿Debería pasar de fantys? Es que hacen que el cambio de pantalla sea demasiado aparente.

Mirando el tiempo de frame, además de que, en general, lo veo todo más apretado, se nota como en cuanto aparece un fanty el tema cae en picado. ¿Cómo es posible que lo carguen tanto todo?

Voy a ver qué puedo modificar, aunque cada vez tengo más claro que va a tener que irse.

~~

Voy a tener que empezar a hacer cosas en frames alternos.

Cosa que podría alternar:

- Colisión con los enemigos. No hace falta comprobar siempre. 	IMPAR
- Imprimir puntuaciones.										PAR
- Comprobar si creamos enemigos nuevos.							PAR

Por ahora va mejor con esto, pero tiene que haber más. Por ejemplo, el cambio de dirección de los fantys podría hacerse alterno, o sea, si (rdt & 1) == half_life. A la buchaca.

Esto ha solucionado algunas cosas, pero no todas. Vamos a tener que seguir mirando. Hay más cosas que puedo optimizar seguro, en todas las partes del motor.

Más optimizaciones hechas, pero sigue habiendo "picos" cuando pasan muchas cosas a la vez. Esto parece que no puedo evitarlo. Lo que sí voy a hacer es medio modificar famitone2, de forma que si una posición fija de RAM libre ($01bf, en mi configuración) vale <> 0, no actualiza los streams de SFX. Esto sólo vale un frame, la propia famitone2 volverá a poner a 0 la posición $01bf en cada ejecución. Esto me sirve para que cuando haya colisión y salte sonidos poner $01bf a 1 y que no salte esa parte del código en ese frame, ganando algo de tiempo. Tampoco se nota si está un frame retrasado.

~~

Tras más mierdas de estas, he metido los pezones con éxito. Ahora voy a las sierras estas que van dándole vueltas a un tile.

~~

Increíble, han funcionado a la primera con tres jodidas lineas de código. Tres. Jodidas. Lineas. Bastante densas, eso sí:

	delta = (en_my [rdt] ? (en_r [rdt] >> 1) : (((en_r [rdt] + 1) & 3) >> 1)) ? GYROSAW_V : -GYROSAW_V;
	if (en_r [rdt] & 1) en_y [rdt] += delta; else en_rx += delta;
	en_mx [rdt] = (en_mx [rdt] + GYROSAW_V) & 31; if (!en_mx [rdt]) en_r [rdt] = (en_r [rdt] + 1) & 3;

Luego pinté otra paleta y algunas pantallas de la segunda tira para ver si lo había hecho bien y cambiar de tira de mapa (en este juego, de nivel) funcionaba bien... Y coño que si funciona. ¡Es genial!

Cosas fáciles que debería pensar en meter:

- Tiles resbalosos
- Tiles conveyor

Y ahora se acabó el día.

20160209
========

Más cosas que se me han ocurrido para añadir:

- Tiles arenas-movedizas que te hacen hundir lentamente.
- Tortilla. Todos los juegos deberían traer tortilla.

Otra cosa que me he dado cuenta: he obtenido un feature gratis: puedo hacer nuevos tilesets usando cualquiera de los 48 tiles arbitrariamente siempre que respete los behs - o bien, puedo añadir una abstracción y tener varios arrays de behs e ir cambiándolos empleando un puntero. De hecho, voy a hacer esa mini modificación para poder usarla del tirón en cuanto lo necesite.

Esto viene guay porque en la tercera tira de tiles tengo muchos vacíos que podría emplear para dar más variedad a las fases que quedan, y no repetir simplemente los tilesets 0 y 1 alternativamente cambiando paletas.

Voy al lío, son tres cambios mierder.

~~

De hecho, voy a crear de una santa vez una estructura que contenga los tiestos de cada nivel, y así cambiar de nivel es más fácil.

~~ 

Tema de los tiles que te hunden: nunca lo he hecho. Tal y como lo veo, hay que meterlo como caso especial dentro de la colisión vertical cuando vy > 0. En ese caso, detectar "& 2" (por ejemplo). En este caso, lo suyo sería establecer vy a un valor fijo, pequeño, de forma que invalide el incremento de G que se hace en cada frame. Esto hará descender al muñeco de forma efectiva poco a poco, y permitirá por ejemplo poner tiras de estos tiles que terminen en el vacío (lo que viene bien para que el muñeco se muera, vaya).

~

Hecho, pero no lo puedo probar. Los tiles conveyor son algo más complejos porque tengo que introducir un valor más en las comprobaciones de colisión, pero no es nada del otro mundo. Los tiles resbalosos implican detectar ppossee más un atributo de tile, y en ese caso utilizar unos valores alternativos PLAYER_AX_SLIP y PLAYER_RX_SLIP. Hagámoslo bien...

La detección la añado tras el ppossee:

	cy1 = cy2 = (pry + 16) >> 4;
	cm_two_points ();
	ppossee = ((at1 & 12) || (at2 & 12));
	pslip = (ppossee && ((at1 & 16) || (at2 & 16)));

Y luego modifico la ecuación del movimiento...		

	if (pad & PAD_LEFT) {
		pfacing = PFACING_LEFT;
		if (pvx > -PLAYER_VX_MAX) pvx -= (pslip ? PLAYER_AX_SLIP : PLAYER_AX);
	} else if (pad & PAD_RIGHT) {
		pfacing = PFACING_RIGHT;
		if (pvx < PLAYER_VX_MAX) pvx += (pslip ? PLAYER_AX_SLIP : PLAYER_AX);
	} else {
		if (pvx > 0) {
			pvx -= (pslip ? PLAYER_RX_SLIP : PLAYER_RX); if (pvx < 0) pvx = 0;
		} else if (pvx < 0) {
			pvx += (pslip ? PLAYER_RX_SLIP : PLAYER_RX); if (pvx > 0) pvx = 0;
		}
	}

~

Los conveyors por lo pronto los dejo para luego. Demasiadas cosas hechas y sin probar (tengo que hacer gráficos, montar algo de fase, mierdas así). Los conveyors funcionan sobre la misma base que las plataformas móviles (bueno, digamos que para meter los conveyors hay que meter cierto enganche en la rutina del player que luego aprovechan las plataformas móviles). Viendo que las plataformas móviles no son más que generalizaciones de los enemigos de trayectoria lineal, puede que sea barato. Aunque ya me estoy flipando mucho.

Llegará el punto en el que sólo pueda evitar las pérdidas de frame mediante diseño de niveles, pero eso no es algo que me pase sólo a mí ;*)

Por cierto, tengo que hacer que no se pueda saltar con el culo sobre las cuchillas.

~

Sobre lo que decía antes de que, de gratis, podía componer tilesets custom de 16 tiles, tiene su explicación: para acelerar el scroller, en lugar de calcular en qué patrón empieza el metatile que tengo que pintar según el valor de 0 a 15 que he extraído del mapa, utilizo una tabla lookup con los valores ya calculados: en un principio el valor N de esta tabla era (16+N)*4, el primer patrón del metatile N del set de 48. Pero nada me impide usar números arbitrarios, sin seguir la secuencia.  Así puedo mezclar tiles de diferentes sets y hacer uno nuevo.

En el set 1 repetía algunos tiles del set 0: el tile vacío, las plataformas, el tile de las olitas del mar... en total 5 tiles repetidos. Este tema me ha permitido reutilizar en el set 1 directamente los del set 0, con lo que tengo 5 tiles más para dar más vidilla a las fases 2 y 3.

Este motor es cada vez mejor. Las posibilidades crecen exponencialmente. Me encanta cuando me salen setas. Porque yo esto no lo había planeado. Sólo quería un lookup table para acelerar el scroll... ¡Y ahora me permite todo esto!

Ojal: A la hora de diseñar una fase con el tileset nuevo, tengo que importar en mappy el tileset nuevo y nada más. Va a ser un poco infierno (cambiar de tileset para editar cada piso del mapa) pero bueno, tampoco es la primera vez.

O NO - sólo tengo que hacerme un tileset con todas tiras, que me acabo de acordar que el conversor de mapa graba el valor del "tile & 15", o sea, que da igual de la tira que sea generará el valor correcto 0..15. Bien.

~~ 

Fase del hielo, lista de tiles para hacer el tileset.

	00,40,41,30,21,05,22,23,08,09,26,27,28,16,14,31

~~

He comprobado que el apaño para los tilesets customs que obtuve "de regalo" funciona genial. La estructura para cambiar de fase fácilmente, también.

20160210
========

Hoy empezaré apañando los tiestos mínimos para la fase del desierto, así pruebo lo de los tiles que te hunden (arenas movedizas) y lo dejo todo maqueao, listo para hacer las fases y programar las tonterías que faltan (pantalla de título mínimal, secuencia de fases) ...

He pensado repetir las cuatro fases al final, pero con auto avance. En plan cabrón.

La otra cosa que se me había ocurrido no sé si será posible "fácilmente": consiste en hacer fade out y fade in del fondo para tener que ir a ciegas a intervalos. El problema es que Neslib hace fade in/out con pal_light pero eso afecta a todo, sprites incluidos. Veré si se puede modificar fácilmente, pero esto me corre menos prisa.

~~

Fase del desierto, lista de tiles para hacer el tileset.

	00,01,02,03,04,05,42,43,44,45,10,11,15,13,14,31

~~

OK - Todas las fases planteadas, el auto-scroll funcionando, un par de cosas limpias, pantalla de título y "LEVEL XX", y poco más. Ahora queda la tarea chunga de hacer las fases, pensando siempre en que deben funcionar también en auto-scroll (no se puede poner un "ir y venir" - yo me entiendo).

A menos que [idea peregrina on] Podría hacerlo si siempre hay una vía de escape en un tile especial que cambiaría en las fases de auto-scroll. ¿Cómo? Pues con las listas de tiles para cada fase. Si elijo bien el tile, es factible - pero cuidao, que esto me pone restricciones bastante heavies.

Viendo los tilesets, estos tiles "sustituibles podrían ser":

- El bloque de piedra rosa en la fase 0 (tile 12).
- El bloque de ladrillos rojos en la fase 1 (tile 15).
- El bloque de ladrillos celestes en la fase 2 (tile 15).
- El bloque de ladrillos grises en la fase 3 (tile 15).

De hecho, paso de la piedra rosa, que es muy fea. Pongo otro bloque de ladrillos ahí. El tile de la piedra rosa se queda sin usar y así tengo para el tile "alternativo" que se vea como un cuadro de linea discontinua.

Joder, esto es la leche XD.

20160212
========

Hoy quiero hacer pequeñas tareas para seguir completando esto poco, y a ver si este finde puedo darle a las fases. Por lo pronto, quiero ver si es factible esconder el sprite original (el de la rubia) para poder cambiarlo por el de linlin usando una combinación de teclas. Todas las paletas del juego cambiarían también.

Otra cosa que quiero hacer es ver cómo detectar el final de la fase. Lo suyo sería llegar a cierto punto y comprobar si hemos cogido las moscas. Puedo ver si hay sitio para un sprite de un enemigo que nos hará perder una vida si no tenemos todas las moscas. ¿Una rana?

Cuando tengamos todas las moscas, el sprite de la rana estará sonriente y no colisionará. Así podremos avanzar hasta sobrepasar el tile número 4088 (la mitad de la última pantalla), o quiza el 4090, para dejar margen para poner la rana.

También hay que ver la forma más mínimal de meter una gota que caiga desde arriba de la pantalla. Necesita colisión básica. 

Vamos primero a hacer cuentas...

La prota ocupa 65 patrones. Ahora mismo hay 179 ocupados, con lo que quedan 77. 77-65 = 12, me quedaría demasiado poco para meter la rana. A menos que haga fullería e intente buscar repetición. También hay un par de cells que no uso y de los que podría ir prescindiendo.

Hago backup y me pongo a ello...

Otra cosa que tengo que hacer es preparar la zona de RAM compartida para poder atender a comandos del menú (por ejemplo, para las ROMs que tengan dos juegos - hablo del Multicart, bla bla bla). Con 16 bytes me basta, pero tengo que tocar el .cfg para meter el segmento y dejarlo protegido, y tocar neslib para que no limpie esa zona de RAM. Futesas, futesas.

Otra cosa: también molaría que las fases 5-8 (1-4 repetidas) tuviesen la paleta levemente alterada. No tanto como para perder la identidad (rojizo para lava ...) pero sí para hacerlas levemente diferentes.

Vamos, que tengo que hacer 12 paletas más (4 más las 8 alternativas para el juego modo "N").

~~

Ángel me ha sugerido un tipo de enemigo que puede venir bien y hacer secciones muy chulas: un bloque que no te mata, pero que al "pisarlo" (o culiarlo) se va para abajo a toda leche y luego vuelve a subir poco a poco. En realidad funcionaría como una plataforma móvil vertical (a modo interno, quiero decir, si tiene que arrastrar al jugador), así que tendré que introducir en la ecuación las variables de nombre misterioso (no sé qué coño significaban, ni si eran siglas, pero llevo años usándolas), al menos en el eje Y: pgtmy (¿Player GoTten MY? es posible).

Este es el cacho de código de MK1 NES que controla las plataformas verticales:

	// Vertical moving platforms
	if (
		(en_my [gpit] < 0 && pry + 17 >= en_y [gpit] && pry + 12 <= en_y [gpit]) ||
		(en_my [gpit] > 0 && pry + 16 + en_my [gpit] >= en_y [gpit] && pry + 12 <= en_y [gpit])
	) {
		pgotten = 1;
		pgtmy = en_my [gpit] << (6 - en_status [gpit]);
		py = (en_y [gpit] - 16) << 6; pry = py >> 6;
		pvy = 0;
	}

El tema debe ser una simplificación de esto porque sólo es para descender.

Creo que podría "enganchar" esto en la colisión. Si hay colisión, primero se comprueba que esta sea en la parte alta del tile (con los valores que manejo, con pry entre en_y - 16 y en_y - 12). Si es así, arrastramos: pvy = 0, pgtmy = BLOCO_VY_FALL << FIX_BITS; pgotten = 1; y ponemos al enemigo en estado "cayendo". Si no, hacemos rebotar levemente al jugador [*].

[*] Esto siempre queda raro. ¿para dónde se rebota? Puedo probar con cambiar de sentido ambas velocidades, a ver.

Tenemos que tener dos estados:

	- Idle: 
		si en_y > en_y1 -> en_y -= BLOCO_VY_IDLE; 
		si en_y < en_y1 -> en_y = en_y1;
		si collide (player, en), pry entre en_y -16 y en_y - 12 --> Estado = Falling
	- Falling: 
		si en_y < 240 -> en_y += BLOCO_VY_FALL;
		si !collide (player, en) --> Estado = Idle.

Voy a pintar un bloque en el maltrecho set de gráficos (sustituyendo uno de los enemigos mierder de jet paco) y pruebow.

~~ 

Apunte rápido (a ver si modifico el colocador de una puta vez y no tengo que estar siempre recordando estas mierdas - este finde lo hago sí o sí, que si no hacer las fases va a ser un dolor) - tipo 6, gráfico 9 -> 0x69 = 105.

20160222
========

Joder, han pasado 10 días. He estado con esto, a ratos, pero también con otras cosas. La verdad es que tengo un poco de dispersión y tal, pero bueno. Despacito todo termina saliendo adelante.

Los blocos funcionan perfectamente. Tuve que ajustar un poco la colisión para hacerla más ancha (queda más natural con la forma de los sprites) y la verdad es que darán mucho juego.

Empecé también con el mapa definitivo. Es un proceso que me da bastante pereza, y quizá por eso tenga esto medio parado - como el Cherils R... Definitivamente, tengo que ponerme un poco las pilas. 

Otra cosa que he hecho es trabajar en los ranos del final de fase (enems_final_frog). Tienen un comportamiento muy sencillo que apenas ha necesitado programación: Dependiendo si tenemos los objectos (abejas) suficientes o no presentan un gráfico u otro, y nos dejan pasar o no. Una cosa que tendré que hacer para que esto quede bien y natural es gastar dos enemigos para el rano, y usar gráficos de 16x16, uno encima de otro. De esa forma no habrá que hacer apaños raros con la colisión del escenario y quedará bonito y holgado, como el resto del juego. Ahora lo que tengo que hacer es un gráfico del rano chuli.

Los ranos son el tipo 7, así que los números deberían ser 0x7E y 0x7F. Los gráficos deberán ser los dos últimos del set.

20160223
========

Ayer hice los ranos al 100% y coloqué todos los objetos y mierdas de la primera fase. Luego lo compilé todo y resulta que se iba todo al carajo. ¡Mierda! Estaba seguro de que estaba saliéndome de algún array y escribiendo sobre los valores de otras variables. El tema era bastante grave. Hasta hoy no lo pude mirar, y resultó ser una cagada al inicializar los pezones que no había visto porque estaba probando todas las cosas en la primera pantalla. Las variables en punto fijo para ciertos elementos se crean al vuelo sólo para las dos pantallas activas durante el ciclo del juego, al ir desplazándose el scroll. El problema es que estaba dándole valores a uno de estos arrays en la creación de los enemigos de la fase - que itera hasta 48 elementos, cuando estos arrays sólo tienen 6 (vamos, que estaba mal: eso no se puede inicializar ahí). Se salía y escribía por sitios chungows. Pero ya está arreglado.

Debería echarle una partida a la primera fase para ver que se puede coger todo y que la dificultad está bien ajustada. Validada la fase 1, pasaré a la 2 (lava).

En la fase de la lava quiero meter gyrosaws y cambiar los peces por bolas de fuego. Aún tengo algún enemigo "placeholder" que puedo cambiar por esto.

~~

Jugando se me ha ocurrido que podría estar bastante bien que pudiésemos perder la ropa para tener una segunda oportunidad a la hora de ser golpeados. Como tengo sitio en el tileset, lo haré así. A ver qué tal se da. Voy a retocar los gráficos de la versión chochote para que sea la versión normal pero en bragas o algo.

~

Ya lo tengo, y queda muy chulo, pero hay por ahí algo chungo que no tengo bien controlado. Hay veces que los pezones se ponen a hostiar el doble de rápido. Es como si se actualizase dos veces el mismo enemigo. Es bastante probable que la esté cagando con la asignación al vuelo de los enemigos y los "slots" de punto flotante para el movimiento suave, de forma que haya dos enemigos con el mismo slot asociado siendo procesados al tiempo. Voy a intentar verlo.

~~

Había un pequeño bug al inicializar la fase pero tampoco era nada grave. Sin embargo hay un punto del mapa en el que un enemigo que no está me golpea y a veces incluso cambia radicalmente cam_pos. Voy a ver donde es a ver si tengo alguna idea... 

No sé si se tratará de otro array fuera de madre.

Por lo pronto, antes de llegar ya había un pez donde no debería (en medio de una plataforma de tierra). El tema pasa en la pantalla 6, que no es ningún número "sospechoso" (en plan ¡pasa justo en la mitad de la fase! ... no)

~

Desactivo los peces y no pasa...

- Puede ser por los peces en si.
- Puede ser por los enemigos de punto fijo, en general.

Por lo menos ya lo tengo medio acotado.

Otra cosa que también falla: la colisión vertical hacia arriba. [FIXED], era un >> en vez de <<. Típico de programar dormido y encarajado. Pero arreglado fácilmente. ¿Qué será lo que le pasa a los pezones? ¿Será cosa de ellos, o de la asignación al vuelo de slots? Es que cada vez me escama más. Los slots de los enemigos parecen llenarse correctamente 0 1 2 3 4 5 0 1 2 3 ... etc, de tres en tres, por mitades, y al cambiar de pantalla. Pero el hecho de que haya colisiones fantasma y que otros pezones salga donde no deban cuando están activados. No sé. Ya me aclararé.

Puedo aprovechar para probar si funciona el rano, con los pezones desactivados (si es que así se puede pasar la fase - si no, la puentearé). Voy a hacerlo ahora y así me despejo.

Otro glitch: puedes sacar a los enemigos de trayectoria lineal vertical de su trayectoria saltando sobre ellos. Creo que el tema está en cuando los golpeas justo cuando acaban de llegar al límite y han cambiado su dirección. En este caso no deberíamos cambiarlos. [FIXED]

~

He comprobado que sale el rano enfadado si no tienes los bichos y te mata - aunque creo que la animación de la cabeza no está bien. Le echaré un vistazo.

~

Tema glitch de pezones: arreglado. Ha sido como buscar una aguja en un pajar, pero ha surtido efecto eso de dejarlo un buen rato y luego volver. En cuanto he abierto emems_pezon.h lo he visto: estaba indexando una de las variables dinámicas con el índice estático (yo me entiendo). Vaya, lo mismo que la otra vez, pero más oscuramente oculto. Creo que eso debería arreglarlo. Voy a activarlo y a echar un ojal.

Por otro lado, el rano hace cosas raras que tengo que revisar. Pero eso será mañana.

20160224
========

Por más que reviso "offline" no veo nada - creo que lo suyo es que me ponga a jugar en Fceux hasta que se reproduzca. Cuando esto ocurra, abro el visor hex. de la memoria y miro qué me encuentro. Más que nada para saber qué está pasando, y por qué van más rápido. Sólo se me ocurre que varias instancias de pezones estén actualizando el mismo "slot" de las variables de punto fijo, de forma que, efectivamente, el pezón que vemos vaya el doble de rápido. La cosa es que no he echado ningún pezón en falta - si fuera esto (tal y como yo creo) habrá pezones que no saldrían ya que dos apunta(ría)n al mismo sprite...

No lo sé, a ver si suena la campana. Mientras tanto pensaré en la segunda fase, la de la lava. Aquí deberían ir apareciendo los gyrosaws. También quiero hacer por meter un item que nos vuelva a vestir. Para ello reaprovecharé el tipo de enemigo "buzzer" y según el gráfico que lleven haré una cosa u otra en la rutina de colisión (incrementar objetos o volver a vestir).

~~ 

Apunte: como se me ha olvidado qué significa el título, quizá cambiarlo por 我想尿尿 (Wǒ xiang niào niào), que significa "quiero hacer pipí" sea buena idea - sobre todo porque me deja patrones libres (32 en total) para hacer algo más en las pantallas de título/final (que aún no he hecho, por cierto) - aunque sea una simple greca.

~~

Para la recarga de ropa, el símbolo será 衩, que significa (como no podía ser de otra forma) bragas. Ya está metido el código (sin probar) y el gráfico. Ahora sólo tengo que colocar uno en la fase, en la primera pantalla, ver que funciona, y luego poner uno a mitad de nivel, que será buen sitio. Pero que cueste cogerlo. Tengo que aprovechar también para mover algunas cosas de sitio. Por lo general me he dado cuenta de que Lin Lin salta lo suficiente para no tener que usar a los enemigos en muchas ocasiones. No sé si mover los enemigos o mirar las rutinas para que salte levemente menos.

~

Otra cosa: la actualización de los slots sólo se hacía en los cuadros impares (por el tema de ahorrar tiempo de frame distribuyendo tareas) y es posible que este fuese precisamente el problema, pero no podré saberlo. Si vuelvo a ver a los pezones acelerados, volveré a colocarlo como estaba y tal. Pero ahora no puedououooooo (sonido de E.Honda muriendo).

~

Joé, qué arte tengo, estoy recuperando mi mojo. Todo lo que he metido desde hace un par de días ha funcionado a la primera. Ya hay "objeto revestidor". Voy a ver la fase 2.

~~

He estado casi todo el rato de hoy montando un mapper 113 para que Doragasu pruebe su placa y descubriendo de mala manera que los emuladores no soportan la característica de cambiar el mirroring leyendo el bit 7 del registro del mapper. Fceux tiene esta característica comentada, por ejemplo, y VirtuaNES sólo la soporta (según los fuentes que he visto) para un juego en concreto. Mal.

Pero bueno, no es algo que me preocupe. Volviendo a este tema, he añadido el soporte para leer la RAM compartida a PongPong. Por lo pronto voy a poner que si COMM_POOL[14] y COMM_POOL[15] valen, yo qué sé, 69, se active el segundo juego de paletas, con vistas a llamar al juego con otro CHR-ROM. Esto es fácil de probar escribiendo valores en la RAM con FCEUX y haciendo un soft reset. Creo. Lo veré.

¡Oh, sí! Funciona perfectamente :) Escribo $69 $69 en $030E y $030F, hago un soft reset, y el juego usa el segundo set de paletas (que cambiaré cuando tenga gráficos definitivos para el reemplazo). He pensado que el juego alternativo podría implementar el movimiento tipo choco.

20160226
========

Estoy haciendo la fase 2. Aquí los pezones deben ir con otro gráfico, el de la bola de fuego, para que tengan más thrust y suban más, dando el pego de que son otro tipo de enemigos. Supongo, ya veré. En las colisiones está también toqueteao para que no puedas culiar.

La bola de fuego sería 0x4A = 74; el pezón era 0x48 = 72.

Una cosa que hice y que no apunté es que mejoré algo más mkts.exe, de forma que al exportar sprites detecte también reutilización de tiles espejados en ambas direcciones. La bola de fuego, dos cells de 16x16, que deberían ocupar 8 patrones, se quedan así en 2 (por la forma del gráfico y tal).

Con estos tiestos he conseguido liberar un montón de patrones de los destinados para sprites que seguro que vienen bien para algo (por ejemplo, para hacer un cambio de banco, usarlos para tiles, y hacer una pantalla final chuli). 

REMEMBER: Para colocar Gyrosaws:

- Tienes que colocarlas en el sitio correcto, dependiendo si las quieres CW o CCW [vaya: recordando que la primera dirección siempre es izquierda]:

	CW: ··· CCW: ··o
	    ·X·      ·X·
	    ··o      ···

- Hay que seleccionar, con el atributo del enemigo, la dirección. CW es 1, CCW es 0.
- El número con el que hay que crear esto (hasta que modifique el colocador: de hoy no pasa) es 0x2B = 43

~~~

Qué bonito queda todo. He cambiado algo la paleta en esta fase para que lin lin sea mejor (Qi Pao verde) y para que los sprites rosas salgan más anaranjados. Queda mejor.

También se me ha ocurrido que, dado el cambio de título, necesitamos poner un WC al final de la fase y a Lin Lin haciendo su pipí victorioso. O también podemos poner a un señor seta que diga SORRY LIN LIN BUT YOUR WC IS IN ANOTHER CASTLE. Pero no. Mejor el pipí.

Tengo que hacer el logo nuevo 我想尿尿 (Wǒ xiang niào niào)

~~

Antes de seguir con esta mierda voy a modificar col-incog para que pille hex.

20160307
========

Modifiquéle. Todo guay. Hace días y días. Pero he estado haciendo el tonto con otras cosas (Lala the Magical). En este tiempo también pinté el WC y a LinLin sentada haciendo niào niào, y ahora que tengo un ratico me dispongo a ponerla. 

En principio voy a usar el tipo de enemigo de los objetos, o sea, el que lleva las abejas y las recargas de ropa. En este caso, tengo que modificar cómo se termina el nivel, para que no termine hasta haber cogido el WC.

Lo suyo es que se quede unos segundos el tema parado mientras suena un jingle o algo así. Por ahora esperaré un par de segundos fuera del bucle del juego si se detecta que hemos salido ganando y no gameoverizando. Y eso.

Como el sprite se me sale de rango (sería el 17) crearé este nuevo objeto como si el sprite id fuera "0". O sea, será el $30 [el 48, pero ya no necesito cambiar a decimal porque tengo modificado el colocador - MUAJÁ MUAJÁ MUAJÁ]...

~

Hay una cosa rara que yo no he programado: ¡¡el rano se vuelve a mosquear cuando lo hemos sobrepasado!! ¿algo de la colisión? Lo revisaré. No me discusta así, pero me aterra que sea un efecto colateral de algo que luego de la cara de mala manera.

He comprobado también que el remedio que le puse al tema de que podíamos sacar de la trayectoria a los enemigos verticales no funciona, así que... Tendré que pensawr.

~ 

Sobre lo del rano: lo acabo de ver: hay algo ahí haciendo de las suyas. El espacio en RAM reservado para pobjs lo sobrescribe "alguien" cuando le da la gana. De repente valía 8, estando yo con el muñeco parao sin hacer nada. Habrá que ver qué variables le lindan a ver si no estoy haciendo el pelotillo.

en_slot es el array más cercano.

	00066D	en_cell
	00066E	en_slot
	00069E	plives
	00069F	opscore
	0006A0	pobjs

La cosa es que plives y opscore parecen tener bien los valores... -> Es cuando salto. Cuando le doy al botón de salto, el valor que haya se sobrescribe con 0x08! What. The. Fuck. Um - ¿no era 8 el número de abejas que había que pillar? Me suena a cheat mal puesto.

Sí, joder, era el puto cheat mal puesto. Pero antes no estaba así y algo raro pasaba. Lo voy a deshacer y ver más. Afuerifeiufe. Y ya.

Hum! De entrada he visto que la cuenta de objetos no se reinicia al morir. ¡Ahí ya hay algo mal! Lo arreglo y pruebo de nuevo. . .  Supú, es que pobjs no lo estoy inicializando nunca, manda cojonatos. Arreglo y repruebo.

~~

Otra cosa que he visto es que cuento como el puto culo :-O Esperaba 8 moscas y en la fase hay 11... ¿¿¿WTF??? Lo cambio a 11 fasi, pero...

Vale, aquí está lo raro: el rano tenía la cara de molar (claro, 11 >= 8) Pero justo cuando lo paso, pobjs cambia a ¡2! y por eso se pone mosqueao.... Pero ¿Por qué? ¿Qué milagro extraño se obra?

VALE. Las demás variables también se han jodido. Y ya sé por qué es: a partir de esa posición el juego intenta cargar nuevos enemigos en los slots... ¡y ya se ha acabado el mapa! Se sale por tós laos. Tengo que controlar eso. Urm. URM. Voy a ponerme el gorro de pensar.

Ahora se llama a enems_fp_create cuando se cambia de pantalla (en el MSB de cam_pos). Veamos cuánto vale ahí, y lo voy a ver con el visor de la RAM de fceux porque hoy no tengo ganas de pensar, sobre todo a la hora que es y sin haber salido de este sótanaco desde las 7 de la mañana (¿llevo ya 11 horas? qué largos son los Lunes) -> cuando vale 0x0F. Voy a parchear y probar de nuevo.

Vale - ya he visto lo de los 11 bichos, y me he acordado: en la fase 1 debe ser más fácil acabárselo y hay más abejas de las que quiere el rano. Ok. Aunque este es el tipo de cosas que luego a la gente le suena raro. No lo puede concebir. Tienen mindfucks y luego, por la noche, no duermen.

Voy a ver si el arreglo que he introducido ha molao y tal y cual.

Sí, funciona. Pues a cagar pepinos. Hasta mañana... 

20160619
========

Retomo un poco aprovechando que tengo música murciana que montar. Arreglo cosas y perfilo mejor las fases de autoavance. Bajo el marcador 8 pixels para que se vea mejor en NTSC. Esto también da más tiempo antes del split por si famitone hace fullerías, lo cual viene bien.

La fase de autoavance es muy difícil. Estoy pensando que al igual que hay un tile que solo aparecen en las fases normales y en las de autoavance es traspasable, podría ocurrir también al revés para apañar un poco la dificultad en los puntos negros. Voy a ver los tilesets a ver qué puedo hacel.

Tendría que prescindir de algunos adornos, pero creo que es lo suyo. Tampoco creo que se pierda demasiado. Voy al lío.

20160620
========

Todos los tramollismos estos están resueltos. La música está prácticamente metida. Queda muy poca ROM, pero en realidad lo único que queda de añadir es un "niao niao" y algo para el final (tengo que ver cómo llevo las nametables). Debería liberar algo de ROM, por ejemplo quitando todo el soporte que pensé para lanzar el juego con otro sprite y gameplay. Con eso ahorraría de la leche.

Creo que podría dedicarme tranquilamente a eso hoy mientras hago las tareas del curro de verdad, en descansitos, que es un trabajo bastante divertido y muy agradecido.

~~

Empezamos midiendo cuanto ocupa ahora (de aquella manera, ya tu sabeh). Tenemos 263 bytes libres. Cágate lorito y empezamos. Lo primero es cargarse todo el soporte para cambiar de juego (esto estaba pensado para ser lanzado desde un menú de un multicart y, dependiendo de los valores que leyese de RAM, cambiar de sprite, paletas y motor). Apaño primero el make.bat y quito los gráficos y paletas extra. Eso también me liberará bastantes patrones en la tabla 1.

Fuck - el sprite extra ya estaba quitado. Olvídate de los patrones XD Siempre puedo echarles un ojaldre para ver cuánto puedo optimizarlos, que a veces mueves un pixel y ganas una repetición. Voy con el resto, anyway.

~

Ok, sólo quitando cosas que no necesito me voy a 528 bytes libres, lo que está genial. Luego, poco a poco, iré identificando código repe y cosas que podría cambiar modificando el formato de los datos, e iré recortando aún más.

~

769 bytes cambiando una tontería de los puntos en bcd; voy a comprobar que no me he cargado nada.

~

Limpiando neslib (quitando cosas que no uso) y un par de merdas más, me quedo con 1027 bytes... Y creo que no puedo sacar más. Este parece que lo hice bien desde el principio, no es como Yun/Cherils/MK1 XD

En fin, voy al trabajo de verdad.

~~

En poco más de 1Kb tengo que meter:

- Checkpoints, un punto intermedio al que se pueda volver al pasarlo, justo en el centro de la fase.
- Una escena para el final.

Sinceramente, no sé cómo coño lo voy a hacer. (Sí lo sé, pero me gusta quejarme)

~~~ 

Sobre la optimización, voy a comprobar qué sprites necesitan realmente estar girados para ahorrarme definiciones de metasprites, que son unos cuantos bytes potenciales.

Recordemos: 
	- La moscabeja se pone como tipo 3 (buzzer) y atributo (sprite) 12
	- La recarga se pone como tipo 3 (buzzer) y atributo (sprite) 13
	- El water se pone como tipo 3 (buzzer) y atributo (sprite) 0.
	- [NUEVO] El checkpoint [zurully] se pone como tipo 3 (buzzer) y atributo (sprite) 1.

Joer.

Cuando coja el hotspot, se debe recordar la posición "X" [¡ojal con el autoavance!], el número de abejas conseguidas, y el estado de todos los enemigos. Ahora mismo, cuando mueres, se sale al bucle principal que controla el juego, que detecta que te has muerto y te quita una vida. En la siguiente vuelta, se inicializa todo [game_init ();] y luego se lanza el juego.

Veamos qué se hace en game_init (). Marco las cosas que debría cambiar o adaptar.

	[X]	cam_pos = 0; 
		
		map_ptr = (unsigned char *) (map + (level >> 1) * COLUMN_SIZE * MAP_W);
		pal_bg (world_pals [level & 7]);
		pal_spr ((level >> 1) == 1 ? pal_fg_1 : pal_fg_0);
		mtile_pattern_offsets = (unsigned char *) world_mpos [level & 7];
		behs = (unsigned char *) world_behs [level & 7];

	[X]	enems_init_level ();
	[X]	player_init ();

	[X]	pobjs = 0; opobjs = 0;

En primer lugar lo suyo es mover cam_pos tras player_init y hacer la inicialización como Cthulhu manda:

	player_init ();
	cam_pos = prx - 120; if (cam_pos < 0) cam_pos = 0;

¡Con esto me empiezo a allanar el camino para que el autoavance empiece bien! Voy a hacer esta micromodificación y ver si va bien para la condición inicial, que me gusta ir poco a poco los días que me duele la cabeza.

Sigamos. enems_init_level (); <- básicamente esto inicializa todos los enemigos de la tira (nivel) donde estamos. Entiendo que si estamos continuando en un checkpoint, esto no debería llamarse.

player_init () hace lo siguiente:

	px = 16 << FIX_BITS;
	py = 64 << FIX_BITS;
	prx = pry = 16;
	prx_advance = prx + 64;
	pvx = 0; pvy = 0;
	pgotten = 0; ppossee = 0; pkilled = 0;
	phit = penhit = 0;
	pfacing = 0; pfr = 0;
	pj = pjb = 0;
	do_game_loop = 1;
	pen = 1;
	psoff = 0;

Habría que cambiar la definición de px y prx.

Puedo establecer una señal. Esta señal debe reiniciarse cada vez que se inicie un nuevo nivel. Añadamos pcheckpoint a las variables en ZP, y actuamos así:

Si pcheckpoint == 0 -> nuevo nivel. Si pcheckpoint != 0 -> valor inicial de prx, indica checkpoint.

Miedou me da. Voy a ver si tal y cual.

~~~ 

Hecho. Vamos a probar. Pongo uno cerca y pruebo y tal.

Cosas:
- Inicio en punto aleatorio, no va fino. Ver en Sir Ababol, que creo que tuve que resolverlo.
- Los enemigos se reinician igualmente. WTF.

~~

Todo arreglado, los checkpoints van geniales y aún quedan unos 1000 bytes. Bien.  Incluso en el modo de autoavance se comportan como dios manda, genial. Todo guay y molón y tal y cual.

Pero sigo viendo a veces pezones follados, y creo que sé por qué es. Bueno, sé por qué *puede* ser: seguro que en pantallas en las que falta algún enemigo por rellenar o en mierdas por el estilo se añade dos veces de forma dinámica el mismo enemigo a los slots de punto flotante o algo parecido. Tiene que ser eso. No hay otra. Lo miraré un rato pero ya me tengo que ir.

20160621
========

A lo mejor se solucionó con lo que hice (no me acuerdo, me duele el camuy). Ahora tengo que ver qué hago para el final. Tengo 64 patrones ocupados por un alfabeto + letras que apenas (creo) estoy usando, pero a lo mejor me vale con hacer un escenario bonito y pintar a Lin Lin haciendo pipí y poco más. Voy a usar el screen tool de Shiru para hacer algo sencillo a ver qué tal se da. Si no ocupa mucho en RLE, le añado un texto engrish y hago sonar el jingle de start.

Texto: 现在我手淫

现在 xiàn zài == en este momento
我 wǒ == Yo
手淫 shǒu yín == ??

Se queda más en wǒ shǒu yín.

¡Me acabo de dar cuenta de que puedo ahorrar un huevazo en las definiciones de metasprites (no en patrones, en bytes de PRG) para Lin Lin, que está muy mal optimizado! Ahora tengo -> ~710 bytes; luego: 1255 bytes. Me cago y me queda. Joder: Me cabe lo que quería hacer de "continuar". Cuando te matan, en la pantalla de título, aparece "PRESS START" o "PRESS SELECT TO CONTINUE" y te lleva al mundo X-1 donde estuvieses (a level & 0xfe, vaya)

Sea lo que sea, quiero poner a Lin Lin bailando en el final (tengo 28 patrones, que me dan de sobra) y para eso tengo que dibujar, y aquí mal. Pero lo otro que tengo que hacer, que es revisar el recorrido de la fase 2 de Yun en modo limite, también canta. Y lo otro que tengo que hacer, que es terminar el set de la piscina para empezar a hacer el Isshokuta, idem de idem. Y me vuelvo a ver en la tesitura de que tengo muchas cosas que hacer, pero todas bloqueadas por necesitar actividades que dan el cantazo. Y en casa, imposibol. Fuck.

Voy a hacer lo de PRESS SELECT TO CONTINUE, que como tengo sitio de sobra, irá guay. Esto debe guardar un latest_level, y mostrar la pantalla diferente si >= 2.

20160720
========

Retomamos para hacerle una fullería a esto que creo que es necesaria. En PAL es muy difícil. En NTSC roza lo imposible, por lo que voy a ajustar las velocidades de NTSC para que se parezcan a PAL.

Esto implica sustituir algunas constantes por variables a las que tengo que hacer sitio en ZP sí o si para no perder demasiados ciclos.

Según mis cálculos (que he puesto en Nesdev para que los super dales fran me los validen, que es de gratis y siempre viene estupendamente), las conversiones serían, para velocidades y aceleraciones:

	V(NTSC) = V(PAL) * 50 / 60
	A(NTSC) = A(PAL) * 50 / 72

Ahora que lo veo, parece interesante notar que V(PAL) = 1.2 * V(NTSC), y que, si te fijas, 72 = 60 * 1.2, y que, además, 72 * 5 / 6 = 60. Seguro que la que he liado para encontrar las constantes es un pifostio increíble y que con lo de arriba lo hubiese averiguando antes, pero mi cabeza ya no es lo que era, duermo poco, tengo mil paranoias, y, total, con que funcione...

Por supuesto ese 50/72 es chungo chungo a la hora de dar valores enteros, por lo que la precisión no es perfecta, pero según las simulaciones que he hecho resultará, almenos, suficiente. Espero.

Total, con que se juegue parecido, ya me vale. Como solo estoy jugando con 4 bits de precisión, seguro que tengo que ajustar a mano luego. Sólo quiero lograr dos cosas, de todos modos:

- Que Lin Lin se mueva igual de rápido (¡más o menos!) en PAL y en NTSC.
- Que salte igual de alto y llegue igual de lejos (¡más o menos!) en PAL y en NTSC.

							PAL NTSC
	PLAYER_VY_FALLING_MAX	64	53
	PLAYER_G				4	3 		(2.8!)
	PLAYER_VY_JUMP_INITIAL	16	13
	PLAYER_VY_JUMP_MAX		64	54
	PLAYER_VY_JUMP_BUTT		96	80
	PLAYER_VY_JUMP_A_STEPS  16	13
	PLAYER_VY_SINK			2 	2 		(1.6!)
	PLAYER_AY_JUMP 			8	6 		(5.5!)
	PLAYER_VX_MAX			32	26
	PLAYER_AX				4	3 		(2.8!)
	PLAYER_RX				4 	3 		(2.8!)
	PLAYER_AX_SLIP			1 	1 		(nada que hacer)
	PLAYER_RX_SLIP			1 	1
	PLAYER_V_REBOUND		56	46

Probemos con esta mierdaw.

He hecho leves ajustes y parece que se juega bien. No sé si mejor. Eso ya lo probaré en casa con el mando. 

~~

Ya en casa, y tras leer dalefrania (nesdev), he hecho rollback (con backup, claro, no vaya a ser que quiera volver a los dos sets) y voy a probar algo que me han sugerido: en NTSC, llevar un contador, y 1 de cada 6 frames NO llamar a la actualización de las mierdas móviles.

Como es muy sencillo, voy a probarlo ahora a ver qué tal.

VA DE LA HOSTIA. Asín se queda.

20160721
========

Sigo teniendo el glitch de los pezones follaos y todo esto tiene que ser por la asignación de los slots chunga.

Veamos, se me ha ocurrido que puedo preasignar los slots al principio del juego. Los enemigos, cuando se cargan en RAM, les asigno los slots 0 1 2 3 4 5 0 1 2 3 4 5 ... Así ya está todo precalculado y me ahorro tener que buscarles slot al crear las variables fp. En cada cambio de pantalla, se inicializan las tres variables FP que toquen: 0 1 2 o 3 4 5. Ahora mismo hago fullerías raras, pero funciona... Creo. Se podría simplificar... creo. Pero por ahora voy a ver si precalculando el slot ya funciona.

Sí que funciona.

20160725
========

Bueno, no. A veces hace cosas raras. Creo que tengo que examinar bien la asignación. O no se hace cuando debe, o se hace muy rápido, o aquí hay algo que no estoy tomando en cuenta. Luego me haré unos dibujillos. Antes quiero dejar apuntado que ya he terminado la fase de la lava (3-4), y que me pondré con la del desierto (7-8) en breve, pero antes voy a dar una pequeña pensada al tema de la asignación de los slots de punto fijo dinámicos.

Voy a escribir. Cada pantalla tiene 3 enemigos. Hay 6 slots, 0 a 5. Según la pantalla, estos son los slots que ocuparía cada enemigo de cada pantalla:

	0 1 2 3 4 5 6 7 8 9 a b c d e f ...             enemigo
	0 1 2 3 4 5 0 1 2 3 4 5 0 1 2 3 4 5 0 1 2 3 4 5 slot
	     |     |     |     |     |     |     |     | ...
	0    |1    |2    |3    |4    |5    |6    |7    | ... hasta 15

Al empezar el juego, cam_pos = 0, estamos en la pantalla rda = 0. Tenemos que cargar los enemigos de las pantallas 0 y 1.
Al avanzar un poco, empezará a verse la pantalla 1. Los enemigos están ahí ya.

CUANDO CAM_POS HAYA LLEGADO A |1, o sea, = 256, entonces la pantalla 0 ya no se ve para nada, y es el momento de cargar la pantalla 2.

Creo que el fallo está justo aquí. No estoy cargando los nuevos enemigos donde debo.

Avanzando hacia la derecha, cuando rda != rda_old (o cuando cam_pos & 0xff == 0), tengo que cargar rda+1.
Avanzando hacia la izquierda, cuando rda != rda_old, tengo que cargar rda.

Voy a recapacitar.

	slot_offs [] = {0, 3}

	rda = 0. Avanzo... Cuando rda cambia a 1:
	[cargo los enemigos (rda+1)*3 y siguientes a partir de slots_offs [(rda + 1) & 1];]
	-> cargo los enemigos 6 7 8 a partir de slots_offs [0] = 0 1 2.

	rda = 1. Avanzo... Cuando rda cambia a 2:
	[cargo los enemigos (rda+1)*3 y siguientes a partir de slots_offs [(rda + 1) & 1];]
	-> cargo los enemigos 9 a b a partir de slots_offs [1] = 3 4 5.

	rda = 2. Se ve cacho de 2 y cacho de 3.
	En este momento tengo 6 7 8 9 10 11. Ahora retrocedo!

	rda = 1, se ve cacho de 1 y cacho de 3.
	[cargo los enemigos (rda)*3 y siguientes a partir de slots_offs [(rda) & 1];]
	-> cargo los enemigos 3 4 5 a partir de slots_offs [1] = 3 4 5

Voy a revisar esto en el código.

Parece que ya por fin lo he dejado fino, y de camino le he pegado un pequeño afeitado al código. Voy a limpiar, que hay ya mucha mierda comentada que lo que hace es entorpecer.

~~ 

Veamos, recordemos lo que tenemos para esta fase:

Girosaws
--------

	- Tienes que colocarlas en el sitio correcto, dependiendo si las quieres CW o CCW [vaya: recordando que la primera dirección siempre es izquierda]:

	CW: ··· CCW: ··o
	    ·X·      ·X·
	    ··o      ···

	- Hay que seleccionar, con el atributo del enemigo, la dirección. CW es 1, CCW es 0.
	- El número con el que hay que crear esto (hasta que modifique el colocador: de hoy no pasa) es 0x2B = 43

Blocos
------

	- Muy fácil, colocar en la posición inicial, con t = 0x69 (tipo 6, gráfico 9).

Pezon
-----

	- Puedo usar los dos: los normales son 0x48; las bolas de lava son 0x4a

~~

Voy a colocar unos blocos para probar como funciona todo. Y hago combos y  mierdas divertidas :D

~~

Pero ahora se me ha ocurrido que no me gusta nada eso de tener que tener los atributos de los tiles precalculados para hacer el scroll... Tengo que calcularlos yo al vuelo.

Por lo pronto he hecho un experimento: el scroller, hasta ahora, llevaba una cuenta de 4 y actualizaba la columna correspondiente del lado hacia donde estuviésemos avanzando. Todo el rato. Por probar, he hecho que cuente hasta 5 pero que en el 5º ciclo no haga nada. Funciona, scrollea bien, no te "coge el toro".

La idea sería hacer que en ese ciclo que ahora mismo tengo libre se calculasen los atributos de la columna actual. O quizá lo más inteligente sea hacerlo en el ciclo 0 para que ya estén... Pero bueno, puedo ir probando ahora.

¿Qué gano con esto? Pues que los mapas pasen de ocupar 15 bytes por columna de 32 pixels de ancho (15*128 = 1920 bytes por tira) a ocupar 10 bytes (1280 bytes por tira), con lo que a lo mejor me cabe alguna fase más.

Tengo un rato, voy a ver adonde llego. Tendré que hacer a pelo los cálculos pero luego generaré una tabla de paletas precalculada con los desplazamientos hechos.

~~~~~~~~~~~~~~~~~~~~~~

20161207
========

Girosaws
--------

	- Tienes que colocarlas en el sitio correcto, dependiendo si las quieres CW o CCW [vaya: recordando que la primera dirección siempre es izquierda]:

	CW: ··· CCW: ··o
	    ·X·      ·X·
	    ··o      ···

	- Hay que seleccionar, con el atributo del enemigo, la dirección. CW es 1, CCW es 0.
	- El número con el que hay que crear esto 0x2B 

Blocos
------

	- Muy fácil, colocar en la posición inicial, con t = 0x69 (tipo 6, gráfico 9).

Pezon
-----

	- Puedo usar los dos: los normales son 0x48; las bolas de lava son 0x4a

Mosca: 0x3c
Vestido: 0x3d
Mojon: 0x31

He terminado las fases 7-8 (desierto), a falta de retocar mogollón, y de paso he afinado un poco la colisión vertical que no comprobaba un caso porque creía que iba a ser marginal pero ha resultado no serlo con los trazados de las fases 5-6 y 7-8.

20161211
========

Antes de seguir quiero meter las fases de bonus. Como veo que no había apuntado por aquí un carajo, pongo lo que dije en el forow en Julio:

Dijo el maño de poner fases de bonus, y como aquí es tontería ganar vidas y ganar puntos no me parece un fin en si mismo (aunque mola), se me ha ocurrido lo siguiente.

Como sabéis, el juego está organizado en 4 mundos, de 2 fases cada uno. Se trata de recorrer el mapeado en cada fase, y llegar al final, donde hay un rano. Para que el rano te deje pasar, hay que tener al menos 8 moscas. 

En la primera fase de cada mundo se avanza o retrocede a placer. En la segunda, se repite el mapeado (con ligeros cambios) pero el scroll avanza automáticamente. Si te pilla el borde, estás muerto. Si te dejas atrás algunas moscas y llegas con menos de 8 al rano, estás muerto.

EHecho: Lo más difícil, con diferencia, de este juego, es que en las fases de autoavance haya que coger también al menos 8 moscas. En las primeras fases no es tan difícil porque hay más de 8 moscas, y te puedes dejar atrás alguna... Pero a partir del mundo 3 pienso poner 9, y no más: ¡sólo te puedes perder 1! y serán jodidas de coger.

La idea: Ofrecer una ayuda al respecto.

La idea es: si en la primera fase de cada mundo consigues llegarl final con más de las 8 moscas que quiere el rano, salta una fase bonus. La fase bonus ofrece un mapeado con agujeros y algún enemigo sencillo, principalmente, y en ella hay 8 moscas artificiales.

Si te matan o te caes en la fase bonus, se acabó. Sólo hay una oportunidad. Cuando empiezas la fase de autoavance, no partes de 0 moscas, sino que partes del número de moscas artificiales que hayas conseguido en la fase bonus. Así se facilita mucho la tarea, porque tendrás que coger menos moscas para tener 8 al final.

~~

Parece que funciona, pero necesitará tuning. Como todo :-)

20161228
========

El Multicart está ya casi fino (faltan dos músicas y arreglar un par de flecos, y es algo que tampoco me importaría que se quedase sin hacer, a estas alturas) así que le voy a dar un poquito más a Pong Pong. Acabo de terminar de colocar los tiles para la fase del hielo. Pongo enemigos y a probar.

Con esto ya quedaría finiquitado el juego, a falta de limar aristas, y listo papeles para la compo.

~~
 
Enemigos colocados, voy a probar. También voy a probar a poner RX = 0 en el hielo, que ahora no resbala lo suficiente.

Y luego a fregal.

20161229
========

Cosas que he visto: 

- Es posible morir saltando verticalmente sin VX sobre un enemigo y quedarte rebotando contra él indefinidamente, con lo que el juego se queda pillado ahí. Puedo resolverlo poniendo un contador de rebotes y permitiendo maximo 3, o revisando para que siempre haya VX.

- Cuando resbalas se anima el muñeco y debería quedarse clavao.

Había algo más pero can't remember. Voy a por estas dos cosas.

20161230
========

Davidian me ha pasado ya la OGT completa y ahora el juego es top-top. Lo que no recordaba ayer era hacer que el motor de enemigos se saltase los tipo = 0 y que las fases saliesen como fase N-M en vez de como fase 2N+M.

Ahora seguro que hay mil cosas que pueden quedar mejor con un poco de pulido, pero el juego está básicamente terminado. 

nessc me dice que aún queda algo de espacio.

Hummm... ¿Estalactitas que caen en la fase de hielo? XD Ya mañana. Hoy no habrá siesta por la tarde :-/
