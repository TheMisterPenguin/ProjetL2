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


typedef enum{SUD, NORD, EST, OUEST}t_direction;

/**
 * \struct struct position
 * \brief Structure regroupant les coordonnées
 * 
 * \author Bruneau Antoine
 */
typedef struct position_s
{
    int x;
    int y;
}position_t;


/**
 * \struct struct monstre
 * \brief Structure monstre
 * 
 * \author Bruneau Antoine
 */
typedef struct monstre_s
{
	char nom_monstre[20]; /**<nom*/
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
 * \brief Structure contenant un tableau de monstre
 * 
 * \author Bruneau Antoine
 */
typedef struct base_monstres_s
{
    int nb_monstre;
    monstre_t** tab;
}base_monstres_t;


/**
 * \fn void detuire_base_monstres(base_monstre_t* base_monstre)
 * \brief Fonction qui désalloue la structure base_monstres
 * \param base_monstres structure base_monstres_t à détruire
 */
void detuire_base_monstres(base_monstres_t** base_monstres);

/**
 * \fn base_monstres_t* charger_monstres(char* nom_fichier)
 * \brief Fonction qui recopie les informations d'un fichier pour les insérrer dans une structure base_monstres_t
 * \param nom_fichier nom du fichier à lire
 * \return base_monstres_t* une structure contenant la liste des monstres
 */
base_monstres_t* charger_monstres(char* nom_fichier);

#endif