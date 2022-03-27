#include <stdlib.h>
#include <string.h>
#include <affichage.h>
#include <personnage.h>

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

    SDL_Rect boutton_sortie = {.h = floor(56 * multiplicateur_y), .w = floor(66 * multiplicateur_x)};

    SDL_Rect boutton_quitter = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_reprendre = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_sauvegarder = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_charger = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};

    deplacer_rect_haut_droit(&boutton_sortie, floor(-9 * multiplicateur_x), floor(7 * multiplicateur_y));

    deplacer_rect_origine(&boutton_quitter, floor(427 * multiplicateur_x), floor(836 * multiplicateur_y));
    deplacer_rect_origine(&boutton_reprendre, floor(427 * multiplicateur_x), floor(108 * multiplicateur_y));
    deplacer_rect_origine(&boutton_charger, floor(427 * multiplicateur_x), floor(590 * multiplicateur_y));
    deplacer_rect_origine(&boutton_sauvegarder, floor(427 * multiplicateur_x), floor(348 * multiplicateur_y));

    if(!text_pause){
        return;
    }
    while(1){
        debut = SDL_GetPerformanceCounter();
        SDL_RenderClear(rendu_principal);
        afficher_texture(text_pause, rendu_principal);

        SDL_RenderDrawRect(rendu_principal, &boutton_sortie);
        SDL_RenderDrawRect(rendu_principal, &boutton_quitter);

        SDL_RenderPresent(rendu_principal);
        SDL_Event lastEvent; /* On récupère les événements */

        SDL_Point coord_souris;
        while (SDL_PollEvent(&lastEvent))
        {
            switch (lastEvent.type)
            {
            case SDL_QUIT:
                printf("Détection de la fermeture de la fenêtre\n");
                fermer_programme(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                if (lastEvent.key.keysym.sym == SDLK_ESCAPE)
                    return;
                break;
            case SDL_MOUSEBUTTONUP:
                coord_souris.x = lastEvent.button.x;
                coord_souris.y = lastEvent.button.y;

                if(SDL_PointInRect(&coord_souris, &boutton_sortie))
                    return;
                if(SDL_PointInRect(&coord_souris, &boutton_reprendre))
                    return;
                if(SDL_PointInRect(&coord_souris, &boutton_quitter))
                    fermer_programme(0);
                if (SDL_PointInRect(&coord_souris, &boutton_sauvegarder)){
                    creer_sauvegarde_json(perso_principal);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Sauvegarde", "La sauvegarde a été effectuée avec succès\n", NULL);
                    break;
                }
                if (SDL_PointInRect(&coord_souris, &boutton_charger)){
                    char temp[510];
                    sprintf(temp,"%s/perso.sav", save_path);
                    detruire_joueur(perso_principal);
                    perso_principal = charger_sauvegarde_joueur(temp);
                }
                break;
            }
        }
        fin = SDL_GetPerformanceCounter();
        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float)60) - temps_passe));
        compteur++;
        }
}