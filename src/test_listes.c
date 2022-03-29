#include <commun.h>
#include <listes.h>
#include <affichage.h>

/**
 * \file test_listes.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du type de structure liste générique
 * \version 0.1
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

void afficher_int(int * nb){
    printf("%d ", *nb);
}

int main(){
    list * liste_int = NULL;

    printf("----- Création de liste de textures -----\n\n");
    init();

    printf("----- Ajouts droits à la liste -----\n\n");
    creer_texture(N_T_MARCHER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    creer_texture(N_T_ATTAQUE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    creer_texture(N_T_ATTAQUE_CHARGEE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);

    printf("----- Affichage de la liste -----\n\n");
    afficher_liste(listeDeTextures);

    printf("----- Création de simple liste d'entiers -----\n\n");
    liste_int = init_liste(NULL, NULL, (void(*)(void *))afficher_int);
    
    printf("----- Affichage d'une liste vide -----\n\n");
    afficher_liste(liste_int);

    printf("----- destruction d'une liste vide -----\n\n");
    detruire_liste(&liste_int);

    fermer_programme(EXIT_SUCCESS);

    return 0;
}