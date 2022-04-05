/**
 * \file sorts.h
 * \author Bruneau Antoine (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les définitions concernant les sorts
 * \version 0.1
 * \date 28/03/2022
 * 
 * \copyright Copyright (c) 2022
 *  
 */


#ifndef __SORTS_H__
#define __SORTS_H__

#include "affichage.h"
#include "monstres.h"

#define PATH_SPELL_BOSS "ressources/sprite/spell_boss.bmp"
#define PATH_SPELL_WITCHER "ressources/sprite/spell_witcher.bmp"
#define CONVERTIR_RADIANT_DEGREE 57.3
typedef enum {SP_WITCHER,SP_BOSS_BALL,SP_BOSS_GROUP,SP_BOSS_SPLIT}type_sort_t;
typedef enum {LANCER, PARER}statut_sort_t;


/**
 * \struct sort_t
 * \brief Structure contenant les propriétées d'un sort en jeu
 * \author Bruneau Antoine
 */

typedef struct sort_s {
    type_sort_t type;       /**<type de sort*/
    int degat;              /**<degat du sort*/
    statut_sort_t statut;   /**<statut du sort*/
    SDL_Rect collision;      /**<hitbox du sort*/
    t_aff * texture;        /**<texture du sort*/
}sort_t;

/**
 * \struct base_sort_t
 * \brief Structure contenant les propiétées d'origine des sorts
 * \author Bruneau Antoine
 */
typedef struct base_sort_s
{
    type_sort_t type;   /**<type de sort*/
    int degat;          /**<degat du sort*/
    SDL_Rect collision; /**<hitbox du sort*/
}base_sort_t;


extern base_sort_t liste_base_sort[3];

void detruire_sort_cb(void * sort);
void * ajouter_sort_cb(void * sort);
void init_liste_base_sort(liste_base_monstres_t * liste_base_monstres);
void creer_sort_monstre(monstre_t * monstre, joueur_t * joueur);
void action_sort(sort_t * sort, joueur_t * joueur);
void orienter_sort_vers_joueur(monstre_t * monstre, sort_t * sort, joueur_t * joueur);
#endif