/**
 * \file monstre.h
 * \author Bruneau Antoine (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les monstres
 * \version 0.1
 * \date 01/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __MONSTRES_H__
#define __MONSTRES_H__

#include "definition_commun.h"
#include <affichage.h>

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
	char nom_monstre[20]; /**<nom du monstre*/
    int pdv; /**<points de vie*/
    int attaque; /**<attaque*/
    float vitesse; /**<vitesse de déplacement*/
    position_t position; /**<coordonnées*/
    int gainXp; /**<gain d'xp pour le joueur*/
    t_direction orientation; /**<orientation*/
    t_aff* texture; /**<texture*/
    /*short int niveau;*/ /**<Le niveau du monstre*/
} monstre_t;


/**
 * \struct struct base_monstre
 * \brief Structure contenant les propiétées du monstre importé
 * \author Bruneau Antoine
 */
typedef struct base_monstre_s
{
    char fichier_image[20]; /**<nom fichier image*/
    char nom_monstre[20]; /**<nom du monstre*/
    int pdv; /**<points de vie*/
    int attaque; /**<attaque*/
    float vitesse; /**<vitesse de déplacement*/
    int gainXp; /**<gain d'xp pour le joueur*/
}base_monstre_t;


/**
 * \struct struct liste_base_monstres
 * \brief Structure contenant un tableau avec tous les monstres différent que l'on peut utiliser dans le jeu 
 * \author Bruneau Antoine
 */
typedef struct liste_base_monstres_s
{
    int nb_monstre;
    base_monstre_t** tab;
}liste_base_monstres_t;


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
 * \fn liste_base_monstres_t* charger_monstres(char* nom_fichier)
 * \brief Fonction qui recopie les informations d'un fichier pour les insérrer dans une structure liste_base_monstres_t
 * \param nom_fichier nom du fichier à lire
 * \return liste_base_monstres_t* une structure contenant la liste des monstres
 */
liste_base_monstres_t* charger_monstres(char* nom_fichier);

#endif