/**
 * \file boss.h
 * \author Bruneau Antoine (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief 
 * \version 0.1
 * \date 28/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __BOSS_H__
#define __BOSS_H__

#define CHEMIN_BOSS "ressources/sprite/boss.bmp"

#define DUREE_CLONAGE 60

typedef enum {PRINCIPAL,CLONE}type_boss_1_t;
typedef enum {AVANT_ATTAQUE,AVANT_DISPARITION,DISPARITION,APPARITION,DEPLACEMENT,ATTAQUE,MORT,CLONAGE,SOMMEIL,BLESSE}action_boss_1_t;

typedef struct boss_s{
    type_boss_1_t type;
    int pdv;
    int attaque;
    int xp;
    position_t cible;
    action_boss_1_t action;
    int duree;
    SDL_Rect collision;
    t_aff * texture;
    t_aff * texture_temp[2];
}boss_t;

#endif