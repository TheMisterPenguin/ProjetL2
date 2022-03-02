/**
 * \file liste_objet.h
 * \author Descomps Max (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les définitions concernant les listes d'objets
 * \version 0.1
 * \date 24/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */


#ifndef __LOBJET_H__
#define __LOBJET_H__

#include "objet.h"

/**
 * \struct struct lobjet
 * \brief Structure de liste d'objets
 * 
 * \author Descomps Max
 */

typedef struct lobjet_s {
    int nb;
    objet_t ** liste;
}lobjet_t;

lobjet_t * creer_liste_objet(void);
void detruire_liste_objet( lobjet_t ** liste_obj);
void afficher_liste_objet( lobjet_t * const liste_obj );
#endif