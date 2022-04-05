/**
 * \file boss.h
 * \author Bruneau Antoine (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant les définitions et les fonctions liées au module boss
 * \version 0.1
 * \date 28/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __BOSS_H__
#define __BOSS_H__

#include <definition_commun.h>

#define CHEMIN_BOSS "ressources/sprite/boss.bmp"
#define DUREE_CLONAGE 60

/**
 * \brief Le type du boss
 */
typedef enum 
{
    PRINCIPAL, /**<le boss*/
    CLONE  /**<un clone du boss*/
}type_boss_1_t;

/**
 * \brief L'énumération des actions(phases) du boss
 * 
 * Cela permet de savoir dans quelle état est le boss
 */
typedef enum
{   
    AVANT_ATTAQUE, /**<attante avant l'attaque*/
    AVANT_DISPARITION, /**<attente avant disparition */
    DISPARITION, /**< disparition du boss*/
    APPARITION, /**< apparition du boss*/
    DEPLACEMENT, /**<deplacement du boss*/
    ATTAQUE, /**<attaque du boss*/
    MORT,   /**<mort du boss*/
    CLONAGE, /**<clonage du boss*/
    SOMMEIL, /**<attent l'apparition du joueur*/
    BLESSE /**<boss subit une attaque*/
}action_boss_1_t;

/**
 * \struct monstre_t
 * \brief Structure contenant les propriétées du boss
 * \author Bruneau Antoine
 */
typedef struct boss_s{
    type_boss_1_t type; /**<type de boss*/
    int pdv; /**<pdv du bosse*/
    int attaque; /**<les dégats qu'inflige le boss*/
    int xp; /**<l'xp que rapporte le boss*/
    point cible; /**<l'endroit où le boss réapparaît*/
    action_boss_1_t action; /**<l'action actuelle du boss*/
    int duree; /**<duree de l'action*/
    SDL_Rect collision; /**< zone de collision du boss*/
    t_aff * texture; /**<texture du boss*/
    t_aff * texture_temp[2]; /**texture des 2 sorts que contrôle le boss lors de l'animation de l'attaque */
}boss_t;

#endif