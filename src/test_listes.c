#include <commun.h>
#include <listes.h>
#include <affichage.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
bool running = vrai;
long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    init();

    creer_texture(N_T_MARCHER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    creer_texture(N_T_ATTAQUE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    creer_texture(N_T_ATTAQUE_CHARGEE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);

    afficher_liste(listeDeTextures);

    return 0;
}