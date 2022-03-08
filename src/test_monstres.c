#include <commun.h>
#include <stdio.h>
#include <stdlib.h>



int main(){
    int i;
    liste_base_monstres_t* liste_base_monstres = NULL;

    printf("Debut du programme des test sur les objets monstres_t et base_monstres_t\n\n" ) ; 

    liste_base_monstres = charger_monstres("../ressource/monstres.txt");

    printf("Affichage des monstres\n\n");
    //parcourir base_monstres
    for(i=0; i < liste_base_monstres->nb_monstre; i++){
        printf("fichier = %s\n", liste_base_monstres->tab[i]->fichier_image);
        printf("nom = %s\n", liste_base_monstres->tab[i]->nom_monstre);
        printf("pdv = %d\n", liste_base_monstres->tab[i]->pdv);
        printf("attaque = %d\n", liste_base_monstres->tab[i]->attaque);
        printf("vitesse = %f\n", liste_base_monstres->tab[i]->vitesse);
        printf("gainXp = %d\n\n", liste_base_monstres->tab[i]->gainXp);
    }
    printf("Destruction des monstres\n\n");
    detruire_liste_base_monstres(&liste_base_monstres);
}




