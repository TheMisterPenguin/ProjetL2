#include "commun.h"

#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

typedef struct {
    SDL_Texture *texture; /**<Texture utilisée*/
    SDL_Rect *frame_anim; /**<Désigne la zone de la texture à afficher*/
    SDL_Rect *aff_fenetre; /**<Désigne l'emplacement et la taille de l'objet à l'écran */
}t_aff;

#define N_T_PLAYER_WALK "ressources/sprite/main_caracter.bmp"
#endif