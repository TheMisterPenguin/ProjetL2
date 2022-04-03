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
#include "listes.h"
#include "inventaire.h"

#define DUREE_ATTAQUE_OU_CHARGEE 12
#define DUREE_ATTAQUE 6
#define DUREE_ATTAQUE_CHARGEE 10
#define DUREE_BLOQUER 3
#define DUREE_JOUEUR_BLESSE 4

#define DUREE_SOIN 25 //(nb sprites du spritesheet)

#define TAILLE_PERSONNAGE 16 /*La taille du personnage en pixels*/

#define TAILLE_TRIGGER 200

typedef struct s_l_aff t_l_aff;

typedef enum {RIEN,ATTAQUE,ATTAQUE_CHARGEE,CHARGER,BLOQUER,ATTAQUE_OU_CHARGER, J_BLESSE, SOIN}action_t; /**<l'action qu'est en train de faire le personnage*/
/**
 * \struct struct statut_s
 * \brief Structure contenant les éléments nécéssaires au choix de l'affichage des sprites du personnage
 * 
 * \author Bruneau Antoine
 */
typedef struct statut_s {
	bool en_mouvement; /**<personnage en mouvement*/
	t_direction_1 orient_dep;/**<orientation deplacement du personnage*/
	t_direction_2 orient_att;/**<orientaiton attaqute du personnage*/
	bool bouclier_equipe; /**<personnage à un bouclier d'équipé*/
	int duree; /**<durée de l'action à réaliser*/
    int duree_anim; /**<durée d'une animation éventuelle sur le joueur*/
	action_t action; /**<l'action du personnage*/
	action_t animation; /**<Animation sur le personnage*/
	SDL_Rect zone_colision; /**<zone de colision du personnage*/
	SDL_Rect vrai_zone_collision; /**<La vrai zone de collision du J1 sur la carte */
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
	int maxPdv; /**<Le nombre de Pv max du joueur */
	int pdv; /**<Les points de vie actuels du joueur */
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

/**
 * \fn void stoper_mouvement_joueurs(joueur_t ** joueurs)
 * \brief Stop le mouvement des joueurs en jeu
 * \param joueurs Tableau des joueurs en jeu
 */
void stoper_mouvement_joueurs(joueur_t ** joueurs);

extern char save_path[500];

extern joueur_t *creer_joueur(const char *nom, const int niveau, const int xp, const int maxPdv, const int pdv, const int attaque, const int defense, const int vitesse, const byte trig[TAILLE_TRIGGER], const t_direction_1 orientation, const bool bouclier_equipe, const int num_j);
extern joueur_t *new_joueur(const char* nom, int num_j);
extern void detruire_joueur(joueur_t *j);
extern joueur_t *charger_sauvegarde_joueur(char *nom_sauv);
extern void caracteristiques(joueur_t* perso);
extern void afficher_statistiques(joueur_t* perso);
extern void levelup(joueur_t* perso);
extern void gain_xp(joueur_t* perso);
extern void creer_sauvegarde_json(joueur_t *j);
void check_repertoire_jeux();

void environnement_joueur(list * liste_monstres, list * liste_sorts, list * liste_coffres, joueur_t * joueur);
SDL_Rect * zone_en_dehors_hitbox(SDL_Rect * hitbox,SDL_Rect * sprite, t_direction_2 orientation);


#endif