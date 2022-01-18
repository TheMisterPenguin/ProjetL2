#include "../include/SDL2/SDL.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);

        if( pWindow )
        {   
            SDL_Surface *perso = SDL_LoadBMP("ressources/sprite/Sprite-perso1.bmp");
            SDL_Rect dest = { 640/2 - perso->w/2,480/2 - perso->h/2, 0, 0};
            SDL_BlitSurface(perso,NULL,SDL_GetWindowSurface(pWindow),&dest);
            SDL_UpdateWindowSurface(pWindow);
            SDL_Delay(9999);
            SDL_MinimizeWindow(pWindow);
            SDL_Delay(3000);
            SDL_MaximizeWindow(pWindow);
            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

            SDL_FreeSurface(perso);
            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();

    return 0;
}