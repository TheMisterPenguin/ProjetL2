#include <liste_objet.h>

void main(){
    lobjet_t * liste_obj = NULL;

    printf("Création de la liste d'objets:\n");
    liste_obj = creer_liste_objet();

    printf("Affichage de la liste d'objets:\n");
    afficher_liste_objet(liste_obj);

    printf("Destruction de la liste d'objets:\n");
    detruire_liste_objet(&liste_obj);
}