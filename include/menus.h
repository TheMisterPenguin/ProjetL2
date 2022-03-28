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

typedef enum{JEU,PAUSE,PRINCIPAL,INVENTAIRE}menus_t;

extern menus_t menus;

//extern void afficher_menu(menus_t * menu);

extern void afficher_menu_pause();
extern void afficher_inventaire();
#endif