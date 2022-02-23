/**
 * \file personnage.h
 * \author Descomps Max
 * \brief Fichier contenant toutes les définitions concernant les objets
 * \version 0.1
 * \date 23/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */


#ifndef __OBJET_H__
#define __OBJET_H__

/**
 * \struct struct objet_s
 * 
 * \author Descomps Max
 */

typedef struct objet_s {
	char * nom; /**<Le nom de l'objet*/
	short int niveau; /**<Le niveau necessaire pour équiper l'objet*/
	int attaque; /**<modificateur d'attaque de l'objet*/
    int defense; /**<modificateur de defense de l'objet*/
    int vitesse; /**<modificateur de vitesse de l'objet*/
}objet_t;


extern objet_t * creer_objet(const char * nom, const short int niveau, const int att, const int def, const int vit);
extern void detruire_objet(objet_t *obj);
#endif