/**
 * \file personnage.h
 * \author Descomps Max (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les définitions concernant les objets
 * \version 0.2
 * \date 24/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */


#ifndef __OBJET_H__
#define __OBJET_H__

typedef enum{quete, arme, protection, amulette, consommable}t_item;

/**
 * \struct struct objet_s
 * 
 * \author Descomps Max
 */

typedef struct objet_s {
    char * type; /**<Le type d'objet permet de contrôler sa bonne utilisation*/
	char * nom; /**<Le nom de l'objet*/
	short int niveau; /**<Le niveau necessaire pour équiper l'objet*/
	int attaque; /**<modificateur d'attaque de l'objet*/
    int defense; /**<modificateur de defense de l'objet*/
    int vitesse; /**<modificateur de vitesse de l'objet*/
}objet_t;


extern objet_t * creer_objet(const t_item type, const char * nom, const short int niveau, const int att, const int def, const int vit);
extern void detruire_objet(objet_t *obj);
// void init_objet(void);
#endif