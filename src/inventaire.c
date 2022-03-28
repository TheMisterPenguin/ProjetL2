#include <stdlib.h>
#include <commun.h>
#include <string.h>

inventaire_t * inventaire = NULL;

void changement_statistiques(joueur_t *j,lobjet_t *equipe){
    int i;
    for(i = 0;i<equipe->nb;i++){
        while(equipe->liste[i] == NULL)
            i++;
        j->attaque += (equipe->liste[i])->attaque;
        j->defense += (equipe->liste[i])->defense;
        j->vitesse += (equipe->liste[i])->vitesse;
    }
}

void equiper_objet(joueur_t *j,objet_t **objet,inventaire_t *inventaire){
    objet_t *temp = NULL;

    if(j->niveau < (*objet)->niveau){
        printf("Niveau insuffisant pour équiper\n");
        return;
    }

    temp = *objet;
    *objet = inventaire->equipe->liste[(*objet)->type];
    inventaire->equipe->liste[temp->type] = temp;

    if(*objet == NULL){
        inventaire->sac->nb--;
        inventaire->equipe->nb++;
    }

    changement_statistiques(j,inventaire->equipe);

    if(temp->type == bouclier){
        j->statut->bouclier_equipe = 1;
    }
/*
on clique sur un item de l'inventaire (sac) qui s'équipe automatiquement
on clique sur un item de l'inventaire (équipé) qui s'enlève automatiquement
*/
}

void desequiper(joueur_t *j, objet_t **objet,inventaire_t *inventaire){
    inventaire->sac->liste[inventaire->sac->nb] = *objet;
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

inventaire_t * creer_inventaire(){
    inventaire_t * inventaire = NULL;
    lobjet_t * equipe = NULL;
    lobjet_t * sac = NULL;

    equipe = creer_liste_objet_equipe();
    sac = creer_liste_objet_vide();

    if(equipe != NULL && sac != NULL){
        if(( inventaire = malloc(sizeof(inventaire_t))) == NULL )
        {
        fprintf( stderr , "creer_inventaire: debordement memoire lors de la creation d'une structure inventaire_t\n");
        return((inventaire_t *)NULL);
        }

        inventaire->equipe = equipe;
        inventaire->sac = sac;
    }
    return inventaire;
}

void detruire_inventaire(inventaire_t ** inventaire){
    effacer_liste_objet(&((*inventaire)->equipe));
    effacer_liste_objet(&((*inventaire)->sac));

    free(*inventaire);
    *inventaire = NULL;
}

void ramasser_objet(objet_t * objet, inventaire_t * inventaire){
    inventaire->sac->liste[inventaire->sac->nb] = objet;
    inventaire->sac->nb++;
}

void equiper_sac_slot( int slot )
{
    int i, j ;
    int nb_obj ;

    nb_obj = inventaire->sac->nb ;

    if( slot >= nb_obj )
    {
        return ;
    }

    for( i=0, j=0 ; i<nb_obj ; i++, j++)
    {
        if(inventaire->sac->liste[i] == NULL)
            j--;

        if(j == slot)
            equiper_objet(perso_principal,&(inventaire->sac->liste[i]),inventaire);
    }
}