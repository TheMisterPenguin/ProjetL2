#include <commun.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
bool running = vrai;
long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    t_aff * text = NULL;
    (void)text; //enlève le warning unused biaisé

    init();
    text = creer_texture("ressources/background/logo.bmp", -1, -1, 0, 0, 0);
    
    //atexit détruit le renderer et ses textures
    return 0;
}