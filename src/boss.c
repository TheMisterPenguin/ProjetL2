#include <boss.h>
#include <affichage.h>
#include <sorts.h>
#include <monstres.h>

/**
 * \file boss.c
 * \author Antoine Bruneau
 * \brief Fichier contenant toutes les fonctions concernant les bosses
 * \version 0.1
 * \date 05/04/2022
 * \copyright Copyright (c) 2022
 */

/**
 * \brief ...
 * \author Bruneau Antoine
 * \todo
 */
void deplacement_boss_aleatoir(boss_t * boss){

}

/**
 * \brief ...
 * \author Bruneau Antoine
 * \todo
 */
boss_t * creer_boss_clone(boss_t * boss, t_aff * texture){
    boss_t * clone = (boss_t*) malloc(sizeof(boss_t));
    clone->type = CLONE;
    clone->pdv = boss->pdv;
    clone->attaque = boss->attaque;
    clone->xp = boss->xp;
    clone->action = (action_boss_1_t) RIEN;
    clone->duree = 0;
    clone->collision.h = boss->collision.h;
    clone->collision.w = boss->collision.w;
    clone->collision.x = texture->frame_anim->x;
    clone->collision.y = texture->frame_anim->y;
    clone->texture = texture;
    return clone;
}

/**
 * \brief   animation lancement d'un sort
 * \author Bruneau Antoine
 * \todo
 */
void affichage_chargement_attaque_boss(t_aff * boule_1, t_aff * boule_2, int phase){
    switch(phase){
        case 1: 
        case 3: next_frame_indice(boule_1, 0, 0); next_frame_indice(boule_2, 0, 0); break;
        case 2: 
        case 4: next_frame_indice(boule_1, 0, 1); next_frame_indice(boule_2, 0, 1); break;
        case 5: 
        case 7: next_frame_indice(boule_1, 1, 0); next_frame_indice(boule_2, 1, 0); break;
        case 6: 
        case 8: next_frame_indice(boule_1, 1, 1); next_frame_indice(boule_2, 1, 1); break;
        case 9: 
        case 11: next_frame_indice(boule_1, 2, 0); next_frame_indice(boule_2, 2, 0); break;
        case 10: 
        case 12: next_frame_indice(boule_1, 2, 1); next_frame_indice(boule_2, 2, 1); break;

        // deplacement boule + scintillement
    }
}

/**
 * \brief ...
 * \author Bruneau Antoine
 * \todo
 */
void affichage_clonage_boss(t_aff * boss, t_aff * clone_1, t_aff * clone_2, int phase){
    int choix = phase%4;

    if(choix == 0){
        text_copier_position(clone_1,boss);
        text_copier_position(clone_1,boss);
    }
    else{
        deplacer_texture_origine(clone_1,30,30);
        deplacer_texture_origine(clone_2,30,30);
    }

    afficher_texture(clone_1, rendu_principal);
    afficher_texture(clone_2, rendu_principal);
}

/**
 * \brief ...
 * \author Bruneau Antoine
 * \todo
 */
void intro_boss(boss_t * boss, boss_t * clone_1, boss_t * clone_2){
    switch(boss->action){
        case SOMMEIL:
            if(distance_joueur(boss->collision) < DISTANCE_AGRO){
                boss->action = CLONAGE;
                boss->duree = 0;
                boss->texture_temp[0] = creer_texture(CHEMIN_BOSS,boss->collision.w, boss->collision.h, boss->collision.x, boss->collision.y, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
                boss->texture_temp[1] = creer_texture(CHEMIN_BOSS,boss->collision.w, boss->collision.h, boss->collision.x, boss->collision.y, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
            }break;
        case CLONAGE:
            (boss->duree)++;
            if(boss->duree == NB_PHASE_CLONAGE){
                boss->action = AVANT_DISPARITION;
                boss->duree = DUREE_AVANT_DISPARITION;
                clone_1 = creer_boss_clone(boss, boss->texture_temp[0]);
                clone_2 = creer_boss_clone(boss, boss->texture_temp[1]);
            }else
                affichage_clonage_boss(boss->texture, boss->texture_temp[0], boss->texture_temp[1], boss->duree);
            break;
    }
    afficher_texture(boss->texture,rendu_principal);
}

/**
 * \brief ...
 * \author Bruneau Antoine
 * \todo
 */
void afficher_boss(boss_t * boss){
    switch(boss->action){
        case AVANT_DISPARITION:
            (boss->duree)--;
            if(boss->duree == 0){
                boss->action = DISPARITION;
                boss->duree = DUREE_DISPARITION;
                boss->cible.
            }else{

            }break;
        case 
    }
    afficher_texture(boss->texture,rendu_principal);
}

/**
 * \brief ...
 * \author Bruneau Antoine
 * \todo
 */
void afficher_bosses(boss_t * boss[3]){

    if(boss[0] == NULL){
        return;
    }

    if(boss[0]->action == CLONAGE || boss[0]->action == SOMMEIL){
        intro_boss_1(boss[0],boss[1],boss[2]);
    }
    else{
        for(int i = 0; i < 3; i++){
            action_boss_1(boss[i]);
        }
    }

    if(boss[0]->action == ATTAQUE){
        t_aff * boule_1 = creer_texture(PATH_SPELL_BOSS,);
        t_aff * boule_2 = creer_texture(PATH_SPELL_BOSS,);
        affichage_chargement_attaque_boss(boule_1, boule_2, &(boss[0].duree));
    }
}