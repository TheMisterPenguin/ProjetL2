#include <stdlib.h>
#include <commun.h>
#include <string.h>

joueur_t *changement_statistiques(joueur_t *j,lobjet_t *equipe){
    int i;
    for(i = 0;i<equipe->nb;i++){
        j->attaque += (equipe->liste[i])->attaque;
        j->defense += (equipe->liste[i])->defense;
        j->vitesse += (equipe->liste[i])->vitesse;
    }
    return j;
}

void equiper_objet(joueur_t *j,objet_t **objet,inventaire_t *inventaire){
    objet_t *temp = NULL;

    if(j->niveau < objet->niveau){
        printf("Niveau insuffisant pour équiper\n");
        return;
    }

    temp = *objet;
    *objet = inventaire->equipe->liste[(*objet)->type];
    inventaire->equipe->liste[(*objet)->type] = temp;

    changement_statistiques(j,inventaire->equipe);

    if((*objet)->type == bouclier){
        j->statut->bouclier_equipe = 1;
    }
/*
on clique sur un item de l'inventaire (sac) qui s'équipe automatiquement
on clique sur un item de l'inventaire (équipé) qui s'enlève automatiquement
*/
}

void desequiper(objet_t **objet,inventaire_t *inventaire,joueur_t *j){
    inventaire->sac->liste[inventaire->sac->liste->nb] = *objet;
    *objet = NULL;
    changement_statistiques(j,inventaire->equipe);

    if((*objet)->type == bouclier){
        j->statut->bouclier_equipe = 0;
    }
    /* 
    on n'utilise pas de liste pour les objets de l'inventaire (sac) car on équipe beaucoup plus souvent qu'on deséquipe donc on préfère profiter
    de la rapidité de l'indexage plutôt que de parcourir la liste à chaque équipement pour trouver l'objet équipé. 
    */
}