#include <fonctions.h>
#include <event.h>
#include <affichage.h>
#include <definition_commun.h>
#include <map.h>
#include <stdio.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
bool running = vrai;
long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(int argc, char **argv){
    SDL_Event e;
    init();

    char * fichier_map = charger_f_map("map.json");
    t_map *test_map = charger_s_map(fichier_map);
    t_aff *text = texture_map(test_map);
        free(fichier_map);

    while (vrai){
        if (!text)
            exit(EXIT_FAILURE);

        SDL_RenderClear(rendu_principal);
        afficher_texture(text, rendu_principal);
        SDL_RenderPresent(rendu_principal);

        SDL_WaitEvent(&e);

        if(e.key.keysym.sym == SDLK_ESCAPE)
            exit(EXIT_SUCCESS);
    }

    return 0;
}