#include <json-c/json.h>
#include <affichage.h>
#include <map.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <code_erreur.h>
#include <monstres.h>
#include <math.h>
#include <coffres.h>
#include <fonctions.h>
#include <personnage.h>

/**
 * \file map.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fonctions de gestion de la map
 * \version 0.1
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

t_map *map;

void init_sousbuffer(t_map *map, joueur_t *joueur)
{

    SDL_Texture *sous_buffer = SDL_CreateTexture(rendu_principal, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, floor(map->text_sol->width * map->text_sol->multipli_taille), floor(map->text_sol->height * map->text_sol->multipli_taille));
    if (!sous_buffer)
        erreur("Erreur lors de la création de la texture de sous-buffer : %s", SDL_ERREUR, SDL_GetError());
    /* On alloue le second  buffer */
    map->text_map = malloc(sizeof(t_aff));

    if (!map->text_map)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    map->text_map->aff_fenetre = malloc(sizeof(SDL_Rect));

    if (!map->text_map->aff_fenetre)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    map->text_map->frame_anim = malloc(sizeof(SDL_Rect));

    if (!map->text_map->frame_anim)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    /* On alloue le troisième  buffer */
    fenetre_finale = malloc(sizeof(t_aff));

    if (!fenetre_finale)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->texture = SDL_CreateTexture(rendu_principal, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, floor(map->text_sol->width * map->text_sol->multipli_taille), floor(map->text_sol->height * map->text_sol->multipli_taille));

    if (!fenetre_finale->texture)
        erreur("Erreur lors de la créations des buffers : %s", SDL_ERREUR, SDL_GetError());

    fenetre_finale->aff_fenetre = malloc(sizeof(SDL_Rect));

    if (!fenetre_finale->aff_fenetre)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->frame_anim = malloc(sizeof(SDL_Rect));

    if (!fenetre_finale->frame_anim)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->frame_anim->x = 0;
    fenetre_finale->frame_anim->y = 0;
    fenetre_finale->frame_anim->w = floor(FENETRE_LONGUEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    fenetre_finale->frame_anim->h = floor(FENETRE_LARGEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    fenetre_finale->aff_fenetre->x = 0;
    fenetre_finale->aff_fenetre->y = 0;
    fenetre_finale->aff_fenetre->w = FENETRE_LONGUEUR;
    fenetre_finale->aff_fenetre->h = FENETRE_LARGEUR;

    map->text_map->texture = sous_buffer;

    /* On définit la partie de la map que l'on voie à l'écran */
    map->text_map->aff_fenetre->w = floor(FENETRE_LONGUEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    map->text_map->aff_fenetre->h = floor(FENETRE_LARGEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    map->text_map->aff_fenetre->x = 0;
    map->text_map->aff_fenetre->y = 0;

    /* On place la partie de la map que l'on voit */
    map->text_map->frame_anim->w = floor(FENETRE_LONGUEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    map->text_map->frame_anim->h = floor(FENETRE_LARGEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    map->text_map->frame_anim->x = 0;
    map->text_map->frame_anim->y = 0;

    ty.w = fenetre_finale->frame_anim->w;
    ty.h = joueur->statut->zone_colision.h;

    tx.h = fenetre_finale->frame_anim->h;
    tx.w = joueur->statut->zone_colision.w;

    rect_centre_rect_y(&ty, fenetre_finale->frame_anim);
    rect_centre_rect_x(&tx, fenetre_finale->frame_anim);

    if (SDL_SetRenderTarget(rendu_principal, map->text_map->texture))
        erreur("Erreur lors de la création du sous buffer : %s\n", SDL_ERREUR, SDL_GetError());

    if (SDL_RenderCopy(rendu_principal, map->text_sol->texture, NULL, NULL))
        fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());

    SDL_QueryTexture(map->text_map->texture, NULL, NULL, &(map->text_map->width), &(map->text_map->height));
}

SDL_Rect taille_ecran_cases(){
    SDL_Rect p;

    int taille_case = TAILLE_CASE * 6;
    
    p.w = FENETRE_LONGUEUR / taille_case;
    p.h = FENETRE_LARGEUR / taille_case;
    p.x = 0;
    p.y = 0;


    return p;
}

t_map * charger_map(const char * const nom_map){
    t_map *m = NULL;

    json_object *JSON_fichier = json_object_from_file(nom_map);
    json_object *JSON_id_map =         NULL;
    json_object *JSON_texture_map =    NULL;
    json_object *JSON_width =          NULL;
    json_object *JSON_height =         NULL;
    json_object *JSON_taille_case =    NULL;
    json_object *JSON_tbl_monstre =    NULL;
    json_object *JSON_tbl_coffre  =    NULL;

    json_object *JSON_objet_monstre =  NULL;
    json_object *objet_json =          NULL;
    json_object *JSON_nom_monstre =    NULL;   
    json_object *JSON_position =       NULL;
    json_object *JSON_position2 =      NULL;
    json_object *JSON_x =              NULL;
    json_object *JSON_y =              NULL;
    json_object *x2 =                  NULL;
    json_object *y2 =                  NULL;
    json_object *nom_coffre =          NULL;
    json_object *id_cle =              NULL;

    monstre_t * inserer =              NULL;
    coffre_t * nv_coffre =             NULL;

    json_object *JSON_tbl_wall =       NULL;
    json_object *JSON_object_wall =    NULL;
    json_object *JSON_wall_x =         NULL;
    json_object *JSON_wall_y =         NULL;
    json_object *JSON_wall_h =         NULL;
    json_object *JSON_wall_w =         NULL;

    json_object *JSON_zones_tp =       NULL;
    json_object *JSON_zone_tp =        NULL;
    json_object *JSON_zone_tp_x =      NULL;
    json_object *JSON_zone_tp_y =      NULL;
    json_object *JSON_zone_tp_h =      NULL;
    json_object *JSON_zone_tp_w =      NULL;
    json_object *JSON_zone_tp_dest =   NULL;
    json_object *JSON_zone_tp_coords = NULL;
    json_object *JSON_zone_tp_coord_x= NULL;
    json_object *JSON_zone_tp_coord_y= NULL;


    /* Allocation de la mémoire pour la map */
    m = malloc(sizeof(t_map));

    if(!m)
        erreur("Impossible de charger la map : Plus de mémoire", OUT_OF_MEM);

    /* Initialisation des listes */
    m->liste_monstres =  init_liste(NULL,NULL,NULL);

    if(!m->liste_monstres)
        erreur("Impossible de charger la map", ERREUR_LISTE);
    
    m->liste_coffres =  init_liste(NULL,NULL,NULL);

    if(!m->liste_coffres)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_sorts = init_liste(NULL,NULL,NULL);

    if(!m->liste_sorts)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_collisions = init_liste(NULL, NULL, NULL);

    if(!m->liste_collisions)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_zone_tp = init_liste(NULL, NULL, NULL);

    if(!m->liste_zone_tp)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    /* Récupération des informations dans le fichier */
    if(!json_object_object_get_ex(JSON_fichier, "chest", &JSON_tbl_coffre))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if(!json_object_object_get_ex(JSON_fichier, "id", &JSON_id_map))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if(!json_object_object_get_ex(JSON_fichier, "file-path", &JSON_texture_map))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if(!json_object_object_get_ex(JSON_fichier, "width", &JSON_width))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if(!json_object_object_get_ex(JSON_fichier, "height", &JSON_height))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "taille case", &JSON_taille_case))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if(!json_object_object_get_ex(JSON_fichier, "monsters", &JSON_tbl_monstre))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if(!json_object_object_get_ex(JSON_fichier, "wall", &JSON_tbl_wall))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if(!json_object_object_get_ex(JSON_fichier, "zones tp", &JSON_zones_tp))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    /* Récupération des informations */
    m->id_map = json_object_get_int(JSON_id_map);
    m->text_sol = creer_texture(json_object_get_string(JSON_texture_map), -1, -1, 0, 0, 1);
    m->height = json_object_get_int(JSON_height);
    m->width = json_object_get_int(JSON_width);
    m->taille_case = json_object_get_int(JSON_taille_case);

    if(!m->text_sol)
        erreur("Impossible de charger la map : %s", ERREUR_TEXTURE, SDL_GetError());

    //Génération des collisions de la carte
    for(unsigned int i = 0; i < json_object_array_length(JSON_tbl_wall); i++){
        JSON_object_wall = json_object_array_get_idx(JSON_tbl_wall, i);

        if(!JSON_object_wall)
            erreur("Impossible de charger la map : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_object_wall, "x", &JSON_wall_x))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_object_wall, "y", &JSON_wall_y))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_object_wall, "h", &JSON_wall_h))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_object_wall, "w", &JSON_wall_w))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        SDL_Rect *valeur = malloc(sizeof(SDL_Rect));

        if(!valeur)
            erreur("Impossible de charger la map", OUT_OF_MEM);

        valeur->x = json_object_get_int(JSON_wall_x) * m->taille_case;
        valeur->y = json_object_get_int(JSON_wall_y) * m->taille_case;
        valeur->h = json_object_get_int(JSON_wall_h) * m->taille_case;
        valeur->w = json_object_get_int(JSON_wall_w) * m->taille_case;

        ajout_droit(m->liste_collisions, valeur);
    }

    //Génération des monstres
    for(unsigned int i = 0; i < json_object_array_length(JSON_tbl_monstre); i++){
        JSON_objet_monstre = json_object_array_get_idx(JSON_tbl_monstre,i);

        if(!JSON_objet_monstre)
            erreur("Impossible de charger la map : %s", ERREUR_FICHIER, json_util_get_last_err())

        if(!json_object_object_get_ex(JSON_objet_monstre, "type", &JSON_nom_monstre))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_objet_monstre, "position", &JSON_position))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        JSON_x = json_object_array_get_idx(JSON_position,0);
        JSON_y = json_object_array_get_idx(JSON_position,1);
        
        if(!JSON_x)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!JSON_y)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        inserer = creer_monstre(liste_base_monstres, json_object_get_string(JSON_nom_monstre), json_object_get_int(JSON_x), json_object_get_int(JSON_y), m);

        if(!inserer)
            erreur("Erreur lors de la création du monstre : le monstre \"%s\" n'existe pas !", ERREUR_MAP, json_object_get_string(JSON_nom_monstre));

        ajout_droit(m->liste_monstres, inserer);
        en_queue(m->liste_collisions);
        ajout_droit(m->liste_collisions, &(inserer->collision));
    }

    //Génération des coffres
    for(unsigned int i = 0; i < json_object_array_length(JSON_tbl_coffre); i++){
        objet_json = json_object_array_get_idx(JSON_tbl_coffre,i);

        nom_coffre = json_object_object_get(objet_json,"type");
        id_cle = json_object_object_get(objet_json,"id_cle");
        JSON_position2 = json_object_object_get(objet_json,"position");

        x2 = json_object_array_get_idx(JSON_position2,0);
        y2 = json_object_array_get_idx(JSON_position2,1);

        nv_coffre = creer_coffre(json_object_get_int(id_cle), liste_base_coffres, json_object_get_string(nom_coffre), json_object_get_int(x2), json_object_get_int(y2), m);
        ajout_droit(m->liste_coffres, nv_coffre);
        en_queue(m->liste_collisions);

        //sprite des coffres de profile de 2*3 mais hitbox de 2*2, on baisse la hitbox d'une case pour faire correspondre au sprite
        if(nv_coffre->type == PROFIL_FERME || nv_coffre->type == PROFIL_OUVERT){
            (nv_coffre->collision.y) += TAILLE_CASE;
        }

        ajout_droit(m->liste_collisions, &(nv_coffre->collision));
    }


    for(unsigned int i = 0; i < json_object_array_length(JSON_zones_tp); i++){
        JSON_zone_tp = json_object_array_get_idx(JSON_zones_tp,i);

        /* Récupération des informations de la zone de TP */
        if(!JSON_zone_tp)
            erreur("Impossible de charger la map : %s", ERREUR_FICHIER, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_zone_tp, "x", &JSON_zone_tp_x))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_zone_tp, "y", &JSON_zone_tp_y))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_zone_tp, "w", &JSON_zone_tp_w))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_zone_tp, "h", &JSON_zone_tp_h))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if(!json_object_object_get_ex(JSON_zone_tp, "destination", &JSON_zone_tp_dest))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());
    
        if(!json_object_object_get_ex(JSON_zone_tp, "coords", &JSON_zone_tp_coords))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        JSON_zone_tp_coord_x = json_object_array_get_idx(JSON_zone_tp_coords,0);

        if(!JSON_zone_tp_coord_x)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        JSON_zone_tp_coord_y = json_object_array_get_idx(JSON_zone_tp_coords,1);

        if(!JSON_zone_tp_coord_y)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        /* Création de la zone de TP */
        zone_tp *z = malloc(sizeof(zone_tp));

        if(!z)
            erreur("Impossible de charger la map : %s", OUT_OF_MEM, json_util_get_last_err());

        z->zone.x = json_object_get_int(JSON_zone_tp_x) * m->taille_case;
        z->zone.y = json_object_get_int(JSON_zone_tp_y) * m->taille_case;
        z->zone.w = json_object_get_int(JSON_zone_tp_w) * m->taille_case;
        z->zone.h = json_object_get_int(JSON_zone_tp_h) * m->taille_case;

        z->id_map = json_object_get_int(JSON_zone_tp_dest);

        z->dest.x = json_object_get_int(JSON_zone_tp_coord_x);
        z->dest.y = json_object_get_int(JSON_zone_tp_coord_y);

        ajout_droit(m->liste_zone_tp, z);
    }

    json_object_put(JSON_fichier); //libération mémoire de l'objet json
    return m;
}

