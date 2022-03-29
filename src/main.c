#define SDL_MAIN_HANDLED

#include <commun.h>
#include <stdio.h>
#include <math.h>
#include <map.h>

/**
 * \file main.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme principal du jeu
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

void afficher_intro(void){
    int i;
    
    t_aff * text = creer_texture("ressources/background/logo.bmp", -1, -1, 0, 0, 0);

    /*if(! text){
        fprintf(stderr, "Erreur lors du chargement du menu ! \n");
    }*/

    def_texture_taille(text, FENETRE_LONGUEUR, FENETRE_LARGEUR);

    for(i = 0; i < 256; i += 5 ){ /* Fondu (apparition du logo) */
        if (logo_passer())
            return;
        SDL_SetTextureBlendMode(text->texture, SDL_BLENDMODE_BLEND);
        if (SDL_SetTextureAlphaMod(text->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if(SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(text, rendu_principal) != 0)
            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(25);
    }

    SDL_Delay(1500); /* Temps pendant lequel le logo rest à l'écran */

    for (i = 255; i > 0; i -= 5) /* Fondu (disparition du logo) */
    {
        if (logo_passer())
            return;
        SDL_SetTextureBlendMode(text->texture, SDL_BLENDMODE_BLEND);
        if (SDL_SetTextureAlphaMod(text->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if (SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(text, rendu_principal) != 0)
            fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(25);
    }

    SDL_Delay(150);
}

int main(int argc, char** argv)
{
    int debut, fin; /* le temps pour calculer les performances */
    int i;
    joueur_t * perso_principal = NULL;
    char *fichier_map = NULL;
    t_aff *text = NULL;
    t_aff *next_texture_joueur = NULL;
    t_aff *texture_temp = NULL;
    SDL_Rect temp = {0};
    float temps_passe;

    /* On initialise le programme */
    SDL_SetMainReady();
    init();

    /* On affiche l'introduction */
    afficher_intro();

    /* On charge la map */
    fichier_map = charger_f_map("map.json");
    map = charger_s_map(fichier_map);
    text = texture_map(map); 

    /* On créer le joueur */
    perso_principal = new_joueur("test");
    next_texture_joueur = perso_principal->textures_joueur->liste[TEXT_MARCHER];

    objets = creer_liste_objet();
    creer_textures_objets(objets);
    tout_ramasser(objets, perso_principal->inventaire);

    /*test de l'allocation des textures*/
    for (i = 0; i < perso_principal->textures_joueur->nb_valeurs; i++)
        if (perso_principal->textures_joueur->liste == NULL)
            fermer_programme(EXIT_FAILURE);

    /* On verifie si le répertoire de sauvegarde existe */
    check_repertoire_jeux();

    rect_centre(&(perso_principal->statut->zone_colision));

    init_sousbuffer(map, perso_principal);

    SDL_RenderClear(rendu_principal);
    temp.x=0;
    temp.y=0;
    temp.w=floor(map->text_sol->width * map->text_sol->multipli_taille);
    temp.h=floor(map->text_sol->height * map->text_sol->multipli_taille);

    if(SDL_RenderCopy(rendu_principal, text->texture, NULL, &temp))
        fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());

    SDL_QueryTexture(map->text_map->texture, NULL, NULL, &(map->text_map->width), &(map->text_map->height));

    SDL_SetRenderTarget(rendu_principal, NULL);


    compteur = 0;
    while (running)
    {
        debut = SDL_GetPerformanceCounter();
        jeu_event(perso_principal);
        // en_tete(buffer_affichage);
        if (perso_principal->statut->en_mouvement){ /* Déplacement map */
            switch (perso_principal->statut->orientation)
            {
            case NORD:
                deplacement_y_pers(map, perso_principal, -3);
                break;
            case SUD:
                deplacement_y_pers(map, perso_principal, 3);
                break;
            case OUEST:
                deplacement_x_pers(map, perso_principal, -3);
                break;
            case EST:
                deplacement_x_pers(map, perso_principal, 3);
                break;
            }
        }

        texture_temp = next_frame_joueur(perso_principal);
        if (texture_temp)
            next_texture_joueur = texture_temp;

        SDL_RenderClear(rendu_principal);
        afficher_texture(map->text_map, rendu_principal);

        #ifdef __DEBUG__
            SDL_RenderDrawRect(rendu_principal, &tx);
            SDL_RenderDrawRect(rendu_principal, &(perso_principal->statut->zone_colision));
            SDL_RenderDrawRect(rendu_principal, &ty);
        #endif

        /* On affiche le joueur */
        afficher_texture(next_texture_joueur, rendu_principal);

        /* On affiche l'interface */
        RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
            ((float)perso_principal->pdv/perso_principal->maxPdv), color(195,0,0,0.9), color(125, 125, 125, 1));


        SDL_RenderPresent(rendu_principal);

        // vider_liste(buffer_affichage);
        fin = SDL_GetPerformanceCounter();

        temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float) NB_FPS) - temps_passe));
        if(compteur == NB_FPS)
            compteur = 0;
        compteur++;
    }

    return AUCUNE_ERREUR;
}