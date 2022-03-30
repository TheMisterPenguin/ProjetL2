/**
 * \file objet.h
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Définitions concernant les objets
 * \version 0.3
 * \date 24/02/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __OBJET_H__
#define __OBJET_H__
#define NB_TYPE_OBJ 6

#include "definition_commun.h"
#include "affichage.h"

/**
 * Types d'objets du jeu
 */
typedef enum{quete, arme, bouclier, protection, amulette, consommable}t_item;

/**
 * \struct struct objet
 * \brief Structure objet
 * \author Descomps Max
 */

typedef struct objet_s {
    t_aff * texture; /**<Image de l'objet*/
    char * texture_src; /**<Chemin de l'image de l'objet*/
    t_item type; /**<Le type d'objet permet de contrôler sa bonne utilisation*/
	char * nom; /**<Le nom de l'objet*/
	short int niveau; /**<Le niveau necessaire pour équiper l'objet*/
	int attaque; /**<modificateur d'attaque de l'objet*/
    int defense; /**<modificateur de defense de l'objet*/
    int vitesse; /**<modificateur de vitesse de l'objet*/
}objet_t;

/**
 * \fn objet_t * creer_objet(const char * const texture_src, const t_item type, const char * nom, const short int niveau, const int att, const int def, const int vit)
 * \brief Créé un objet du jeu
 * \param texture_src Chemin vers l'image de l'objet
 * \param type Type d'objet
 * \param nom Nom de l'objet
 * \param niveau Niveau nécessaire pour s'équiper de l'objet
 * \param att Bonus d'attaque de l'objet
 * \param def Bonus de défense de l'objet
 * \param vit Bonus de vitesse de l'objet
 * \return Instance nouvellement allouée du type objet_t ou NULL
 */
extern objet_t * creer_objet(const char * const texture_src, const t_item type, const char * nom, const short int niveau, const int att, const int def, const int vit);

/**
 * \fn void detruire_objet(objet_t **obj)
 * \brief Libère la mémoire allouée à un objet
 * \param obj L'objet à libérer
 */
extern void detruire_objet(objet_t **obj);

/**
 * \fn void afficher_objet(objet_t * obj)
 * \brief Affiche les caractéristiques d'un objet dans la console
 * \param obj L'objet à afficher
 */
extern void afficher_objet(objet_t * obj);
#endif