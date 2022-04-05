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

extern SDL_GameController *manette; /**<La manette du J1*/

/**
 * \brief Fonction qui gère les événements pendant l'affichage de l'introduction.
 * \author Ange Despert
 * 
 * Cette fonction permet de passer l'introduction avec une touche mais gère encore les évenement tels que `SDL_QUIT`.
 * 
 * \return Si l'on doit passer le logo
 */
extern _Bool logo_passer(void); 

/**
 * \fn void jeu_event(joueur_t ** joueurs, char * f_src_obj)
 * \brief Fonction qui gère les événements
 * \author Despert Ange
 * \param joueur Joueurs pouvant provoquer l'événement
 * \param f_src_obj Fichier source des objets du jeu utile à certains événements
 */
extern void jeu_event(joueur_t ** joueurs, char * f_src_obj);

/**
 * \brief Fonction qui gère les événements de la manette.
 * \author Ange Despert
 * 
 * \param joueurs Les joueurs existants
 */
extern void jeu_event_manette(joueur_t **joueurs);
#endif