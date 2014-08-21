/*
 * data_struct.h
 *
 *      Author: Belle & Bruce
 */

//C++ header
#include<iostream>

//allegro header
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

#ifndef DATA_STRUCT_
#define DATA_STRUCT_

//Variabili Globali
const int SCREENWIDTH = 850;	/**< Larghezza dello schermo*/
const int SCREENHEIGHT = 600;	/**< Altezza dello schermo*/
const int OFFSETX = SCREENWIDTH * 0.02;	/**< Margine laterale della finestra */
const int OFFSETY = SCREENHEIGHT * 0.04; /** < Margine Superiore della finestra */
const int FPS = 25;		/**< Frame del gioco*/
const int BLOCKSIZE = 16;	/**< Blocchi della mappa*/
const char filenamelv1[] = "data/map/map1.txt";     /**< Mappa Livello 1 */
const char filenamelv2[] = "data/map/map2.txt";     /**< Mappa Livello 2 */

/**Stato di direzione per pacman e per i fantasmi*/
enum DIREZ{FERMO, SU, GIU, DX, SX};

/**
 *  Stato del gioco, serve per il loop della funzione ::main per eseguire diverse
 *  operazioni a seconda della fase in cui si trova il gioco
 */
enum STATO_GIOCO{MENU, PLAY, PAUSA, CONTROLS, HIGH_SCORE, GAME_OVER};

/**Struttura contenente i dati del giocatore*/
struct PLAYER_t{
	DIREZ dir;		/**< Stato attuale della direzione di pacman*/
	float movespeed;	/**< Velocità del pacman*/
	int sourcex;		/**< Coordinata x per regione dello sheet di pacman*/
	int sourcey;		/**< Coordinata y per regione dello sheet di pacman*/
	float x;		/**< Coordinata x schermo*/
	float y;		/**< Coordinata y schermo*/
	int stato;		/**< da 1 a tre che indica che immagine è in esecuzione*/
	int vita;		/**< Vite di pacman che possono essere minimo 0 massimo 3*/
	bool potente;		/**< se vera pacman aumenta la velocità e può mangiare i fantasmi*/
	int punteggio;		/**< punteggio attuale*/
	bool mangiato;		/**< se vera pacman è mangiato dai fantasmi */
};

/**Struttura contenente i dati del singolo fantasma*/
struct FANTASMA_t{
	DIREZ dir;		/**< Stato attuale della direzione del fantasma*/
	float movespeed;	/**< Velocità del fantasma*/
	int sourcex;		/**< Coordinata x per regione dello sheet di pacman*/
	int sourcey;		/**< Coordinata y per regione dello sheet di pacman*/
	float x;		/**< Coordinata x schermo*/
	float y;		/**< Coordinata y schermo*/
	bool debole;		/**< Vera quando pacman mangia il pallino grande. Riduce la velocità dei fantasmi e possono essere mangiati*/
	bool mangiato;		/**< Vera quando pacman mangia il fantasma*/
};

/**Struttura contenente i dati dell'audio*/
struct AUDIO_t{
	ALLEGRO_SAMPLE_ID id; /**< Identificatore audio in riproduzione */
	ALLEGRO_SAMPLE *ghost_eaten;
	ALLEGRO_SAMPLE *ghosts_scared;
	ALLEGRO_SAMPLE *pacman_beginning;
	ALLEGRO_SAMPLE *pacman_death;
	ALLEGRO_SAMPLE *pacman_eaten;
	ALLEGRO_SAMPLE *pacman_eatfruit;
	ALLEGRO_SAMPLE *pallet_eaten1;
	ALLEGRO_SAMPLE *pallet_eaten2;
	ALLEGRO_SAMPLE *siren;
};

/**Struttura contenente le bitmap utilizzate*/
struct BITMAP_t{
    ALLEGRO_BITMAP *header_image;
    ALLEGRO_BITMAP *puntino;
    ALLEGRO_BITMAP *autotile;
    ALLEGRO_BITMAP *main_image;
};

/**Struttura contenente i font del gioco*/
struct FONT_t{
    ALLEGRO_FONT *h1;
    ALLEGRO_FONT *h2;
    ALLEGRO_FONT *h3;
    ALLEGRO_FONT *h4;
};
#endif // DATA_STRUCT_
