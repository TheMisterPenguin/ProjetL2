#include <monstres.h>
#include <string.h>
#include <personnage.h>
#include <time.h>
#include <stdlib.h>
#include <map.h>
#include <math.h>
#include <json-c/json.h>
#include <code_erreur.h>
#include <definition_commun.h>
#include <sorts.h>

/**
 * \file monstres.c
 * \author Antoine Bruneau (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les monstres
 * \version 0.1
 * \date 03/03/2022
 * \copyright Copyright (c) 2022
 */

typedef struct t_map t_map;

liste_base_monstres_t * liste_base_monstres = NULL;

void detruire_liste_base_monstres(liste_base_monstres_t** liste_base_monstres){

    free((**liste_base_monstres).tab);
    free(*liste_base_monstres);
    *liste_base_monstres = NULL;
}

monstre_t* creer_monstre(liste_base_monstres_t* liste_base_monstres, const char * const nom_monstre, int x, int y, t_map *map){
    int i;

    /* allocation monstre_t*/
    monstre_t* monstre = malloc(sizeof(monstre_t));
    for(i=0; i<liste_base_monstres->nb_monstre; i++){
        if(strcmp(liste_base_monstres->tab[i].nom_monstre,nom_monstre) == 0){
            monstre->type = nom_monstre_to_type_monstre(nom_monstre);
            monstre->collision.x = x;
            monstre->collision.y = y;
            monstre->collision.w = liste_base_monstres->tab[i].hitbox.w * (map->taille_case / TAILLE_CASE);
            monstre->collision.h = liste_base_monstres->tab[i].hitbox.h * (map->taille_case / TAILLE_CASE);

            monstre->orientation = NORD;
            monstre->duree = 0;
            monstre->action = MONSTRE_EN_GARDE;

            /*copie les informations de base_monstre dans monstre*/
            monstre->pdv = liste_base_monstres->tab[i].pdv;
            monstre->attaque = liste_base_monstres->tab[i].attaque;
            monstre->vitesse = liste_base_monstres->tab[i].vitesse;
            monstre->gainXp = liste_base_monstres->tab[i].gainXp;

            monstre->texture = creer_texture(liste_base_monstres->tab[i].fichier_image, LARGEUR_ENTITE, LONGUEUR_ENTITE, -100, -100, map->taille_case / TAILLE_CASE);
            monstre->texture->duree_frame_anim = NB_FPS;

            return monstre;
        }
    }
    return NULL;
}


type_monstre_t nom_monstre_to_type_monstre(char * nom_monstre){
    if(strcmp(nom_monstre,"witcher") == 0)
        return WITCHER;
    else if(strcmp(nom_monstre,"knight") == 0)
        return KNIGHT;
    else if(strcmp(nom_monstre,"boss") == 0)
        return BOSS;
    else{
        fprintf(stderr,"Erreur, nom du monstre incorrect\n");
    }

    return ERREUR;
}

int distance_x_joueur(SDL_Rect collision, joueur_t * joueur){
    return joueur->statut->vrai_zone_collision.x - collision.x;
}

int distance_y_joueur(SDL_Rect collision, joueur_t * joueur){
    return joueur->statut->vrai_zone_collision.y - collision.y;
}

int distance_joueur(SDL_Rect collision, joueur_t * joueur){
    int x = distance_x_joueur(collision, joueur);
    int y = distance_y_joueur(collision, joueur);

    return sqrt(x*x + y*y);
}

void marcher_monstre(monstre_t * monstre){
    switch(monstre->type){
        case(KNIGHT): next_frame_x_indice(monstre->texture, (current_frame_x(monstre->texture)+1) % 2);
        default : break; 
    }
}

void orienter_monstre(monstre_t * monstre){
    switch(monstre->type){
        case(WITCHER): next_frame_x_indice(monstre->texture, monstre->orientation); break;
        case(KNIGHT): next_frame_y_indice(monstre->texture, monstre->orientation); break;
        case(BOSS): /**/ break;
        default : break; 
    }
}

void orienter_monstre_vers_joueur(monstre_t * monstre, joueur_t * joueur){
    int y_diff, x_diff;
    x_diff = distance_x_joueur(monstre->collision, joueur);
    y_diff = distance_y_joueur(monstre->collision, joueur);

    if( abs(x_diff) < abs(y_diff) ){
        if(y_diff < 0)
            monstre->orientation = NORD;
        else
            monstre->orientation = SUD;
    }
    else{
        if(x_diff < 0)
            monstre->orientation = OUEST;
        else
            monstre->orientation = EST;
    }
    orienter_monstre(monstre);
}

