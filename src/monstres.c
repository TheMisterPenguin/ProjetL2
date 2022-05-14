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

#include <utils.h>

/**
 * \file monstres.c
 * \author Antoine Bruneau (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les monstres
 * \version 0.1
 * \date 03/03/2022
 * \copyright Copyright (c) 2022
 */

liste_base_monstres_t * liste_base_monstres = NULL; /* le tableau de modèles de monstre */

void detruire_monstre(monstre_t ** monstre){
    free((*monstre)->texture);
    free(*monstre);
    *monstre = NULL;
}

void detruire_monstre_cb(void * monstre){
    detruire_monstre(monstre);
}

monstre_t * ajouter_monstre(monstre_t* monstre){
    return monstre;
}

void * ajouter_monstre_cb(void * monstre){
    return ajouter_monstre(monstre);
}

void detruire_liste_base_monstres(liste_base_monstres_t** liste_base_monstres){

    free((**liste_base_monstres).tab);
    free(*liste_base_monstres);
    *liste_base_monstres = NULL;
}

monstre_t* creer_monstre(liste_base_monstres_t* liste_base_monstres, const char * const nom_monstre, int x, int y, t_map *map){
    int i;
    monstre_t* monstre = malloc(sizeof(monstre_t)); /* allocation monstre_t*/
    base_monstre_t* base_monstre = NULL;

    for(i=0; i<liste_base_monstres->nb_monstre; i++){
        base_monstre = &(liste_base_monstres->tab[i]);
        if(strcmp(base_monstre->nom_monstre, nom_monstre) == 0){
            monstre->type = nom_monstre_to_type_monstre(nom_monstre);

            if(monstre->type == TYPE_MONSTRE_INCONNU)
                erreur("Erreur lors de la création du monstre : le monstre %s n'existe pas !", ERREUR_MAP, nom_monstre);
            
            /* initialisation du monstre */
            monstre->orientation = NORD_1;
            monstre->duree = 0;
            monstre->action = MONSTRE_EN_GARDE;
            monstre->collision.x = x;
            monstre->collision.y = y;
            /* copie les informations de base_monstre dans monstre */
            monstre->collision.w = base_monstre->hitbox.w * (map->taille_case / TAILLE_CASE); /* adaptation de la largeur en fonction de la taille d'une case de la map */
            monstre->collision.h = base_monstre->hitbox.h * (map->taille_case / TAILLE_CASE); /* adaptation de la hauteur en fonction de la taille d'une case de la map */
            monstre->pdv = base_monstre->pdv;
            monstre->attaque = base_monstre->attaque;
            monstre->vitesse = base_monstre->vitesse;
            monstre->gainXp = base_monstre->gainXp;
            /* creation de la texture */
            monstre->texture = creer_texture(base_monstre->fichier_image, LARGEUR_ENTITE, LONGUEUR_ENTITE, x, y, map->taille_case / TAILLE_CASE);
            monstre->texture->duree_frame_anim = NB_FPS;

            return monstre;
        }
    }
    return NULL;
}

type_monstre_t nom_monstre_to_type_monstre(const char * const nom_monstre){
    if(strcmp(nom_monstre,"witcher") == 0)
        return WITCHER;
    else if(strcmp(nom_monstre,"knight") == 0)
        return KNIGHT;
    else{
        fprintf(stderr,"Erreur, nom du monstre incorrect\n");
        return TYPE_MONSTRE_INCONNU;
    }
}

/**
 * \fn void marcher_monstre(monstre_t * monstre);
 * \brief Fonction qui met à jour la texture du monstre pour ses déplacements
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 */
void marcher_monstre(monstre_t * monstre){
    switch(monstre->type){
        case(KNIGHT): next_frame_x_indice(monstre->texture, (current_frame_x(monstre->texture)+1) % 2);
        default : break; 
    }
}

/**
 * \fn void orienter_monstre(monstre_t * monstre)
 * \brief Fonction qui met à jour la texture du monstre par rapport à son orientation
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 */
void orienter_monstre(monstre_t * monstre){
    switch(monstre->type){
        case(WITCHER): next_frame_x_indice(monstre->texture, monstre->orientation); break;
        case(KNIGHT): next_frame_y_indice(monstre->texture, monstre->orientation); break;
        default : break; 
    }
}

