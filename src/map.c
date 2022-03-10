#include <json-c/json.h>
#include <map.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commun.h>

/**
 * \brief Fonction qui charge le contenu du fichier dont le nom est donné en paramètre dans un buffer de caractères
 * 
 * \param nom_map Le nom du fichier map à charger
 * \return Un buffer de caractères contenant l'intégralité du fichier
 */
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

    m = malloc(sizeof(t_map));
}