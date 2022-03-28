/**
 * \file menus.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Définitions relatives à la gestion des menus du jeu
 * \version 1.0
 * \date 27/03/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __MENUS_H__
#define __MENUS_H__

#include "definition_commun.h"

/**
 * Différentes interfaces du jeu
 */
typedef enum{JEU,PAUSE,PRINCIPAL,INVENTAIRE}menus_t;

extern menus_t menus;

//extern void afficher_menu(menus_t * menu);

/**
 * \fn void afficher_menu_pause()
 * \brief Affiche le menu pause et gère les interactions avec l'utilisateur
 */
extern void afficher_menu_pause();

/**
 * \fn void afficher_inventaire()
 * \brief Affiche l'inventaire et gère les interactions avec l'utilisateur
 */
extern void afficher_inventaire();
#endif