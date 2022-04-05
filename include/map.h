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
#include "affichage.h"
#include "listes.h"
#include "personnage.h"

#define TAILLE_CASE 16

typedef struct s_aff t_aff; //!< \brief Structure de texture
typedef struct joueur_s joueur_t;
typedef struct liste_base_monstres_s liste_base_monstres_t;

/**
 * \brief Structure représentant une zone de tp.
 *      
 * Il s'agit ici d'identifier une zone de colision ou le joueur sera téléporté
 * Pour cela, on doit également savoir dans quelle map on va attérir mais également à quel endroit.
 * \author Ange Despert
 */
typedef struct {
    SDL_Rect zone; /**< Rectangle représentant la zone de tp */
    unsigned int id_map; /**< l'id de la map de destination */
    SDL_Point dest; /**< Les coordonnées du point d'apparition sur la map */
}zone_tp;

/**
 * \brief Structure représentant une map
 * 
 * Cette structure doit permettre de stocker toutes les informations liées à la map. \n
 * Pour cela, On va stocké sous forme de listes toutes les \ref s_map.liste_collisions "zones de collisions", \ref s_map.liste_sorts "les sorts", \ref s_map.liste_monstres "les monstres", \ref s_map.liste_coffres "les coffres" et enfin \ref s_map.liste_zone_tp "les zones de tp". \n
 * 
 * On retient également des informations importantes comme des textures : \ref s_map.text_sol "la texture de fond", \ref s_map.texture_superposition "une texture à supperposer" et enfin \ref s_map.text_map "la map avec toutes les entitées".
 * \authors Ange Despert Antoine Bruneau Descomps Max
*/
typedef struct s_map{
    unsigned int id_map;
    t_aff * text_map; /**< La texture de la map */
    t_aff *text_sol;  /**< La texture du sol */
    t_aff *texture_superposition; /**<La texture à supperposer devant le personnage */
    unsigned int width, height; /**< La largeur et la hauteur de la map */
    unsigned int taille_case; /**< La taille d'une case */
    unsigned int cases_x; /**< Le nombre de cases affichées en x */
    unsigned int cases_y; /**< Le nombre de cases affichées en y */
    list *liste_monstres; /**< La liste des monstres de la map */
    list *liste_sorts;    /**< La liste des sorts de la map */
    list *liste_collisions; /**< La liste de toutes les les collisions */
    list *liste_coffres; /**< La liste de tous les coffres */
    list *liste_zone_tp; /**<La liste des points de téléportation */
}t_map;

extern t_map *map; /**< La map courante */

/**
 * \brief Fonction qui récupère les informations stockées dans le buffer en entrée.
 * \param liste_base_monstres Les montres à placer sur la map
 * \param liste_base_coffres Les coffres à placer sur la map
 * \param buffer Le buffeur qui contient les informations
 * \return Une map initialisée avec toutes les informations dedans;
 */
t_map *charger_map(const char *const nom_map);

/**
 * \fn void init_sousbuffer(t_map *map, joueur_t * joueur)
 * \brief
 * \author Ange Despert
 * \param map
 * \param joueur Joueur autour duquel se fait la fenêtre d'affichage de la carte
 */
void init_sousbuffer(t_map *map, joueur_t *joueur);

/**
 * \brief Fonction qui renvoie la texture de la map
 * 
 * \param map La map dont on veut la texture
 * \return La texture de la map
 */
t_aff *texture_map(const t_map *map);

void transition(t_map **actuelle, unsigned int num_map, joueur_t **joueurs, unsigned short int nb_joueurs, unsigned int new_x, unsigned int new_y);

void tp_joueurs(t_map *map, unsigned int x, unsigned int y, joueur_t **joueurs, unsigned short int nb_joueurs);

void detruire_map(t_map **map);

#ifdef DEBUG_TP
    void afficher_zone_tp(zone_tp *z);

#endif

#endif