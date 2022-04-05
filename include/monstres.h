/**
 * \file monstres.h
 * \author Antoine Bruneau (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fonctions concernant les monstres
 * \version 0.1
 * \date 01/02/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __MONSTRES_H__
#define __MONSTRES_H__

#include "definition_commun.h"
#include "affichage.h"
#include "map.h"
#include "personnage.h"

#define DISTANCE_AGRO 130           /* distance à partir de laquelle le joueur n'est pas détecté par les monstres*/
#define DUREE_MONSTRE_MARCHER 60
#define DUREE_MONSTRE_EN_GARDE 80
#define DUREE_RUSH_OU_FUITE 40
#define DUREE_MONSTRE_ATTAQUE 50
#define DUREE_MONSTRE_BLESSE 20
#define DUREE_MONSTRE_PAUSE 15

/**
 * \brief L'énumération des types de monstre
 * 
 * Cela permet de différencier les monstres pour réaliser des actions particulières en fonction de celui-ci.
 */
typedef enum
{   
    WITCHER,
    KNIGHT,
    BOSS,
    TYPE_MONSTRE_INCONNU /* pour pouvoir retourner une erreur */
}type_monstre_t;

/**
 * \brief L'énumération des actions du monstre
 * 
 * Cela permet de savoir dans quelle état est le monstre
 */
typedef enum
{
    MONSTRE_MARCHER, /**<le monstre marche normalement*/
    MONSTRE_EN_GARDE, /**<le monstre est immobile*/
    MONSTRE_ATTAQUE, /**<le monstre attaque*/
    RUSH_OU_FUITE, /**<le monstre va vers le joueur ou le fuit*/
    MONSTRE_BLESSE, /**<le monstre prend des dégats*/
    MONSTRE_PAUSE /**<le monstre se stop (après avoir bléssé un joueur)*/
}action_monstre_t;

/**
 * \struct monstre_t
 * \brief Structure contenant les propriétées du monstre en jeu
 * \author Bruneau Antoine
 */
typedef struct monstre_s
{
	type_monstre_t type; /**<type de monstre*/
    int pdv; /**<points de vie*/
    int attaque; /**<attaque*/
    float vitesse; /**<vitesse de déplacement*/
    int gainXp; /**<gain d'xp pour le joueur*/
    t_direction_1 orientation; /*orientation deplacement du monstre*/
    action_monstre_t action; /*action en cours par le monstre*/
    int duree; /*duree de l'action*/
    SDL_Rect collision; /**<zone de collision du monstre (hitbox) + ses coordonnées*/
    t_aff* texture; /**<texture du monstre*/
} monstre_t;

/**
 * \struct base_monstre_t
 * \brief Structure contenant les propiétées du modèle d'un monstre
 * \author Bruneau Antoine
 */
typedef struct base_monstre_s
{
    char fichier_image[50]; /**<chemin d'accès du sprite du monstre*/
    char nom_monstre[25]; /**<nom du monstre*/
    int pdv; /**<points de vie*/
    int attaque; /**<attaque*/
    float vitesse; /**<vitesse de déplacement*/
    int gainXp; /**<gain d'xp pour le joueur*/
    SDL_Rect hitbox; /**<hitbox du monstre*/
}base_monstre_t;

/**
 * \struct liste_base_monstres_t
 * \brief Structure contenant un tableau avec tous les monstres différent(modèle de monstre) que l'on peut utiliser dans le jeu 
 * \author Bruneau Antoine
 */
typedef struct liste_base_monstres_s
{
    int nb_monstre; /**<nombre de modèles de monstre*/
    base_monstre_t* tab; /**<tableau de modèles de monstre*/
}liste_base_monstres_t; 

extern liste_base_monstres_t * liste_base_monstres; /* le tableau de modèles de monstre */

/**
 * \fn void * ajouter_monstre_cb(void * monstre);
 * \brief Fonction de "call back" qui retourne une structure monstre
 * \author Bruneau Antoine
 * \param monstre le monstre à retourner
 * \return void* un pointeur générique sur une structure monstre
 */
extern void * ajouter_monstre_cb(void * monstre);

/**
 * \fn void detruire_monstre_cb(void * monstre);
 * \brief Fonction de "call back" qui détruit une structure monstre
 * \author Bruneau Antoine
 * \param monstre le monstre à détruire
 */
extern void detruire_monstre_cb(void * monstre);

/**
 * \fn monstre_t* creer_monstre(liste_base_monstres_t* liste_base_monstre, char* nom_monstre, int x, int y, t_map *map);
 * \brief Fonction qui creer et initialise un monstre
 * \author Bruneau Antoine
 * \param liste_base_monstre les monstres de base
 * \param nom_monstre le nom du monstre à creer
 * \param x la position en abscisse du monstre sur la map
 * \param y la position en ordonnée du monstre sur la map
 * \param map la map dans laquelle apparaît le monstre
 * \return monstres_t* une structure contenant les informations du monstre
 */
extern monstre_t *creer_monstre(liste_base_monstres_t *liste_base_monstres, const char *const nom_monstre, int x, int y, t_map *map);

/**
 * \fn void detruire_liste_base_monstres(liste_base_monstre_t* liste_base_monstre)
 * \brief Fonction qui désalloue la structure liste_base_monstres
 * \author Bruneau Antoine
 * \param base_monstres structure base_monstres_t à détruire
 */
extern void detruire_liste_base_monstres(liste_base_monstres_t ** liste_base_monstres);

/**
 * \fn void charger_base_monstre(char * chemin_fichier, liste_base_monstres_t ** liste_base_monstres)
 * \brief Fonction qui recopie les informations d'un fichier json pour les insérer dans la structure liste_base_monstres
 * \author Bruneau Antoine
 * \param nom_fichier nom du fichier à lire
 * \param liste_base_monstres tableau dans lequel enregistrer les monstres
 */
extern void charger_base_monstre(char * chemin_fichier, liste_base_monstres_t ** liste_base_monstres);

/**
 * \fn void action_monstre(monstre_t * monstre, joueur_t * joueur);
 * \brief Fonction qui met à jour le sprite d'un monstre en fonction d'un joueur
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur qui provoque l'action du monstre
 */
extern void action_monstre(monstre_t * monstre, joueur_t * joueur);

/**
 * \fn type_monstre_t nom_monstre_to_type_monstre(const char * const nom_monstre)
 * \brief Convertit une chaîne de caractères en type de monstre
 * \author Bruneau Antoine
 * \param nom_monstre La chaîne de caractères à convertir
 * \return type_monstre_t le type de monstre
 */
extern type_monstre_t nom_monstre_to_type_monstre(const char * const nom_monstre);



#endif