#ifndef __H_INVENTAIRE__
#define __H_INVENTAIRE__

#include "commun.h"

typedef struct inventaire_s inventaire_t;
struct inventaire_s
{
    lobjet_t *equipe;
    lobjet_t *sac;
};

joueur_t *changement_statistiques(joueur_t *j,lobjet_t *liste);
void equiper_objet(joueur_t *j,objet_t **objet,inventaire_t *inventaire);
void desequiper(objet_t **objet,inventaire_t *inventaire,joueur_t *j);

#endif