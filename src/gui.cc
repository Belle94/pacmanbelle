/*
 * gui.cc
 *
 *      Author: Belle & Bruce
 */

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <fstream>
//#include <windows.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "data_struct.h"
#include "gui.h"
#include "io.h"
#include "logic.h"

using namespace std;

void draw_screen_menu(const int menu, const FONT_t &f, const BITMAP_t &b)
{
    static float inc_dec;
    static bool b_inc_dec;

    if(b_inc_dec){
        inc_dec += 0.2;
        if(inc_dec > 5){
            inc_dec = 5;
            b_inc_dec = false;
        }
    }
    else{
        inc_dec -= 0.2;
        if(inc_dec < 2){
            inc_dec = 2;
            b_inc_dec = true;
        }

    assert(inc_dec <= 5 && inc_dec >= 2);

    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(f.h1, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *10/100, ALLEGRO_ALIGN_CENTER, "pACMAN gAME");
    al_draw_bitmap(b.header_image, SCREENWIDTH *21/100, SCREENHEIGHT *25/100, 0);
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *55/100, ALLEGRO_ALIGN_CENTER, "sTART gAME");
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *65/100, ALLEGRO_ALIGN_CENTER, "cONTROLS");
    al_draw_text(f.h2, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *75/100, ALLEGRO_ALIGN_CENTER, "hIGH sCORES");
    al_draw_text(f.h4, al_map_rgb(255,255,255), SCREENWIDTH / 2, SCREENHEIGHT *95/100, ALLEGRO_ALIGN_CENTER, "Powered by Belle & Bruce");

    switch (menu)
    {
      case 0:
      break;
      case 1:
            al_draw_filled_circle(SCREENWIDTH *66/100, SCREENHEIGHT *56/100, inc_dec, al_map_rgb(255,255,255));
            al_draw_filled_circle(SCREENWIDTH *34/100, SCREENHEIGHT *56/100, inc_dec, al_map_rgb(255,255,255));
            break;
      case 2:
            al_draw_filled_circle(SCREENWIDTH *66/100, SCREENHEIGHT *66/100, inc_dec, al_map_rgb(255,255,255));
            al_draw_filled_circle(SCREENWIDTH *34/100, SCREENHEIGHT *66/100, inc_dec, al_map_rgb(255,255,255));
      break;
      case 3:
            al_draw_filled_circle(SCREENWIDTH *66/100, SCREENHEIGHT *76/100, inc_dec, al_map_rgb(255,255,255));
            al_draw_filled_circle(SCREENWIDTH *34/100, SCREENHEIGHT *76/100, inc_dec, al_map_rgb(255,255,255));
      break;
    }
    al_flip_display();
}

void draw_pause(const FONT_t &f)
{
    al_draw_text(f.h2, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "gAME pAUSE");
	al_flip_display();
}

void draw_countdown(const FONT_t &f, const BITMAP_t &b, const MAPPA_t &m)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "TRE");
    al_flip_display();
    al_rest(1.4);

    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "DUE");
    al_flip_display();
    al_rest(1.4);

    al_clear_to_color(al_map_rgb(0,0,0));
    draw_path(b,m);
    al_draw_text(f.h5, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "UNO");
    al_flip_display();
    al_rest(1.4);
}


void draw_path(const BITMAP_t &b, const MAPPA_t &m)
{
    static int alpha;
    static bool b_alpha;

    if(b_alpha){
        alpha += 15;
        if(alpha >= 255){
            alpha = 255;
            b_alpha = false;
        }
    }
    else{
        alpha -= 15;
        if(alpha <= 0){
            alpha = 0;
            b_alpha = true;
        }
    }

    assert(alpha < 255 || alpha > 0);

    for (int i=0; i < m.r; i++){
        for (int j = 0; j < m.c; j++){
            switch (m.mappa[i][j]){
                case '0':{
                    ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 32, 0, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 32, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);
                break;
                }
                case 'B':{
                    ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 0, 0, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 0, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);
                break;
                }
                case 'C':{
                    ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 16, 0, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 16, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);
                break;
                }
                case 'D':{
                    ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 48, 0, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 48, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'E':{
                    ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 0, 16, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 0, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'F':{
                ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 16, 16, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 16, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'G':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 32, 16, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 32, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'H':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 48, 16, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 48, 16, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'I':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 0, 32, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 0, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'L':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 16, 32, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 16, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'M':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 32, 32, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 32, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'N':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 48, 32, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 48, 32, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'P':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 0, 48, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 0, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'Q':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 16, 48, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 16, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'R':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 32, 48, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 32, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'S':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 48, 48, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 48, 48, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'J':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 0, 64, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 0, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'K':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 16, 64, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 16, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'W':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 32, 64, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 32, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'X':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 48, 64, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 48, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'Y':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 32, 64, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 32, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 1);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 1);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'A':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 48, 64, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 48, 64, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 2);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 2);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'T':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 0, 80, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 0, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'U':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 16, 80, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 16, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'V':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 32, 80, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 32, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'Z':{ALLEGRO_BITMAP *subBitmap;
                    subBitmap = al_create_sub_bitmap(b.autotile, 48, 80, BLOCKSIZE,BLOCKSIZE);
                    al_draw_bitmap_region(b.autotile, 48, 80, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_draw_tinted_bitmap(subBitmap, al_map_rgba(255, 255, 255, alpha), BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                    al_destroy_bitmap(subBitmap);

                break;
                }
                case 'O':
                    al_draw_bitmap_region(b.autotile, 32, 0, BLOCKSIZE, BLOCKSIZE, BLOCKSIZE * j + OFFSETX, BLOCKSIZE * i + OFFSETY, 0);
                break;
            }
        }
    }
}

