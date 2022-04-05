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

#define COFFRE_FACE_OUVERT "ressources/sprite/coffrefaceouvert.bmp"
#define COFFRE_PROFIL_OUVERT "ressources/sprite/coffreprofilouvert.bmp"

/**
 * \brief Définition de la structure de texture
 * 
 * Cette définition est la pour éviter une inclusion mutuelle des fichiers \ref coffres.h et \ref affichage.h .
 */
typedef struct s_aff t_aff;

/**
 * Type enum renseignant sur le type d'un coffre
 */
typedef enum {PROFIL_FERME,PROFIL_OUVERT,FACE_FERME,FACE_OUVERT, COFFRE_INCONNU}type_coffre_t;

/**
 * Type enum indiquant si un coffre à été ouvert par un joueur
 */
typedef enum {OUVERT, FERME}etat_coffre_t;

/**
 * \struct coffre_s
 * \brief Structure contenant les propriétées du coffre
 * \author Max Descomps
 */
typedef struct coffre_s
{
    int id_cle; /**<Indentificateur de l'objet de quête nécessaire pour ouvrir le coffre sinon 0*/
    int id_loot; /**<Indentificateur de l'objet obtenu en ouvrant le coffre sinon 0*/
	type_coffre_t type; /**<Type de coffre*/
    t_direction_1 orientation; /*Orientation du coffre*/
    etat_coffre_t etat; /*Etat en cours par le coffre*/
    SDL_Rect collision; /**<Coordonnées*/
    t_aff* texture; /**<Texture*/
} coffre_t;

/**
 * \struct base_coffre_s
 * \brief Structure contenant les propiétées du coffre importé
 * \author Max Descomps
 */
typedef struct base_coffre_s
{
    char fichier_image[50]; /**<Nom du fichier image*/
    char nom_coffre[20]; /**<Nom du modèle de coffre*/
    SDL_Rect hitbox; /**<Hitbox du modèle de coffre*/
}base_coffre_t;

/**
 * \struct liste_base_coffres_s
 * \brief Structure contenant un tableau avec tous les coffres possibles du jeu
 * \author Max Descomps
 */
typedef struct liste_base_coffres_s
{
    int nb_coffre; /**<Nombre de modèles de coffres du jeu*/
    base_coffre_t* tab; /**<Modèles des coffres du jeu*/
}liste_base_coffres_t;

/* Variables globales */
extern liste_base_coffres_t * liste_base_coffres; /*Liste des coffres générés par le programme*/

/* Définition des fonctions */

/**
 * \fn void charger_base_coffre(char * chemin_fichier, liste_base_coffres_t ** liste_base_coffres)
 * \brief Fonction qui recopie les informations d'un fichier json pour les insérer dans la structure liste_base_coffres
 * \author Max Descomps
 * \param nom_fichier Le nom du fichier à lire
 * \param liste_base_coffres La base dans laquelle enregistrer les coffres
 */
void charger_base_coffre(char * chemin_fichier, liste_base_coffres_t ** liste_base_coffres);

/**
 * \fn coffre_t* creer_coffre(int id_cle, int id_loot, liste_base_coffres_t* liste_base_coffres, const char * const nom_coffre, int x, int y, t_map *map)
 * \brief Fonction qui creer et initialise un coffre sur une carte
 * \author Max Descomps
 * \param id_cle L'identificateur de l'objet de quête nécessaire pour ouvrir le coffre, sinon 0
 * \param id_loot L'identificateur de l'objet obtenu en ouvrant le coffre, sinon 0
 * \param liste_base_coffre Les coffres de base
 * \param nom_coffre Le nom du coffre à creer
 * \param x La position en abscisse du coffre sur la map
 * \param y La position en ordonnée du coffre sur la map
 * \param map La carte dans laquelle mettre le coffre
 * \return Instance nouvellement allouée du type coffre_t contenant les informations du coffre ou NULL
 */
coffre_t* creer_coffre(int id_cle, int id_loot, liste_base_coffres_t* liste_base_coffres, const char * const nom_coffre, int x, int y, t_map *map);

/**
 * \fn type_coffre_t nom_coffre_to_type_coffre(char * nom_coffre)
 * \brief Convertit une chaîne de caractères en type de coffre
 * \author Max Descomps
 * \param nom_coffre La chaîne de caractères à convertir
 * \return Une valeur du type type_coffre_t représentant le type de coffre
 */
type_coffre_t nom_coffre_to_type_coffre(const char * nom_coffre);

/**
 * \fn void info_coffre(coffre_t * coffre)
 * \brief Affcihe les informations sur un coffre dans la console
 * \author Max Descomps
 * \param coffre Le coffre sur lequel on se renseigne
 */
void info_coffre(coffre_t * coffre);

/**
 * \fn void interaction_coffre(SDL_Rect * coffre_rect, joueur_t * joueur, lobjet_t * objets)
 * \brief Gère les interactions du joueur avec un coffre lors d'une collision
 * \author Max Descomps
 * \param coffre_rect Les coordonnées du prochain pas du personnage
 * \param joueur Le joueur activant le coffre
 * \param objets Les objets du jeu
 */
void interaction_coffre(SDL_Rect * coffre_rect, joueur_t * joueur, lobjet_t * objets);

/**
 * \fn void inverser_direction(t_direction_1 direction)
 * \brief Inverse une direction
 * \author Max Descomps
 * \param direction La direction à inverser
 * \return Un type t_direction_1
 */
t_direction_1 inverser_direction(t_direction_1 direction);

#endif