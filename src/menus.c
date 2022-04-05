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

t_aff * text_pause = NULL;
t_aff * text_inventaire1 = NULL;
t_aff * text_inventaire2 = NULL;
t_aff * text_accueil = NULL;

/*void afficher_menu(menus_t * menu){
    switch (menu) {
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
    
        default: exit(EXIT_SUCCESS);
    }
}*/

void afficher_menu_pause(joueur_t *joueur[], char * f_src_objet, unsigned short int nb_joueurs){

    int debut, fin; /* le temps pour calculer les performances */

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Affichage du menu pause");

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

        #ifdef __DEBUG__
        SDL_RenderDrawRect(rendu_principal, &boutton_sortie);
        #endif

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
                if (lastEvent.key.keysym.sym == SDLK_ESCAPE){
                    while(SDL_PollEvent(&lastEvent)); /* Nettoye les événements avant de revenir au jeu */
                    return;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                coord_souris.x = lastEvent.button.x;
                coord_souris.y = lastEvent.button.y;

                if(SDL_PointInRect(&coord_souris, &boutton_sortie)){
                    while(SDL_PollEvent(&lastEvent)); /* Nettoye les événements avant de revenir au jeu */
                    return;
                }
                if(SDL_PointInRect(&coord_souris, &boutton_reprendre)){
                    while(SDL_PollEvent(&lastEvent)); /* Nettoye les événements avant de revenir au jeu */
                    return;
                }
                if(SDL_PointInRect(&coord_souris, &boutton_quitter)){
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fermeture du programme ...\n");
                    fermer_programme(EXIT_SUCCESS);
                }
                if (SDL_PointInRect(&coord_souris, &boutton_sauvegarder)){
                    creer_sauvegarde_json(*joueur);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Sauvegarde", "La sauvegarde a été effectuée avec succès\n", NULL);
                    break;
                }
                if (SDL_PointInRect(&coord_souris, &boutton_charger)){
                    char temp[510];
                    sprintf(temp,"%s/perso.sav", save_path);
                    detruire_joueur(*joueur);
                    joueur[0] = charger_sauvegarde_joueur(temp, f_src_objet, joueur, nb_joueurs);

                    joueur[1] = NULL;

                    SDL_SetTextureBlendMode(fenetre_finale->texture, SDL_BLENDMODE_BLEND);

                    for(unsigned int i = 0; i < 256; i += 5 ){ /* Fondu (disparition de la map) */
                        if (SDL_SetTextureAlphaMod(fenetre_finale->texture, i) < 0)
                            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
                        if(SDL_RenderClear(rendu_principal) < 0)
                            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
                        if (afficher_texture(fenetre_finale, rendu_principal) != 0)
                            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
                        SDL_RenderPresent(rendu_principal);
                        SDL_Delay(10);
                    }

                    return;
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

void afficher_inventaire(joueur_t * joueur, SDL_KeyCode touche_inventaire)
{
    int slot_selectionne = -1;
    int debut, fin; /* le temps pour calculer les performances */
    t_aff *text_inventaire = NULL;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Affichage de l'inventaire");

    //affiche la bonne texture de l'inventaire selon le joueur
    if(touche_inventaire == SDLK_TAB)
        text_inventaire = text_inventaire1;
    else
        text_inventaire = text_inventaire2;


    if (!text_inventaire){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors du chargement de l'inventaire");
        return;
    }

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

        afficher_texture(text_pause, rendu_principal);

        afficher_texture(fenetre_finale, rendu_principal);
        afficher_texture(text_inventaire, rendu_principal);

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
                if(lastEvent.key.keysym.sym == touche_inventaire){
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

void afficher_menu_accueil(int * nb_joueur){

    int debut, fin; /* le temps pour calculer les performances */

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Affichage du menu d'accueil");

    if (!text_accueil){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors du chargement du menu d'accueil");
        return;
    }

    SDL_Rect boutton_sortie = {.h = floor(56 * multiplicateur_y), .w = floor(66 * multiplicateur_x)};

    SDL_Rect boutton_quitter = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_nouvelle_partie = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_solo = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_coop = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};

    deplacer_rect_haut_droit(&boutton_sortie, floor(-9 * multiplicateur_x), floor(7 * multiplicateur_y));

    deplacer_rect_origine(&boutton_quitter, floor(427 * multiplicateur_x), floor(836 * multiplicateur_y));
    deplacer_rect_origine(&boutton_nouvelle_partie, floor(427 * multiplicateur_x), floor(108 * multiplicateur_y));
    deplacer_rect_origine(&boutton_coop, floor(427 * multiplicateur_x), floor(590 * multiplicateur_y));
    deplacer_rect_origine(&boutton_solo, floor(427 * multiplicateur_x), floor(348 * multiplicateur_y));

    while(1){
        debut = SDL_GetPerformanceCounter();
        SDL_RenderClear(rendu_principal);
        afficher_texture(text_accueil, rendu_principal);

        #ifdef __DEBUG__
        SDL_RenderDrawRect(rendu_principal, &boutton_sortie);
        #endif

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
                break;
            case SDL_MOUSEBUTTONUP:
                coord_souris.x = lastEvent.button.x;
                coord_souris.y = lastEvent.button.y;

                if(SDL_PointInRect(&coord_souris, &boutton_sortie))
                    fermer_programme(EXIT_SUCCESS);
                if(SDL_PointInRect(&coord_souris, &boutton_nouvelle_partie)){
                    *nb_joueur = 1;
                    goto transition;
                    return;
                }
                if(SDL_PointInRect(&coord_souris, &boutton_quitter)){
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fermeture du programme ...\n");
                    fermer_programme(EXIT_SUCCESS);
                }
                if (SDL_PointInRect(&coord_souris, &boutton_solo)){
                    *nb_joueur = 1;
                    goto transition;
                    return;
                }
                if (SDL_PointInRect(&coord_souris, &boutton_coop)){
                    *nb_joueur = 2;
                    goto transition;
                    return;
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

    transition :
    SDL_SetRenderTarget(rendu_principal, NULL);
    SDL_SetTextureBlendMode(text_accueil->texture, SDL_BLENDMODE_BLEND);

    for(unsigned int i = 255; i > 0; i -= 5 ){ /* Fondu (disparition de la map) */
        if (SDL_SetTextureAlphaMod(text_accueil->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if(SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(text_accueil, rendu_principal) != 0)
            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(10);
    }
}

void init_text_menus(int nb_joueur){
    text_pause = creer_texture("ressources/background/menu/Sprite_Menu_Pause.bmp", -1, -1, 0, 0, 0);
    text_inventaire1 = creer_texture("ressources/background/menu/inventaire.bmp", -1, -1, 0, 0, 0);
    text_accueil = creer_texture("ressources/background/menu/Sprite_Menu_Accueil.bmp", -1, -1, 0, 0, 0);
}

void creer_inventaire_j2(){
    text_inventaire2 = creer_texture("ressources/background/menu/inventaire_green.bmp", -1, -1, 0, 0, 0);
}

static int draw_rect_epaisseur(const SDL_Rect * a_dessiner, SDL_Renderer *rendu, unsigned int epaisseur){

    if(epaisseur == 0)
        epaisseur = 1;

    /* On créer les bordures du rectangle avec l'épaisseur définie */
    SDL_Rect haut = {.h = epaisseur, .w = a_dessiner->w, .x = a_dessiner->x, .y = a_dessiner ->y};
    SDL_Rect bas = {.h = epaisseur, .w = a_dessiner->w, .x = a_dessiner->x, .y = a_dessiner->y - epaisseur + a_dessiner->h};
    SDL_Rect gauche = {.h = a_dessiner->h, .w = epaisseur, .x = a_dessiner->x, .y = a_dessiner->y};
    SDL_Rect droit = {.h = a_dessiner->h, .w = epaisseur, .x = a_dessiner->x - epaisseur + a_dessiner->w, .y = a_dessiner->y};

    int erreur = 0;

    if((erreur = SDL_RenderFillRect(rendu, &haut)))
        return erreur;
    if ((erreur = SDL_RenderFillRect(rendu, &bas)))
        return erreur;
    if ((erreur = SDL_RenderFillRect(rendu, &gauche)))
        return erreur;
    if ((erreur = SDL_RenderFillRect(rendu, &droit)))
        return erreur;
    
    return 0;
}

/* Menu spécial manette */

void afficher_menu_pause_manette(joueur_t *joueur)
{

    int debut, fin; /* le temps pour calculer les performances */

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Affichage du menu pause");

    if (!text_pause)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors du chargement du menu pause");
        return;
    }

    SDL_Rect selectionne[4];

    SDL_Rect boutton_quitter = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_reprendre = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_sauvegarder = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_charger = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};

    deplacer_rect_origine(&boutton_quitter, floor(427 * multiplicateur_x), floor(836 * multiplicateur_y));
    deplacer_rect_origine(&boutton_reprendre, floor(427 * multiplicateur_x), floor(108 * multiplicateur_y));
    deplacer_rect_origine(&boutton_charger, floor(427 * multiplicateur_x), floor(590 * multiplicateur_y));
    deplacer_rect_origine(&boutton_sauvegarder, floor(427 * multiplicateur_x), floor(348 * multiplicateur_y));

    selectionne[0] = boutton_reprendre;
    selectionne[1] = boutton_sauvegarder;
    selectionne[2] = boutton_charger;
    selectionne[3] = boutton_quitter;

    unsigned int selection = 0;
    while (1)
    {
        debut = SDL_GetPerformanceCounter();
        SDL_RenderClear(rendu_principal);
        afficher_texture(text_pause, rendu_principal);

        SDL_SetRenderDrawColor(rendu_principal, 0,255,128, SDL_ALPHA_OPAQUE);
        draw_rect_epaisseur(&selectionne[selection], rendu_principal, floor(5 * multiplicateur_y));
        SDL_SetRenderDrawColor(rendu_principal, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_RenderPresent(rendu_principal);
        SDL_Event lastEvent; /* On récupère les événements */

        while (SDL_PollEvent(&lastEvent))
        {
            switch (lastEvent.type)
            {
            case SDL_QUIT:

                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Détection de la fermeture de la fenêtre\n");
                fermer_programme(EXIT_SUCCESS);
            case SDL_JOYBUTTONDOWN :
                switch (((SDL_JoyButtonEvent *) &lastEvent)->button){
                    case SDL_CONTROLLER_BUTTON_START :
                        return;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN :
                        if(selection == 3)
                            selection = 0;
                        else
                            selection ++;
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP :
                        if (selection == 0)
                            selection = 3;
                        else
                            selection--;
                        break;
                    case SDL_CONTROLLER_BUTTON_A :
                        switch (selection) {
                            case 0:
                                return;
                            case 1:

                            case 2:
                                    break;
                            case 3:
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fermeture du programme ...\n");
                                fermer_programme(EXIT_SUCCESS);
                                break;
                        }
                        break;
                }
            }
        }
        fin = SDL_GetPerformanceCounter();
        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float)60) - temps_passe));

        if (compteur == NB_FPS)
            compteur = 0;
        else
            compteur++;
    }
}

void afficher_menu_accueil_manette(int *nb_joueur)
{
    int debut, fin; /* le temps pour calculer les performances */

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Affichage du menu d'accueil");

    if (!text_accueil)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors du chargement du menu d'accueil");
        return;
    }

    SDL_Rect selectionne[3];

    SDL_Rect boutton_quitter = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_nouvelle_partie = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};
    SDL_Rect boutton_solo = {.h = floor(136 * multiplicateur_y), .w = floor(1064 * multiplicateur_x)};

    deplacer_rect_origine(&boutton_quitter, floor(427 * multiplicateur_x), floor(836 * multiplicateur_y));
    deplacer_rect_origine(&boutton_nouvelle_partie, floor(427 * multiplicateur_x), floor(108 * multiplicateur_y));
    deplacer_rect_origine(&boutton_solo, floor(427 * multiplicateur_x), floor(348 * multiplicateur_y));

    selectionne[0] = boutton_nouvelle_partie;
    selectionne[1] = boutton_solo;
    selectionne[2] = boutton_quitter;

    unsigned int selection = 0;

    while (1)
    {
        debut = SDL_GetPerformanceCounter();
        SDL_RenderClear(rendu_principal);
        afficher_texture(text_accueil, rendu_principal);

        SDL_SetRenderDrawColor(rendu_principal, 0, 255, 128, SDL_ALPHA_OPAQUE);
        draw_rect_epaisseur(&selectionne[selection], rendu_principal, floor(5 * multiplicateur_y));
        SDL_SetRenderDrawColor(rendu_principal, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_RenderPresent(rendu_principal);
        SDL_Event lastEvent; /* On récupère les événements */

        while (SDL_PollEvent(&lastEvent))
        {
            switch (lastEvent.type)
            {
            case SDL_QUIT:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Détection de la fermeture de la fenêtre\n");
                fermer_programme(EXIT_SUCCESS);
            case SDL_JOYBUTTONDOWN:
                switch (((SDL_JoyButtonEvent *)&lastEvent)->button)
                {
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    if (selection == 2)
                        selection = 0;
                    else
                        selection++;
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    if (selection == 0)
                        selection = 2;
                    else
                        selection--;
                    break;
                case SDL_CONTROLLER_BUTTON_A:
                    switch (selection)
                    {
                    case 0:
                        *nb_joueur = 1;
                        goto transition;
                        return;
                    case 1:
                        *nb_joueur = 1;
                        goto transition;
                        return;
                    case 2:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fermeture du programme ...\n");
                        fermer_programme(EXIT_SUCCESS);
                        break;
                    }
                    break;
                }
            }
        }
        fin = SDL_GetPerformanceCounter();
        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float)60) - temps_passe));

        if (compteur == NB_FPS)
            compteur = 0;
        else
            compteur++;
    }

    transition :
    SDL_SetRenderTarget(rendu_principal, NULL);
    SDL_SetTextureBlendMode(text_accueil->texture, SDL_BLENDMODE_BLEND);

    for(unsigned int i = 255; i > 0; i -= 5 ){ /* Fondu (disparition de la map) */
        if (SDL_SetTextureAlphaMod(text_accueil->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if(SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(text_accueil, rendu_principal) != 0)
            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(10);
    }
}

void afficher_inventaire_manette(joueur_t *joueur){
    unsigned int selection = 0;
    int debut, fin; /* le temps pour calculer les performances */
    t_aff *text_inventaire = NULL;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Affichage de l'inventaire");

    // affiche la bonne texture de l'inventaire selon le joueur
    text_inventaire = text_inventaire1;

    if (!text_inventaire)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors du chargement de l'inventaire");
        return;
    }

    SDL_Rect selectionne[16];

    /* Création des slots de l'inventaire */
    SDL_Rect slot0 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot1 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot2 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot3 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot4 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot5 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot6 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot7 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot8 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot9 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};

    SDL_Rect slot10 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot11 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot12 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot13 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot14 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};
    SDL_Rect slot15 = {.h = floor(120 * multiplicateur_y), .w = floor(144 * multiplicateur_x)};

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

    selectionne[0] = slot0;
    selectionne[1] = slot1;
    selectionne[2] = slot2;
    selectionne[3] = slot3;
    selectionne[4] = slot4;
    selectionne[5] = slot5;
    selectionne[6] = slot6;
    selectionne[7] = slot7;
    selectionne[8] = slot8;
    selectionne[9] = slot9;
    
    selectionne[10] = slot10;
    selectionne[11] = slot11;
    selectionne[12] = slot12;
    selectionne[13] = slot13;
    selectionne[14] = slot14;
    selectionne[15] = slot15;
    
    while (1)
    {
        debut = SDL_GetPerformanceCounter();

        SDL_RenderClear(rendu_principal);

        afficher_texture(text_pause, rendu_principal);

        afficher_texture(fenetre_finale, rendu_principal);
        afficher_texture(text_inventaire, rendu_principal);

        afficher_textures_sac(joueur->inventaire);
        afficher_textures_equipe(joueur->inventaire);

        /* On affiche la case sélèctionnée */
        SDL_SetRenderDrawColor(rendu_principal, 0, 255, 128, SDL_ALPHA_OPAQUE);
        draw_rect_epaisseur(&selectionne[selection], rendu_principal, floor(5 * multiplicateur_y));
        SDL_SetRenderDrawColor(rendu_principal, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_RenderPresent(rendu_principal);

        SDL_Event lastEvent; /* On récupère les événements */

        while (SDL_PollEvent(&lastEvent))
        {
            switch (lastEvent.type)
            {
            case SDL_QUIT:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Détection de la fermeture de la fenêtre\n");
                fermer_programme(EXIT_SUCCESS);
            case SDL_JOYBUTTONDOWN:
                switch (((SDL_JoyButtonEvent *)&lastEvent)->button){
                    case SDL_CONTROLLER_BUTTON_B :
                    case SDL_CONTROLLER_BUTTON_BACK :
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "On quitte l'inventaire");
                        return;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        if (selection >= 5 && selection <= 9) /* Ligne du bas */
                            break;
                        if(selection >= 0 && selection <= 4){ /* Ligne du haut */
                            selection += 5;
                            break;
                        }
                        if(selection == 10 || selection == 14 || selection == 15){
                            switch (selection){
                                case 10: selection = 11; break;
                                case 14: selection = 13; break;
                                case 15: selection = 12; break;
                            }
                            break;
                        }
                        switch (selection){
                            case 11: selection = 0; break;
                            case 13: selection = 2; break;
                            case 12: selection = 4; break;
                        }
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        if (selection >= 0 && selection <= 4){/* Ligne du haut */
                            switch (selection){
                                case 0:
                                case 1: selection = 11; break;
                                case 2: selection = 13; break;
                                case 3: 
                                case 4: selection = 12; break;
                            }
                            break;
                        }
                        if (selection >= 5 && selection <= 9){ /* Ligne du bas */
                            selection -= 5;
                            break;
                        }
                        if(selection >= 11 && selection <= 13){
                            switch (selection){
                                case 11: selection = 10; break;
                                case 13: selection = 14; break;
                                case 12: selection = 15; break;
                            }
                            break;
                        }
                        if(selection == 10 || selection == 15)
                            selection = 14;
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT :
                        if(selection >= 0 && selection < 10){ /* On se trouve dans les objects à équiper */
                            if(selection == 4 || selection == 9){
                                selection = selection - 4;
                            }
                            else
                                selection++;
                            break;
                        }
                        if(selection == 10 || selection == 11){
                            selection = 13;
                            break;
                        }
                        if(selection == 14){
                            selection = 15;
                            break;
                        }
                        if(selection == 13)
                            selection = 12;
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT :
                        if(selection >= 0 && selection < 10){ /* On se trouve dans les objects à équiper */
                            if(selection == 0 || selection == 5){
                                selection = selection + 4;
                            }
                            else
                                selection--;
                            break;
                        }
                        if(selection == 12 || selection == 15){
                            selection = 13;
                            break;
                        }
                        if(selection == 14){
                            selection = 10;
                            break;
                        }
                        if(selection == 13)
                            selection = 11;
                        break;
                    case SDL_CONTROLLER_BUTTON_A:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "On a selectionné le slot %d\n", selection);
                        if(selection < 10){
                            /* Fonction pour équiper l'item */
                            equiper_sac_slot(joueur, selection);
                        }
                        else{
                            /* Fonction pour déséquiper l'item */
                            desequiper_slot(joueur, selection);
                        }
                        break;
                }
            }
        }

        /* On ajuste la vitesse en fonction du temps écoulé */
        fin = SDL_GetPerformanceCounter();
        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();

        SDL_Delay(floor((1000 / (float)NB_FPS) - temps_passe));

        if (compteur == NB_FPS)
            compteur = 0;
        else
            compteur++;
    }
}