void draw_pacman(PLAYER_t& pg)
{
    pg.sourcex += al_get_bitmap_width(pg.img)/3;
    if(pg.sourcex >= al_get_bitmap_width(pg.img))
        pg.sourcex = 0;

    pg.sourcey = pg.dir;
    if(pg.dir == FERMO){
        pg.sourcey = pg.precdir;
        pg.sourcex = 0;
    }

    al_draw_bitmap_region(pg.img, pg.sourcex
                          , pg.sourcey * al_get_bitmap_height(pg.img)/4
                          , al_get_bitmap_width(pg.img)/3
                          , al_get_bitmap_height(pg.img)/4
                          , pg.x, pg.y, 0);
}

void draw_fant_fuga(const BITMAP_t &b, FANTASMA_t& f, int fine_fuga)
{
    f.sourcex += al_get_bitmap_width(b.fant_fuga)/2;
    if(f.sourcex >= al_get_bitmap_width(b.fant_fuga))
        f.sourcex = 0;
    f.sourcey = fine_fuga;
    al_draw_bitmap_region(b.fant_fuga, f.sourcex
                          , f.sourcey * al_get_bitmap_height(b.fant_fuga)/2
                          , al_get_bitmap_width(b.fant_fuga)/2
                          , al_get_bitmap_height(b.fant_fuga)/2
                          , f.x, f.y, 0);
}

void draw_fant_mangiato(const BITMAP_t &b, FANTASMA_t& f)
{
    f.sourcex = 0;
    f.sourcey = f.dir;
    al_draw_bitmap_region(b.fant_mangiato, f.sourcex
                          , f.sourcey * al_get_bitmap_height(b.fant_mangiato)/4
                          , al_get_bitmap_width(b.fant_mangiato)
                          , al_get_bitmap_height(b.fant_mangiato)/4
                          , f.x, f.y, 0);
}

void draw_fantasma(FANTASMA_t& f)
{
    f.sourcex += al_get_bitmap_width(f.img)/2;
    if(f.sourcex >= al_get_bitmap_width(f.img))
        f.sourcex = 0;
    f.sourcey = f.dir;
    al_draw_bitmap_region(f.img, f.sourcex
                          , f.sourcey * al_get_bitmap_height(f.img)/4
                          , al_get_bitmap_width(f.img)/2
                          , al_get_bitmap_height(f.img)/4
                          , f.x, f.y, 0);
}