void monstre_en_garde(monstre_t * monstre){
    switch(monstre->type){
        case(KNIGHT): next_frame_x_indice(monstre->texture, 2); break;
        default : break; 
    }
}

void monstre_attaque(monstre_t * monstre /*liste texture sort*/){
    switch(monstre->type){
        case(WITCHER): next_frame_y_indice(monstre->texture, 1); break ;
        default: break;
    //creation texture sort + insertion dans liste sorts
    }
}

void fuir_joueur(monstre_t *monstre, joueur_t * joueur){
    int y_diff, x_diff;
    x_diff = distance_x_joueur(monstre->collision, joueur);
    y_diff = distance_y_joueur(monstre->collision, joueur);

    if( abs(x_diff) < abs(y_diff) ){
        if(y_diff < 0)
            monstre->orientation = SUD;
        else
            monstre->orientation = NORD;
    }
    else{
        if(x_diff < 0)
            monstre->orientation = EST;
        else
            monstre->orientation = OUEST;
    }
    orienter_monstre(monstre);
    marcher_monstre(monstre);
}

void rush_joueur(monstre_t * monstre, joueur_t * joueur){
    
    orienter_monstre_vers_joueur(monstre, joueur);
    marcher_monstre(monstre);
}

void agro_witcher(monstre_t * monstre, joueur_t * joueur){
    if(monstre->action == RUSH_OU_FUITE)
        if(monstre->duree > 0){
            if(compteur%5 == 0)
                fuir_joueur(monstre, joueur);
        }
        else{
            monstre->action = MONSTRE_ATTAQUE;
            monstre->duree = DUREE_MONSTRE_ATTAQUE;
            orienter_monstre_vers_joueur(monstre, joueur);
            creer_sort_monstre(monstre, joueur);
        }
    else
        if(monstre->duree > 0){
            if(compteur%5 == 0)
                monstre_attaque(monstre);
        }
        else{
            monstre->action = RUSH_OU_FUITE;
            monstre->duree = DUREE_RUSH_OU_FUITE;
            next_frame_y_indice(monstre->texture, 0);
        }  
}

void agro_knight(monstre_t * monstre, joueur_t * joueur){
    if(monstre->action == RUSH_OU_FUITE){
        if(monstre->duree > 0){
            if(compteur%5 == 0){
                rush_joueur(monstre, joueur);
            }
        }
        else
            monstre->duree = DUREE_RUSH_OU_FUITE;
    }
}

void agro_monstre(monstre_t * monstre, joueur_t * joueur){
    switch(monstre->type){
        case(WITCHER): agro_witcher(monstre, joueur); break;
        case(KNIGHT): agro_knight(monstre, joueur); break;
        default : break; 
    }
}

void ronde_monstre(monstre_t * monstre){
    if(monstre->duree <= 0){
        if(rand()%3){
            monstre->action = MONSTRE_MARCHER;
            monstre->duree = DUREE_MONSTRE_MARCHER;
            monstre->orientation = rand()%4;
            orienter_monstre(monstre);
        }else{
            monstre->action = MONSTRE_EN_GARDE;
            monstre->duree = DUREE_MONSTRE_EN_GARDE;
        }
    }
    if(monstre->action == MONSTRE_MARCHER){
        if(compteur%16 == 0){
            marcher_monstre(monstre);
        }
    }
    else
        monstre_en_garde(monstre);
}

bool hors_map_monstre(monstre_t * monstre){
    //test gauche
    if(monstre->collision.x <= 0)
        return 1;
    //test haut
    if(monstre->collision.y <= 0)
        return 1;
    //test droit
    if(monstre->collision.w + monstre->collision.x >= map->text_map->width)
        return 1;
    //test bas
    if(monstre->collision.h + monstre->collision.y >= map->text_map->height)
        return 1;
    return 0;
}

void deplacer_entite(SDL_Rect collision, t_direction orientation, int nb_pixel){
    
}

void monstre_blesse(monstre_t * monstre){
    if(monstre->duree <= 0)
            monstre->action = MONSTRE_EN_GARDE;
    else{
        //clignotement affichage frame

    }
}

