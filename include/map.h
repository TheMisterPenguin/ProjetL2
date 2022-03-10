

#ifndef __MAP_H__
#define __MAP_H__
#include "definition_commun.h"


typedef struct {
    point p1,p2; /*< Rectangle représentant la zone de tp */
    unsigned int id_map; /*< l'id de la map de destination */
    point dest; /*< Les coordonnées du point d'apparition sur la map */
}zone_tp;

typedef struct t_map {
    t_aff * text_map;
    unsigned int width, height;
    
}t_map;

#endif