void draw_frutta(ALLEGRO_TIMER *t, BITMAP_t b, int liv, PLAYER_t &pg, AUDIO_t &a){
    static bool mangiata = false;



    if(al_get_timer_count(t) >= 30 && al_get_timer_count(t) <= 42){

        float dist = 3;
        float px = pg.x + dist;
        float py = pg.y + dist;
        float ph = pg.y + BLOCKSIZE -dist;
        float pw = pg.x + BLOCKSIZE -dist;
        float frx = (13 * BLOCKSIZE + OFFSETX) + dist;
        float fry = (17 * BLOCKSIZE + OFFSETY) + dist;
        float frh = al_get_bitmap_height(b.frutta) -dist;
        float frw = al_get_bitmap_width(b.frutta)/8 -dist;


        if (((frx>=px && frx<=pw) || (frw>=px && frw<=pw))
            && ( (fry>=py && fry<=ph) || (frh>=py && frh<=ph) )
            && !mangiata){
            al_play_sample(a.pacman_eatfruit,1.0,0.0, 1, ALLEGRO_PLAYMODE_ONCE , 0);
            if((pg.punteggio <= 10000 && pg.punteggio + 100*liv > 10000) ||
               (pg.punteggio <= 20000 && pg.punteggio + 100*liv  > 20000) ||
               (pg.punteggio <= 40000 && pg.punteggio + 100*liv  > 40000)){
                al_play_sample(a.pacman_extrapac, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
                pg.vita++;
            }
            pg.punteggio += 100*liv;
            mangiata = true;
        }

        if(!mangiata){
            if(liv <= 8)
                al_draw_bitmap_region(b.frutta,(liv-1)*al_get_bitmap_width(b.frutta)/8, 0
                                        , al_get_bitmap_width(b.frutta)/8
                                        , al_get_bitmap_height(b.frutta)
                                        , 13 * BLOCKSIZE + OFFSETX, 17 * BLOCKSIZE + OFFSETY, 0);
            else
                al_draw_bitmap_region(b.frutta, 8 * al_get_bitmap_width(b.frutta)/8, 0
                                        , al_get_bitmap_width(b.frutta)/8
                                        , al_get_bitmap_height(b.frutta)
                                        , 13 * BLOCKSIZE + OFFSETX, 17 * BLOCKSIZE + OFFSETY, 0);
        }
    }
    else
        mangiata = false;
}

void draw_gameover(const FONT_t &f, const BITMAP_t &b, bool nuovo_record, int punteggio)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(f.h1, al_map_rgb(255,15,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "**** g a m e  o v e r ****");
    al_draw_text(f.h5, al_map_rgb(255,255,255), SCREENWIDTH / 2, (SCREENHEIGHT *50/100)+200, ALLEGRO_ALIGN_CENTER, "Press Enter");
    if(nuovo_record)
        al_draw_text(f.h5, al_map_rgb(255,255,255), SCREENWIDTH / 2, (SCREENHEIGHT *50/100)-200, ALLEGRO_ALIGN_CENTER, "Nuovo Record");
    al_draw_textf(f.h5, al_map_rgb(255,15,15), SCREENWIDTH / 2, (SCREENHEIGHT *50/100)+100, ALLEGRO_ALIGN_CENTER, "Punteggio: %d", punteggio);
    al_flip_display();
}

void draw_win(const FONT_t &f, const BITMAP_t &b, bool nuovo_record)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_text(f.h1, al_map_rgb(15,255,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER, "**** v i c t o r y ****");
    al_draw_text(f.h5, al_map_rgb(255,255,255), SCREENWIDTH / 2, (SCREENHEIGHT *50/100)+200, ALLEGRO_ALIGN_CENTER, "Press Enter");
    if(nuovo_record)
        al_draw_text(f.h5, al_map_rgb(255,255,255), SCREENWIDTH / 2, (SCREENHEIGHT *50/100)-200, ALLEGRO_ALIGN_CENTER, "Nuovo Record");
    al_flip_display();
}

void draw_controls(const FONT_t &f, const BITMAP_t &b)
{
    int size = 48;
    int posx, posy;

    posx = OFFSETX;
    posy = OFFSETY + 3*size;

    //up
    al_draw_bitmap_region(b.controls, size, size, size, size, posx + size/2, posy - size +10, 0);
    //down
    al_draw_bitmap_region(b.controls, 0, size, size, size, posx +size/2 -1, posy + size -10, 0);
    //left
    al_draw_bitmap_region(b.controls, 0, 0, size, size, posx -10, posy, 0);
    //right
    al_draw_bitmap_region(b.controls, size, 0, size, size, posx + size +10, posy, 0);

    posy = OFFSETY + SCREENHEIGHT * 0.20;
    al_draw_text(f.h5, al_map_rgb(105,253,105), SCREENWIDTH /2 - SCREENWIDTH *0.05 , posy , ALLEGRO_ALIGN_LEFT, "Utilizza i tasti");
    al_draw_text(f.h5, al_map_rgb(105,253,105), SCREENWIDTH /2 - SCREENWIDTH *0.05, posy +22 , ALLEGRO_ALIGN_LEFT, "direzionali");
    al_draw_text(f.h5, al_map_rgb(105,253,105), SCREENWIDTH /2 - SCREENWIDTH *0.05, posy +42 , ALLEGRO_ALIGN_LEFT, "per muoverti");
    al_draw_text(f.h5, al_map_rgb(105,253,105), SCREENWIDTH /2 - SCREENWIDTH *0.05, posy +82, ALLEGRO_ALIGN_LEFT, "Spazio per la Pausa");

    al_draw_text(f.h5, al_map_rgb(225,255,225), OFFSETX, OFFSETY, ALLEGRO_ALIGN_LEFT, "Premere esc per tornare al menu");

    al_flip_display();

}


void draw_high_score(const FONT_t &f, int record)
{
    al_draw_textf(f.h5, al_map_rgb(15,255,15), SCREENWIDTH / 2, SCREENHEIGHT *50/100, ALLEGRO_ALIGN_CENTER,"%d",record);

    al_draw_text(f.h5, al_map_rgb(225,255,225), OFFSETX, OFFSETY, ALLEGRO_ALIGN_LEFT, "Premere esc per tornare al menu");

}
