#include <json-c/json.h>
#include <affichage.h>
#include <map.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <code_erreur.h>


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

    file_buffer = malloc(sizeof(char) * (taille_fichier)); /* On alloue d'ynamiquement en fonction de la taille du fichier */

    if(!file_buffer){
        fprintf(stderr, "Erreur : plus de mémoire disponible !\n");
        exit(OUT_OF_MEM);
    }

    rewind(fp); /* On revient au début du fichier */

    fread(file_buffer, taille_fichier, 1, fp); /* On lit le fichier */
    fclose(fp); /* On a plus besoin du fichier */

    return file_buffer;
}

t_map * charger_s_map(const char * const buffer){
    t_map *m;
    json_object *fichier;
    json_object *texture_map;
    json_object *width;
    json_object *height;
    json_object *tbl_monstre;
    json_object *monstre;


    fichier = json_tokener_parse(buffer);
    m = malloc(sizeof(t_map));
    m->liste_monstres =  init_liste(NULL,NULL);

    json_object_object_get_ex(fichier, "file-path", &texture_map);
    json_object_object_get_ex(fichier, "width", &width);
    json_object_object_get_ex(fichier, "height", &height);
    json_object_object_get_ex(fichier, "monsters", &tbl_monstre);

    m->text_map = creer_texture(json_object_get_string(texture_map),
                                -1, -1, 0, 0, FENETRE_LARGEUR );
    m->height = json_object_get_int(height);
    m->width = json_object_get_int(width);

    for(unsigned int i = 0; i < json_object_array_length(tbl_monstre); i++){
        monstre = json_object_array_get_idx(tbl_monstre,i);
        /* Fonction qui permet de creer un monstre */
    }

    return m;
}

t_aff * texture_map(const t_map * map){
    return map->text_map;
}