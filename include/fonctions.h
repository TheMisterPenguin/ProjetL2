/**
 * \file fonctions.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Définitions des fonctions d'initialisation
 * \version 0.1
 * \date 02/02/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __H_FONCTION__
#define __H_FONCTION__

#include "map.h"
#include "personnage.h"

/**
 * \fn void init(void);
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */
extern void init(void);

/**
 * \fn void terminate(void);
 * \brief Fonction qui appelle les fonctions pour terminer le programme
 * \author Ange Despert
 */
extern void terminate_init(void);



/**
 * \fn init_event(void)
 * \brief Fonction qui initialise les fonctions liées aux évenements
 */
void init_event(void);

/**
 * \fn void init_sousbuffer(t_map *map, joueur_t * joueur)
 * \brief
 * \author Ange Despert
 * \param map
 * \param joueur Joueur autour duquel se fait la fenêtre d'affichage de la carte
 */
void init_sousbuffer(t_map *map, joueur_t * joueur);
#endif