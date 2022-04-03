#include <json-c/json.h>
#include <affichage.h>
#include <map.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <code_erreur.h>
#include <monstres.h>
#include <math.h>
#include <fonctions.h>

/**
 * \file map.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fonctions de gestion de la map
 * \version 0.1
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

t_map *map;

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

    json_object *JSON_objet_monstre =  NULL; 
    json_object *JSON_nom_monstre =    NULL;   
    json_object *JSON_position =       NULL;
    json_object *JSON_x =              NULL;
    json_object *JSON_y =              NULL; 

    monstre_t * inserer =              NULL;

    json_object *JSON_tbl_wall =       NULL;
    json_object *JSON_object_wall =    NULL;
    json_object *JSON_wall_x =         NULL;
    json_object *JSON_wall_y =         NULL;
    json_object *JSON_wall_h =         NULL;
    json_object *JSON_wall_w =         NULL;

    /* Allocation de la mémoire pour la map */
    m = malloc(sizeof(t_map));

    if(!m)
        erreur("Impossible de charger la map : Plus de mémoire", OUT_OF_MEM);

    /* Initialisation des listes */
    m->liste_monstres =  init_liste(NULL,NULL,NULL);

    if(!m->liste_monstres)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_sorts = init_liste(NULL,NULL,NULL);

    if(!m->liste_sorts)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_collisions = init_liste(NULL, NULL, NULL);

    if(!m->liste_collisions)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    /* Récupération des informations dans le fichier */
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

    /* Récupération des informations */
    m->id_map = json_object_get_int(JSON_id_map);
    m->text_sol = creer_texture(json_object_get_string(JSON_texture_map), -1, -1, 0, 0, 1);
    m->height = json_object_get_int(JSON_height);
    m->width = json_object_get_int(JSON_width);
    m->taille_case = json_object_get_int(JSON_taille_case);

    if(!m->text_sol)
        erreur("Impossible de charger la map : %s", ERREUR_TEXTURE, SDL_GetError());

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
        ajout_droit(m->liste_monstres, inserer);
        en_queue(m->liste_collisions);
        ajout_droit(m->liste_collisions, &(inserer->collision));
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
        free(valeur_elt((*map)->liste_collisions));
        suivant((*map)->liste_collisions);
    }

    detruire_liste((*map)->liste_collisions);

    /* Destruction des textures */

    selectionner_element((*map)->liste_collisions, (*map)->text_sol, NULL);
    oter_elt((*map)->liste_collisions);

    detruire_texture(&(*map)->text_map);

    /* Libération de la mémoire */
    free(*map);
    *map = NULL;
}

void transition(t_map **actuelle, const char * const nom_map, joueur_t ** joueurs, unsigned short int nb_joueurs){

    detruire_map(actuelle);
    detruire_texture(&fenetre_finale);
    *actuelle = charger_map(nom_map);

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
}

void tp_joueurs(t_map *map, unsigned int x, unsigned int y, joueur_t **joueurs, unsigned short int nb_joueurs){
    
    if(x < 0 || x > map->text_map->width)
        return;

    if (y < 0 || y > map->text_map->height)
        return;

    for(unsigned int i = 0; i < nb_joueurs; i++){
        joueur_t *j = joueurs[i];

        if(i == 0) { /* Joueur principal */
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
                    /* Centrer à l'écran */
                }
            }
            
            /* Pour y */
            if(y < fenetre_finale->frame_anim->h / 2){ /* Extrémité gauche */
                j->statut->zone_colision.y = y;
                fenetre_finale->frame_anim->y = 0;
            }
            else{
                if(y > (map->text_map->height - fenetre_finale->frame_anim->h / 2 )){ /* Extémité droite */
                    j->statut->zone_colision.y = y;
                    fenetre_finale->frame_anim->y = map->text_map->height - fenetre_finale->frame_anim->h;
                }
                else {
                    /* Centrer à l'écran */
                }
            }
        }
        else {
            j->statut->zone_colision.x = x;
            j->statut->zone_colision.y = y;
        }
    }
}
