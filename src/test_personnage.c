#include <commun.h>
#include <personnage.h>

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    init();

    perso_principal = new_joueur("test");
    detruire_joueur(perso_principal);

    fermer_programme(EXIT_SUCCESS);

    return 0;
}