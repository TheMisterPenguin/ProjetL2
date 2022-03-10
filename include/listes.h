/**
 * \file liste.h
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief 
 * \version 1.0
 * \date 10/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __LISTE_H__
#define __LISTE_H__

/**
 * \brief Définition du type liste
 * 
 */
typedef struct list list;

/**
 * Fonction qui permet de créer une liste
 *
 * On peut préciser des fonction pour l'insertion et la supprésion des objets.
 *
 * Mais on ne peut pas avoir une fonction d'insertion et aucune fonction de supprésion et vice-versa.
 *
 * Par défault la liste fonctionne par référencement, pour cela il suffit de ne pas fournir de fonctions dans l'appel de la fonction.
 *
 * On attend des éléments dynamiques dans la liste
 * 
 * \param fonction_ajout La fonction qui permet d'intertion des objets, NULL sinon
 * \param f_suppresion La fonction qui permet la suppresion des objets, NULL sinon
 * \return La liste qui vient d'être crée, NULL s'il y a eu une erreur
 */
extern list *init_liste(void *(*fonction_ajout)(void *), void (*f_suppresion)(void *));

/**
 * Fonction booléenne qui permet de savoir si la liste est vide.
 * 
 * \param to_verify La liste que l'on doit vérifier
 * \return Vrai si la liste est vide, faux sinon
 */
extern _Bool liste_vide(const list * const to_verify);

/**
 * Fonction booléenne qui permet de savoir si ll'on est actuellement hors de la liste.
 * 
 * \param to_verify La liste que l'on doit vérifier
 * \return Vrai si on se trouve en dehors de la liste, faux sinon
 */
extern _Bool hors_liste(const list * const to_verify);

/**
 * Fonction qui permet de se placer en tête de la liste.
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void en_tete(list *mylist);

/**
 * Fonction qui permet de se placer en queue de la liste.
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void en_queue(list *mylist);

/**
 * Fonction qui permet de passer à l'élément suivant dans la liste
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void suivant(list *mylist);

/**
 * \Fonction qui permet de passer à l'élément suivant dans la liste
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void precedent(list *mylist);

/**
 * Fonction qui renvoie l'élément courant
 * 
 * \param mylist La liste dont on veut l'élément
 * \return L'élément que l'on convoite
 */
extern void * valeur_elt(const list *const mylist);

/**
 * Fonction qui permet de modifier l'élément courant. 
 * 
 * ATTENTION : si les élément sont placés dans la liste par référencement cela détruira l'élément précédent !
 * 
 * \param mylist La liste donc on veut modifier l'élément courant
 * \param v L'élément à mettre à la place de l'ancien
 */
extern void modif_elt(list *mylist, void *v);

/**
 * Fonction qui permet de supprimer un élément de la liste.
 *
 * ATTENTION : si les élements sont placés dans la liste par référencement cela détruira l'élément (ne pas y accéder après) !
 *
 * On attend des éléments dynamiques dans la liste.
 *
 * \param mylist La liste dont on veut oter l'éléement
 */
extern void oter_elt(list *mylist);

/**
 * Fonction qui permet d'ajouter un élément à droite de l'élément courant
 * 
 * \param mylist La liste où on veut ajouter l'élément
 * \param v L'élément que l'on veut ajouter
 */
extern void ajout_droit(list *mylist, void *v);

/**
 * Fonction qui permet d'ajouter un élément à gauche de l'élément courant
 *
 * \param mylist La liste où on veut ajouter l'élément
 * \param v L'élément que l'on veut ajouter
 */
extern void ajout_gauche(list *mylist, void *v);

/**
 * Fonction qui renvoie le nombre d'éléments dans la liste
 * 
 * \param mylist La liste dont on veut conaitre le nombre d'éléments
 * \return Le nombre d'élements dans la liste
 */
extern unsigned int taille_liste(const list *const mylist);

/**
 * Fonction qui supprimme tout les éléments de la liste. 
 * 
 * ATTENTION : si les éléments sont insérés par référencement, ils seront tous détruits ! 
 * 
 * On attend des éléments dynamiques dans la liste.
 * 
 * \param mylist La liste que l'on veut vider
 */
extern void vider_liste(list *mylist);
#endif