/**
 * \fn void orienter_monstre_vers_joueur(monstre_t * monstre, joueur_t * joueur);
 * \brief Fonction qui met à jour la texture du monstre pour qu'il soit orienté vers le joueur
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur ciblé
 */
void orienter_monstre_vers_joueur(monstre_t * monstre, joueur_t * joueur){
    int y_diff, x_diff;
    x_diff = distance_x_joueur(monstre->collision, joueur);
    y_diff = distance_y_joueur(monstre->collision, joueur);

    /* choisit le chemin le plus court en comparant la distance x à y pour avoir la meilleur orientaiton possible vers le joueur*/
    if( abs(x_diff) < abs(y_diff) ){
        if(y_diff < 0)
            monstre->orientation = NORD_1;
        else
            monstre->orientation = SUD_1;
    }
    else{
        if(x_diff < 0)
            monstre->orientation = OUEST_1;
        else
            monstre->orientation = EST_1;
    }
    /* oriente le monstre grâce à l'orientation trouvé */
    orienter_monstre(monstre);
}

/**
 * \fn void monstre_en_garde(monstre_t * monstre);
 * \brief Fonction qui met à jour la texture du monstre sur la position de garde (immobile) 
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 */
void monstre_en_garde(monstre_t * monstre){
    switch(monstre->type){
        case(KNIGHT): next_frame_x_indice(monstre->texture, 2); break;
        default : break; 
    }
}

/**
 * \fn void monstre_attaque(monstre_t * monstre);
 * \brief Fonction qui met à jour la texture du monstre sur la position d'attaque 
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 */
void monstre_attaque(monstre_t * monstre){
    switch(monstre->type){
        case(WITCHER): next_frame_y_indice(monstre->texture, 1); break ;
        default: break;
    }
}

/**
 * \fn void fuir_joueur(monstre_t *monstre, joueur_t * joueur);
 * \brief Fonction qui met à jour la texture du monstre de sorte à ce qu'il fuit le joueur
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur à fuire
 */
void fuir_joueur(monstre_t *monstre, joueur_t * joueur){
    int y_diff, x_diff;
    x_diff = distance_x_joueur(monstre->collision, joueur);
    y_diff = distance_y_joueur(monstre->collision, joueur);

    /* choisit la direction opposé au joueur */
    if( abs(x_diff) < abs(y_diff) ){
        if(y_diff < 0)
            monstre->orientation = SUD_1;
        else
            monstre->orientation = NORD_1;
    }
    else{
        if(x_diff < 0)
            monstre->orientation = EST_1;
        else
            monstre->orientation = OUEST_1;
    }
    /* oriente le monstre dans cette direction */
    orienter_monstre(monstre);
    marcher_monstre(monstre);
}

/**
 * \fn void rush_joueur(monstre_t * monstre, joueur_t * joueur);
 * \brief Fonction qui met à jour la texture du monstre de sorte à ce qu'il se deplace vers le joueur
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur à atteindre
 */
void rush_joueur(monstre_t * monstre, joueur_t * joueur){
    orienter_monstre_vers_joueur(monstre, joueur);
    marcher_monstre(monstre);
}

/**
 * \fn void agro_witcher(monstre_t * monstre, joueur_t * joueur);
 * \brief Fonction qui met à jour la texture du monstre "witcher" lorsqu'il est dans sa phase d'attaque
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur à attaquer
 */
void agro_witcher(monstre_t * monstre, joueur_t * joueur){
    /* replie ou rush du joueur */
    if(monstre->action == RUSH_OU_FUITE)
        /* l'action n'est pas terminé */
        if(monstre->duree > 0){
            if(compteur%5 == 0) /* vitesse de l'animation */
                fuir_joueur(monstre, joueur);
        }
        /* l'action est terminé */
        else{
            monstre->action = MONSTRE_ATTAQUE;
            monstre->duree = DUREE_MONSTRE_ATTAQUE;
            orienter_monstre_vers_joueur(monstre, joueur);
            creer_sort_monstre(monstre, joueur);
        }
    /* attaque du joueur */
    else
        /* l'action n'est pas terminé */
        if(monstre->duree > 0){
            if(compteur%5 == 0) /* vitesse de l'animation */
                monstre_attaque(monstre);
        }
        /* l'action est terminé */
        else{
            monstre->action = RUSH_OU_FUITE;
            monstre->duree = DUREE_RUSH_OU_FUITE;
            next_frame_y_indice(monstre->texture, 0); /* repositionnement sur le sprite correspondant à l'action RUSH_OU_FUITE */
        }  
}

