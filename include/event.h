/**
 * \file event.h
 * \brief Définitions relatives aux événements
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \version 0.1
 * \date 03/02/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __EVENT_H__
#define __EVENT_H__

#include "SDL2/SDL_events.h"
#include "personnage.h"

#define TOUCHE_HAUT SDLK_z
#define TOUCHE_BAS SDLK_s
#define TOUCHE_GAUCHE SDLK_q
#define TOUCHE_DROITE SDLK_d
#define TOUCHE_TAB SDLK_TAB
#define TOUCHE_ECHAP SDLK_ESCAPE
#define TOUCHE_CONSOMMABLE SDLK_e

extern _Bool logo_passer(void);

/**
 * \fn void jeu_event(joueur_t * joueur)
 * \brief Fonction qui gère les événements
 * \author Despert Ange
 * \param joueur Le joueur provoquant l'événement
 */
extern void jeu_event(joueur_t * joueur);


#endif