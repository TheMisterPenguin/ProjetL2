/**
 * \file event.h
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief 
 * \version 0.1
 * \date 03/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __EVENT_H__
#define __EVENT_H__
#include "SDL2/SDL_events.h"
#define TOUCHE_HAUT SDLK_z
#define TOUCHE_BAS SDLK_s
#define TOUCHE_GAUCHE SDLK_q
#define TOUCHE_DROITE SDLK_d

#define DUREE_ATTAQUE_OU_CHARGEE 4
#define DUREE_ATTAQUE 6
#define DUREE_ATTAQUE_CHARGEE 10
#define DUREE_BLOQUER 3

extern bool logo_passer(void);

/**
 * \fn void jeu_event(void)
 * \brief Fonction qui gère les événements
 * \author Despert Ange
 *
 */
extern void jeu_event(void);


#endif