

/** 
 * \file definition_commun.h
 * \brief Contient toutes les définitions communes à tout les fichiers
 * \author Ange Despert 
 * \version 0.1
 * \date 20/01/22
 */

#ifndef __H_DEF_COMMUN__
#define __H_DEF_COMMUN__

#include "SDL2/SDL.h"

#define FENETRE_LONGUEUR 1920
#define FENETRE_LARGEUR 1078

typedef unsigned char byte;
typedef int err_t;
typedef struct point {int x,y;}point;
typedef enum
{
    NORD,
    EST,
    SUD,
    OUEST
} t_direction;

#define bool _Bool
#define vrai 1
#define faux 0

extern SDL_Window *fenetre_Principale; /**Pointeur vers fenêtre globale pointant sur la fenêtre principale du programme*/
extern SDL_Renderer *rendu_principal;
extern long int compteur; /*compteur utilisé pour gérer la vitesse d'affichage (fps)*/
extern bool running;
#define SAVE_PATH "~/Games/Bloody Sanada/"
#endif