#include <commun.h>

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;

int main(){
    t_aff * text = NULL;
    (void)text; //enlève le warning unused biaisé

    init();
    text = creer_texture("ressources/background/logo.bmp", -1, -1, 0, 0, 0);
    
    fermer_programme(EXIT_SUCCESS);
    return 0;
}