/**
 * \fn void agro_knight(monstre_t * monstre, joueur_t * joueur);
 * \brief Fonction qui met à jour la texture du monstre "knight" lorsqu'il est dans sa phase d'attaque (reboucle la même action)
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur à attaquer
 */
void agro_knight(monstre_t * monstre, joueur_t * joueur){
    if(monstre->action == RUSH_OU_FUITE){
        /* l'action n'est pas terminé */
        if(monstre->duree > 0){
            if(compteur%5 == 0) /* vitesse de l'animation */
                rush_joueur(monstre, joueur);
        }
        /* l'action est terminé */
        else
            monstre->duree = DUREE_RUSH_OU_FUITE;
    }
}

/**
 * \fn void agro_monstre(monstre_t * monstre, joueur_t * joueur);
 * \brief Fonction qui met à jour la texture d'un monstre lorsqu'il est dans sa phase d'attaque
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 * \param joueur le joueur à attaquer
 */
void agro_monstre(monstre_t * monstre, joueur_t * joueur){
    switch(monstre->type){
        case(WITCHER): agro_witcher(monstre, joueur); break;
        case(KNIGHT): agro_knight(monstre, joueur); break;
        default : break; 
    }
}

/**
 * \fn void ronde_monstre(monstre_t * monstre);
 * \brief Fonction qui met à jour la texture d'un monstre lorsqu'il est dans sa phase passive
 * \author Bruneau Antoine
 * \param monstre le monstre à mettre à jour
 */
void ronde_monstre(monstre_t * monstre){
    /* l'action est terminé */
    if(monstre->duree <= 0){
        /* 2 chance sur 3 que le monstre marche */ 
        if(rand()%3){
            monstre->action = MONSTRE_MARCHER;
            monstre->duree = DUREE_MONSTRE_MARCHER;
            monstre->orientation = rand()%4;
            orienter_monstre(monstre);
        /* 1 chance sur 3 que le monstre s'arrète */ 
        }else{
            monstre->action = MONSTRE_EN_GARDE;
            monstre->duree = DUREE_MONSTRE_EN_GARDE;
        }
    }
    /* faire marcher */
    if(monstre->action == MONSTRE_MARCHER){
        if(compteur%16 == 0) /* vitesse de l'animation */
            marcher_monstre(monstre);
    }
    /* faire s'arrèter */
    else
        monstre_en_garde(monstre);
}

void action_monstre(monstre_t * monstre, joueur_t * joueur){
    bool deplacement = vrai;

    /* faire correspondre les coordonnées de la texture monstre à celles de la zone de collison du monstre */
    monstre->texture->aff_fenetre->x = monstre->collision.x - floor(13 * monstre->texture->multipli_taille);
    monstre->texture->aff_fenetre->y = monstre->collision.y - floor(13 * monstre->texture->multipli_taille);

    (monstre->duree)--;

    if(monstre->action == MONSTRE_BLESSE){
        /* l'action est terminé */
        if(monstre->duree <= 0)
            monstre->action = MONSTRE_EN_GARDE;
    }
    /* monstre est dans sa phase passive */
    else if(monstre->action != MONSTRE_ATTAQUE && monstre->action != RUSH_OU_FUITE){
        /* le monstre détecte le joueur */
        if(distance_joueur(monstre->collision, joueur) < DISTANCE_AGRO && monstre->action != MONSTRE_PAUSE){
            monstre->action = RUSH_OU_FUITE;
            monstre->duree = DUREE_RUSH_OU_FUITE;
        }
        else
            ronde_monstre(monstre);
    }
    /* monstre est dans sa phase aggresive */
    else
        agro_monstre(monstre, joueur);
    
    /* deplacement du monstre sur la map en fonction de son action*/
    if( monstre->action == MONSTRE_MARCHER || monstre->action == RUSH_OU_FUITE || monstre->action == MONSTRE_BLESSE )
        if(compteur%2 == 0){ /* vitesse de deplacement */
            switch(monstre->orientation){
                case(NORD_1): deplacement = deplacement_y_entite(map, monstre->texture, -1, &(monstre->collision) ); break;
                case(EST_1): deplacement = deplacement_x_entite(map, monstre->texture, 1, &(monstre->collision) ); break;
                case(SUD_1): deplacement = deplacement_y_entite(map, monstre->texture, 1, &(monstre->collision) ); break;
                case(OUEST_1): deplacement = deplacement_x_entite(map, monstre->texture, -1, &(monstre->collision) ); break;
                default: break;
            }
            //si bloquer par une entité, faire une action
            if(deplacement == faux)
                monstre->duree = 0;
        }
}

