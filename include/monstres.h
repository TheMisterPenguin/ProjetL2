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

#define DISTANCE_AGRO 50
#define DUREE_MONSTRE_MARCHER 100
#define DUREE_MONSTRE_EN_GARDE 140
#define DUREE_RUSH_OU_FUITE 150
#define DUREE_MONSTRE_ATTAQUE 100
#define DUREE_MONSTRE_BLESSE 30

#define CHEMIN_TEXTURE "ressources/sprite"

typedef enum {WITCHER,KNIGHT,BOSS}type_monstre_t;
typedef enum {MONSTRE_MARCHER, MONSTRE_EN_GARDE, MONSTRE_ATTAQUE, RUSH_OU_FUITE, MONSTRE_BLESSE}action_monstre_t;

/**
 * \struct struct position
 * \brief Structure regroupant les coordonnées
 * \author Bruneau Antoine
 */
typedef point position_t;


/**
 * \struct struct monstre
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

    t_direction orientation; /*orientation du monstre*/
    int duree; /*duree de l'action*/
    action_monstre_t action; /*action en cours par le monstre*/

    SDL_Rect collision; /**<coordonnées*/
    t_aff* texture; /**<texture*/
} monstre_t;


/**
 * \struct struct base_monstre
 * \brief Structure contenant les propiétées du monstre importé
 * \author Bruneau Antoine
 */
typedef struct base_monstre_s
{
    char fichier_image[25]; /**<nom fichier image*/
    char nom_monstre[25]; /**<nom du monstre*/
    int pdv; /**<points de vie*/
    int attaque; /**<attaque*/
    float vitesse; /**<vitesse de déplacement*/
    int gainXp; /**<gain d'xp pour le joueur*/
    SDL_Rect hitbox; /**<hitbox du monstre*/
}base_monstre_t;


/**
 * \struct struct liste_base_monstres
 * \brief Structure contenant un tableau avec tous les monstres différent que l'on peut utiliser dans le jeu 
 * \author Bruneau Antoine
 */
typedef struct liste_base_monstres_s
{
    int nb_monstre;
    base_monstre_t* tab;
}liste_base_monstres_t;

extern liste_base_monstres_t * liste_base_monstres;

/**
 * \fn void detruire_liste_base_monstres(liste_base_monstre_t* liste_base_monstre)
 * \brief Fonction qui désalloue la structure liste_base_monstres
 * \param base_monstres structure base_monstres_t à détruire
 */

void detruire_liste_base_monstres(liste_base_monstres_t** liste_base_monstres);


/**
 * \fn void detruire_monstre(base_monstre_t* base_monstre)
 * \brief Fonction qui désalloue la structure monstre
 * \param base_monstres structure monstre_t à détruire
 */
void detruire_monstre(monstre_t** monstre);

/**
 * \fn monstre_t * ajout_monstre(monstre_t * monstre);
 * \brief Fonction qui retourne un monstre
 * \param monstre le monstre à retourner
 */
monstre_t * ajout_monstre(monstre_t * monstre);

/**
 * \fn void charger_base_monstre(char* nom_fichier);
 * \brief Fonction qui recopie les informations d'un fichier json pour les insérrer dans la structure global liste_base_monstres
 * \param nom_fichier nom du fichier à lire
 */
void charger_base_monstre(char* nom_fichier);

/**
 * \fn monstre_t* creer_monstre(liste_base_monstres_t* liste_base_monstre, char* nom_monstre, int x, int y);
 * \brief Fonction qui creer et initialise un monstre
 * \param liste_base_monstre les monstres de base
 * \param nom_monstre le nom du monstre à creer
 * \param x la position en abscisse du monstre sur la map
 * \param y la position en ordonnée du monstre sur la map
 * \return monstres_t* une structure contenant les informations du monstre
 */
monstre_t* creer_monstre(liste_base_monstres_t* liste_base_monstre, char* nom_monstre, int x, int y);



/**
 * \fn void action_monstre(monstre_t * monstre)
 * \brief Fonction qui met à jour le sprite d'un monstre
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur qui provoque l'action du monstre
 */
void action_monstre(monstre_t * monstre, joueur_t * joueur);

/**
 * \fn type_monstre_t nom_monstre_to_type_monstre(char * nom_monstre)
 * \brief Convertit une chaîne de caractères en type de monstre
 * \param nom_monstre La chaîne de caractères à convertir
 * \return type_monstre_t le type de monstre
 */
type_monstre_t nom_monstre_to_type_monstre(char * nom_monstre);
#endif