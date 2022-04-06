/** 
 * \file definition_commun.h
 * \brief Contient toutes les définitions communes à tout les fichiers
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \version 1.0
 * \date 05/04/22
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

extern unsigned int FENETRE_LONGUEUR; /**<La longueur de la fenêtre obtenue par requête SDL*/
extern unsigned int FENETRE_LARGEUR; /**<La largeur de la fenêtre obtenue par requête SDL*/
typedef unsigned char byte; /**<Type servant pour des triggers faisant la taille d'un octet*/


typedef struct point {int x,y;}point; /**<Un point*/

/**
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

#define bool _Bool /**<Définition du type booléen */
#define vrai 1 /**<Valeur vrai*/
#define faux 0 /**<Valeur faux*/

extern SDL_Window *fenetre_Principale; /**<Pointeur sur la fenêtre principale du programme*/
extern SDL_Renderer *rendu_principal; /**<Le rendu principal du programme*/
extern bool running; /**<Booléen qui permet de savoir si le programme doit s'arrêter*/


#define SAVE_PATH "Bloody_Sanada"/**<L'emplacement de la sauvegarde */

/* Fonctions indispensables */

/**
 * \fn void fermer_programme(int code_erreur);
 * \brief Fonction qui appelle les fonctions pour terminer le programme
 * \author Ange Despert
 */
void fermer_programme(int code_erreur);

#endif