t_aff * texture_map(const t_map * map){
    return map->text_sol;
}

void detruire_map(t_map **map){
    
    /* Destruction des monstres */
    detruire_liste(&(*map)->liste_monstres);

    /* Destruction des sorts */
    detruire_liste(&(*map)->liste_sorts);

    /* Destruction des collisions */
    en_tete((*map)->liste_collisions);

    while(!hors_liste((*map)->liste_collisions)){
        SDL_Rect *temp = valeur_elt((*map)->liste_collisions);
        //free(temp);
        suivant((*map)->liste_collisions);
    }

    detruire_liste(&(*map)->liste_collisions);

    /* Destruction des textures */

    selectionner_element(buffer_affichage, (*map)->text_sol, NULL);
    oter_elt(buffer_affichage);

    detruire_texture(&(*map)->text_map);

    /* Libération de la mémoire */
    free(*map);
    *map = NULL;
}

void transition(t_map **actuelle, unsigned int num_map, joueur_t ** joueurs, unsigned short int nb_joueurs, unsigned int new_x, unsigned int new_y){
    char nom_fichier_map[50];

    SDL_SetRenderTarget(rendu_principal, NULL);
    SDL_SetTextureBlendMode(fenetre_finale->texture, SDL_BLENDMODE_BLEND);

    for(unsigned int i = 255; i > 0; i -= 5 ){ /* Fondu (disparition de la map) */
        if (SDL_SetTextureAlphaMod(fenetre_finale->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if(SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(fenetre_finale, rendu_principal) != 0)
            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(10);
    }

    sprintf(nom_fichier_map, "map/%d.json", num_map);
    detruire_map(actuelle);
    detruire_texture(&fenetre_finale);
    *actuelle = charger_map(nom_fichier_map);
    init_sousbuffer(*actuelle, *joueurs);

    /* Mise à jour des textures du joueur */
    for(unsigned short int i = 0; i < nb_joueurs; i++){
        joueur_t *j = joueurs[i];
        
        j->statut->zone_colision.h = (*actuelle)->taille_case;
        j->statut->zone_colision.w = (*actuelle)->taille_case;

        j->statut->vrai_zone_collision.h = (*actuelle)->taille_case;
        j->statut->vrai_zone_collision.w = (*actuelle)->taille_case;

        for(unsigned int y = 0; y < j->textures_joueur->nb_valeurs; y++){
            j->textures_joueur->liste[y]->multipli_taille = (*actuelle)->taille_case / TAILLE_CASE;
            def_texture_taille(j->textures_joueur->liste[i], LONGUEUR_ENTITE * (*actuelle)->taille_case / TAILLE_CASE, LARGEUR_ENTITE * (*actuelle)->taille_case / TAILLE_CASE);
        }
    }

    tp_joueurs(*actuelle, new_x, new_x, joueurs, nb_joueurs);

}

void tp_joueurs(t_map *map, unsigned int x, unsigned int y, joueur_t **joueurs, unsigned short int nb_joueurs){
    
    if(x < 0 || x > map->text_map->width)
        return;

    if (y < 0 || y > map->text_map->height)
        return;

    for(unsigned int i = 0; i < nb_joueurs; i++){
        joueur_t *j = joueurs[i];

        if(i == 0) { /* Joueur principal */
            fenetre_finale->frame_anim->x = 0;
            fenetre_finale->frame_anim->y = 0;
            place_rect_center_from_point(fenetre_finale->frame_anim, get_rect_center_coord(&j->statut->vrai_zone_collision));
            j->statut->vrai_zone_collision.x = x;
            j->statut->vrai_zone_collision.y = y;
            
            if(x < fenetre_finale->frame_anim->w / 2){ /* Extrémité gauche */
                j->statut->zone_colision.x = x;
                fenetre_finale->frame_anim->x = 0;
            }
            else{
                if(x > (map->text_map->width - fenetre_finale->frame_anim->w / 2 )){ /* Extémité droite */
                    j->statut->zone_colision.x = x;
                    fenetre_finale->frame_anim->x = map->text_map->width - fenetre_finale->frame_anim->w;
                }
                else {
                    place_rect_center_from_point(&j->statut->zone_colision, get_rect_center_coord(fenetre_finale->frame_anim));
                }
            }
            
            /* Pour y */
            if(y < fenetre_finale->frame_anim->h / 2){ /* Extrémité haut */
                j->statut->zone_colision.y = y;
                fenetre_finale->frame_anim->y = 0;
            }
            else{
                if(y > (map->text_map->height - fenetre_finale->frame_anim->h / 2 )){ /* Extémité basse */
                    j->statut->zone_colision.y = y;
                    fenetre_finale->frame_anim->y = map->text_map->height - fenetre_finale->frame_anim->h;
                }
                else {
                    place_rect_center_from_point(&j->statut->zone_colision, get_rect_center_coord(fenetre_finale->frame_anim));
                }
            }
        }
        else {
            j->statut->zone_colision.x = x;
            j->statut->zone_colision.y = y;
        }
    }
}


void afficher_zone_tp(zone_tp *z){
    SDL_SetRenderDrawColor(rendu_principal, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(rendu_principal, &z->zone);
    SDL_SetRenderDrawColor(rendu_principal, 0, 0, 0, SDL_ALPHA_OPAQUE);
}