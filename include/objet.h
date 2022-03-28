/**
 * \file objet.h
 * \author Descomps Max (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les définitions concernant les objets
 * \version 0.3
 * \date 24/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */


#ifndef __OBJET_H__
#define __OBJET_H__

#include "definition_commun.h"
#include "affichage.h"

typedef enum{quete, arme, bouclier, protection, amulette, consommable}t_item;

/**
 * \struct struct objet
 * \brief Structure objet
 * 
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

void detruire_texture(t_aff **texture);

extern objet_t * creer_objet(const char * const texture_src, const t_item type, const char * nom, const short int niveau, const int att, const int def, const int vit);
extern void detruire_objet(objet_t **obj);
extern objet_t ** init_objet(void);
extern void afficher_objet(objet_t * obj);
#endif