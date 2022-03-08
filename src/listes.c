// Mise en oeuvre par pointeurs de listes de base_monstre
#include <stdlib.h>
#include <listes.h>
#include <commun.h>


// Primitives de listes 

void init_liste(t_liste *l) {
	l->drapeau = (t_element*)malloc(sizeof(t_element));

	l->drapeau->pred = l->drapeau;
	l->drapeau->succ = l->drapeau;
	l->ec = l->drapeau;
}

int liste_vide(t_liste *l) {
	return ((l->drapeau->pred == l->drapeau) && (l->drapeau->succ == l->drapeau));
}

int hors_liste(t_liste *l) {
	return (l->ec == l->drapeau);
}

void en_tete(t_liste *l) {
	if(!liste_vide(l))
		l->ec = l->drapeau->succ;
}

void en_queue(t_liste *l) {
	if(!liste_vide(l))
		l->ec = l->drapeau->pred;
}

void suivant(t_liste *l) {
	if(!hors_liste(l))
		l->ec = l->ec->succ;
}

void precedent(t_liste *l) {
	if(!hors_liste(l))
		l->ec = l->ec->pred;
}

void valeur_elt(t_liste *l, base_monstre_t* f) {
	if(!hors_liste(l))
		*f = l->ec->f;
}

void modif_elt(t_liste *l, base_monstre_t f) {
	if(!hors_liste(l))
		l->ec->f = f;
}

void oter_elt(t_liste *l) {
	if(!hors_liste(l)) {
		t_element* p;

		(l->ec->pred)->succ = l->ec->succ;
		(l->ec->succ)->pred = l->ec->pred;
		p = l->ec;
		precedent(l);
		free(p);
	}
}

void ajout_droit(t_liste *l, base_monstre_t f) {
	if(liste_vide(l) || !hors_liste(l)) {
		t_element* nouv;

		nouv = (t_element*)malloc(sizeof(t_element));
		nouv->f = f;
		nouv->pred = l->ec;
		nouv->succ = l->ec->succ;
		//Mise a jour des chainages des voisins
		(l->ec->succ)->pred = nouv;
		l->ec->succ = nouv;
		//On se positionne sur le nouvel ?lement
		l->ec = nouv;
	}
}

void ajout_gauche(t_liste *l, base_monstre_t f) {
	if(liste_vide(l) || !hors_liste(l)) {
		t_element* nouv;

		nouv = (t_element*)malloc(sizeof(t_element));
		nouv->f = f;
		nouv->pred = l->ec->pred;
		nouv->succ = l->ec;
		//Mise a jour des chainages des voisins
		(l->ec->pred)->succ = nouv;
		l->ec->pred = nouv;
		//On se positionne sur le nouvel element
		l->ec = nouv;
	}
}

int taille(t_liste* l){
	int t=0;
	for(en_tete(l);!hors_liste(l);suivant(l))
		t++;
	return t;
}
