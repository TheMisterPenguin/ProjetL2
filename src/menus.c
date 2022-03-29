#include <stdlib.h>
#include <string.h>
#include <affichage.h>
#include <personnage.h>
#include <liste_objet.h>
#include <inventaire.h>

/**
 * \file menus.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonctions des menus du jeu
 * \version 0.2
 * \date 29/03/2022
 * \copyright Copyright (c) 2022
 */

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

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Affichage du menu pause");

    t_aff * text_pause = creer_texture("ressources/background/menu/Sprite_Menu_Pause.bmp", -1, -1, 0, 0, 0);

    if (!text_pause){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors du chargement du menu pause");
        return;
    }

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

    while(1){
        debut = SDL_GetPerformanceCounter();
        SDL_RenderClear(rendu_principal);
        afficher_texture(text_pause, rendu_principal);

        SDL_RenderDrawRect(rendu_principal, &boutton_sortie);
        SDL_RenderDrawRect(rendu_principal, &boutton_quitter);

        SDL_RenderPresent(rendu_principal);
        SDL_Event lastEvent; /* On récupère les événements */

        SDL_Point coord_souris;
        while (SDL_PollEvent(&lastEvent)){
            switch (lastEvent.type)
            {
            case SDL_QUIT:

                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Détection de la fermeture de la fenêtre\n");
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
                if(SDL_PointInRect(&coord_souris, &boutton_quitter)){
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fermeture du programme ...\n");
                    fermer_programme(EXIT_SUCCESS);
                }
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
        
        if(compteur == NB_FPS)
            compteur = 0;
        else
            compteur++;
    }
}

void afficher_inventaire(joueur_t * joueur)
{
    int slot_selectionne = -1;
    int debut, fin; /* le temps pour calculer les performances */
    t_aff *text_pause = creer_texture("ressources/background/menu/inventaire.bmp", -1, -1, 0, 0, 0);
    if (!text_pause)
        return;

    /* Création des slots de l'inventaire */
    SDL_Rect slot0 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot1 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot2 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot3 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot4 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot5 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot6 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot7 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot8 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot9 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};

    SDL_Rect slot10 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot11 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot12 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot13 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot14 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};
    SDL_Rect slot15 = {.h = floor(144 * multiplicateur_y), .w = floor(120 * multiplicateur_x)};

    /* Placemennt des slots */
    deplacer_rect_origine(&slot0, floor(582 * multiplicateur_x), floor(659 * multiplicateur_y));
    deplacer_rect_origine(&slot1, floor(734 * multiplicateur_x), floor(659 * multiplicateur_y));
    deplacer_rect_origine(&slot2, floor(887 * multiplicateur_x), floor(659 * multiplicateur_y));
    deplacer_rect_origine(&slot3, floor(1038 * multiplicateur_x), floor(659 * multiplicateur_y));
    deplacer_rect_origine(&slot4, floor(1190 * multiplicateur_x), floor(659 * multiplicateur_y));
    deplacer_rect_origine(&slot5, floor(582 * multiplicateur_x), floor(787 * multiplicateur_y));
    deplacer_rect_origine(&slot6, floor(734 * multiplicateur_x), floor(787 * multiplicateur_y));
    deplacer_rect_origine(&slot7, floor(887 * multiplicateur_x), floor(787 * multiplicateur_y));
    deplacer_rect_origine(&slot8, floor(1038 * multiplicateur_x), floor(787 * multiplicateur_y));
    deplacer_rect_origine(&slot9, floor(1190 * multiplicateur_x), floor(787 * multiplicateur_y));

    deplacer_rect_origine(&slot10, floor(673 * multiplicateur_x), floor(281 * multiplicateur_y));
    deplacer_rect_origine(&slot11, floor(636 * multiplicateur_x), floor(421 * multiplicateur_y));
    deplacer_rect_origine(&slot12, floor(1137 * multiplicateur_x), floor(421 * multiplicateur_y));
    deplacer_rect_origine(&slot13, floor(890 * multiplicateur_x), floor(338 * multiplicateur_y));
    deplacer_rect_origine(&slot14, floor(887 * multiplicateur_x), floor(121 * multiplicateur_y));
    deplacer_rect_origine(&slot15, floor(1100 * multiplicateur_x), floor(281 * multiplicateur_y));

    while (1)
    {
        debut = SDL_GetPerformanceCounter();

        slot_selectionne = -1;

        SDL_RenderClear(rendu_principal);

        afficher_texture(map->text_map, rendu_principal);
        afficher_texture(text_pause, rendu_principal);
        afficher_textures_sac(joueur->inventaire);
        afficher_textures_equipe(joueur->inventaire);

        SDL_RenderPresent(rendu_principal); 

        SDL_Event lastEvent; /* On récupère les événements */

        SDL_Point coord_souris; 
        while (SDL_PollEvent(&lastEvent))
        {
            switch (lastEvent.type){
            case SDL_QUIT:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Détection de la fermeture de la fenêtre\n");
                fermer_programme(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                if(lastEvent.key.keysym.sym == SDLK_TAB){
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "On quitte l'inventaire\n");
                    return;
                }
                if(lastEvent.key.keysym.sym == SDLK_ESCAPE){
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "On quitte l'inventaire\n");
                    return;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                coord_souris.x = lastEvent.button.x;
                coord_souris.y = lastEvent.button.y;

                if (SDL_PointInRect(&coord_souris, &slot0))
                    slot_selectionne = 0;
                if (SDL_PointInRect(&coord_souris, &slot1))
                    slot_selectionne = 1;
                if (SDL_PointInRect(&coord_souris, &slot2))
                    slot_selectionne = 2;
                if (SDL_PointInRect(&coord_souris, &slot3))
                    slot_selectionne = 3;
                if (SDL_PointInRect(&coord_souris, &slot4))
                    slot_selectionne = 4;
                if (SDL_PointInRect(&coord_souris, &slot5))
                    slot_selectionne = 5;
                if (SDL_PointInRect(&coord_souris, &slot6))
                    slot_selectionne = 6;
                if (SDL_PointInRect(&coord_souris, &slot7))
                    slot_selectionne = 7;
                if (SDL_PointInRect(&coord_souris, &slot8))
                    slot_selectionne = 8;
                if (SDL_PointInRect(&coord_souris, &slot9))
                    slot_selectionne = 9;
                if (SDL_PointInRect(&coord_souris, &slot10))
                    slot_selectionne = 10;
                if (SDL_PointInRect(&coord_souris, &slot11))
                    slot_selectionne = 11;
                if (SDL_PointInRect(&coord_souris, &slot12))
                    slot_selectionne = 12;
                if (SDL_PointInRect(&coord_souris, &slot13))
                    slot_selectionne = 13;
                if (SDL_PointInRect(&coord_souris, &slot14))
                    slot_selectionne = 14;
                if (SDL_PointInRect(&coord_souris, &slot15))
                    slot_selectionne = 15;

                if(slot_selectionne > -1){
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "On a selectionné le slot %d\n", slot_selectionne);
                    if(slot_selectionne < 10){
                        /* Fonction pour équiper l'item */
                        equiper_sac_slot(joueur, slot_selectionne);
                    }
                    else{
                        /* Fonction pour déséquiper l'item */
                        desequiper_slot(joueur, slot_selectionne);
                    }
                }
                break;
            }
        }

        /* On ajuste la vitesse en fonction du temps écoulé */
        fin = SDL_GetPerformanceCounter();
        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();

        SDL_Delay(floor((1000 / (float) NB_FPS) - temps_passe));


        if(compteur == NB_FPS)
            compteur = 0;
        else
            compteur++;
    }
}