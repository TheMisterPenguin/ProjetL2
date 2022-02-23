#include <commun.h>
#include <stdio.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
t_game game;

int t_affichage(void *ptr){

    for(int i = 0; i < 10; i++)
        printf("Cet affichage est dans le thread affichage !\n");

    return 0;
}

int main(int argc, char** argv)
{
    /*SDL_Thread *p_t_affichage;
    int val_retour;

    p_t_affichage = SDL_CreateThread(t_affichage, "Gestion de l'affichage du programme", NULL);
    /* Initialisation simple 
    
    for(int i = 0; i < 15; i++)
        printf("%i\n", i);

    SDL_WaitThread(p_t_affichage, &val_retour);*/

    printf("test\n");
    init();

    t_aff *text = creer_texture(N_T_PLAYER_WALK, 14, 21, 50,50,10);

    if(! text) 
        exit(EXIT_FAILURE);
    
    next_frame_y_indice(text, 2);
    while (SDL_TRUE)
    {
        SDL_RenderClear(rendu_principal);
        afficher_texture(text, rendu_principal);
        SDL_RenderPresent(rendu_principal);
        next_frame_x(text);
        jeu_event();
    }
    
    

}