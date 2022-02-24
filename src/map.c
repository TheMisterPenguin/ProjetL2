#include <json-c/json.h>
#include <stdlib.h>
#include <stdio.h>

void charger_map(const char const * nom_map){
    FILE * fp;
    char *file_buffer;
    unsigned long taille_fichier;

    json_object *json_entree;
    json_object *type;

    fp = fopen(nom_map,"r");
    if(! fp){
        fprintf(stderr, "Erreur : impossible de charge la map, fichier \"%s\" introuvable !\n", nom_map);
        exit(EXIT_FAILURE);
    }

    fseek(fp, (long)0, SEEK_END); /* On parcourt le fichier afin de connaitre sa taille */
    taille_fichier = ftell(fp) + 1;

    file_buffer = malloc(sizeof(char) * (taille_fichier)); /* On alloue d'ynamiquement en fonction de la taille du fichier */

    rewind(fp); /* On revient au début du fichier */

    fread(file_buffer, taille_fichier, 1, fp); /* On lit le fichier */
    fclose(fp); /* On a plus besoin du fichier */

    json_entree = json_tokener_parse(file_buffer); /* On regarde les clefs */

    json_object_object_get_ex(json_entree,"type", &type); /* On récupère les données associés à la clef */

    printf("Le type du fichier est : %s \n", json_object_get_string(type)); /* On récupère les données sous forme d'une chaine de caractères */

    free(file_buffer);
}

int main(){

    charger_map("map.json");
    return 0;
}