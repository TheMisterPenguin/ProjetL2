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

/**
 * \brief L'énumération des types de sort
 * 
 * Cela permet de différencier les sorts pour réaliser des actions particulières en fonction de ce type.
 */
typedef enum
{
    SP_WITCHER, /**<sort du Witcher*/
    SP_BOSS_BALL, /**< le sort "boule" du boss*/
    SP_BOSS_GROUP, /**< le sort "groupé" du boss*/
    SP_BOSS_SPLIT /**< le sort "split" qui est créé à partir du sort "groupé" du boss*/
}type_sort_t;

/**
 * \struct sort_t
 * \brief Structure contenant les propriétées d'un sort en jeu
 * \author Bruneau Antoine
 */

typedef struct sort_s {
    type_sort_t type;       /**<type de sort*/
    int degat;              /**<degat du sort*/
    SDL_Rect collision;      /**<hitbox du sort*/
    t_aff * texture;        /**<texture du sort*/
}sort_t;

/**
 * \struct struct base_sort
 * \brief Structure contenant les propiétées d'origine des sorts (modèles de sort)
 * \author Bruneau Antoine
 */
typedef struct base_sort_s
{
    type_sort_t type;   /**<type de sort*/
    int degat;          /**<degat du sort*/
    SDL_Rect collision; /**<hitbox du sort*/
}base_sort_t;

extern base_sort_t liste_base_sort[3]; /* le tableau des différents sorts (modèles de sort) */

/**
 * \fn void detruire_sort_cb(void * sort);
 * \brief Fonction de "call back" qui détruit une structure sort
 * \author Bruneau Antoine
 * \param sort le sort à détruire
 */
extern void detruire_sort_cb(void * sort);

/**
 * \fn void * ajouter_sort_cb(void * sort);
 * \brief Fonction de "call back" qui retourne une structure sort
 * \author Bruneau Antoine
 * \param sort le sort à retourner
 * \return void* un pointeur générique sur une structure sort
 */
extern void * ajouter_sort_cb(void * sort);

/**
 * \fn void init_liste_base_sort(liste_base_monstres_t * liste_base_monstres);
 * \brief Fonction qui initialise le tableau de modèles de sort
 * \author Bruneau Antoine
 * \param liste_base_monstres le tableau de modèles de sort
 */
extern void init_liste_base_sort(liste_base_monstres_t * liste_base_monstres);

/**
 * \fn void creer_sort_monstre(monstre_t * monstre, joueur_t * joueur);
 * \brief Fonction qui creer un sort orienté vers le joueur
 * \author Bruneau Antoine
 * \param monstre le monstre qui à créé le sort
 * \param joueur le joueur qui est ciblé par le sort
 */
extern void creer_sort_monstre(monstre_t * monstre, joueur_t * joueur);

/**
 * \fn void action_sort(sort_t * sort, joueur_t * joueur);
 * \brief Fonction qui gère le déplacement du sort sur la map
 * \author Bruneau Antoine
 * \param sort le sort à déplacer
 * \param joueur les joueurs qui peuvent être touchés par le sort
 */
extern void action_sort(sort_t * sort, joueur_t * joueur);

/**
 * \fn void orienter_sort_vers_joueur(monstre_t * monstre, sort_t * sort, joueur_t * joueur);
 * \brief Fonction qui met à jour la texture sort de façon à ce qu'elle soit orienté vers le joueur
 * \author Bruneau Antoine
 * \param monstre le monstre qui lance le sort
 * \param sort le sort à orienter
 * \param joueur le joueur cible
 */
extern void orienter_sort_vers_joueur(monstre_t * monstre, sort_t * sort, joueur_t * joueur);

#endif