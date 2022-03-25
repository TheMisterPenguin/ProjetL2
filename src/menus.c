#include <stdlib.h>
#include <string.h>
#include <affichage.h>

/*void afficher_menu(menus_t * menu){
    switch (menu) {
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
    
        default: exit(EXIT_SUCCESS);
    }
}*/

void afficher_menu_pause(){

    int debut, fin; /* le temps pour calculer les performances */
    t_aff * text_pause = creer_texture("ressources/background/menu/Sprite_Menu_Pause.bmp", -1, -1, 0, 0, 0);

    if(!text_pause){
        return;
    }
    while(1){
        debut = SDL_GetPerformanceCounter();
        SDL_RenderClear(rendu_principal);

        afficher_texture(text_pause, rendu_principal);

        SDL_RenderPresent(rendu_principal);
        SDL_Event lastEvent; /* On récupère les événements */

        while (SDL_PollEvent(&lastEvent))
        {
            switch (lastEvent.type)
            {
            case SDL_QUIT:
                printf("Détection de la fermeture de la fenêtre\n");
                exit(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                if (lastEvent.key.keysym.sym == SDLK_ESCAPE)
                    return;
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            }
        }
        fin = SDL_GetPerformanceCounter();
        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float)60) - temps_passe));
        compteur++;
        }
}