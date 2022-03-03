/**
 * \file personnage.h
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les définitions concernant le personnage
 * \version 0.1
 * \date 01/02/2022
 * 
 * \copyright Copyright (c) 2022
 *  
 */


#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include "definition_commun.h"

/**
 * \struct struct joueur_s
 * \brief Structure non manipulable hors des fonctions du personnage contenant les informations sur le joueur
 * 
 * \author Despert Ange
 */

typedef unsigned char byte;

typedef struct joueur_s {
	char * nom_pers; /**<Le nom du personnage*/
	short int niveau; /**<Le niveau du joueur*/
	int xp; /**<Le nombre de points d'expérience que possède le joueur */
	byte *trigger; /**<Une variable contenant des triggers logiques concernant le personnage */
	/** TODO : créer un type énuméré map*/
	int maxPdv;
	int pdv;
	int attaque; /**<attaque du joueur*/
    int defense; /**<defense du joueur*/
    int vitesse; /**<vitesse de déplacement du joueur*/
	t_direction orientation; /**<orientation du joueur*/
}joueur_t;

extern joueur_t *perso_principal;

#define TAILLE_TRIGGER 200

extern joueur_t * creer_joueur(const char * nom);
extern void detruire_joueur(joueur_t *j);
extern joueur_t * charger_sauvegarde_joueur(FILE *sauvegarde);
extern joueur_t * caracteristiques(joueur_t* perso);
extern void afficher_statistiques(joueur_t* perso);
extern joueur_t * levelup(joueur_t* perso);
extern joueur_t * gain_xp(joueur_t* perso);

#endif