void charger_base_monstre(char * chemin_fichier, liste_base_monstres_t ** liste_base_monstres){
    char *filePath = catAlloc(execDir, chemin_fichier);

    json_object *fichier = json_object_from_file(filePath);

    free(filePath);

    int nb_monstre;

    if(!fichier)
        erreur("Erreur lors du chargement des monstres : %s", ERREUR_FICHIER, json_util_get_last_err());

    json_object *JSON_tbl_monstre = NULL;
    json_object *JSON_monstre = NULL;

    /* Définition des attributs */

    json_object *JSON_fichier_image = NULL;
    json_object *JSON_type = NULL;
    json_object *JSON_pdv = NULL;
    json_object *JSON_attaque = NULL;
    json_object *JSON_vitesse = NULL;
    json_object *JSON_xp = NULL;
    json_object *JSON_hitbox = NULL;

    /* Définition des attributs de la hitbox */
    json_object *JSON_hitbox_x = NULL;
    json_object *JSON_hitbox_y = NULL;

    /* Récupération des données */

    if(!json_object_object_get_ex(fichier, "monstre", &JSON_tbl_monstre))
        erreur("Erreur lors de la récupération des monstres : %s", ERREUR_FICHIER, json_util_get_last_err());

    //allocation de liste_base_monstre avec le nombre de monstre nécéssaire
    (*liste_base_monstres) = malloc(sizeof(liste_base_monstres_t));
    nb_monstre = json_object_array_length(JSON_tbl_monstre);
    (*liste_base_monstres)->tab = malloc(sizeof(base_monstre_t) * nb_monstre);
    (*liste_base_monstres)->nb_monstre = nb_monstre;

    for(unsigned int i = 0; i < nb_monstre; i++){
    
        JSON_monstre = json_object_array_get_idx(JSON_tbl_monstre, i);

        if(!JSON_monstre)
            erreur("Erreur lors de la récupération des informations sur les monstres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_monstre, "fichier", &JSON_fichier_image))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_monstre, "type", &JSON_type))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_monstre, "pdv", &JSON_pdv))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_monstre, "attaque", &JSON_attaque))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_monstre, "vitesse", &JSON_vitesse))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());
        
        if(!json_object_object_get_ex(JSON_monstre, "xp", &JSON_xp))
            erreur("Erreur lors de la récupération des informations sur les coffres : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_monstre, "hitbox", &JSON_hitbox))
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

        /*inserrer les caractèristiques dans base_monstre_t*/
        strcpy((*liste_base_monstres)->tab[i].fichier_image, fichier_image);
        strcpy((*liste_base_monstres)->tab[i].nom_monstre, type);
        (*liste_base_monstres)->tab[i].pdv = json_object_get_int(JSON_pdv);
        (*liste_base_monstres)->tab[i].attaque = json_object_get_int(JSON_attaque);
        (*liste_base_monstres)->tab[i].vitesse = json_object_get_int(JSON_vitesse);
        (*liste_base_monstres)->tab[i].gainXp = json_object_get_int(JSON_xp);
        (*liste_base_monstres)->tab[i].hitbox.w = json_object_get_int(JSON_hitbox_x);
        (*liste_base_monstres)->tab[i].hitbox.h = json_object_get_int(JSON_hitbox_y);
    }
    json_object_put(fichier);
}