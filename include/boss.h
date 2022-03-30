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

typedef enum {PRINCIPAL,CLONE}type_boss_1_t;
typedef enum {RIEN,DISPARITION,APPARITION,DEPLACEMENT,ATTAQUE,MORT,CLONAGE}action_boss_1_t;

typedef struct boss_s{
    type_boss_1_t type;
    int pdv;
    int attaque;
    int xp;
    action_boss_1_t action;
    SDL_Rect collision;
    t_aff * texture;
}boss_t;





#endif