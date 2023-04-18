#include <json-c/json.h>
#include <affichage.hpp>
#include <map.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <code_erreur.hpp>
#include <monstres.hpp>
#include <math.h>
#include <coffres.hpp>
#include <personnage.hpp>
#include <sorts.hpp>
#include <macros.hpp>
#include <utils.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <vector>

/**
 * \file map.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fonctions de gestion de la map
 * \version 0.1
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

t_map* map = NULL;

void init_sousbuffer(t_map* map, joueur_t* joueur) {

    SDL_Texture* sous_buffer = SDL_CreateTexture(rendu_principal, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, floor(map->text_sol->width * map->text_sol->multipli_taille), floor(map->text_sol->height * map->text_sol->multipli_taille));
    if (!sous_buffer)
        erreur("Erreur lors de la création de la texture de sous-buffer : %s", SDL_ERREUR, SDL_GetError());
    /* On alloue le second  buffer */
    map->text_map = (t_aff*) malloc(sizeof(t_aff));

    if (!map->text_map)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    map->text_map->aff_fenetre = (SDL_Rect*) malloc(sizeof(SDL_Rect));

    if (!map->text_map->aff_fenetre)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    map->text_map->frame_anim = (SDL_Rect*) malloc(sizeof(SDL_Rect));

    if (!map->text_map->frame_anim)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    /* On alloue le troisième  buffer */
    fenetre_finale = (t_aff*) malloc(sizeof(t_aff));

    if (!fenetre_finale)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->texture = SDL_CreateTexture(rendu_principal, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, floor(map->text_sol->width * map->text_sol->multipli_taille), floor(map->text_sol->height * map->text_sol->multipli_taille));

    if (!fenetre_finale->texture)
        erreur("Erreur lors de la créations des buffers : %s", SDL_ERREUR, SDL_GetError());

    fenetre_finale->aff_fenetre = (SDL_Rect*) malloc(sizeof(SDL_Rect));

    if (!fenetre_finale->aff_fenetre)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->frame_anim = (SDL_Rect*) malloc(sizeof(SDL_Rect));

    if (!fenetre_finale->frame_anim)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->frame_anim->x = 0;
    fenetre_finale->frame_anim->y = 0;
    fenetre_finale->frame_anim->w = floor(FENETRE_LONGUEUR / (float) floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    fenetre_finale->frame_anim->h = floor(FENETRE_LARGEUR / (float) floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    fenetre_finale->aff_fenetre->x = 0;
    fenetre_finale->aff_fenetre->y = 0;
    fenetre_finale->aff_fenetre->w = FENETRE_LONGUEUR;
    fenetre_finale->aff_fenetre->h = FENETRE_LARGEUR;

    map->text_map->texture = sous_buffer;

    /* On définit la partie de la map que l'on voie à l'écran */
    map->text_map->aff_fenetre->w = floor(FENETRE_LONGUEUR / (float) floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    map->text_map->aff_fenetre->h = floor(FENETRE_LARGEUR / (float) floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    map->text_map->aff_fenetre->x = 0;
    map->text_map->aff_fenetre->y = 0;

    /* On place la partie de la map que l'on voit */
    map->text_map->frame_anim->w = floor(FENETRE_LONGUEUR / (float) floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    map->text_map->frame_anim->h = floor(FENETRE_LARGEUR / (float) floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    if (map->texture_superposition) {
        map->texture_superposition->frame_anim = map->text_map->frame_anim;
        map->texture_superposition->aff_fenetre->w = map->text_map->aff_fenetre->w;
        map->texture_superposition->aff_fenetre->h = map->text_map->aff_fenetre->h;
    }

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

SDL_Rect taille_ecran_cases() {
    SDL_Rect p;

    int taille_case = TAILLE_CASE * 6;

    p.w = FENETRE_LONGUEUR / taille_case;
    p.h = FENETRE_LARGEUR / taille_case;
    p.x = 0;
    p.y = 0;

    return p;
}

t_map* charger_map(const char* const nom_map) {
    t_map* m = NULL;
    void* filePath = NULL;

    json_object* JSON_fichier = NULL;
    json_object* JSON_id_map = NULL;
    json_object* JSON_texture_map = NULL;
    json_object* JSON_text_superpos = NULL;
    json_object* JSON_width = NULL;
    json_object* JSON_height = NULL;
    json_object* JSON_taille_case = NULL;
    json_object* JSON_tbl_monstre = NULL;
    json_object* JSON_tbl_coffre = NULL;

    json_object* JSON_objet_monstre = NULL;
    json_object* objet_json = NULL;
    json_object* JSON_nom_monstre = NULL;
    json_object* JSON_position = NULL;
    json_object* JSON_position2 = NULL;
    json_object* JSON_x = NULL;
    json_object* JSON_y = NULL;
    json_object* x2 = NULL;
    json_object* y2 = NULL;
    json_object* nom_coffre = NULL;
    json_object* id_cle = NULL;
    json_object* id_loot = NULL;

    monstre_t* inserer = NULL;
    coffre_t* nv_coffre = NULL;

    json_object* JSON_tbl_wall = NULL;
    json_object* JSON_object_wall = NULL;
    json_object* JSON_wall_x = NULL;
    json_object* JSON_wall_y = NULL;
    json_object* JSON_wall_h = NULL;
    json_object* JSON_wall_w = NULL;

    json_object* JSON_zones_tp = NULL;
    json_object* JSON_zone_tp = NULL;
    json_object* JSON_zone_tp_x = NULL;
    json_object* JSON_zone_tp_y = NULL;
    json_object* JSON_zone_tp_h = NULL;
    json_object* JSON_zone_tp_w = NULL;
    json_object* JSON_zone_tp_dest = NULL;
    json_object* JSON_zone_tp_coords = NULL;
    json_object* JSON_zone_tp_coord_x = NULL;
    json_object* JSON_zone_tp_coord_y = NULL;

    log_info("Chargement de la map...")

        log_debug("Chargement du chemin d'accès au fichier de la map '%s'", nom_map);

    callocate(filePath, sizeof(char), strlen(nom_map) + strlen(execDir) + 1);

    strcat(strcat((char*) filePath, execDir), nom_map);

    log_debug("Ouverture du fichier : '%s'", filePath);

    JSON_fichier = json_object_from_file((char*) filePath);

    log_debug("Fichier map chargé avec succès !");

    free(filePath);

    /* Allocation de la mémoire pour la map */
    m = (t_map*) malloc(sizeof(t_map));

    if (!m)
        erreur("Impossible de charger la map : Plus de mémoire", OUT_OF_MEM);

    /* Initialisation des listes */
    m->liste_monstres = init_liste(ajouter_monstre_cb, detruire_monstre_cb, NULL);

    if (!m->liste_monstres)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_coffres = init_liste(NULL, NULL, NULL);

    if (!m->liste_coffres)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_sorts = init_liste(ajouter_sort_cb, detruire_sort_cb, NULL);

    if (!m->liste_sorts)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_collisions = init_liste(NULL, NULL, NULL);

    if (!m->liste_collisions)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    m->liste_zone_tp = init_liste(NULL, NULL, NULL);

    if (!m->liste_zone_tp)
        erreur("Impossible de charger la map", ERREUR_LISTE);

    log_debug("Récupération des données de la map");

    /* Récupération des informations dans le fichier */
    if (!json_object_object_get_ex(JSON_fichier, "chest", &JSON_tbl_coffre))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "id", &JSON_id_map))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "file-path", &JSON_texture_map))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "width", &JSON_width))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "height", &JSON_height))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "taille case", &JSON_taille_case))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "monsters", &JSON_tbl_monstre))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "wall", &JSON_tbl_wall))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "zones tp", &JSON_zones_tp))
        erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

    if (!json_object_object_get_ex(JSON_fichier, "superposition", &JSON_text_superpos)) {
        m->texture_superposition = NULL;
    }
    else {
        m->texture_superposition = creer_texture(json_object_get_string(JSON_text_superpos), -1, -1, 0, 0, 1);
    }

    /* Récupération des informations */
    m->id_map = json_object_get_int(JSON_id_map);
    m->text_sol = creer_texture(json_object_get_string(JSON_texture_map), -1, -1, 0, 0, 1);
    m->height = json_object_get_int(JSON_height);
    m->width = json_object_get_int(JSON_width);
    m->taille_case = json_object_get_int(JSON_taille_case);

    log_debug("Informations sur la map :");

    log_debug("\tmap.id : %d", m->id_map);
    log_debug("\tmap.texture_sol : %s", json_object_get_string(JSON_texture_map));
    log_debug("\tmap.taille_cases : %dpx", m->taille_case);

    if (!m->text_sol)
        erreur("Impossible de charger la map : %s", ERREUR_TEXTURE, SDL_GetError());

    // Génération des collisions de la carte
    for (unsigned int i = 0; i < json_object_array_length(JSON_tbl_wall); i++) {
        JSON_object_wall = json_object_array_get_idx(JSON_tbl_wall, i);

        if (!JSON_object_wall)
            erreur("Impossible de charger la map : %s", ERREUR_FICHIER, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_object_wall, "x", &JSON_wall_x))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_object_wall, "y", &JSON_wall_y))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_object_wall, "h", &JSON_wall_h))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_object_wall, "w", &JSON_wall_w))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        SDL_Rect* valeur = (SDL_Rect*) malloc(sizeof(SDL_Rect));

        if (!valeur)
            erreur("Impossible de charger la map", OUT_OF_MEM);

        valeur->x = json_object_get_int(JSON_wall_x) * m->taille_case;
        valeur->y = json_object_get_int(JSON_wall_y) * m->taille_case;
        valeur->h = json_object_get_int(JSON_wall_h) * m->taille_case;
        valeur->w = json_object_get_int(JSON_wall_w) * m->taille_case;

        log_debug("Ajout d'une zone de collision :: numero : %-3d / x : %-4d / y : %-4d / w : %-4d / h : %-4d / adresse : %p", m->liste_collisions->nb_elem + 1, valeur->x, valeur->y, valeur->w, valeur->h, valeur);

        ajout_droit(m->liste_collisions, valeur);
    }

    // Génération des monstres
    for (unsigned int i = 0; i < json_object_array_length(JSON_tbl_monstre); i++) {
        JSON_objet_monstre = json_object_array_get_idx(JSON_tbl_monstre, i);

        if (!JSON_objet_monstre)
            erreur("Impossible de charger la map : %s", ERREUR_FICHIER, json_util_get_last_err())

            if (!json_object_object_get_ex(JSON_objet_monstre, "type", &JSON_nom_monstre))
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_objet_monstre, "position", &JSON_position))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        JSON_x = json_object_array_get_idx(JSON_position, 0);
        JSON_y = json_object_array_get_idx(JSON_position, 1);

        if (!JSON_x)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!JSON_y)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        inserer = creer_monstre(liste_base_monstres, json_object_get_string(JSON_nom_monstre), json_object_get_int(JSON_x), json_object_get_int(JSON_y), m);

        if (!inserer)
            erreur("Erreur lors de la création du monstre : le monstre \"%s\" n'existe pas !", ERREUR_MAP, json_object_get_string(JSON_nom_monstre));

        ajout_droit(m->liste_monstres, inserer);
        en_queue(m->liste_collisions);
        ajout_droit(m->liste_collisions, &(inserer->collision));
    }

    // Génération des coffres
    for (unsigned int i = 0; i < json_object_array_length(JSON_tbl_coffre); i++) {
        objet_json = json_object_array_get_idx(JSON_tbl_coffre, i);

        nom_coffre = json_object_object_get(objet_json, "type");
        id_cle = json_object_object_get(objet_json, "id_cle");
        id_loot = json_object_object_get(objet_json, "id_loot");
        JSON_position2 = json_object_object_get(objet_json, "position");

        x2 = json_object_array_get_idx(JSON_position2, 0);
        y2 = json_object_array_get_idx(JSON_position2, 1);

        nv_coffre = creer_coffre(json_object_get_int(id_cle), json_object_get_int(id_loot), liste_base_coffres, json_object_get_string(nom_coffre), json_object_get_int(x2) * m->taille_case, json_object_get_int(y2) * m->taille_case, m);
        ajout_droit(m->liste_coffres, nv_coffre);
        en_queue(m->liste_collisions);

        // sprite des coffres de profile de 2*3 mais hitbox de 2*2, on baisse la hitbox d'une case pour faire correspondre au sprite
        if (nv_coffre->type == PROFIL_FERME || nv_coffre->type == PROFIL_OUVERT) {
            (nv_coffre->collision.y) += TAILLE_CASE;
        }

        ajout_droit(m->liste_collisions, &(nv_coffre->collision));
    }

    for (unsigned int i = 0; i < json_object_array_length(JSON_zones_tp); i++) {
        JSON_zone_tp = json_object_array_get_idx(JSON_zones_tp, i);

        /* Récupération des informations de la zone de TP */
        if (!JSON_zone_tp)
            erreur("Impossible de charger la map : %s", ERREUR_FICHIER, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_zone_tp, "x", &JSON_zone_tp_x))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_zone_tp, "y", &JSON_zone_tp_y))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_zone_tp, "w", &JSON_zone_tp_w))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_zone_tp, "h", &JSON_zone_tp_h))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_zone_tp, "destination", &JSON_zone_tp_dest))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        if (!json_object_object_get_ex(JSON_zone_tp, "coords", &JSON_zone_tp_coords))
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        JSON_zone_tp_coord_x = json_object_array_get_idx(JSON_zone_tp_coords, 0);

        if (!JSON_zone_tp_coord_x)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        JSON_zone_tp_coord_y = json_object_array_get_idx(JSON_zone_tp_coords, 1);

        if (!JSON_zone_tp_coord_y)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

        /* Création de la zone de TP */
        zone_tp* z = (zone_tp*) malloc(sizeof(zone_tp));

        if (!z)
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

    json_object_put(JSON_fichier); // libération mémoire de l'objet json
    return m;
}

