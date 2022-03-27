#include <commun.h>
#include <personnage.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
bool running = vrai;
long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    init();

    perso_principal = new_joueur("test");
    detruire_joueur(perso_principal);

    return 0;
}