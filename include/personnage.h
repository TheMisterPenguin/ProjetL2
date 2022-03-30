/**
 * \file personnage.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \author Antoine Bruneau (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les définitions concernant le personnage
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include "definition_commun.h"
#include "inventaire.h"

typedef struct s_l_aff t_l_aff;

typedef enum {RIEN,ATTAQUE,ATTAQUE_CHARGEE,CHARGER,BLOQUER,ATTAQUE_OU_CHARGER,J_BLESSE}action_t; /**<l'action qu'est en train de faire le personnage*/
/**
 * \struct struct statut_s
 * \brief Structure contenant les éléments nécéssaires au choix de l'affichage des sprites du personnage
 * 
 * \author Bruneau Antoine
 */
typedef struct statut_s {
	bool en_mouvement; /**<personnage en mouvement*/
	t_direction	orientation;/**<ordientation du personnage*/
	bool bouclier_equipe; /**<personnage à un bouclier d'équipé*/
	int duree; /**<duree de l'action à réaliser*/
	action_t action; /**<l'action du personnage*/
	SDL_Rect zone_colision; /**<zone de colision du personnage*/
}statut_t;

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
	int attaque; /**<attaque de base du joueur*/
    int defense; /**<defense de base du joueur*/
    int vitesse; /**<vitesse de déplacement de base du joueur*/
    int attaque_actif; /**<attaque du joueur avec bonus d'equipement*/
    int defense_actif; /**<defense du joueur avec bonus d'equipement*/
    int vitesse_actif; /**<vitesse du joueur avec bonus d'equipement*/
	statut_t *statut; /**<statut du joueur*/
	t_l_aff *textures_joueur; /**<Tableau contenant toutes les textures du joueur*/
    inventaire_t * inventaire; /**<Inventaire du joueur*/
}joueur_t;

#define DUREE_ATTAQUE_OU_CHARGEE 4
#define DUREE_ATTAQUE 6
#define DUREE_ATTAQUE_CHARGEE 10
#define DUREE_BLOQUER 3
#define DUREE_JOUEUR_BLESSE 4

#define TAILLE_PERSONNAGE 16 /*La taille du personnage en pixels*/

extern char save_path[500];

#define TAILLE_TRIGGER 200

	extern joueur_t *
	creer_joueur(const char *nom, const int niveau, const int xp, const int maxPdv, const int pdv, const int attaque, const int defense, const int vitesse, const byte trig[TAILLE_TRIGGER], const t_direction orientation, const bool bouclier_equipe);
extern joueur_t *new_joueur(const char *nom);
extern void detruire_joueur(joueur_t *j);
extern joueur_t *charger_sauvegarde_joueur(char *nom_sauv);
extern joueur_t * caracteristiques(joueur_t* perso);
extern void afficher_statistiques(joueur_t* perso);
extern joueur_t * levelup(joueur_t* perso);
extern joueur_t * gain_xp(joueur_t* perso);
extern void creer_sauvegarde_json(joueur_t *j);
void check_repertoire_jeux();

#endif