t_aff* texture_map(const t_map* map) {
    return map->text_sol;
}

void detruire_map(t_map** map, joueur_t* joueurs[], unsigned short int nb_joueurs) {

    /* Destruction des collisions */
    en_tete((*map)->liste_collisions);

    while (!hors_liste((*map)->liste_collisions)) {
        SDL_Rect* temp = (SDL_Rect*) valeur_elt((*map)->liste_collisions); /* On parcourt la liste des collisions de la map */

        for (unsigned short int i = 0; i < nb_joueurs; i++) /* On vérifie que ce n'est pas une collision de joueur */
        {
            if (i == 0) {                                                         /* Joueur 1 */
                if (temp == &joueurs[0]->statut->vrai_zone_collision) /* On évite la collision du joueur (variable statique) */
                    goto next_collision;                              /* On passe à la collision suivante */
            }
            else {                                                   /* Les autres joueurs */
                if (temp == &joueurs[i]->statut->zone_colision) /* On évite la collision du joueur (variable statique) */
                    goto next_collision;                        /* On passe à la collision suivante */
            }
        }

        en_tete((*map)->liste_monstres); /* On vérifie que la coliision n'est pas celle d'un monstre */

        while (!hors_liste((*map)->liste_monstres)) {
            monstre_t* monstre_temp = (monstre_t*) valeur_elt((*map)->liste_monstres);
            if (temp == &monstre_temp->collision)
                goto next_collision; /* On passe à la collision suivante */

            suivant((*map)->liste_monstres);
        }

        en_tete((*map)->liste_sorts); /* On vérifie que la coliision n'est pas celle d'un sort */

        while (!hors_liste((*map)->liste_sorts)) {
            sort_t* sort_temp = (sort_t*) valeur_elt((*map)->liste_sorts);
            if (temp == &sort_temp->collision)
                goto next_collision; /* On passe à la collision suivante */
            suivant((*map)->liste_sorts);
        }

        en_tete((*map)->liste_coffres); /* On vérifie que la coliision n'est pas celle d'un coffre */

        while (!hors_liste((*map)->liste_coffres)) {
            coffre_t* coffre_temp = (coffre_t*) valeur_elt((*map)->liste_coffres);
            if (temp == &coffre_temp->collision)
                goto next_collision; /* On passe à la collision suivante */
            suivant((*map)->liste_coffres);
        }

        free(temp); /* On libère la mémoire allouée */
    next_collision:
        suivant((*map)->liste_collisions); /* On passe à la collision suivante */
    }

    /* Enfin, on dédruit la liste */
    detruire_liste(&(*map)->liste_collisions);

    /* Destruction des monstres */
    detruire_liste(&(*map)->liste_monstres);

    /* Destruction des sorts */
    detruire_liste(&(*map)->liste_sorts);

    /* Destruction des textures */

    selectionner_element(listeDeTextures, (*map)->text_sol, NULL);
    oter_elt(listeDeTextures);

    detruire_texture(&(*map)->text_map);

    (*map)->texture_superposition->frame_anim = NULL;
    selectionner_element(listeDeTextures, (*map)->texture_superposition, NULL);
    oter_elt(listeDeTextures);

    /* Libération de la mémoire */
    free(*map);
    *map = NULL;
}

