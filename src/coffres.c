#include <json-c/json.h>
#include <definition_commun.h>
#include <code_erreur.h>
#include <map.h>
#include <coffres.h>

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

    json_object *JSON_fichier = json_object_from_file(chemin_fichier); //objet json contenant des informations de jeu
    int nb_coffres;

    if(!JSON_fichier)
        erreur("Erreur lors du chargement des coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

    json_object *JSON_tbl_coffre = NULL;
    json_object *JSON_coffre = NULL;

    /* Définition des attributs */

    json_object *JSON_fichier_image = NULL;
    json_object *JSON_type = NULL;
    json_object *JSON_hitbox = NULL;

    /* Définition des attributs de la hitbox */
    json_object *JSON_hitbox_x = NULL;
    json_object *JSON_hitbox_y = NULL;

    /* Récupération des données */

    if(!json_object_object_get_ex(JSON_fichier, "coffre", &JSON_tbl_coffre))
        erreur("Erreur lors de la récupération des coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

    //allocation de liste_base_coffre avec le nombre de coffre nécéssaire
    (*liste_base_coffres) = malloc(sizeof(liste_base_coffres_t));
    nb_coffres = json_object_array_length(JSON_tbl_coffre);
    (*liste_base_coffres)->tab = malloc(sizeof(base_coffre_t) * nb_coffres);
    (*liste_base_coffres)->nb_coffre = nb_coffres;

    for(unsigned int i = 0; i < nb_coffres; i++){
    
        JSON_coffre = json_object_array_get_idx(JSON_tbl_coffre, i);

        if(!JSON_coffre)
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_coffre, "fichier", &JSON_fichier_image))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_coffre, "type", &JSON_type))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_coffre, "hitbox", &JSON_hitbox))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());
        
        JSON_hitbox_x = json_object_array_get_idx(JSON_hitbox, 0);

        if(!JSON_hitbox_x)
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());
            
        JSON_hitbox_y = json_object_array_get_idx(JSON_hitbox, 1);

        if(!JSON_hitbox_y)
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        const char *fichier_image = json_object_get_string(JSON_fichier_image);

        if(!fichier_image)
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        const char *type = json_object_get_string(JSON_type);

        if(!type)
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());
        
        /*inserrer les caractèristiques dans base_coffre_t*/
        strcpy((*liste_base_coffres)->tab[i].fichier_image, fichier_image);
        strcpy((*liste_base_coffres)->tab[i].nom_coffre, type);
        (*liste_base_coffres)->tab[i].hitbox.w = json_object_get_int(JSON_hitbox_x);
        (*liste_base_coffres)->tab[i].hitbox.h = json_object_get_int(JSON_hitbox_y);
    }
    json_object_put(JSON_fichier);
}

type_coffre_t nom_coffre_to_type_coffre(const char * nom_coffre){
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
    return COFFRE_INCONNU;
}

coffre_t* creer_coffre(int id_cle, int id_loot, liste_base_coffres_t* liste_base_coffres, const char * const nom_coffre, int x, int y, t_map *map){
    int i;

    /* allocation coffre_t*/
    coffre_t* coffre = malloc(sizeof(coffre_t));
    for(i=0; i<liste_base_coffres->nb_coffre; i++){
        if(strcmp(liste_base_coffres->tab[i].nom_coffre,nom_coffre) == 0){ //comparer les id des coffres car deux coffres peuvent avoir le même nom?
            coffre->id_cle = id_cle;
            coffre->id_loot = id_loot;
            coffre->type = nom_coffre_to_type_coffre(nom_coffre);
            coffre->collision.x = x * TAILLE_CASE;
            coffre->collision.y = y * TAILLE_CASE;
            coffre->collision.w = liste_base_coffres->tab[i].hitbox.w * TAILLE_CASE;
            coffre->collision.h = liste_base_coffres->tab[i].hitbox.h * TAILLE_CASE;

            //orientation du coffre
            if((coffre->type == PROFIL_OUVERT) || (coffre->type == PROFIL_FERME))
                coffre->orientation = EST_1;
            else{
                coffre->orientation = SUD_1;
            }

            //état du coffre
            if((coffre->type == PROFIL_FERME) || (coffre->type == FACE_FERME))
                coffre->etat = FERME;
            else
                coffre->etat = OUVERT;

            /*copie les informations de base_coffre dans coffre*/
            coffre->texture = creer_texture(liste_base_coffres->tab[i].fichier_image, -1, -1, coffre->collision.x, coffre->collision.y, map->taille_case /(float)32);
            coffre->texture->duree_frame_anim = NB_FPS;

            return coffre;
        }
    }
    return NULL;
}

void info_coffre(coffre_t * coffre){
    printf("Coffre: %p\ntype: %d\norientation: %d\netat%d\ncollision:{x:%d y:%d w:%d h:%d}\n", coffre, coffre->type, coffre->orientation, coffre->etat,
    coffre->collision.x, coffre->collision.y, coffre->collision.w, coffre->collision.h);
    info_texture(coffre->texture);
}

t_direction_1 inverser_direction(t_direction_1 direction){
    return((direction + 2) %4);
}

void interaction_coffre(SDL_Rect * coffre_rect, joueur_t * joueur, lobjet_t * objets){
    coffre_t * coffre = NULL;
    objet_t * cle_joueur = NULL;
    en_tete(map->liste_coffres);

    //detection collision avec coffre
    while(!hors_liste(map->liste_coffres)){
        coffre = valeur_elt(map->liste_coffres);

        if(&(coffre->collision) == coffre_rect){
            //conditions pour ouvrir un coffre
            cle_joueur = joueur->inventaire->equipe->liste[quete];
            if((coffre->etat == FERME) && (joueur->statut->orient_dep == inverser_direction(coffre->orientation)) && ((coffre->id_cle == 0) || ((cle_joueur != NULL) && (coffre->id_cle == cle_joueur->id) ) ) ){
                //changent état coffre
                coffre->etat = OUVERT;
                
                //ramasser l'objet du coffre
                if(coffre->id_loot != 0)
                    ramasser_objet(objets->liste[coffre->id_loot - 1], joueur->inventaire);
                    
                //animation ouverture
                if(coffre->type == PROFIL_FERME)
                    coffre->texture = creer_texture(COFFRE_PROFIL_OUVERT, -1, -1, coffre->collision.x, coffre->collision.y - TAILLE_CASE, map->taille_case /(float)32);
                if(coffre->type == FACE_FERME){
                    coffre->texture = creer_texture(COFFRE_FACE_OUVERT, -1, -1, coffre->collision.x, coffre->collision.y, map->taille_case /(float)32);
                }
            }
            //changer la texture coffre
            //ajouter un bouton d'ouverture
            //ajouter gestion direction
        }
    suivant(map->liste_coffres);
    }
}