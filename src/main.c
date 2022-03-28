#define SDL_MAIN_HANDLED

#include <commun.h>
#include <stdio.h>
#include <math.h>
#include <map.h>



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
    SDL_SetMainReady();
    init();
    afficher_intro();
    char *fichier_map = charger_f_map("map.json");
    map = charger_s_map(fichier_map);

    int debut, fin; /* le temps pour calculer les performances */
    int i;

    perso_principal = new_joueur("test");
    t_aff *text = texture_map(map);
    //t_l_aff *textures_joueur = init_textures_joueur(perso_principal);                 /* initialise la liste de textures joueur*/
    //t_aff *next_texture_joueur = init_texture_joueur(perso_principal->textures_joueur); /* initialise la texture joueur à afficher*/
    t_aff *next_texture_joueur = perso_principal->textures_joueur->liste[TEXT_MARCHER];
    t_aff *texture_temp;

    objets = creer_liste_objet();
    inventaire = creer_inventaire();
    objets->liste[0]->texture = creer_texture(objets->liste[0]->texture_src, 46, 48, 0, 0, (FENETRE_LONGUEUR * 0.022f) / 16 * 0.8);
    ramasser_objet(objets->liste[0], inventaire);

    /*test de l'allocation des textures*/
    for (i = 0; i < perso_principal->textures_joueur->nb_valeurs; i++)
        if (perso_principal->textures_joueur->liste == NULL)
            fermer_programme(EXIT_FAILURE);

    rect_centre_x(&tx);
    rect_centre_y(&ty);

    check_repertoire_jeux();

    rect_centre(&(perso_principal->statut->zone_colision));
    compteur = 0;
    while (running)
    {
        debut = SDL_GetPerformanceCounter();
        jeu_event();
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
        afficher_texture(text, rendu_principal);
        SDL_RenderDrawRect(rendu_principal, &tx);
        SDL_RenderDrawRect(rendu_principal, &(perso_principal->statut->zone_colision));
        SDL_RenderDrawRect(rendu_principal, &ty);
        afficher_monstres(map->liste_monstres);
        afficher_texture(next_texture_joueur, rendu_principal);
        RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
            ((float)perso_principal->pdv/perso_principal->maxPdv), color(195,0,0,0.9), color(125, 125, 125, 1));
        // afficher_buffer(buffer_affichage, rendu_principal);
        SDL_RenderPresent(rendu_principal);

        // vider_liste(buffer_affichage);
        fin = SDL_GetPerformanceCounter();

        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float) NB_FPS) - temps_passe));
        if(compteur == NB_FPS)
            compteur = 0;
        compteur++;
    }

    return AUCUNE_ERREUR;
}