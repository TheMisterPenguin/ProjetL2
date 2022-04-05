/**
 * \file map.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Définitions des fonctions de gestion de la map
 * \version 1.0
 * \date 05/04/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __MAP_H__
#define __MAP_H__ 

#include "definition_commun.h"
#include "affichage.h"
#include "listes.h"
#include "personnage.h"

#define TAILLE_CASE 16

typedef struct s_aff t_aff;  /* Cette définition est la pour éviter une inclusion mutuelle des fichiers map.h et affichage.h */

typedef struct joueur_s joueur_t; /* Cette définition est la pour éviter une inclusion mutuelle des fichiers map.h et personnage.h */

typedef struct liste_base_monstres_s liste_base_monstres_t; /* Cette définition est la pour éviter une inclusion mutuelle des fichiers \ref map.h et \ref monstre.h */

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
 * \authors Ange Despert 
 * \authors Antoine Bruneau 
 * \authors Max Descomps
*/
typedef struct s_map{
    unsigned int id_map; /**< L'identificateur de la map */
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
 * \brief Fonction qui récupère les informations stockées dans le fichier don le nom est donne en entrée.
 * \author Ange Despert
 * 
 * Fonction qui fait appel à la librairie JSON-C pour charger les informations de la map au format JSON.
 * \param nom_map Le nom du fichier qui contient les informations sur la map
 * \return Une map initialisée avec toutes les informations dedans
 */
extern t_map *charger_map(const char *const nom_map);

/**
 * \brief Fonction qui initialise les textures qui serviront de buffer d'affichage au moteur du jeu.
 * \author Ange Despert
 *
 * On va initialiser 2 sous buffer : l'un pour le \ref s_map.text_map "plan principal" et l'un pour le \ref fenetre_finale "1er plan". 
 *
 * \param map La mat qui contiendra l'un des sous buffer
 * \param joueur Joueur autour duquel se fait la fenêtre d'affichage de la carte
 */
extern void init_sousbuffer(t_map *map, joueur_t *joueur);

/**
 * \brief Fonction qui renvoie la texture de la map
 * \author Ange Despert
 * 
 * On va directement chercher cette information dans la structure \ref s_map "de la map".
 * 
 * \param map La map dont on veut la texture
 * \return La texture de la map
 */
extern t_aff *texture_map(const t_map *map);

/**
 * \brief Fonction qui permet de faire la transition avec une autre map.
 * \author Ange Despert
 * 
 * Cette fonction va détruire la map actuelle, charger la nouvelle et déplacer les personnages a leur nouvel emplacement donné en paramètre.
 * 
 * \param actuelle L'addresse de la map actuelle
 * \param num_map L'identifiant de la map que l'on veut accéder
 * \param joueurs Les joueurs qui existent
 * \param nb_joueurs Le nombre de joueurs existants
 * \param new_x La nouvelle coordonnée x des joueurs
 * \param new_y La nouvelle coordonnée y des joueurs
 */
extern void transition(t_map **actuelle, unsigned int num_map, joueur_t *joueurs[], unsigned short int nb_joueurs, unsigned int new_x, unsigned int new_y);

/**
 * \brief Fonction qui permet de téléporter des joueurs à un certaine coordonnée
 * \author Ange Despert
 * 
 * Cette fonction va placer les joueurs aux coordonnées voulues. Elle centrera la caméra au niveau du personnage principal si cela est possible.
 * 
 * \param map La map où l'on téléporte les joueurs
 * \param x La nouvelle coordonnée x des joueurs
 * \param y La nouvelle coordonnée y des joueurs
 * \param joueurs Les joueurs qui existent
 * \param nb_joueurs Le nombre de joueurs qui existent
 */
extern void tp_joueurs(t_map *map, unsigned int x, unsigned int y, joueur_t *joueurs[], unsigned short int nb_joueurs);

/**
 * \brief Fonction qui permet de détruire une map
 * \author Ange Despert
 * 
 * Cette fonction libèrera toute la mémoire allouée a la map.
 * Elle détruira égalament les éléments des listes de la map. \n
 * En ce qui concerne la liste de collision, étant donné que certains rectangle ne sont pas dynamiques, la fonction va d'abord s'assurer qu'ils peuvent être supprimer. 
 * 
 * \param map L'addresse de la map que l'on veut détruire
 * \param joueurs Les joueurs qui existent
 * \param nb_joueurs Le nombre de joueurs qui existent
 */
extern void detruire_map(t_map **map, joueur_t *joueurs[], unsigned short int nb_joueurs);

#ifdef DEBUG_TP
    /**
     * \brief Fonction qui permet d'afficher le rectangle de la zone de téléportation à l'écran.
     * \author Ange Despert
     * 
     * \param z La zone de tp à afficher
     */
    void afficher_zone_tp(zone_tp *z);

#endif

#endif