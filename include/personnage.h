/**
 * \file personnage.h
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant le personnage
 * \version 0.1
 * \date 01/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

/**
 * \struct struct joueur_s
 * \brief Structure non manipulable hors des fonctions du personnage contenant les informations sur le joueur
 * 
 * \author Despert Ange
 */

typedef struct joueur_s
{
	char * nom_pers; /**<Le nom du personnage*/
	short int niveau; /**<Le niveau du joueur*/
	int xp; /**<Le nombre de points d'expérience que possède le joueur */
	long trigger; /**<Une variable contenant des triggers logiques concernant le personnage */
	/** TODO : créer un type énuméré map*/
	int pdv;
	int attaque; /**<attaque du joueur*/
    int defense; /**<defense du joueur*/
    int vitesse; /**<vitesse de déplacement du joueur*/
}joueur_t;

extern joueur_t * creer_joueur(const char * nom);
extern void detruire_joueur(joueur_t *j);
extern joueur_t * charger_sauvegarde_joueur(void);
#endif