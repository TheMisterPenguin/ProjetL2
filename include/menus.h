/**
 * \file menus.h
 * \authors Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \authors Max Descomps
 * \brief Définitions relatives à la gestion des menus du jeu
 * \version 1.0
 * \date 05/04/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __MENUS_H__
#define __MENUS_H__

#include "definition_commun.h"

extern t_aff * text_pause; /**<La texture du menu de pause*/
extern t_aff * text_inventaire1; /**<La texture de l'inventaire du J1*/
extern t_aff * text_inventaire2; /**<La texture de l'inventaire du J2*/
extern t_aff * text_accueil; /**<La texture du menu d'accueil*/

/**
 * \brief Affiche le menu pause et gère les interactions avec le joueur.
 * \author Ange Despert
 * 
 * Cette fonction affiche le menu pause et gère le clic des boutons à la souris.
 *
 * \param joueur Les joueurs qui existent
 * \param f_src_objet Liste des objets du jeux utilisée dans certaines fonctionnalités du menu pause
 * \param nb_joueurs Le nombre de joueurs qui exsitents
 */
extern void afficher_menu_pause(joueur_t *joueur[], char *f_src_objet, unsigned short int nb_joueurs);

/**
 * \brief Affiche le menu pause et gère les interactions avec le joueur.
 * \author Ange Despert
 *
 * Cette fonction affiche le menu pause et fonctionne de façon similaire à la fonction \ref afficher_menu_pause mais les seléctions sont faites à la manette.
 *
 * \todo Permmetre la sauvegarde et le chargement de celle-ci avec la manette.
 * 
 * \param joueur Le joueur principal 
 */
extern void afficher_menu_pause_manette(joueur_t *joueur);

/**
 * \fn void afficher_menu_accueil(int * nb_joueur)
 * \brief Affiche le menu d'acceuil et gère les interactions avec le joueur.
 * \author Max Descomps
 * \param nb_joueur Le nombre de joueurs souhaitant commencer une partie
 */
extern void afficher_menu_accueil(int * nb_joueur);

/**
 * \brief Affiche le menu d'acceuil et gère les interactions avec le joueur.
 * \author Ange Despert
 * 
 * Fonction qui est similaire à la fonction \ref afficher_menu_accueil mais permet l'utilisation de la manette.
 *
 * \todo Ajout du multijoueur.
 * 
 * \param nb_joueur Le nombre de joueurs souhaitant commencer une partie (renvoie toujours 1)
 */
void afficher_menu_accueil_manette(int *nb_joueur);

/**
 * \fn void afficher_inventaire(joueur_t * joueur)
 * \brief Affiche l'inventaire et gère les interactions avec l'utilisateur.
 * \authors Ange Despert
 * \authors Max Descomps
 * 
 * Permet d'afficher l'inventaire et d'équiper et déequiper des objets à l'aide du clic de la souris.
 * 
 * Cette fonction affichera en arrière plan le \ref fenetre_finale "buffer de 1er plan".
 * 
 * \param joueur Joueur auquel appartient l'inventaire
 * \param touche_inventaire Touche inventaire du joueur
 */
extern void afficher_inventaire(joueur_t *joueur, SDL_KeyCode touche_inventaire);

/**
 * \brief Affiche l'inventaire et gère les interactions avec l'utilisateur.
 * \author Ange Despert 
 *
 * Fonctionnement similaire à la fonction \ref afficher_inventaire mais fonctionne à l'aide d'une manette.
 * 
 * \param joueur Joueur auquel appartient l'inventaire
 */
void afficher_inventaire_manette(joueur_t *joueur);

/**
 * \fn void init_text_menus(void)
 * \brief Créer les textures des menus
 * \author Max Descomps
 */
void init_text_menus(void);

/**
 * \fn void creer_inventaire_j2(void)
 * \brief Créer l'inventaire du joueur 2
 * \author Max Descomps
 */
void creer_inventaire_j2(void);
#endif