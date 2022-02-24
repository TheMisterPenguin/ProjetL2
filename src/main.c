#include <commun.h>
#include <stdio.h>
#include <math.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
bool running = vrai;

void afficher_intro(void){
    int i;
    t_aff *text_intro = creer_texture("ressources/background/logo.bmp",640,480,0,0,1);

    for(i = 0; i < 256; i += 5 ){ /* Fondu (apparition du logo) */
        SDL_SetTextureAlphaMod(text_intro->texture, i);
        SDL_RenderClear(rendu_principal);
        afficher_texture(text_intro, rendu_principal);
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(50);
    }

    SDL_Delay(1500); /* Temps pendant lequel le logo rest à l'écran */

    for (i = 255; i > 0; i -= 5) /* Fondu (disparition du logo) */
    {
        SDL_SetTextureAlphaMod(text_intro->texture, i);
        SDL_RenderClear(rendu_principal);
        afficher_texture(text_intro, rendu_principal);
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(50);
    }

    SDL_Delay(150);
}

int t_affichage(void *ptr){

    int debut, fin; /* le temps pour calculer les performances */

    t_aff *text = creer_texture(N_T_PLAYER_WALK, 14, 21, 150, 150, 10);

    if (!text)
        exit(EXIT_FAILURE);
    perso_principal = creer_joueur("test");

    while (running)
    {
        debut = SDL_GetPerformanceCounter();
        next_frame_y_indice(text, perso_principal->orientation);
        SDL_RenderClear(rendu_principal);
        afficher_texture(text, rendu_principal);
        SDL_RenderPresent(rendu_principal);
        next_frame_x(text);

        fin = SDL_GetPerformanceCounter();

        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(32.666f - temps_passe));
    }
    return 0;
}

int main(int argc, char** argv)
{
    SDL_Thread *f_t_aff;

    init();

    afficher_intro();

    f_t_aff = SDL_CreateThread(t_affichage,"thread affichage", NULL);
    SDL_DetachThread(f_t_aff);

    while (running)
    {   
        jeu_event();
    }
    

}