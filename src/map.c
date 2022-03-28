#include <json-c/json.h>
#include <affichage.h>
#include <map.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <code_erreur.h>
#include <monstres.h>
#include <math.h>

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

char * charger_f_map(const char * const nom_map){
    FILE * fp;
    char *file_buffer;
    unsigned long taille_fichier;

    fp = fopen(nom_map,"r");
    if(! fp){
        fprintf(stderr, "Erreur : impossible de charge la map, fichier \"%s\" introuvable !\n", nom_map);
        fermer_programme(EXIT_FAILURE);
    }

    fseek(fp, (long)0, SEEK_END); /* On parcourt le fichier afin de connaitre sa taille */
    taille_fichier = ftell(fp) + 1;

    file_buffer = calloc((taille_fichier) + 1, sizeof(char)); /* On alloue d'ynamiquement en fonction de la taille du fichier */
    if(!file_buffer){
        fprintf(stderr, "Erreur : plus de mémoire disponible !\n");
        fermer_programme(OUT_OF_MEM);
    }

    rewind(fp); /* On revient au début du fichier */

    fread(file_buffer, 1, taille_fichier, fp); /* On lit le fichier */
    fclose(fp); /* On a plus besoin du fichier */

    file_buffer[taille_fichier] = '\0';

    return file_buffer;
}

t_map * charger_s_map(char * buffer){
    t_map *m;
    json_object *fichier;
    json_object *texture_map;
    json_object *width;
    json_object *height;
    json_object *tbl_monstre;

    json_object *monstre; 
    json_object *taille_case;

    json_object *nom_monstre;
    json_object *position;
    json_object *x;
    json_object *y;
  
    monstre_t * inserer;

    SDL_Rect s = taille_ecran_cases();

    fichier = json_tokener_parse(buffer);
    m = malloc(sizeof(t_map));
    m->liste_monstres =  init_liste(NULL,detruire_monstre,NULL);

    json_object_object_get_ex(fichier, "file-path", &texture_map);
    json_object_object_get_ex(fichier, "width", &width);
    json_object_object_get_ex(fichier, "height", &height);
    json_object_object_get_ex(fichier, "monsters", &tbl_monstre);
    json_object_object_get_ex(fichier, "taille case", &taille_case);

    int taille_case_val = json_object_get_int(taille_case);

    m->text_sol = creer_texture(json_object_get_string(texture_map),
                                -1, -1, 0, 0, 1);
    m->height = json_object_get_int(height);
    m->width = json_object_get_int(width);

    for(unsigned int i = 0; i < json_object_array_length(tbl_monstre); i++){
        monstre = json_object_array_get_idx(tbl_monstre,i);

        nom_monstre = json_object_object_get(monstre,"type");
        position = json_object_object_get(monstre,"position");

        x = json_object_array_get_idx(position,0);
        y = json_object_array_get_idx(position,1);

        inserer = creer_monstre(liste_base_monstres, json_object_get_string(nom_monstre), json_object_get_int(x), json_object_get_int(y));
        ajout_droit(m->liste_monstres, inserer);
    }

    m->unite_dep_x = floor(FENETRE_LONGUEUR / (float)m->text_sol->width); /* Calcul en nombre de pixels d'une unité de déplacement */
    m->unite_dep_y = floor(FENETRE_LARGEUR / (float)m->text_sol->height); /* Calcul en nombre de pixels d'une unité de déplacement */

    free(buffer);
    json_object_put(fichier); //libération mémoire de l'objet json
    return m;
}

t_aff * texture_map(const t_map * map){
    return map->text_sol;
}