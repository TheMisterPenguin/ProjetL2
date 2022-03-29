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
#include "listes.h"

#define TAILLE_CASE 16

typedef struct s_aff t_aff; //!< \brief Structure de texture

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
typedef struct {
    t_aff * text_map; /**< La texture de la map */
    unsigned int width, height; /**< La largeur et la hauteur de la map */
    list *liste_monstres; /*< La liste des monstres de la map */
    int unite_dep_x; /**< L'unité de déplacement en x */
    int unite_dep_y; /**< L'unité de déplacement en y */
    t_aff * text_sol; /**< La texture du sol */
    unsigned int taille_case; /**< La taille d'une case */
    unsigned int cases_x; /**< Le nombre de cases affichées en x */
    unsigned int cases_y; /**< Le nombre de cases affichées en y */
}t_map;

extern t_map *map; /**< La map courante */

/**
 * \brief Fonction qui charge le contenu du fichier dont le nom est donné en paramètre dans un buffer de caractères
 *
 * \param nom_map Le nom du fichier map à charger
 * \return Un buffer de caractères contenant l'intégralité du fichier
 */
char *charger_f_map(const char *const nom_map);

/**
 * \brief Fonction qui récupère les informations stockées dans le buffer en entrée.
 * 
 * \param buffer Le buffeur qui contient les informations
 * \return Une map initialisée avec toutes les informations dedans;
 */
t_map *charger_s_map(char * buffer);

/**
 * \brief Fonction qui renvoie la texture de la map
 * 
 * \param map La map dont on veut la texture
 * \return La texture de la map
 */
t_aff *texture_map(const t_map *map);

#endif