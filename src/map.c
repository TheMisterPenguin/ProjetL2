#include <json-c/json.h>
#include <affichage.h>
#include <map.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <code_erreur.h>
#include <math.h>

bool bord_map(t_direction orientation){
    
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

char * charger_f_map(const char * const nom_map){
    FILE * fp;
    char *file_buffer;
    unsigned long taille_fichier;

    fp = fopen(nom_map,"r");
    if(! fp){
        fprintf(stderr, "Erreur : impossible de charge la map, fichier \"%s\" introuvable !\n", nom_map);
        exit(EXIT_FAILURE);
    }

    fseek(fp, (long)0, SEEK_END); /* On parcourt le fichier afin de connaitre sa taille */
    taille_fichier = ftell(fp) + 1;

    file_buffer = calloc((taille_fichier) + 1, sizeof(char)); /* On alloue d'ynamiquement en fonction de la taille du fichier */
    if(!file_buffer){
        fprintf(stderr, "Erreur : plus de mémoire disponible !\n");
        exit(OUT_OF_MEM);
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

    SDL_Rect s = taille_ecran_cases();

    fichier = json_tokener_parse(buffer);
    m = malloc(sizeof(t_map));
    m->liste_monstres =  init_liste(NULL,NULL,NULL);

    json_object_object_get_ex(fichier, "file-path", &texture_map);
    json_object_object_get_ex(fichier, "width", &width);
    json_object_object_get_ex(fichier, "height", &height);
    json_object_object_get_ex(fichier, "monsters", &tbl_monstre);

    m->text_map = creer_texture(json_object_get_string(texture_map),
                                s.w * 16, s.h * 16, 0, 0, 0);
    m->height = json_object_get_int(height);
    m->width = json_object_get_int(width);

    for(unsigned int i = 0; i < json_object_array_length(tbl_monstre); i++){
        monstre = json_object_array_get_idx(tbl_monstre,i);
        /* Fonction qui permet de creer un monstre */
    }

    m->unite_dep_x = floor(FENETRE_LONGUEUR / (float)m->text_map->width); /* Calcul en nombre de pixels d'une unité de déplacement */
    m->unite_dep_y = floor(FENETRE_LARGEUR / (float)m->text_map->height); /* Calcul en nombre de pixels d'une unité de déplacement */

    free(buffer);
    json_object_put(fichier); //libération mémoire de l'objet json
    return m;
}

t_aff * texture_map(const t_map * map){
    return map->text_map;
}