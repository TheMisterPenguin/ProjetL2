#include <stdlib.h>
#include <stdio.h>
#include <listes.h>

/**
 * \file listes.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonctions relatives au type de structure liste générique
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

list * init_liste(void *(*fonction_ajout)(void *), void (*fonction_suppresion)(void *),
    void (*fonction_affichage)(void *)){
    if(fonction_ajout == NULL)
        if(fonction_suppresion != NULL)
            return NULL;
    if(fonction_suppresion == NULL)
        if(fonction_ajout != NULL)
            return NULL;

    list *new = malloc(sizeof(list));
    new->flag = malloc(sizeof(t_element));
    new->flag->pred = new->flag;
    new->flag->succ = new->flag;
    new->ec = new->flag;
    new->nb_elem = 0;
    new->ajout = fonction_ajout;
    new->del = fonction_suppresion;
    new->aff = fonction_affichage;

    return new;
}

_Bool liste_vide(const list * const to_verify) {return (to_verify->flag->pred == to_verify->flag);}

_Bool hors_liste(const list * const to_verify) {return to_verify->ec == to_verify->flag;}

void en_tete(list *mylist){
    if (!liste_vide(mylist))
        mylist->ec = mylist->flag->succ;
}

void en_queue(list *mylist){
    if (!liste_vide(mylist))
        mylist->ec = mylist->flag->pred;
}

void suivant(list *mylist){
    if (!hors_liste(mylist))
        mylist->ec = mylist->ec->succ;
}

void precedent(list *mylist){
    if (!hors_liste(mylist))
        mylist->ec = mylist->ec->pred;
}

void * valeur_elt(const list * const mylist){
    if (!hors_liste(mylist))
        return (mylist->ec->valeur);

    return NULL;
}

void modif_elt(list *mylist, void * v)
{
    if (!hors_liste(mylist)){
            if(mylist->del == NULL){
                free(mylist->ec->valeur);
                mylist->ec->valeur = v;
            }
            else{
                mylist->del(&mylist->ec->valeur);
                mylist->ajout(mylist->ec->valeur);
            }
    }
        else
            mylist->ec->valeur = mylist->ajout(v);
}

void oter_elt(list *mylist){
    t_element *t;

    if (!hors_liste(mylist))
    {
        t = mylist->ec;
        suivant(mylist);
        mylist->ec->pred = t->pred;
        t->pred->succ = mylist->ec;
        if(mylist->del != NULL){
            mylist->del(&t->valeur);
        }
        (mylist->nb_elem)--;

        free(t);
    }
    else
        printf("hors liste\n");
}

void ajout_droit(list *mylist, void * v){
    t_element *t;

    t = malloc(sizeof(t_element));
    if(mylist->ajout == NULL){
        t->valeur = v;
    }
    else
        t->valeur = mylist->ajout(v);

    t->pred = mylist->ec;
    t->succ = mylist->ec->succ;
    (mylist->ec->succ)->pred = t;
    mylist->ec->succ = t;
    mylist->ec = t;
    (mylist->nb_elem)++;
}

void ajout_gauche(list *mylist, void * v){
    t_element *t;

    t = malloc(sizeof(t_element));
    if (mylist->ajout == NULL)
        t->valeur = v;
    else
        t->valeur = mylist->ajout(v);
    t->succ = mylist->ec;
    t->pred = mylist->ec->pred;
    (mylist->ec->pred)->succ = t;
    mylist->ec->pred = t;
    mylist->ec = t;
    (mylist->nb_elem)++;
}

unsigned int taille_liste(const list * const mylist){return mylist->nb_elem;}

void vider_liste(list *mylist){

    en_tete(mylist);
    while(!hors_liste(mylist)){
        oter_elt(mylist);
    }
}

void detruire_liste(list ** liste){
    vider_liste(*liste);

    free((*liste)->flag);

    free(*liste);
    *liste = NULL;
}

void afficher_liste(list * liste){
    if(liste->aff == NULL){
        printf("Pas de fonction d'affichage pour cette liste\n");
    }
    else{
        en_tete(liste);

        while(!hors_liste(liste)){
            liste->aff(liste->ec->valeur);
            suivant(liste);
        }
    }
}

_Bool selectionner_element(list * liste, void * element, _Bool (*f_egalite)(void *, void *)){
    
    if(liste_vide(liste))
        return 0;

    en_tete(liste);

    while(!hors_liste(liste)){
        if(f_egalite == NULL){
            if(valeur_elt(liste) == element)
                return 1;
        }
        else{
            if(f_egalite(valeur_elt(liste), element))
                return 1;
        }

        suivant(liste);
    }

    return 0;
}