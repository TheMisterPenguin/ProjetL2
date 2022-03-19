#include <commun.h>
#include <stdio.h>
#include <math.h>
#include <map.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
bool running = vrai;
long int compteur;
t_map *test_map;


#define NB_FPS 30

void afficher_intro(void){
    int i;
    
    t_aff * text = creer_texture("ressources/background/logo.bmp", -1, -1, 0, 0, 1);

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

int t_affichage(void *ptr){

    int debut, fin; /* le temps pour calculer les performances */
    int i;
    
    perso_principal = creer_joueur("test");
    t_aff *text = texture_map(test_map);
    t_l_aff* textures_joueur = init_textures_joueur();  /* initialise la liste de textures joueur*/
    t_aff* next_texture_joueur = init_texture_joueur(textures_joueur); /* initialise la texture joueur à afficher*/
    t_aff* texture_temp;

    /*test de l'allocation des textures*/
    for(i=0; i<textures_joueur->nb_valeurs; i++)
        if(textures_joueur->liste == NULL)
            exit(EXIT_FAILURE);

    compteur = 0;
    while (running)
    {   
        debut = SDL_GetPerformanceCounter();

        //en_tete(buffer_affichage);

        if (perso_principal->statut->en_mouvement){ /* Déplacement map */
            switch (perso_principal->statut->orientation){
            case NORD:
                deplacement_y_pers(text, next_texture_joueur, -3);
                break;
            case SUD:
                deplacement_y_pers(text, next_texture_joueur, 3);
                break;
            case OUEST:
                deplacement_x_pers(text, next_texture_joueur, -3);
                break;
            case EST:
                deplacement_x_pers(text, next_texture_joueur, 3);
                break;
            }
        }

        texture_temp = next_frame_joueur(textures_joueur);
        if (texture_temp)
            next_texture_joueur = texture_temp;

        SDL_RenderClear(rendu_principal);
        afficher_texture(text, rendu_principal);
        afficher_texture(next_texture_joueur, rendu_principal);
        //afficher_buffer(buffer_affichage, rendu_principal);
        SDL_RenderPresent(rendu_principal);


        //vider_liste(buffer_affichage);
        fin = SDL_GetPerformanceCounter();

        float temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float) 60) - temps_passe));
        compteur++;

    }
    return 0;
}

int main(int argc, char** argv)
{
    SDL_Thread *f_t_aff;
    init();
    afficher_intro();
    char *fichier_map = charger_f_map("map.json");
    test_map = charger_s_map(fichier_map);
    
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