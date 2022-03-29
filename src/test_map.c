#include <fonctions.h>
#include <event.h>
#include <affichage.h>
#include <definition_commun.h>
#include <map.h>
#include <stdio.h>

/**
 * \file test_map.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du module map
 * \version 0.1
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(int argc, char **argv){
    SDL_Event e;
    char * fichier_map = NULL;
    t_map *test_map = NULL;
    t_aff *text = NULL;


    init();

    printf("----- Analyse du fichier json -----\n");
    fichier_map = charger_f_map("map.json");

    printf("----- Création de texture map et traitement des informations json -----\n");
    test_map = charger_s_map(fichier_map);

    text = texture_map(test_map);

    while (vrai){
        if (!text)
            fermer_programme(EXIT_FAILURE);

        SDL_RenderClear(rendu_principal);
        afficher_texture(text, rendu_principal);
        SDL_RenderPresent(rendu_principal);

        SDL_WaitEvent(&e);

        if(e.key.keysym.sym == SDLK_ESCAPE)
            fermer_programme(EXIT_SUCCESS);
    }
    return 0;
}