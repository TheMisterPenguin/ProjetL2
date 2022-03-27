#include <commun.h>
#include <personnage.h>
#include <objet.h>
#include <inventaire.h>

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    printf("----- initialisation SDL -----\n\n");
    init();
    printf("----- création personnage -----\n\n");
    perso_principal = new_joueur("test");
    perso_principal->niveau = 5;
    printf("----- création liste d'objets -----\n\n");
    lobjet_t * objets = creer_liste_objet();
    printf("----- création inventaire -----\n\n");
    inventaire_t * inventaire = creer_inventaire();

    printf("----- ramassage objet -----\n\n");
    ramasser_objet(objets->liste[0], inventaire);
    printf("----- sac avant equipement -----\n\n");
    afficher_liste_objet(inventaire->sac);
    printf("----- équipé avant équipement -----\n\n");
    afficher_liste_objet(inventaire->equipe);
    printf("----- stats avant équipement -----\n\n");
    afficher_statistiques(perso_principal);

    printf("----- équipement objet -----\n\n");
    equiper_objet(perso_principal,&(inventaire->sac->liste[0]),inventaire);
    printf("----- sac après equipement -----\n\n");
    afficher_liste_objet(inventaire->sac);
    printf("----- équipé après équipement -----\n\n");
    afficher_liste_objet(inventaire->equipe);
    printf("----- stats après équipement -----\n\n");
    afficher_statistiques(perso_principal);
    
    printf("----- destruction liste objet -----\n\n");
    detruire_liste_objet(&objets);
    printf("----- destruction inventaire -----\n\n");
    detruire_inventaire(&inventaire);
    printf("OK\n");
    
    return 0;
}