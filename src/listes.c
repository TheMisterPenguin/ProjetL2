#include <stdlib.h>
#include <stdio.h>

typedef struct element
{
    void *valeur;
    struct element *pred;
    struct element *succ;
} t_element;

typedef struct list{
    t_element *flag;
    t_element *ec;
    unsigned int nb_elem;
    void * (*ajout)(void *);
    void (*del)(void *);
}list;

list * init_liste(void *(*fonction_ajout)(void *), void (*fonction_suppresion)(void *)){
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
        precedent(mylist);
        mylist->ec->succ = t->succ;
        (t->succ)->pred = mylist->ec;
        if(mylist->del == NULL)
            free(t->valeur);
        else
            mylist->del(&t->valeur);
        (mylist->nb_elem)--;
    }
}

void ajout_droit(list *mylist, void * v){
    t_element *t;

    t = malloc(sizeof(t_element));
    if(mylist->ajout == NULL)
        t->valeur = v;
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
    for(unsigned int i = 0; i < mylist->nb_elem; i++){
        oter_elt(mylist);
    }
}