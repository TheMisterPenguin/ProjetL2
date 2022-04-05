/**
 * \file listes.h
 * \authors Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \authors Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonction relatives au type de structure liste générique
 * \version 2.0
 * \date 03/04/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __LISTE_H__
#define __LISTE_H__

/**
 * \brief Définition dy type element : un élément d'une liste.
 * \author Ange Despert
 */
typedef struct element
{
    void *valeur; /**<La valeur de l'élément, un pointeur générique*/
    struct element *pred; /**<L'élément précédant*/
    struct element *succ; /**<L'élément suivant*/
} t_element;

/**
 * \brief Définition du type list : une liste générique.
 * \authors Ange Despert
 * \authors Max Descomps
 */
typedef struct list{
    t_element *flag; /**<Le drapeau (1er élément)*/
    t_element *ec; /**<L'élément courant*/
    unsigned int nb_elem; /**<Le nombre d'élément dans la liste*/
    void * (*ajout)(void *); /**<Une fonction pour ajouter un élément dans la liste*/
    void (*del)(void *); /**<Une fonction pour retirer un élément de la liste*/
    void (*aff)(void *); /**<Une fonction pour afficher un élément de la liste*/
}list;
/**
 * \brief Fonction qui permet de créer une liste.
 * \authors Ange Despert
 * \authors Max Descomps
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
 * \param fonction_affichage La fonction qui permet d'afficher les objets de la liste, NULL sinon
 * \return La liste qui vient d'être crée, NULL s'il y a eu une erreur
 */
extern list *init_liste(void *(*fonction_ajout)(void *), void (*f_suppresion)(void *), void (*fonction_affichage)(void *));

/**
 * \brief Fonction booléenne qui permet de savoir si la liste est vide.
 * \author Ange Despert
 * 
 * \param to_verify La liste que l'on doit vérifier
 * \return Vrai si la liste est vide, faux sinon
 */
extern _Bool liste_vide(const list * const to_verify);

/**
 * \brief Fonction booléenne qui permet de savoir si ll'on est actuellement hors de la liste.
 * \author Ange Despert
 * 
 * \param to_verify La liste que l'on doit vérifier
 * \return Vrai si on se trouve en dehors de la liste, faux sinon
 */
extern _Bool hors_liste(const list * const to_verify);

/**
 * \brief Fonction qui permet de se placer en tête de la liste.
 * \author Ange Despert
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void en_tete(list *mylist);

/**
 * \brief Fonction qui permet de se placer en queue de la liste.
 * \author Ange Despert
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void en_queue(list *mylist);

/**
 * \brief Fonction qui permet de passer à l'élément suivant dans la liste.
 * \author Ange Despert
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void suivant(list *mylist);

/**
 * \brief Fonction qui permet de passer à l'élément suivant dans la liste.
 * \author Ange Despert
 * 
 * \param mylist La liste dans laquelle on se déplace
 */
extern void precedent(list *mylist);

/**
 * \brief Fonction qui renvoie l'élément courant.
 * \author Ange Despert
 * 
 * \param mylist La liste dont on veut l'élément
 * \return L'élément que l'on convoite
 */
extern void * valeur_elt(const list *const mylist);

/**
 * \brief Fonction qui permet de modifier l'élément courant. 
 * \author Ange Despert
 * 
 * ATTENTION : si les élément sont placés dans la liste par référencement cela détruira l'élément précédent !
 * 
 * \param mylist La liste donc on veut modifier l'élément courant
 * \param v L'élément à mettre à la place de l'ancien
 */
extern void modif_elt(list *mylist, void *v);

/**
 * \brief Fonction qui permet de supprimer un élément de la liste.
 * \author Ange Despert
 *
 * ATTENTION : si les élements sont placés dans la liste par référencement cela détruira l'élément (ne pas y accéder après) !
 *
 * On attend des éléments dynamiques dans la liste.
 *
 * \param mylist La liste dont on veut oter l'éléement
 */
extern void oter_elt(list *mylist);

/**
 * \brief Fonction qui permet d'ajouter un élément à droite de l'élément courant.
 * \author Ange Despert
 * 
 * \param mylist La liste où on veut ajouter l'élément
 * \param v L'élément que l'on veut ajouter
 */
extern void ajout_droit(list *mylist, void *v);

/**
 * \brief Fonction qui permet d'ajouter un élément à gauche de l'élément courant.
 * \author Ange Despert
 *
 * \param mylist La liste où on veut ajouter l'élément
 * \param v L'élément que l'on veut ajouter
 */
extern void ajout_gauche(list *mylist, void *v);

/**
 * \brief Fonction qui renvoie le nombre d'éléments dans la liste.
 * \author Ange Despert
 * 
 * \param mylist La liste dont on veut conaitre le nombre d'éléments
 * \return Le nombre d'élements dans la liste
 */
extern unsigned int taille_liste(const list *const mylist);

/**
 * \brief Fonction qui supprimme tout les éléments de la liste. 
 * \author Ange Despert
 * 
 * ATTENTION : si les éléments sont insérés par référencement, ils seront tous détruits ! 
 * 
 * On attend des éléments dynamiques dans la liste.
 * 
 * \param mylist La liste que l'on veut vider
 */
extern void vider_liste(list *mylist);

/**
 * \brief Détruit une liste en détruisant tout ses éléménts.
 * \author Ange Despert
 * \param liste Adresse de la liste
 */
extern void detruire_liste(list ** liste);

/**
 * \brief Affiche une liste d'objets génériques.
 * \author Max Descomps 
 * \param liste Pointeur sur la liste
 */
void afficher_liste(list * liste);

/**
 * \brief Fonction qui permet de selectionner l'élément courant à partir d'un élément précis.
 * \author Ange Despert
 * 
 * \param liste La liste dans laquelle on veut faire la recherche
 * \param element L'élément que l'on veut rechercher
 * \param f_egalite Une fonction de comparaison qui renvoie vrai si les deux valeurs sont égales ou NULL si on veut comparer les adresses
 * \return Vrai si l'élément à été trouvé
 */
_Bool selectionner_element(list *liste, void *element, _Bool (*f_egalite)(void *, void *));
#endif