void action_monstre(monstre_t * monstre, joueur_t * joueur){
    bool deplacement = 1;
    monstre->texture->aff_fenetre->x = monstre->collision.x - floor(13 * monstre->texture->multipli_taille);
    monstre->texture->aff_fenetre->y = monstre->collision.y - floor(13 * monstre->texture->multipli_taille);
    (monstre->duree)--;

    if(monstre->action == MONSTRE_BLESSE){
        monstre_blesse(monstre);
    }

    else if(monstre->action == MONSTRE_MARCHER || monstre->action == MONSTRE_EN_GARDE){
        //si le monstre détecte le joueur
        if(distance_joueur(monstre->collision, joueur) < DISTANCE_AGRO){
            monstre->action = RUSH_OU_FUITE;
            monstre->duree = DUREE_RUSH_OU_FUITE;
        }
        else
            ronde_monstre(monstre);
    }
    else
        agro_monstre(monstre, joueur);
    
    if(compteur%2 == 0 && (monstre->action == MONSTRE_MARCHER || monstre->action == RUSH_OU_FUITE || monstre->action == MONSTRE_BLESSE) ){

        switch(monstre->orientation){
            case(NORD): deplacement_y_entite(map, monstre->texture, -1, &(monstre->collision) ); break;
            case(EST): deplacement_x_entite(map, monstre->texture, 1, &(monstre->collision) ); break;
            case(SUD): deplacement_y_entite(map, monstre->texture, 1, &(monstre->collision) ); break;
            case(OUEST): deplacement_x_entite(map, monstre->texture, -1, &(monstre->collision) ); break;
            default: break;
        }
        //si bloquer par une entité
        if(!deplacement)
            monstre->duree = 0;
    }
}



void charger_base_monstre(char * chemin_fichier, liste_base_monstres_t ** liste_base_monstres){

    json_object *fichier = json_object_from_file(chemin_fichier);
    int nb_monstre;

    if(!fichier){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors du chargement des monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        free(msp);
        fermer_programme(ERREUR_FICHIER);
    }

    json_object *json_tbl_monstre = NULL;
    json_object *json_monstre = NULL;

    /* Définition des attributs */

    json_object *json_fichier_image = NULL;
    json_object *json_type = NULL;
    json_object *json_pdv = NULL;
    json_object *json_attaque = NULL;
    json_object *json_vitesse = NULL;
    json_object *json_xp = NULL;
    json_object *json_hitbox = NULL;

    /* Définition des attributs de la hitbox */
    json_object *json_hitbox_x = NULL;
    json_object *json_hitbox_y = NULL;

    /* Récupération des données */

    json_tbl_monstre = json_object_object_get(fichier, "monstre");

    if(!json_tbl_monstre){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de la récupération des monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        free(msp);
        fermer_programme(ERREUR_FICHIER);
    }

    //allocation de liste_base_monstre avec le nombre de monstre nécéssaire
    (*liste_base_monstres) = malloc(sizeof(liste_base_monstres_t));
    nb_monstre = json_object_array_length(json_tbl_monstre);
    (*liste_base_monstres)->tab = malloc(sizeof(base_monstre_t) * nb_monstre);
    (*liste_base_monstres)->nb_monstre = nb_monstre;

    for(unsigned int i = 0; i < nb_monstre; i++){
    
        json_monstre = json_object_array_get_idx(json_tbl_monstre, i);

        if(!json_monstre){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_fichier_image = json_object_object_get(json_monstre, "fichier");

        if(!json_fichier_image){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_type = json_object_object_get(json_monstre, "type");

        if(!json_type){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_pdv = json_object_object_get(json_monstre, "pdv");

        if(!json_pdv){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_attaque = json_object_object_get(json_monstre, "attaque");

        if(!json_attaque){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_vitesse = json_object_object_get(json_monstre, "vitesse");

        if(!json_vitesse){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_xp = json_object_object_get(json_monstre, "xp");

        if(!json_xp){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_hitbox = json_object_object_get(json_monstre, "hitbox");

        if(!json_hitbox){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_hitbox_x = json_object_array_get_idx(json_hitbox, 0);

        if(!json_hitbox_x){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_hitbox_y = json_object_array_get_idx(json_hitbox, 1);

        if(!json_hitbox_y){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        const char *fichier_image = json_object_get_string(json_fichier_image);

        if(!fichier_image){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        const char *type = json_object_get_string(json_type);

        if(!type){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les monstres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }

        
        /*inserrer les caractèristiques dans base_monstre_t*/
        strcpy((*liste_base_monstres)->tab[i].fichier_image, fichier_image);
        strcpy((*liste_base_monstres)->tab[i].nom_monstre, type);
        (*liste_base_monstres)->tab[i].pdv = json_object_get_int(json_pdv);
        (*liste_base_monstres)->tab[i].attaque = json_object_get_int(json_attaque);
        (*liste_base_monstres)->tab[i].vitesse = json_object_get_int(json_vitesse);
        (*liste_base_monstres)->tab[i].gainXp = json_object_get_int(json_xp);
        (*liste_base_monstres)->tab[i].hitbox.w = json_object_get_int(json_hitbox_x);
        (*liste_base_monstres)->tab[i].hitbox.h = json_object_get_int(json_hitbox_y);
    }
    json_object_put(fichier);
}