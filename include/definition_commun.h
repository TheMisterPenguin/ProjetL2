#include "SDL2/SDL.h"

/** 
 * \file definition_commun.h
 * \brief Contient toutes les définitions communes à tout les fichiers
 * \author Ange Despert 
 * \version 0.1
 * \date 20/01/22
 */

#ifndef __H_DEF_COMMUN__
#define __H_DEF_COMMUN__

#define FENETRE_LONGUEUR 1920
#define FENETRE_LARGEUR 1078

typedef unsigned char byte;
typedef int err_t;
typedef struct point {int x,y;}point;

#define bool _Bool
#define vrai 1
#define faux 0

extern SDL_Window *fenetre_Principale; /**Pointeur vers fenêtre globale pointant sur la fenêtre principale du programme*/
extern SDL_Renderer *rendu_principal;
extern bool running;
#define SAVE_PATH "~/Games/Bloody Satana/"
#endif