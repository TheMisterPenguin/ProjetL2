/**
 * \file inventaire.h
 * \author Descomps Max Doneau Rafael
 * \brief 
 * \version 0.2
 * \date 26/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __H_INVENTAIRE__
#define __H_INVENTAIRE__

#include "commun.h"

typedef struct inventaire_s inventaire_t;
struct inventaire_s
{
    lobjet_t *equipe;
    lobjet_t *sac;
};

/**
 * \fn inventaire_t * creer_inventaire()
 * \brief Fonction qui permet de creer un inventaire
 * \return Un pointeur sur l'inventaire
 */
inventaire_t * creer_inventaire();

/**
 * \fn void changement_statistiques(joueur_t *j,lobjet_t *liste)
 * \brief Fonction qui permet de modifier les statistiques du joueur selon une liste d'objets
 * \param j Joueur
 * \param equipe la liste d'objets
 */
void changement_statistiques(joueur_t *j,lobjet_t *equipe);

/**
 * \fn void equiper_objet(joueur_t *j,objet_t **objet,inventaire_t *inventaire)
 * \brief Fonction qui permet de passer un objet du sac(non-équipé) à un emplacement d'équipement(équipé) dans l'inventaire
 * \param j Joueur à équiper
 * \param objet Objet à équiper
 * \param inventaire Inventaire du joueur
 */
void equiper_objet(joueur_t *j,objet_t **objet,inventaire_t *inventaire);

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
 * \fn void * detruire_inventaire(inventaire_t ** inventaire)
 * \brief Détruit un inventaire
 * \param inventaire Adresse du pointeur sur inventaire_t
 */
void detruire_inventaire(inventaire_t ** inventaire);
#endif