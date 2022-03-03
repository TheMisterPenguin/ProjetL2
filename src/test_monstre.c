#include <monstres.h>
#include <stdio.h>
#include <stdlib.h>

void test_monstre(){
int i;
base_monstres_t* base_monstres = NULL;

printf("Debut du programme des test sur les objets monstres_t et base_monstres_t\n" ) ; 

base_monstres = charger_monstres("../ressource/monstres.txt");

//parcourir base_monstres
for(i=0; i < base_monstres->nb_monstre; i++){
    printf("nom = %s\n", base_monstres->tab[i]->nom_monstre);
    printf("pdv = %d\n", base_monstres->tab[i]->pdv);
    printf("attaque = %d\n", base_monstres->tab[i]->attaque);
    printf("vitesse = %f\n", base_monstres->tab[i]->vitesse);
    printf("gainXp = %d\n\n", base_monstres->tab[i]->gainXp);
}

detruire_base_monstres(&base_monstres);
}