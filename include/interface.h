/**
 * \file interface.h
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Définition des fonctions relatives à l'interface joueur
 * \version 1.0
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "definition_commun.h"

/**
 * \brief Fonction qui affiche une barre de vie horizontale
 * \author Max Descomps
 * \param x position horizontale de la barre
 * \param y position verticale de la barre
 * \param w largeur de la barre
 * \param h hauteur de la barre
 * \param vie couleur de la barre de vie
 * \param jauge couleur de la barre vide
 */
void RenderHPBar(int x, int y, int w, int h, float pourcent, SDL_Color vie, SDL_Color jauge);
#endif