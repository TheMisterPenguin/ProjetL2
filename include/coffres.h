/**
 * \file coffres.h
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonctions concernant les coffres
 * \version 0.1
 * \date 04/03/2022
 * \copyright Copyright (c) 2022
 */

#include "definition_commun.h"
#include "affichage.h"
#include "map.h"

#ifndef __COFFRES_H__
#define __COFFRES_H__

typedef struct s_aff t_aff; //!< \brief Structure de texture
typedef struct t_map t_map;

typedef enum {PROFIL_FERME,PROFIL_OUVERT,FACE_FERME,FACE_OUVERT}type_coffre_t;
typedef enum {OUVERT, FERME}action_coffre_t;

/**
 * \struct struct coffre
 * \brief Structure contenant les propriétées du coffre
 * \author Max Descomps
 */
typedef struct coffre_s
{
	type_coffre_t type; /**<type de coffre*/
    t_direction orientation; /*orientation du coffre*/
    action_coffre_t action; /*action en cours par le coffre*/
    SDL_Rect collision; /**<coordonnées*/
    t_aff* texture; /**<texture*/
} coffre_t;

/**
 * \struct struct base_coffre
 * \brief Structure contenant les propiétées du coffre importé
 * \author Max Descomps
 */
typedef struct base_coffre_s
{
    char fichier_image[50]; /**<nom fichier image*/
    char nom_coffre[25]; /**<nom du coffre*/
    SDL_Rect hitbox; /**<hitbox du coffre*/
}base_coffre_t;

/**
 * \struct struct liste_base_coffres
 * \brief Structure contenant un tableau avec tous les coffres possibles du jeu
 * \author Max Descomps
 */
typedef struct liste_base_coffres_s
{
    int nb_coffre;
    base_coffre_t* tab;
}liste_base_coffres_t;

extern liste_base_coffres_t * liste_base_coffres;

/**
 * \fn void charger_base_coffre(char * chemin_fichier, liste_base_coffres_t ** liste_base_coffres)
 * \brief Fonction qui recopie les informations d'un fichier json pour les insérrer dans la structure liste_base_coffres
 * \param nom_fichier nom du fichier à lire
 * \param liste_base_coffres Base dans laquelle enregistrer les coffres
 */
void charger_base_coffre(char * chemin_fichier, liste_base_coffres_t ** liste_base_coffres);

/**
 * \fn coffre_t* creer_coffre(liste_base_coffres_t* liste_base_coffres, const char * const nom_coffre, int x, int y, t_map *map);
 * \brief Fonction qui creer et initialise un coffre
 * \param liste_base_coffre les coffres de base
 * \param nom_coffre le nom du coffre à creer
 * \param x la position en abscisse du coffre sur la map
 * \param y la position en ordonnée du coffre sur la map
 * \return coffres_t* une structure contenant les informations du coffre
 */
coffre_t* creer_coffre(liste_base_coffres_t* liste_base_coffres, const char * const nom_coffre, int x, int y, t_map *map);

/**
 * \fn type_coffre_t nom_coffre_to_type_coffre(char * nom_coffre)
 * \brief Convertit une chaîne de caractères en type de coffre
 * \param nom_coffre La chaîne de caractères à convertir
 * \return type_coffre_t le type de coffre
 */
type_coffre_t nom_coffre_to_type_coffre(char * nom_coffre);

/**
 * \fn void info_coffre(coffre_t * coffre)
 * \brief Affcihe les informations sur un coffre dans la console
 * \param coffre Coffre sur lequel on se renseigne
 */
void info_coffre(coffre_t * coffre);

/**
 * \fn void interaction_coffre(SDL_Rect * obstacle_rect)
 * \brief Gère les interactions du joueur avec les coffres lorsqu'il fonce dessus
 * \param obstacle_rect Coordonnées du prochain pas du personnage
 */
void interaction_coffre(SDL_Rect * obstacle_rect);
#endif