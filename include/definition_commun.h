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

#include "code_erreur.h"

#ifdef DEBUG
    #define DEBUG_TP
    #define _DEBUG_COLLISION
    #define _DEBUG_MOUVEMENT
#endif

extern unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;
typedef unsigned char byte;
typedef struct point {int x,y;}point;

/**
 * \struct struct t_direction_1
 * \brief Structure de quatre points cardinaux
 */
typedef enum
{
    NORD_1, /**<Point cardinal nord*/
    EST_1, /**<Point cardinal est*/
    SUD_1, /**<Point cardinal sud*/
    OUEST_1, /**<Point cardinal ouest*/
} t_direction_1;

/**
 * \struct struct t_direction_2
 * \brief Structure de huit points cardinaux
 */
typedef enum
{
    NORD_2, /**<Point cardinal nord*/
    NORD_EST_2, /**<Point cardinal nord-est*/
    EST_2, /**<Point cardinal est*/
    SUD_EST_2, /**<Point cardinal sud-est*/
    SUD_2, /**<Point cardinal sud*/
    SUD_OUEST_2, /**<Point cardinal sud-ouest*/
    OUEST_2, /**<Point cardinal ouest*/
    NORD_OUEST_2 /**<Point cardinal nord-ouest*/
} t_direction_2;

#define bool _Bool
#define vrai 1
#define faux 0

extern SDL_Window *fenetre_Principale; /**Pointeur sur la fenêtre principale du programme*/
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