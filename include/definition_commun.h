#include "SDL2/SDL.h"
/** 
 * \file definition_commun.h
 * \brief Contient toutes les définitions communes à tout les fichiers
 * \author Ange Despert 
 * \version 0.1
 * \date 20/01/22
 */

#ifndef H_DEF_COMMUN
#define H_DEF_COMMUN
extern SDL_Window *fenetre_Principale; /**Pointeur vers fenêtre global pointant sur la fenêtre principal du programme*/
extern SDL_Renderer *rendu_principal;
#define FENETRE_LONGUEUR 640

#define FENETRE_LARGEUR 480
typedef struct {
    void (*getKeyboardInput)(SDL_KeyboardEvent *);
    void (*init)(void);
    void (*stop)(void);
    void (*crash)(/*TODO*/);
}t_game;

extern t_game game;
#endif