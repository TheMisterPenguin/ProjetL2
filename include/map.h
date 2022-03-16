

#ifndef __MAP_H__
#define __MAP_H__ 
#include "definition_commun.h"
#include "listes.h"

#define TAILLE_CASE 16

typedef struct {
    point p1,p2; /*< Rectangle représentant la zone de tp */
    unsigned int id_map; /*< l'id de la map de destination */
    point dest; /*< Les coordonnées du point d'apparition sur la map */
}zone_tp;

typedef struct {
    t_aff * text_map;
    unsigned int width, height;
    list *liste_monstres;
}t_map;

/**
 * \brief Fonction qui charge le contenu du fichier dont le nom est donné en paramètre dans un buffer de caractères
 *
 * \param nom_map Le nom du fichier map à charger
 * \return Un buffer de caractères contenant l'intégralité du fichier
 */
char *charger_f_map(const char *const nom_map);

/**
 * Fonction qui récupère les informations stockées dans le buffer en entrée.
 * 
 * \param buffer Le buffeur qui contient les informations
 * \return Une map initialisée avec toutes les informations dedans;
 */
t_map *charger_s_map(const char *const buffer);

t_aff *texture_map(const t_map *map);

#endif