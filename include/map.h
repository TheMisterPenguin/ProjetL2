/**
 * \file map.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Définitions des fonctions de gestion de la map
 * \version 1.0
 * \date 27/03/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __MAP_H__
#define __MAP_H__ 

#include "definition_commun.h"
#include "monstres.h"
#include "listes.h"
#include "personnage.h"

#define TAILLE_CASE 16

typedef struct s_aff t_aff; //!< \brief Structure de texture
typedef struct liste_base_monstres_s liste_base_monstres_t;

/**
 * \brief Structure représentant une zone de tp.
 *      
 * Il s'agit ici d'identifier une zone de colision ou le joueur sera téléporté
 * Pour cela, on doit également savoir dans quelle map on va attérir mais également à quel endroit.
 * \author Ange Despert
 */
typedef struct {
    point p1,p2; /**< Rectangle représentant la zone de tp */
    unsigned int id_map; /**< l'id de la map de destination */
    point dest; /**< Les coordonnées du point d'apparition sur la map */
}zone_tp;

/**
 * \brief Structure représentant une map
 * \author Ange Despert
*/
typedef struct t_map{
    unsigned int id_map;
    t_aff * text_map; /**< La texture de la map */
    t_aff *text_sol;  /**< La texture du sol */
    unsigned int width, height; /**< La largeur et la hauteur de la map */
    unsigned int taille_case; /**< La taille d'une case */
    unsigned int cases_x; /**< Le nombre de cases affichées en x */
    unsigned int cases_y; /**< Le nombre de cases affichées en y */
    list *liste_monstres; /*< La liste des monstres de la map */
    list *liste_sorts;    /*< La liste des sorts de la map */
    list *liste_collisions; /*< La liste de toutes les les collisions */
}t_map;

extern t_map *map; /**< La map courante */

/**
 * \brief Fonction qui récupère les informations stockées dans le buffer en entrée.
 * \param liste_base_monstres Les montres à placer sur la map
 * \param buffer Le buffeur qui contient les informations
 * \return Une map initialisée avec toutes les informations dedans;
 */
t_map *charger_map(const char *const nom_map);


/**
 * \brief Fonction qui renvoie la texture de la map
 * 
 * \param map La map dont on veut la texture
 * \return La texture de la map
 */
t_aff *texture_map(const t_map *map);

void transition(t_map **actuelle, const char *const nom_map, joueur_t **joueurs, unsigned short int nb_joueurs);

void tp_joueurs(t_map *map, unsigned int x, unsigned int y, joueur_t **joueurs, unsigned short int nb_joueurs);
#endif