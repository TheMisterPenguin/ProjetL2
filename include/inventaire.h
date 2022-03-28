/**
 * \file inventaire.h
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Définition des fonctions relatives au module inventaire
 * \version 1.0
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __H_INVENTAIRE__
#define __H_INVENTAIRE__

#define CAPACITE_SAC 10

#include "commun.h"

/**
 * \struct inventaire_t
 * \brief Structure inventaire diviser en deux parties: le sac et les objets équipés
 */
typedef struct inventaire_s{
    lobjet_t *equipe; /**<Objets équipés*/
    lobjet_t *sac; /**<Objets dans le sac*/
}inventaire_t;

extern inventaire_t * inventaire;

/**
 * \fn inventaire_t * creer_inventaire()
 * \brief Créé un inventaire
 * \return Instance nouvellement allouée du type inventaire_t ou NULL
 */
inventaire_t * creer_inventaire();

/**
 * \fn void changement_statistiques(joueur_t *j,lobjet_t *liste)
 * \brief Fonction qui permet de modifier les statistiques du joueur selon une liste d'objets
 * \param joueur Joueur dont on change les statistiques
 * \param equipe la liste d'objets
 */
void changement_statistiques(joueur_t *joueur,lobjet_t *equipe);

/**
 * \fn void equiper_objet(joueur_t *j,objet_t **objet,inventaire_t *inventaire)
 * \brief Fonction qui permet de passer un objet du sac(non-équipé) à un emplacement d'équipement(équipé) dans l'inventaire
 * \param joueur Joueur à équiper
 * \param objet Objet à équiper
 * \param inventaire Inventaire du joueur
 */
void equiper_objet(joueur_t *joueur,objet_t **objet,inventaire_t *inventaire);

/**
 * \fn void desequiper(objet_t **objet,inventaire_t *inventaire,joueur_t *j);
 * \brief Fonction qui permet de passer un objet d'un emplacement d'équipement(équipé) au sac(non-équipé) dans l'inventaire
 * \param j Joueur à déséquiper
 * \param objet Objet à déséquiper
 * \param inventaire Inventaire du joueur
 */
void desequiper(joueur_t *j, objet_t **objet,inventaire_t *inventaire);

/**
 * \fn void ramasser_objet(objet_t * objet, inventaire_t * inventaire)
 * \brief Fonction qui permet de mettre un objet trouvé dans le sac(inventaire)
 * \param objet Objet trouvé
 * \param inventaire Inventaire du joueur
 */
void ramasser_objet(objet_t * objet, inventaire_t * inventaire);

/**
 * \fn void tout_ramasser(lobjet_t * objets, inventaire_t * inventaire)
 * \brief Met tous les objets du jeu dans l'inventaire (sac)
 * \param objets Liste d'objets du jeu
 * \param inventaire Inventaire du joueur
 */
void tout_ramasser(lobjet_t * objets, inventaire_t * inventaire);

/**
 * \fn void * detruire_inventaire(inventaire_t ** inventaire)
 * \brief Détruit un inventaire
 * \param inventaire Adresse du pointeur sur inventaire_t
 */
void detruire_inventaire(inventaire_t ** inventaire);

/**
 * \fn void equiper_sac_slot( int slot )
 * \brief Équipe l'objet contenu dans un slot de l'inventaire (sac)
 * \param slot Le slot de l'objet à équiper
 */
void equiper_sac_slot( int slot );
#endif