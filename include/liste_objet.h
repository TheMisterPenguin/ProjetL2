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


extern lobjet_t * objets;

#include "inventaire.h"

lobjet_t * creer_liste_objet(void);
lobjet_t * creer_liste_objet_vide(void);
void detruire_liste_objet( lobjet_t ** liste_obj);
void afficher_liste_objet( lobjet_t * const liste_obj );
lobjet_t * creer_liste_objet_equipe();
void effacer_liste_objet( lobjet_t ** liste_obj);
void placer_objet_sac(objet_t * objet, int slot);
void afficher_textures_sac( inventaire_t * const inventaire );
void afficher_textures_equipe( inventaire_t * const inventaire );

/**
 * \fn void creer_textures_objets(lobjet_t * objets)
 * \brief Creer toutes les textures d'une structure lobjet_t
 * \param liste_obj Pointeur sur la structure lobjet_t
 */
void creer_textures_objets(lobjet_t * liste_obj);

#endif