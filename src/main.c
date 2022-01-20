#include <commun.h>
#include <fonctions.h>
#include <stdio.h>

SDL_Window *fenetre_Principale = NULL;

int main(int argc, char** argv)
{
    /* Initialisation simple */
    init();
 
            SDL_Surface *perso = SDL_LoadBMP("ressources/sprite/Sprite-perso1.bmp");
            SDL_Rect dest = { 640/2 - perso->w/2,480/2 - perso->h/2, 0, 0};
            SDL_BlitSurface(perso,NULL,SDL_GetWindowSurface(fenetre_Principale),&dest);
            SDL_UpdateWindowSurface(fenetre_Principale);
            SDL_Delay(9999);
            SDL_MinimizeWindow(fenetre_Principale);
            SDL_Delay(3000);
            SDL_MaximizeWindow(fenetre_Principale);
            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

            SDL_FreeSurface(perso);
    
    terminate();

    return 0;
}