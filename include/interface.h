/**
 * \file interface.h
 * \author Descomps Max
 * \brief 
 * \version 1.0
 * \date 26/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "definition_commun.h"

/**
 * \fn void RenderHPBar(int x, int y, int w, int h, float pourcent, SDL_Color vie, SDL_Color jauge)
 * \brief Fonction qui affiche une barre de vie horizontale
 * \param x position horizontale de la barre
 * \param y position verticale de la barre
 * \param w largeur de la barre
 * \param h hauteur de la barre
 * \param vie couleur de la barre de vie
 * \param jauge couleur de la barre vide
 * 
 */
void RenderHPBar(int x, int y, int w, int h, float pourcent, SDL_Color vie, SDL_Color jauge);
#endif