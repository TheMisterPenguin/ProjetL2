/**
 * \file texture_struct.h
 * \author Despet Ange (Ange.Despert.Etu@univ-lemans.fr) Descomps Max (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant la structure texture
 * \version 0.1
 * \date 03/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */
#include "definition_commun.h"

#ifndef __TEXTURE_STRUCT_H__
#define __TEXTURE_STRUCT_H__

/**
 * \struct s_aff
 * \brief Structure qui permet l'affichage d'une texture à l'écran de manière précise
 * 
 * 
 */
typedef struct s_aff{
    SDL_Texture *texture; /**<Texture utilisée*/
    SDL_Rect *frame_anim; /**<Désigne la zone de la texture à afficher*/
    SDL_Rect *aff_fenetre; /**<Désigne l'emplacement et la taille de l'objet à l'écran */
    int width;
    int height;
}t_aff;

#endif