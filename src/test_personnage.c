#include <commun.h>

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    init();

    objets = creer_liste_objet();
    inventaire = creer_inventaire();
    creer_textures_objets(objets);
    tout_ramasser(objets, inventaire);

    perso_principal = new_joueur("test");
    afficher_statistiques(perso_principal);
    detruire_joueur(perso_principal);

    fermer_programme(EXIT_SUCCESS);

    return 0;
}