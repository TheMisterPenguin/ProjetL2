#include <stdlib.h>
#include <commun.h>
#include <string.h>

/**
 * \file inventaire.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonctions liées au module inventaire
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

inventaire_t * inventaire = NULL;

void changement_statistiques(joueur_t *joueur,lobjet_t *equipe){
    int i, j;
    int att = joueur->attaque;
    int def = joueur->defense;
    int vit = joueur->vitesse;

    for(i = 0, j=0;i<equipe->nb;i++, j++){
        //recherche du prochain objet
        while(equipe->liste[j] == NULL)
            j++;
        printf("att+%d\n", (equipe->liste[j])->attaque);
        att += (equipe->liste[j])->attaque;
        def += (equipe->liste[j])->defense;
        vit += (equipe->liste[j])->vitesse;
    }
        joueur->attaque_actif = att;
        joueur->defense_actif = def;
        joueur->vitesse_actif = vit;
}

void equiper_objet(joueur_t *joueur,objet_t **objet,inventaire_t *inventaire){
    objet_t *temp = NULL;

    if(joueur->niveau < (*objet)->niveau){
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

    changement_statistiques(joueur,inventaire->equipe);
    afficher_statistiques(perso_principal);

    if(temp->type == bouclier){
        joueur->statut->bouclier_equipe = 1;
    }
/*
on clique sur un item de l'inventaire (sac) qui s'équipe automatiquement
on clique sur un item de l'inventaire (équipé) qui s'enlève automatiquement
*/
}

void desequiper(joueur_t *j, objet_t **objet,inventaire_t *inventaire){
    if(*objet != NULL){
        inventaire->sac->liste[inventaire->sac->nb] = *objet;
        *objet = NULL;

        changement_statistiques(j,inventaire->equipe);
        afficher_statistiques(perso_principal);

        if((*objet)->type == bouclier){
            j->statut->bouclier_equipe = 0;
        }
        inventaire->sac->nb++;
        inventaire->equipe->nb--;
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

void tout_ramasser(lobjet_t * objets, inventaire_t * inventaire){
    int i;
    
    for(i=0; i<objets->nb; i++){
        inventaire->sac->liste[inventaire->sac->nb] = objets->liste[i];
        inventaire->sac->nb++;
    }
}

void equiper_sac_slot( int slot )
{
    int i, j ;
    int tt_obj ;

    tt_obj = inventaire->sac->nb ;

    if( slot >= tt_obj )
    {
        return ;
    }

    for( i=0, j=0 ; i<CAPACITE_SAC ; i++, j++)
    {
        //faire correspondre la liste graphique à la liste du programme
        if(inventaire->sac->liste[i] == NULL)
            j--;

        if(j == slot){
            equiper_objet(perso_principal,&(inventaire->sac->liste[i]),inventaire);
            break;
        }
    }
}

void desequiper_slot(int slot){
    slot -= CAPACITE_SAC; //on met la valeur du premier slot des objets équipés à 0

    desequiper(perso_principal, &(inventaire->equipe->liste[slot]), inventaire);
}