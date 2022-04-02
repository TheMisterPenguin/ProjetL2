/**
 * \file liste_objet.h
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Définition relatives aux structures contenant les objets
 * \version 1.0
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */


#ifndef __LOBJET_H__
#define __LOBJET_H__

#include "objet.h"

typedef struct objet_s objet_t;
typedef struct inventaire_s inventaire_t;

/**
 * \struct struct lobjet
 * \brief Structure de liste d'objets
 * \author Descomps Max
 */

typedef struct lobjet_s {
    int nb; /**<Nombre d'objets stockés*/
    objet_t ** liste; /**<Objets stockés*/
}lobjet_t;


extern lobjet_t * objets;

#include "inventaire.h"

/**
 * \fn lobjet_t * creer_liste_objet(char * fichier_src)
 * \brief Créé une liste d'objets et la remplit à l'aide du fichier des objets du jeu
 * \param fichier_src fichier source contenant la liste des objets
 * \return Instance nouvellement allouée du type lobjet_t ou NULL
 */
lobjet_t * creer_liste_objet(char * fichier_src);

/**
 * \fn lobjet_t * creer_liste_objet_vide(char * fichier_src)
 * \brief Créé une liste d'objets vide
 * \param fichier_src fichier source contenant la liste des objets pour en connaître le nombre
 * \return Instance nouvellement allouée du type lobjet_t ou NULL
 */
lobjet_t * creer_liste_objet_vide(char * fichier_src);

/**
 * \fn lobjet_t * creer_liste_objet_equipe()
 * \brief Créé une liste d'objets vide contenant les objets équipés
 * \return Instance nouvellement allouée du type lobjet_t ou NULL
 */
lobjet_t * creer_liste_objet_equipe();

/**
 * \fn void detruire_liste_objet( lobjet_t ** liste_obj)
 * \brief Détruit une liste d'objets
 * \param liste_obj La liste d'objets à détruire
 */
void detruire_liste_objet( lobjet_t ** liste_obj);

/**
 * \fn void afficher_liste_objet( lobjet_t * const liste_obj )
 * \brief Affiche une liste d'objets dans la console
 * \param liste_obj La liste d'objets à afficher
 */
void afficher_liste_objet( lobjet_t * const liste_obj );

/**
 * \fn void effacer_liste_objet( lobjet_t ** liste_obj)
 * \brief Efface une liste d'objets sans libérer la mémoire allouée aux objets qu'elle contient
 * \param liste_obj La liste d'objets à effacer
 */
void effacer_liste_objet( lobjet_t ** liste_obj);

/**
 * \fn void placer_objet_sac(objet_t * objet, int slot)
 * \brief Place la texture d'un objet contenu dans une liste d'objet dans le sac depuis le menu inventaire selon son numéro de slot
 * \param objet L'objet dont on place la texture dans le sac
 * \param slot le numéro de slot de l'objet
 */
void placer_objet_sac(objet_t * objet, int slot);

/**
 * \fn void afficher_textures_sac( inventaire_t * const inventaire )
 * \brief Affiche les textures des objets du sac dans le menu inventaire
 * \param inventaire L'inventaire contenant le sac
 */
void afficher_textures_sac( inventaire_t * const inventaire );

/**
 * \fn void afficher_textures_equipe( inventaire_t * const inventaire )
 * \brief Affiche les textures des objets équipés dans le menu inventaire
 * \param inventaire L'inventaire contenant les objets équipés
 */
void afficher_textures_equipe( inventaire_t * const inventaire );

/**
 * \fn void creer_textures_objets(lobjet_t * objets)
 * \brief Creer toutes les textures d'une structure lobjet_t
 * \param liste_obj Pointeur sur la structure lobjet_t
 */
void creer_textures_objets(lobjet_t * liste_obj);

#endif