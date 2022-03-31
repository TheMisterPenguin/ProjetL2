/**
 * \file menus.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Définitions relatives à la gestion des menus du jeu
 * \version 1.0
 * \date 27/03/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __MENUS_H__
#define __MENUS_H__

#include "definition_commun.h"

/**
 * Différentes interfaces du jeu
 */
typedef enum{JEU,PAUSE,PRINCIPAL,INVENTAIRE}menus_t;

extern menus_t menus;

extern t_aff * text_pause;
extern t_aff * text_inventaire1;
extern t_aff * text_inventaire2;
extern t_aff * text_accueil;

//extern void afficher_menu(menus_t * menu);

/**
 * \fn void afficher_menu_pause(joueur_t * joueur)
 * \brief Affiche le menu pause et gère les interactions avec le joueur
 * \param joueur Joueur qui ouvre le menu
 */
extern void afficher_menu_pause(joueur_t * joueur);

/**
 * \fn void afficher_menu_accueil(int * nb_joueur)
 * \brief Affiche le menu d'acceuil et gère les interactions avec le joueur
 * \param nb_joueur Le nombre de joueurs souhaitant commencer une partie
 */
extern void afficher_menu_accueil(int * nb_joueur);

/**
 * \fn void afficher_inventaire(joueur_t * joueur)
 * \brief Affiche l'inventaire et gère les interactions avec l'utilisateur
 * \param joueur Joueur auquel appartient l'inventaire
 * \param touche_inventaire Touche inventaire du joueur
 */
extern void afficher_inventaire(joueur_t * joueur, SDL_KeyCode touche_inventaire);

/**
 * \fn void init_text_menus(void)
 * \brief Créer les textures des menus
 */
void init_text_menus(void);

/**
 * \fn void creer_inventaire_j2(void)
 * \brief Créer l'inventaire du joueur 2
 */
void creer_inventaire_j2(void);
#endif