#include <commun.h>

/**
 * \file test_personnage.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du module personnage
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    joueur_t * perso_principal = NULL;

    init();

    perso_principal = new_joueur("test");

    objets = creer_liste_objet();
    creer_textures_objets(objets);
    tout_ramasser(objets, perso_principal->inventaire);

    afficher_statistiques(perso_principal);
    detruire_joueur(perso_principal);

    fermer_programme(EXIT_SUCCESS);

    return 0;
}