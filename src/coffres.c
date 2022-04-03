#include <json-c/json.h>
#include <coffres.h>
#include <definition_commun.h>
#include <code_erreur.h>

/**
 * \file coffres.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les coffres
 * \version 0.1
 * \date 03/04/2022
 * \copyright Copyright (c) 2022
 */

liste_base_coffres_t * liste_base_coffres = NULL;

void charger_base_coffre(char * chemin_fichier, liste_base_coffres_t ** liste_base_coffres){

    json_object *fichier = json_object_from_file(chemin_fichier);
    int nb_coffres;

    if(!fichier){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors du chargement des coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        free(msp);
        fermer_programme(ERREUR_FICHIER);
    }

    json_object *json_tbl_coffre = NULL;
    json_object *json_coffre = NULL;

    /* Définition des attributs */

    json_object *json_fichier_image = NULL;
    json_object *json_type = NULL;
    json_object *json_hitbox = NULL;

    /* Définition des attributs de la hitbox */
    json_object *json_hitbox_x = NULL;
    json_object *json_hitbox_y = NULL;

    /* Récupération des données */

    json_tbl_coffre = json_object_object_get(fichier, "coffre");

    if(!json_tbl_coffre){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de la récupération des coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
        free(msp);
        fermer_programme(ERREUR_FICHIER);
    }

    //allocation de liste_base_coffre avec le nombre de coffre nécéssaire
    (*liste_base_coffres) = malloc(sizeof(liste_base_coffres_t));
    nb_coffres = json_object_array_length(json_tbl_coffre);
    (*liste_base_coffres)->tab = malloc(sizeof(base_coffre_t) * nb_coffres);
    (*liste_base_coffres)->nb_coffre = nb_coffres;

    for(unsigned int i = 0; i < nb_coffres; i++){
    
        json_coffre = json_object_array_get_idx(json_tbl_coffre, i);

        if(!json_coffre){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_fichier_image = json_object_object_get(json_coffre, "fichier");

        if(!json_fichier_image){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_type = json_object_object_get(json_coffre, "type");

        if(!json_type){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        
        json_hitbox = json_object_object_get(json_coffre, "hitbox");

        if(!json_hitbox){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_hitbox_x = json_object_array_get_idx(json_hitbox, 0);

        if(!json_hitbox_x){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        json_hitbox_y = json_object_array_get_idx(json_hitbox, 1);

        if(!json_hitbox_y){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        const char *fichier_image = json_object_get_string(json_fichier_image);

        if(!fichier_image){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }
        const char *type = json_object_get_string(json_type);

        if(!type){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Erreur lors de la récupération des informations sur les coffres : %s\n Erreur : 0x%X\n", json_util_get_last_err(), ERREUR_FICHIER);
            free(msp);
            fermer_programme(ERREUR_FICHIER);
        }

        
        /*inserrer les caractèristiques dans base_coffre_t*/
        strcpy((*liste_base_coffres)->tab[i].fichier_image, fichier_image);
        strcpy((*liste_base_coffres)->tab[i].nom_coffre, type);
        (*liste_base_coffres)->tab[i].hitbox.w = json_object_get_int(json_hitbox_x);
        (*liste_base_coffres)->tab[i].hitbox.h = json_object_get_int(json_hitbox_y);
    }
    json_object_put(fichier);
}

type_coffre_t nom_coffre_to_type_coffre(char * nom_coffre){
    if(strcmp(nom_coffre,"profilferme") == 0)
        return PROFIL_FERME;
    else if(strcmp(nom_coffre,"profilouvert") == 0)
        return PROFIL_OUVERT;
    else if(strcmp(nom_coffre,"faceferme") == 0)
        return FACE_FERME;
    else if(strcmp(nom_coffre,"faceouvert") == 0)
        return FACE_OUVERT;
    else{
        fprintf(stderr,"Erreur, nom du coffre incorrect\n");
    }

    fermer_programme(ERREUR_FICHIER);
}

coffre_t* creer_coffre(liste_base_coffres_t* liste_base_coffres, const char * const nom_coffre, int x, int y, t_map *map){
    int i;

    /* allocation coffre_t*/
    coffre_t* coffre = malloc(sizeof(coffre_t));
    for(i=0; i<liste_base_coffres->nb_coffre; i++){
        if(strcmp(liste_base_coffres->tab[i].nom_coffre,nom_coffre) == 0){
            coffre->type = nom_coffre_to_type_coffre(nom_coffre);
            coffre->collision.x = x * TAILLE_CASE;
            coffre->collision.y = y * TAILLE_CASE;
            coffre->collision.w = liste_base_coffres->tab[i].hitbox.w * TAILLE_CASE;
            coffre->collision.h = liste_base_coffres->tab[i].hitbox.h * TAILLE_CASE;

            coffre->orientation = NORD; //à changer selon le type
            coffre->action = FERME;

            /*copie les informations de base_coffre dans coffre*/
            coffre->texture = creer_texture(liste_base_coffres->tab[i].fichier_image, -1, -1, coffre->collision.x, coffre->collision.y, map->taille_case /(float)32);
            info_coffre(coffre);
            coffre->texture->duree_frame_anim = NB_FPS;

            return coffre;
        }
    }
    return NULL;
}

void info_coffre(coffre_t * coffre){
    printf("Coffre: %p\ntype: %d\norientation: %d\naction%d\ncollision:{x:%d y:%d w:%d h:%d}\n", coffre, coffre->type, coffre->orientation, coffre->action,
    coffre->collision.x, coffre->collision.y, coffre->collision.w, coffre->collision.h);
    info_texture(coffre->texture);
}

void interaction_coffre(SDL_Rect * coffre_rect){
    coffre_t * coffre = NULL;
    en_tete(map->liste_coffres);

    //detection collision avec coffre
    while(!hors_liste(map->liste_coffres)){
        coffre = valeur_elt(map->liste_coffres);

        if(&(coffre->collision) == coffre_rect){
            printf("ouverture du coffre\n");
            //changer la texture coffre
            //ajouter un bouton d'ouverture
            //ajouter gestion direction
        }
    suivant(map->liste_coffres);
    }
}