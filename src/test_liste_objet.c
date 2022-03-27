#include <liste_objet.h>

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    lobjet_t * liste_obj = NULL;

    printf("----- Création de la liste d'objets selon le fichier correspondant -----\n\n");
    liste_obj = creer_liste_objet();

    printf("----- Affichage de la liste d'objets -----\n\n");
    afficher_liste_objet(liste_obj);

    printf("----- Destruction de la liste d'objets -----\n\n");
    detruire_liste_objet(&liste_obj);

    return 0;
}