void transition(t_map** actuelle, unsigned int num_map, joueur_t** joueurs, unsigned short int nb_joueurs, unsigned int new_x, unsigned int new_y) {
    char nom_fichier_map[50];

    SDL_SetRenderTarget(rendu_principal, NULL);
    SDL_SetTextureBlendMode(fenetre_finale->texture, SDL_BLENDMODE_BLEND);

    for (unsigned int i = 255; i > 0; i -= 5) { /* Fondu (disparition de la map) */
        if (SDL_SetTextureAlphaMod(fenetre_finale->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if (SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(fenetre_finale, rendu_principal) != 0)
            fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(10);
    }

    sprintf(nom_fichier_map, "map/%d.json", num_map);
    detruire_map(actuelle, joueurs, nb_joueurs);
    detruire_texture(&fenetre_finale);
    *actuelle = charger_map(nom_fichier_map);
    init_sousbuffer(*actuelle, *joueurs);

    /* Mise à jour des textures du joueur */
    for (unsigned short int i = 0; i < nb_joueurs; i++) {
        joueur_t* j = joueurs[i];

        j->statut->zone_colision.h = (*actuelle)->taille_case;
        j->statut->zone_colision.w = (*actuelle)->taille_case;

        j->statut->vrai_zone_collision.h = (*actuelle)->taille_case;
        j->statut->vrai_zone_collision.w = (*actuelle)->taille_case;

        for (unsigned int y = 0; y < j->textures_joueur->nb_valeurs; y++) {
            j->textures_joueur->liste[y]->multipli_taille = (*actuelle)->taille_case / TAILLE_CASE;
            def_texture_taille(j->textures_joueur->liste[i], LONGUEUR_ENTITE * (*actuelle)->taille_case / TAILLE_CASE, LARGEUR_ENTITE * (*actuelle)->taille_case / TAILLE_CASE);
        }
    }

    tp_joueurs(*actuelle, new_x, new_y, joueurs, nb_joueurs);
}

void tp_joueurs(t_map* map, unsigned int x, unsigned int y, joueur_t** joueurs, unsigned short int nb_joueurs) {

    if (x < 0 || x > map->text_map->width)
        return;

    if (y < 0 || y > map->text_map->height)
        return;

    for (unsigned int i = 0; i < nb_joueurs; i++) {
        joueur_t* j = joueurs[i];

        if (i == 0) { /* Joueur principal */
            map->text_map->frame_anim->x = x;
            map->text_map->frame_anim->y = y;
            j->statut->vrai_zone_collision.x = x;
            j->statut->vrai_zone_collision.y = y;
            place_rect_center_from_point(map->text_map->frame_anim, get_rect_center_coord(&j->statut->vrai_zone_collision));

            if (x < map->text_map->frame_anim->w / 2) { /* Extrémité gauche */
                j->statut->zone_colision.x = x;
                map->text_map->frame_anim->x = 0;
            }
            else {
                if (x > (map->text_map->width - map->text_map->frame_anim->w / 2)) { /* Extémité droite */
                    map->text_map->frame_anim->x = map->text_map->width - map->text_map->frame_anim->w;
                    j->statut->zone_colision.x = x - map->text_map->frame_anim->x;
                }
                else {
                    place_rect_center_from_point(&j->statut->zone_colision, get_rect_center(map->text_map->frame_anim));
                }
            }

            /* Pour y */
            if (y < map->text_map->frame_anim->h / 2) { /* Extrémité haut */
                j->statut->zone_colision.y = y;
                map->text_map->frame_anim->y = 0;
            }
            else {
                if (y > (map->text_map->height - map->text_map->frame_anim->h / 2)) { /* Extémité basse */
                    map->text_map->frame_anim->y = map->text_map->height - map->text_map->frame_anim->h;
                    j->statut->zone_colision.y = y - map->text_map->frame_anim->y;
                }
                else {
                    int x_temp = map->text_map->frame_anim->x;
                    int x_temp_bis = j->statut->zone_colision.x;
                    place_rect_center_from_point(&j->statut->zone_colision, get_rect_center(map->text_map->frame_anim));
                    place_rect_center_from_point(map->text_map->frame_anim, get_rect_center_coord(&j->statut->vrai_zone_collision));
                    map->text_map->frame_anim->x = x_temp;
                    j->statut->zone_colision.x = x_temp_bis;
                }
            }
        }
        else {
            j->statut->zone_colision.x = x;
            j->statut->zone_colision.y = y;
        }
    }
}

void afficher_zone_tp(zone_tp* z) {
    SDL_SetRenderDrawColor(rendu_principal, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(rendu_principal, &z->zone);
    SDL_SetRenderDrawColor(rendu_principal, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

/**
 * \fn bool hors_map_monstre(SDL_Rect * collision, t_map * map);
 * \brief Fonction qui regarde si l'entité est hors_map
 * \author Bruneau Antoine
 * \param collision la collision de l'entité
 * \param map la map
 * \return bool 1 si l'entité est en dehors de la map, 0 sinon
 */
bool hors_map_monstre(SDL_Rect* collision, t_map* map) {
    // test gauche
    if (collision->x <= 0)
        return 1;
    // test haut
    if (collision->y <= 0)
        return 1;
    // test droit
    if (collision->w + collision->x >= map->text_map->width)
        return 1;
    // test bas
    if (collision->h + collision->y >= map->text_map->height)
        return 1;
    return 0;
}

class Map {

    unsigned int id_map;          /**< L'identificateur de la map */
    t_aff* text_map;              /**< La texture de la map */
    t_aff* text_sol;              /**< La texture du sol */
    t_aff* texture_superposition; /**<La texture à supperposer devant le personnage */
    unsigned int width;           /**<La longueur de la map */
    unsigned int height;          /**<la hauteur de la map */
    unsigned int taille_case;     /**< La taille d'une case */
    unsigned int cases_x;         /**< Le nombre de cases affichées en x */
    unsigned int cases_y;         /**< Le nombre de cases affichées en y */
    std::vector<monstre_t>* liste_monstres;          /**< La liste des monstres de la map */
    std::vector<sort_t>* liste_sorts;                /**< La liste des sorts de la map */
    std::vector<SDL_Rect>* liste_collisions;         /**< La liste de toutes les les collisions */
    std::vector<coffre_t>* liste_coffres;            /**< La liste de tous les coffres */
    std::vector<zone_tp>* liste_zone_tp;             /**<La liste des points de téléportation */

public:
    Map(std::string nomFichierMap) {
        log_info("Chargement de la map...")

        log_debug("Chargement du chemin d'accès au fichier de la map '%s'", nomFichierMap.c_str());

        nomFichierMap = execDir + nomFichierMap;

        log_debug("Ouverture du fichier : '%s'", nomFichierMap.c_str());

        std::ifstream fichierMap(nomFichierMap);

        log_debug("Fichier map chargé avec succès !");

        log_debug("Parsing JSON");

        // Variables JSON
        Json::Reader reader;
        Json::Value root;

        reader.parse(fichierMap, root);

        log_debug("Parsing DONE");

        /* Initialisation des listes */
        try {
            liste_monstres = new std::vector<monstre_t>();
        }
        catch (std::exception error) {
            erreur("Impossible de charger la map", ERREUR_LISTE, error.what());
        }

        try {
            liste_coffres = new std::vector<coffre_t>();
        }
        catch (std::exception error) {
            erreur("Impossible de charger la map", ERREUR_LISTE, error.what());
        }

        try {
            liste_sorts = new std::vector<sort_t>();
        }
        catch (std::exception error) {
            erreur("Impossible de charger la map", ERREUR_LISTE, error.what());
        }

        try {
            liste_collisions = new std::vector<SDL_Rect>();
        }
        catch (std::exception error) {
            erreur("Impossible de charger la map", ERREUR_LISTE, error.what());
        }

        try {
            liste_zone_tp = new std::vector<zone_tp>();
        }
        catch (std::exception error) {
            erreur("Impossible de charger la map", ERREUR_LISTE, error.what());
        }

        log_debug("Récupération des données de la map");

        // Variables JSON
        Json::Value chests = root.get("chest", NULL);
        if (chests == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value id = root.get("id", NULL);
        if (id == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value file_path = root.get("file-path", NULL);
        if (file_path == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value width = root.get("width", NULL);
        if (width == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value height = root.get("height", NULL);
        if (height == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value tileSize = root.get("taille_case", NULL);
        if (tileSize)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value monsters = root.get("monsters", NULL);
        if (monsters == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value walls = root.get("wall", NULL);
        if (walls == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value tpZones = root.get("zones tp", NULL);
        if(tpZones == NULL)
            erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE);

        Json::Value superpositionLayer = root.get("superposition", NULL);
        texture_superposition = superpositionLayer != NULL ? texture_superposition = creer_texture(superpositionLayer.asCString(), -1, -1, 0, 0, 1) : NULL;

        /* Récupération des informations */
        id_map = id.asInt();
        text_sol = creer_texture(file_path.asCString(), -1, -1, 0, 0, 1);
        height = height.asInt();
        width = width.asInt();
        taille_case = tileSize.asInt();

        log_debug("Informations sur la map :");

        log_debug("\tmap.id : %d", id_map);
        log_debug("\tmap.texture_sol : %s", file_path.asCString());
        log_debug("\tmap.taille_cases : %dpx", taille_case);

        if (!text_sol)
            erreur("Impossible de charger la map : %s", ERREUR_TEXTURE, SDL_GetError());

        // Génération des collisions de la carte
        for (auto wall : walls) {
            // On récupère les attributs du mur

            SDL_Rect collision = {
                .x = wall["x"].asInt(),
                .y = wall["y"].asInt(),
                .w = wall["w"].asInt(),
                .h = wall["h"].asInt(),
            };

            log_debug("Ajout d'une zone de collision :: numero : %-3d / x : %-4d / y : %-4d / w : %-4d / h : %-4d", liste_collisions->size() + 1, collision.x, collision.y, collision.w, collision.h);

            liste_collisions->push_back(collision);
        }

        // Génération des monstres
        for(auto monster : monsters){
            Json::Value monsterType = monster["type"];
            Json::Value position = monster["position"];
            Json::Value x = position[0];
            Json::Value y = position[1];


            monstre_t *inserer = creer_monstre(liste_base_monstres, monsterType.asCString(), x.asInt(), y.asInt(), *this);

            liste_monstres->push_back(*inserer);
            liste_collisions->push_back(inserer->collision);

            free(inserer);
        }

        // Génération des coffres
        for(auto chest : chests){
            Json::Value chestType = chest["type"];
            Json::Value keyId = chest["id_cle"];
            Json::Value lootId = chest["id_loot"];
            Json::Value chestPosition = chest["position"];

            Json::Value chestX = chestPosition[0];
            Json::Value chestY = chestPosition[1];

            coffre_t *nv_coffre = creer_coffre(keyId.asInt(), lootId.asInt(), liste_base_coffres, chestType.asCString(), chestX.asInt() * taille_case, chestY.asInt() * taille_case, *this);

            // sprite des coffres de profile de 2*3 mais hitbox de 2*2, on baisse la hitbox d'une case pour faire correspondre au sprite
            if (nv_coffre->type == PROFIL_FERME || nv_coffre->type == PROFIL_OUVERT) {
                (nv_coffre->collision.y) += TAILLE_CASE;
            }

            liste_coffres->push_back(*nv_coffre);
            liste_collisions->push_back(nv_coffre->collision);

            free(nv_coffre);
        }

        for(auto tpZone : tpZones){

            /* Récupération des informations de la zone de TP */
            Json::Value x = tpZone["x"];
            

            if (!json_object_object_get_ex(JSON_zone_tp, "x", &JSON_zone_tp_x))
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            if (!json_object_object_get_ex(JSON_zone_tp, "y", &JSON_zone_tp_y))
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            if (!json_object_object_get_ex(JSON_zone_tp, "w", &JSON_zone_tp_w))
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            if (!json_object_object_get_ex(JSON_zone_tp, "h", &JSON_zone_tp_h))
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            if (!json_object_object_get_ex(JSON_zone_tp, "destination", &JSON_zone_tp_dest))
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            if (!json_object_object_get_ex(JSON_zone_tp, "coords", &JSON_zone_tp_coords))
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            JSON_zone_tp_coord_x = json_object_array_get_idx(JSON_zone_tp_coords, 0);

            if (!JSON_zone_tp_coord_x)
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            JSON_zone_tp_coord_y = json_object_array_get_idx(JSON_zone_tp_coords, 1);

            if (!JSON_zone_tp_coord_y)
                erreur("Impossible de charger la map : %s", ERREUR_JSON_CLE_NON_TROUVEE, json_util_get_last_err());

            /* Création de la zone de TP */
            zone_tp* z = (zone_tp*) malloc(sizeof(zone_tp));

            if (!z)
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

        json_object_put(JSON_fichier); // libération mémoire de l'objet json
    };
}
