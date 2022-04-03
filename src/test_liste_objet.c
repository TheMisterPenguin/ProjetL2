#include <commun.h>

/**
 * \file test_liste_objet.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du module liste_objet
 * \version 0.1
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    lobjet_t * liste_obj = NULL;

    init();
    
    printf("----- Création de la liste d'objets selon le fichier correspondant -----\n\n");
    liste_obj = creer_liste_objet("../ressource/objet.txt");

    printf("----- Affichage de la liste d'objets -----\n\n");
    afficher_liste_objet(liste_obj);

    printf("----- Destruction de la liste d'objets -----\n\n");
    detruire_liste_objet(&liste_obj);

    fermer_programme(EXIT_SUCCESS);
    return 0;
}