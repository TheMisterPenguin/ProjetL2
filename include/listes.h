// Mise en oeuvre par pointeurs de listes de base_monstre

// Definition des types

typedef struct element {base_monstre_t f; struct element* pred; struct element* succ;} t_element;
typedef struct {t_element* drapeau; t_element* ec;} t_liste;

// Primitives de listes 

void init_liste(t_liste *l);
int liste_vide(t_liste *l);
int hors_liste(t_liste *l);
void en_tete(t_liste *l);
void en_queue(t_liste *l);
void suivant(t_liste *l);
void precedent(t_liste *l);
void valeur_elt(t_liste *l, base_monstre_t * f);
void modif_elt(t_liste *l, base_monstre_t  f);
void oter_elt(t_liste *l);
void ajout_droit(t_liste *l, base_monstre_t f);
void ajout_gauche(t_liste *l, base_monstre_t f);
int taille(t_liste *l);
