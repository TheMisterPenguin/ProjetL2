/** 
 * \file definition_commun.h
 * \brief Contient toutes les définitions communes à tout les fichiers
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \version 0.1
 * \date 20/01/22
 * \copyright Copyright (c) 2022
 */

#ifndef __H_DEF_COMMUN__
#define __H_DEF_COMMUN__

/** \cond */
#include "SDL2/SDL.h"
/** \endcond */

#include "code_erreur.h"

extern unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;
typedef unsigned char byte;
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
extern SDL_Window *fenetre_sous_rendu;
extern SDL_Renderer *sous_rendu;
extern bool running;
extern SDL_Rect * hors_hitbox;

#ifndef _WIN32
#define SAVE_PATH "Bloody_Sanada"
#else
#define SAVE_PATH "Bloody_Sanada"
#endif

/* Fonctions indispensables */

/**
 * \fn void fermer_programme(int code_erreur);
 * \brief Fonction qui appelle les fonctions pour terminer le programme
 * \author Ange Despert
 */
void fermer_programme(int code_erreur);

#endif