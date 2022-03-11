#include <commun.h>
#include <stdio.h>
#include <math.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
bool running = vrai;
#define NB_FPS 30

void afficher_intro(void){
    int i;
    SDL_Rect aff_logo = {0,0,FENETRE_LONGUEUR,FENETRE_LARGEUR};

    SDL_Surface *temp = SDL_LoadBMP("ressources/background/logo.bmp");
    if (!temp)
    {
        fprintf(stderr, "Erreur lors du chargement de la texture : %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *text = SDL_CreateTextureFromSurface(rendu_principal, temp);
    if (!text)
    {
        fprintf(stderr, "Erreur lors de la convertion de la surface : %s\n", SDL_GetError());
        return;
    }

    SDL_FreeSurface(temp);

    if(SDL_SetTextureAlphaMod(text, 0))
        fprintf(stderr,"Erreur : impossible de régler l'alpha de la texture : %s\n", SDL_GetError());

    for(i = 0; i < 256; i += 5 ){ /* Fondu (apparition du logo) */
        if (logo_passer())
            return;
        SDL_SetTextureAlphaMod(text, i);
        SDL_RenderClear(rendu_principal);
        if (SDL_RenderCopy(rendu_principal, text, NULL, &aff_logo) != 0)
            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(50);
    }

    SDL_Delay(1500); /* Temps pendant lequel le logo rest à l'écran */

    for (i = 255; i > 0; i -= 5) /* Fondu (disparition du logo) */
    {
        if (logo_passer())
            return;
        SDL_SetTextureAlphaMod(text, i);
        SDL_RenderClear(rendu_principal);
        if (SDL_RenderCopy(rendu_principal, text, NULL, &aff_logo) != 0)
            SDL_RenderPresent(rendu_principal);
        SDL_Delay(50);
    }

    SDL_Delay(150);
}

int t_affichage(void *ptr){

    int debut, fin; /* le temps pour calculer les performances */
    int i;
    
    t_l_aff* textures_joueur = init_textures_joueur();
    t_aff* next_texture_joueur;

    for(i=0; i<textures_joueur->nb_valeurs; i++)
        if(textures_joueur->liste == NULL)
            exit(EXIT_FAILURE);
    perso_principal = creer_joueur("test");

    while (running)
    {
        debut = SDL_GetPerformanceCounter();
        next_texture_joueur = next_frame_joueur(textures_joueur);
        //next_frame_y_indice(text, perso_principal->orientation);
        SDL_RenderClear(rendu_principal);
        afficher_texture(next_texture_joueur, rendu_principal);
        SDL_RenderPresent(rendu_principal);
        //next_frame_x(text);

        fin = SDL_GetPerformanceCounter();

        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float) NB_FPS) - temps_passe));
    }
    return 0;
}

int main(int argc, char** argv)
{
    SDL_Thread *f_t_aff;
    printf("bonjour\n\n");
    init();
    afficher_intro();
    f_t_aff = SDL_CreateThread(t_affichage,"thread affichage", NULL);
    if(f_t_aff == NULL){
        fprintf(stderr,"Erreur : le thread n'a pas pus être créer : %s\n", SDL_GetError());
        exit(SDL_ERREUR);
    }
    SDL_DetachThread(f_t_aff);

    while (running)
    {   
        jeu_event();
    }


}