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
#define DUREE_ATTAQUE 4
#define DUREE_ATTAQUE_CHARGEE 10
#define DUREE_BLOQUER 14
#define DUREE_JOUEUR_BLESSE 12

#define DUREE_SOIN 25 /**< Nombre de sprites dans le spritesheet de soin */

#define TAILLE_PERSONNAGE 16 /*La taille du personnage en pixels*/

#define TAILLE_TRIGGER 200

typedef struct s_l_aff t_l_aff; /* Cette définition est la pour éviter une inclusion mutuelle des fichiers personnage.h et affichage.h */

typedef struct inventaire_s inventaire_t; /* Cette définition est la pour éviter une inclusion mutuelle des fichiers \ref personnage.h et \ref inventaire.h */

typedef unsigned char byte;


typedef enum {
    RIEN, /**< Aucune action */
    ATTAQUE, /**< Action d'attaque */
    ATTAQUE_CHARGEE, /**< Action d'attaque chargée */
    CHARGER, /**< Action de charge */
    BLOQUER, /**< Action de bloquage */
    ATTAQUE_OU_CHARGER, /**< Action d'attaque ou de charge */
    J_BLESSE, /**< Action de blessure */
    SOIN /**< Action de soin */
}action_t; /**<l'action qu'est en train de faire le personnage*/

/**
 * \brief Structure contenant les éléments nécéssaires au choix de l'affichage des sprites du personnage
 * 
 * \authors Bruneau Antoine
 * \authors Ange Despert
 */
typedef struct statut_s {
	bool en_mouvement; /**<personnage en mouvement*/
	t_direction_1 orient_dep;/**<orientation deplacement du personnage*/
	t_direction_2 orient_att;/**<orientaiton attaque du personnage*/
	bool bouclier_equipe; /**<personnage à un bouclier d'équipé*/
	int duree; /**<durée de l'action à réaliser*/
    int duree_anim; /**<durée d'une animation éventuelle sur le joueur*/
	action_t action; /**<l'action du personnage*/
	action_t animation; /**<Animation sur le personnage*/
	SDL_Rect zone_colision; /**<zone de colision du personnage*/
	SDL_Rect vrai_zone_collision; /**<La vrai zone de collision du J1 sur la carte */
	t_aff * texture_prec; /**<la texture precedente du personnage*/
}statut_t;

typedef unsigned char byte;

/**
 * \brief Structure non manipulable hors des fonctions du personnage contenant les informations sur le joueur
 * 
 * \authors Despert Ange
 * \authors Descomps Max
 */
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

extern char save_path[500]; /**<Le répertoire complet de sauvegarde du jeu*/

/**
 * \fn void stoper_mouvement_joueurs(joueur_t ** joueurs)
 * \brief Stop le mouvement des joueurs en jeu
 * \param joueurs Tableau des joueurs en jeu
 */
void stoper_mouvement_joueurs(joueur_t ** joueurs);

/**
 * \brief Creer un joueur
 * \authors Max Descomps
 * \authors Ange Despert
 * \param nom Le nom du joueur
 * \param niveau Le niveau du joueur
 * \param xp L'expérience du joueur
 * \param maxPdv Le nombre maximu de points de vie du joueur
 * \param pdv Le nombre de points de vie du joueur
 * \param attaque L'attaque du joueur
 * \param defense La défense du joueur
 * \param vitesse La vitesse du joueur
 * \param trig Le trigger d'information sur le joueur
 * \param orient L'orientation spatiale du joueur
 * \param bouclier_equipe La possession d'un bouclier équipé par le joueur
 * \param num_j La place du joueur dans le tableau des joueurs
 * \param f_src_obj Le fichier source des objets du jeu
 * \return Instance nouvellement allouée du type joueur_t contenant les informations du joueur
 */
extern joueur_t *creer_joueur(const char *nom, const int niveau, const int xp, const int maxPdv, const int pdv, const int attaque, const int defense, const int vitesse, const byte trig[TAILLE_TRIGGER], const t_direction_1 orient, const bool bouclier_equipe, const int num_j, char * f_src_obj);

/**
 * \brief Fonction de création d'un joueur correspondant au modèle standard du jeu
 * \author Ange Despert
 * 
 * \param nom Le nom du joueur
 * \param num_j La place du joueur dans le tableau des joueurs
 * \param f_src_obj Le fichier source des objets du jeu
 * \return Instance nouvellement allouée du type joueur_t contenant les informations du joueur
 */
