#include <stdlib.h>
#include <commun.h>
#include <string.h>

/**
 * \file inventaire.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonctions liées au module inventaire
 * \version 0.3
 * \date 29/03/2022
 * \copyright Copyright (c) 2022
 */

void changement_statistiques(joueur_t * joueur){
    lobjet_t * equipe = joueur->inventaire->equipe;
    int nb_conso = (equipe->liste[consommable] != NULL) + (equipe->liste[quete] != NULL); //nombre d'objets ne modifiant pas les statistiques
    int att = joueur->attaque;
    int def = joueur->defense;
    int vit = joueur->vitesse;
    int nb_trouve, i;

    //on boucle dans tous les éléments sauf les objets de quête et les consommables (on commence donc à arme)
    for(nb_trouve = 0, i=arme;nb_trouve < (equipe->nb - nb_conso); nb_trouve++, i++){
        //recherche du prochain objet
        while(equipe->liste[i] == NULL)
            i++;

        //application des bonus de l'objet trouvé
        att += (equipe->liste[i])->attaque;
        def += (equipe->liste[i])->defense;
        vit += (equipe->liste[i])->vitesse;
    }
        joueur->attaque_actif = att;
        joueur->defense_actif = def;
        joueur->vitesse_actif = vit;
}

void equiper_objet(joueur_t * joueur,objet_t ** objet){
    lobjet_t * equipe = joueur->inventaire->equipe;
    lobjet_t * sac = joueur->inventaire->sac;
    objet_t *temp = NULL;

    if(joueur->niveau < (*objet)->niveau){
        printf("Niveau insuffisant pour équiper\n");
        return;
    }

    //on échange l'objet avec celui contenu dans le slot de son type dans les objets équipés
    temp = *objet;
    *objet = equipe->liste[(*objet)->type];
    equipe->liste[temp->type] = temp;

    if(*objet == NULL){
        (sac->nb)--;
        (equipe->nb)++;
    }

    if(temp->type != consommable && temp->type != quete){
        changement_statistiques(joueur);
        afficher_statistiques(joueur);

        if(temp->type == bouclier){
            joueur->statut->bouclier_equipe = 1;
        }
    }
/*
on clique sur un item de l'inventaire (sac) qui s'équipe automatiquement
on clique sur un item de l'inventaire (équipé) qui s'enlève automatiquement
*/
}

void desequiper(joueur_t * joueur, objet_t ** objet){
    lobjet_t * equipe = joueur->inventaire->equipe;
    lobjet_t * sac = joueur->inventaire->sac;
    int i;

    if(*objet != NULL){
        if((*objet)->type == bouclier){
            joueur->statut->bouclier_equipe = 0;
        }

        for(i=0; i<CAPACITE_SAC; i++){
            if(sac->liste[i] == NULL){
                sac->liste[i] = *objet;
                *objet = NULL;
                break;
            }
        }

        (sac->nb)++;
        (equipe->nb)--;

        changement_statistiques(joueur);
        afficher_statistiques(joueur);

    }
    /* 
    on n'utilise pas de liste pour les objets de l'inventaire (sac) car on équipe beaucoup plus souvent qu'on deséquipe donc on préfère profiter
    de la rapidité de l'indexage plutôt que de parcourir la liste à chaque équipement pour trouver l'objet équipé. 
    */
}

inventaire_t * creer_inventaire(char * fichier_src){ //refaire fonction##################
    inventaire_t * inventaire = NULL;

    if(( inventaire = malloc(sizeof(inventaire_t))) == NULL ){
        fprintf( stderr , "creer_inventaire: debordement memoire lors de la creation d'une structure inventaire_t\n");
        return((inventaire_t *)NULL);
    }

    inventaire->equipe = creer_liste_objet_equipe();
    inventaire->sac = creer_liste_objet_vide(fichier_src);

    if(inventaire->equipe == NULL || inventaire->sac == NULL){
        fprintf( stderr , "creer_inventaire: erreur de création du sac ou du équipé\n");
        return((inventaire_t *)NULL);
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
    int i;

    //chercher une case libre dans le sac
    for(i=0; i<inventaire->sac->nb && inventaire->sac->liste[i] != NULL; i++);

    inventaire->sac->liste[i] = objet;
    (inventaire->sac->nb)++;
}

void tout_ramasser(lobjet_t * objets, inventaire_t * inventaire){
    int i;
    
    for(i=0; i<objets->nb; i++){
        ramasser_objet(objets->liste[i], inventaire);
    }
}

void equiper_sac_slot(joueur_t * joueur, int slot){
    lobjet_t * sac = joueur->inventaire->sac;
    int i, j ;
    int tt_obj ;

    tt_obj = sac->nb ;

    if( slot >= tt_obj )
    {
        return ;
    }

    for( i=0, j=0 ; i<CAPACITE_SAC ; i++, j++)
    {
        //faire correspondre la liste graphique à la liste du programme
        if(sac->liste[i] == NULL)
            j--;

        //on se trouve sur le bon objet donc on l'équipe
        if(j == slot){
            equiper_objet(joueur,&(sac->liste[i]));
            break;
        }
    }
}

void desequiper_slot(joueur_t * joueur, int slot){
    lobjet_t * equipe = joueur->inventaire->equipe;

    slot -= CAPACITE_SAC; //on met la valeur du premier slot des objets équipés à 0

    desequiper(joueur, &(equipe->liste[slot]));
}

void consommer_objet(joueur_t * joueur){
    lobjet_t * equipe = joueur->inventaire->equipe;
    
    //soigne le joueur
    joueur->pdv = joueur->maxPdv;

    //retire le consommable de l'inventaire
    equipe->liste[consommable] = NULL;
    (equipe->nb)--;
}