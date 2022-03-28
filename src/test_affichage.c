#include <commun.h>

/**
 * \file test_affichage.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du module affichage
 * \version 0.1
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    t_aff * text = NULL;

    init();
    text = creer_texture("ressources/background/logo.bmp", -1, -1, 0, 0, 0);
    
    fermer_programme(EXIT_SUCCESS);
    return 0;
}