extern joueur_t *new_joueur(const char* nom, int num_j, char * f_src_obj);

/**
 * \brief Fonction qui détruit un joueur
 * \author Max Descomps
 * 
 * \param j Le joueur à détruire
 */
extern void detruire_joueur(joueur_t *j);

/**
 * \brief Fonction qui charge une sauvegarde au format JSON.
 * \author Ange Despert
 * 
 * Cette fonction va récupérer les informations dans la sauvegarde au format JSON. \n
 * 
 * Il va ensuite detruire les joueurs et la carte, pour ensuite les recrées avec les infomations qui correspondent à la sauvegarde puis téléporter le joueur aux coordonnées voulues. 
 * \param nom_sauv Chemin complet du fichier de sauvegarde
 * \param f_src_obj Le fichier source contenant les objets du jeu
 * \param joueurs Les joueurs existants
 * \param nb_joueurs Le nombre de joueurs existants
 * \return joueur_t*
 */
extern joueur_t *charger_sauvegarde_joueur(char * nom_sauv, char *f_src_obj, joueur_t *joueurs[], unsigned short int nb_joueurs);

/**
 * \brief Fonction qui met à jour les statistiques d'un joueur lors d'un passage de niveau
 * \param perso Le joueur qui passe un niveau
 */
extern void maj_statistiques(joueur_t* perso);

/**
 * \brief Fonction qui affiche les statistiques d'un joueur dans la console
 * \author Rafael Doneau
 * \author Max Descomps
 * \param perso Le joueur sur lequel on se renseigne
 */
extern void afficher_statistiques(joueur_t* perso);

/**
 * \brief Fonction qui gère le passage de niveau d'un joueur
 * \param perso Le joueur qui passe un niveau
 */
extern void levelup(joueur_t* perso);

/**
 * \brief Fonction qui gère les effets d'un gain d'expérience
 * \param perso Le joueur qui gagne de l'expérience
 */
extern void gain_xp(joueur_t* perso);

/**
 * \brief Fonction qui créer les sauvegardes du jeu.
 * \author Ange Despert
 * 
 * Cette fonction va créer une sauvegarde dans le répertoire de sauvegarde au format JSON contenant toutes les informations a conserver sur le joueur.
 * 
 * \param j Le joueur qui sauvegarde
 */
extern void creer_sauvegarde_json(joueur_t *j);

/**
 * \brief Fonction gère le répertoire de jeux
 * \author Ange Despert
 * 
 * Cette fonction vérifie si le répertoire de jeux existe (emplacement différent selon les OS). \n
 * Puis le créer s'il n'existe pas.
 * 
 */
void check_repertoire_jeux();

/**
 * \brief Fonction qui gère les effets de l'environnement sur le joueur
 * \param liste_monstres La liste des monstres du jeu
 * \param liste_sorts La liste des sorts du jeu
 * \param liste_coffres La liste des coffres du jeu
 * \param joueurs Les joueurs qui interagissent avec l'environnement du jeu
 * \param nb_joueur Le nombre de joueurs en jeu
 */
void environnement_joueurs(list * liste_monstres, list * liste_sorts, list * liste_coffres, joueur_t ** joueurs, int nb_joueur);

/**
 * \brief Renvoie la distance séparant le joueur d'une entité définit par sa collision sur l'axe des abscisses
 * \author Bruneau Antoine
 * \param collision la zone de collision de l'entité
 * \param joueur le joueur
 * \return int la distance entre l'entité et le joueur sur l'axe des abscisses
 */
extern int distance_x_joueur(SDL_Rect collision, joueur_t * joueur);

/**
 * \brief Renvoie la distance séparant le joueur d'une entité définit par sa collision sur l'axe des ordonnées
 * \author Bruneau Antoine
 * \param collision la zone de collision de l'entité
 * \param joueur le joueur
 * \return int la distance entre l'entité et le joueur sur l'axe des ordonnées
 */
extern int distance_y_joueur(SDL_Rect collision, joueur_t * joueur);

/**
 * \brief Renvoie la distance séparant le joueur d'une entité définit par sa collision
 * \author Bruneau Antoine
 * \param collision la zone de collision de l'entité
 * \param joueur le joueur
 * \return int la distance entre l'entité et le joueur
 */
extern int distance_joueur(SDL_Rect collision, joueur_t * joueur);



#endif