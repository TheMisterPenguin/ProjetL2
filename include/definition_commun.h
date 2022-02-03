#include "SDL2/SDL.h"
#include "personnage.h"
/** 
 * \file definition_commun.h
 * \brief Contient toutes les définitions communes à tout les fichiers
 * \author Ange Despert 
 * \version 0.1
 * \date 20/01/22
 */

#ifndef __H_DEF_COMMUN__
#define __H_DEF_COMMUN__
extern SDL_Window *fenetre_Principale; /**Pointeur vers fenêtre globale pointant sur la fenêtre principale du programme*/
extern SDL_Renderer *rendu_principal;
extern joueur_t *joueur; /**<Pointeur vers la structure du joueur principal*/

#define FENETRE_LONGUEUR 640
#define FENETRE_LARGEUR 480

typedef struct {
    void (*getKeyboardInput)(SDL_KeyboardEvent *);
    void (*init)(void);
    void (*stop)(void);
    void (*crash)(/*TODO*/);
}t_game;

extern t_game game;

#define SAVE_PATH "~/Games/Bloody Satana/"
#endif