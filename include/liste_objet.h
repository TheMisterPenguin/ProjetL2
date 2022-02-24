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

typedef enum{quete, arme, protection, amulette, consommable}t_item;

/**
 * \struct struct lobjet
 * \brief Structure de liste d'objets
 * 
 * \author Descomps Max
 */

typedef struct lobjet_s {
    int nbobj;
    objet_t ** liste;
}lobjet_t;

extern objet_t ** init_objet(void);
#endif