#include "SDL2/SDL.h"
/** 
 * \file definition_commun.h
 * \brief Contient toutes les définitions communes à tout les fichiers
 * \author Ange Despert 
 * \version 0.1
 * \date 20/01/22
 */

extern SDL_Window *fenetre_Principale; /**
 * \brief Pointeur vers fenêtre global pointant sur la fenêtre principal du programme
 * \author Ange Despert
 */
#ifndef FENETRE_LONGUEUR
    #define FENETRE_LONGUER 640
#endif
#ifndef FENETRE_LARGEUR
    #define FENETRE_LARGEUR 480
#endif