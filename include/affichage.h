/**
 * \file affichage.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant les définitions et les fonctions liées au module affichage.
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

/** \cond */
#include "SDL2/SDL.h"
/** \endcond */
#include "definition_commun.h"
#include "personnage.h"
#include "listes.h"
#include "map.h"



#define NB_FPS 60 /**< Le nombre maximum de FPS */
#define NB_SPRITE_JOUEUR 5 /**< Le nombre de sprites différents du joueur */

/* On définit l'emplacement des textures du joueur */
#define N_T_MARCHER "ressources/sprite/marcher.bmp" /**<La texture du personnage qui marche */
#define N_T_ATTAQUE "ressources/sprite/attaque.bmp" /**<La texture du personnage qui attaque */
#define N_T_ATTAQUE_CHARGEE "ressources/sprite/attaque_chargee.bmp" /**<La texture du personnage qui fait son attaque chargée */
#define N_T_CHARGER "ressources/sprite/charger.bmp" /**<La texture du personnage qui charge son attaque chargée */
#define N_T_MARCHER_BOUCLIER "ressources/sprite/marcher_bouclier.bmp" /**<La texture du personnage qui marche avec son bouclier équipé*/

#define N_T_MARCHER2 "ressources/sprite/marcher_green.bmp" /**<La texture du personnage qui marche */
#define N_T_ATTAQUE2 "ressources/sprite/attaque_green.bmp" /**<La texture du personnage qui attaque */
#define N_T_ATTAQUE_CHARGEE2 "ressources/sprite/attaque_chargee_green.bmp" /**<La texture du personnage qui fait son attaque chargée */
#define N_T_CHARGER2 "ressources/sprite/charger_green.bmp" /**<La texture du personnage qui charge son attaque chargée */
#define N_T_MARCHER_BOUCLIER2 "ressources/sprite/marcher_bouclier_green.bmp" /**<La texture du personnage qui marche avec son bouclier équipé */

/* On définit la taille d'une frame de sprite */
#define LONGUEUR_ENTITE 48 /**<La longueur d'une frame d'un sprite d'une entitée */
#define LARGEUR_ENTITE 48 /**<La largeur d'une frame d'un sprite d'une entitée */

/**
 * \brief Définition de la structure map
 * 
 * Cette définition est la pour éviter une inclusion mutuelle des fichiers \ref affichage.h et \ref map.h .
 */
typedef struct s_map t_map;

/**
 * \brief Définition de la structure joueur
 *
 * Cette définition est la pour éviter une inclusion mutuelle des fichiers \ref affichage.h et \ref personnage.h .
 */
typedef struct joueur_s joueur_t;

/**
 * Type enum renseignant sur la texture personnage à utiliser
 */
typedef enum {TEXT_MARCHER, TEXT_ATTAQUE, TEXT_ATTAQUE_CHARGEE, TEXT_CHARGER, TEXT_MARCHER_BOUCLIER}t_texture_perso;

/**
 * \struct s_aff
 * \brief Structure qui permet l'affichage d'une texture à l'écran de manière précise
 *
 * # Le but de la structure
 * Cette structure à pour but de permettre l'affichage d'une texture à l'écran de manière précise.
 * Ainsi, on peut facilement placer une texture où l'on veut sans savoir utiliser la SDL.
 * 
 * # Éléments de la structure
 * - texture : la SDL_Texture que l'on veut afficher à l'écran. Elle est crée par la fonction creer_texture. à partir d'une surface chargée à partir d'un fichier.
 * - frame_anim : Un rectangle permettant de n'afficher qu'une partie bien précise de la texture. C'est à dire, un rectangle qui contient la frame que l'on veut afficher. 
 * Cela permet donc d'animer la texture.
 * - aff_fenetre : Un rectangle qui permet de savoir où placer la texture à l'écran et de connaitre sa taille. Sa taille est définie à l'aide d'un multiplicateur où bien elle peut être choisie graâce à l'appel d'une fonction.
 * - width : La largeur de la texture. Cette valeur est obtenue grâce à une requête SDL et renseignée dans la structure par la fonction creer_texture.
 * - height : La hauteur de la texture. Cette valeur est obtenue grâce à une requête SDL et renseignée dans la structure par la fonction creer_texture.
 * - multipli_taille : Un multiplicateur qui permet de modifier la taille de la texture. Il s'agit de celui que l'on renseigne dans la fonction creer_texture.
 * - duree_frame_anim : entier qui permet de savoir combien de temps une frame dure. C'est à dire, combien de temps une frame dure sur l'écran.
 */
typedef struct s_aff
{
    SDL_Texture *texture;  /**<Texture utilisée*/
    SDL_Rect *frame_anim;  /**<Désigne la zone de la texture à afficher*/
    SDL_Rect *aff_fenetre; /**<Désigne l'emplacement et la taille de l'objet à l'écran */
    int width; /**< Longueur de la texture */
    int height; /**< Hauteur de la texture */
    float multipli_taille; /**<Sauvegarde du multiplicateur de taille de la texture*/
    unsigned int duree_frame_anim; /**<Durée d'une frame*/
    unsigned int compteur_frame_anim; 
} t_aff;

/**
 * \brief Structure contenant la liste des textures créées par le programme
 * 
 */
typedef struct s_l_aff{
    t_aff **liste;
    unsigned int nb_valeurs;
}t_l_aff;

/* Variables globales */
extern list *listeDeTextures;
extern list *buffer_affichage; /*<Buffer contenant toutes les textures à afficher */
extern long int compteur;      /*compteur utilisé pour gérer la vitesse d'affichage (fps)*/
extern SDL_Rect tx, ty;
extern float multiplicateur_x, multiplicateur_y; /* Multiplicateurs qui dépendent de la résolution */
extern t_aff * heal;
extern t_aff *fenetre_finale; /* La fenêtre de jeu finale sans l'interface */

/* Définition des fonctions */

/**
 * \fn void detruire_texture(t_aff **texture)
 * \brief Fonction qui détruit une structure d'affichage de texture passée en paramètre
 * \author Despert Ange
 * \param texture L'adresse du pointeur sur la structure à détruire
 */
extern void detruire_texture(t_aff **texture); /**<La liste des textures créées */
/**
 * \brief Fonction qui détruit une liste de textures
 *
 * \param l_texture L'adresse de la liste de texture à détruire
 */
extern void detruire_liste_textures(t_l_aff **l_texture);
/**
 * \brief Fonction qui détermine si la structure SDL_Rect ne dépasse pas la taille de la texture.
 *
 * \param to_verify La structure SDL_Rect à vérifier
 * \param width La longueur de la texture
 * \param height La largeur de la texture
 * \return vrai Si tout est OK, faux sinon.
 */
extern _Bool rect_correct_texture(const SDL_Rect *const to_verify, const int width, const int height);
/**
 * \fn t_aff * creer_texture(const char* nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const int multiplicateur_taille)
 * \brief Fonction qui renvoie, charge une texture et la prépare à se faire afficher
 *
 * \param nom_fichier Le nom du fichier contenant la texture
 * \param taille_t_x La longueur de la texture à montrer
 * \param taille_t_y La largeur de la texture à montrer
 * \param x La coordonnée x où afficher la texture à l'écran
 * \param y La coordonnée y où afficher la texture à l'écran
 * \param multiplicateur_taille Une valeur par laquelle multiplier la taille de la texture
 * \return t_aff* Une structure qui permet l'affichage de la texture à l'écran ou NULL s'il y a eu une érreur
 */
extern t_aff *creer_texture(const char *nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const float multiplicateur_taille);

/**
 * \brief Affiche la texture donnée en paramètre à l'écran
 *
 * \param texture La texture à afficher
 * \param rendu Le rendu sur lequel afficher la texture à l'écran
 * \return 0 s'il n'y a pas eu d'erreur sinon un entier négatif
 */
extern err_t afficher_texture(t_aff *texture, SDL_Renderer *rendu);

/**
 * \fn void next_frame_y(t_aff *texture);
 * \brief Fonction qui positionne la texture au sprite d'après sur l'axe des y
 *
 * \param t_aff* une texture joueur
 */
extern void next_frame_y(t_aff* texture);

/**
 * \fn void next_frame_x(t_aff *texture);
 * \brief Fonction qui positionne la texture au sprite d'après sur l'axe des x
 *
 * \param t_aff* une texture joueur
 */
extern void next_frame_x(t_aff *texture);

/**
 * \fn void next_frame_indice(t_aff *texture, const unsigned int x, const unsigned int y);
 * \brief Fonction qui positionne la texture au n-ème sprite sur l'axe des x
 *
 * \param texture une texture joueur
 * \param x qui correspond au n-ème sprite sur l'axe des x ou l'on souhaite positionner la texture
 * \param y qui correspond au n-ème sprite sur l'axe des y ou l'on souhaite positionner la texture
 * \return err_t un entier pour savoir si il y a eu une erreur
 */
extern err_t next_frame_indice(t_aff *texture, const unsigned int x, const unsigned int y);

/**
 * \fn void next_frame_x_indice(t_aff *texture, const unsigned int indice);
 * \brief Fonction qui positionne la texture au n-ème sprite sur l'axe des x
 *
 * \param t_aff* une texture joueur
 * \param const unsigned int qui correspond au n-ème sprite sur l'axe des x ou l'on souhaite positionner la texture
 * \return err_t un entier pour savoir si il y a eu une erreur
 */
extern err_t next_frame_x_indice(t_aff *texture, const unsigned int indice);

/**
 * \fn void next_frame_y_indice(t_aff *texture, const unsigned int indice);
 * \brief Fonction qui positionne la texture au n-ème sprite sur l'axe des y
 *
 * \param t_aff* une texture joueur
 * \param const unsigned int qui correspond au n-ème sprite sur l'axe des y ou l'on souhaite positionner la texture
 * \return err_t un entier pour savoir si il y a eu une erreur
 */
extern err_t next_frame_y_indice(t_aff *texture, const unsigned int indice); 

void *ajout_text_liste(void *t);

/**
 * Fonction qui affiche les textures contenues dans la liste en paramètre. 
 * 
 * Les premiers éléments seront en arrière plan et les derniers seront en 1er plan.
 * 
 * \param buffer La liste de textures que l'on veut afficher
 * \param rendu Le rendu sur lequel on veut afficher ces textures
 * \return Une valeur différente à 0 lors d'une erreur
 */
extern err_t afficher_buffer(list *buffer, SDL_Renderer *rendu);

/**
 * Déplacez la texture pour que son centre soit au centre de l'écran
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x du centre de la texture.
 * @param y La coordonnée y du centre de la texture.
 */
void deplacer_texture_centre(t_aff *texture, int x, int y);

extern void deplacer_rect_origine(SDL_Rect *r, int x, int y);

/**
 * Déplacez l'origine de la texture aux coordonnées données.
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x de l'origine de la texture.
 * @param y La coordonnée y de l'origine de la texture.
 */
void deplacer_texture_origine(t_aff *texture, int x, int y);

void deplacer_rect_haut_droit(SDL_Rect *r, int x, int y);

/**
 * La texture est déplacée vers la droite et vers le haut
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche du rectangle.
 */
void deplacer_texture_haut_droit(t_aff *texture, int x, int y);

/**
 * La texture est déplacée vers le coin inférieur gauche de l'écran
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche de la texture.
 */
void deplacer_texture_bas_gauche(t_aff *texture, int x, int y);

/**
 * La texture est déplacée vers le coin inférieur droit de la fenêtre
 *
 * @param texture la texture à déplacer
 * @param x Coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche de la texture.
 */
void deplacer_texture_bas_droit(t_aff *texture, int x, int y);

/**
 * Modifie le rectangle qui définit la zone de l'écran qui sera utilisée pour le rendu de la texture
 *
 * @param texture La texture à modifier.
 * @param r Le rectangle à appliquer.
 */
void modif_affichage_rect(t_aff *texture, SDL_Rect r);

/**
 * Permet de déplacer le personnage de x unités sur la map
 * 
 * \param map La map sur laquelle le personnage ce déplace
 * \param pers La texture du personnage elle même
 * \param x Le nombre d'unités de déplacements
 */
bool deplacement_x_pers(t_map *m, joueur_t **joueurs, unsigned short int nb_joueurs, int x);

/**
 * \fn t_l_aff* init_textures_joueur(joueur_t *j, int num_j)
 * \brief Fonction qui creer et renvoie une liste de textures pour le personnage (joueur)
 * \author Antoine Bruneau
 * \param j Le joueur dont on initialise les textures
 * \param num_j Indice du joueur dans le tableau des joueurs
 * \return t_l_aff* Une liste de textures
 */
extern t_l_aff* init_textures_joueur(joueur_t *j, int num_j);

/**
 * \fn t_aff* init_texture_joueur(t_l_aff* textures_joueur, joueur_t * joueur)
 * \brief Fonction qui renvoie la texture de départ du personnage (joueur)
 * \author Antoine Bruneau
 * \param t_l_aff Liste de textures personnage
 * \param joueur Joueur dont on veut la texture de départ
 * \return t_aff* Une textures personnage
 */
extern t_aff *init_texture_joueur(t_l_aff *textures_joueur, joueur_t * joueur);

/**
 * \fn t_aff * next_frame_joueur(t_l_aff* textures_joueur);
 * \brief Fonction qui modifie et renvoie une textures en fonction des évênements (clics, touches claviers). Cette texture renvoyée sera par la suite affichée.
 * \author Antoine Bruneau
 * \param t_l_aff* un structure contenant un tableau de textures joueur
 * \return t_aff* Une texture joueur
 */
extern t_aff *next_frame_joueur(joueur_t *j);

/**
 * Permet de déplacer le personnage de y unités sur la map
 *
 * \param map La map sur laquelle le personnage ce déplace
 * \param pers La texture du personnage elle même
 * \param y Le nombre d'unités de déplacements
 */
bool deplacement_y_pers(t_map *m, joueur_t **joueurs, unsigned short int nb_joueurs, int y);

/**
 * Fonction qui permet de définir exactement la taille de la texture à affichar sur l'écran
 * 
 * \param a_modifier La texture à modifier
 * \param longueur La nouvelle longueure en pixel à appliquer
 * \param largeur La nouvelle largeur en pixel à appliquer
 */
void def_texture_taille(t_aff *a_modifier, const int longueur, const int largeur);

/**
 * Fonction qui permet de placer 2 textures aux mêmes endroit à l'écran
 * 
 * \param a_modifier La texture dont on veut modifier la position
 * \param original La texture dont on veut copier la position
 */
void text_copier_position(t_aff *a_modifier, const t_aff *const original);

void rect_centre_x(SDL_Rect *rectangle);

void rect_centre_y(SDL_Rect *rectangle);

void rect_centre(SDL_Rect *rectangle);

bool rects_egal_x(const SDL_Rect *const r1, SDL_Rect const *const r2);

bool rects_egal_y(const SDL_Rect *const r1, SDL_Rect const *const r2);

/**
 * \fn SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
 * \brief Fonction qui permet de choisir une couleur SDL
 * \param r niveau de rouge
 * \param g niveau de vert
 * \param b niveau de bleu
 * \param a niveau d'opacité
 * \return SDL_Color une couleur SDL
 */
extern SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/**
 * \fn void info_texture(t_aff * texture)
 * \brief Affiche des informations sur une texture
 * \param texture la texture sur laquelle on se renseigne
 */
extern void info_texture(t_aff * texture);

/**
* \fn extern int current_frame_x(t_aff * texture);
 * \brief Fonction qui donne l'indice sur l'axe des abscisses actuelle de la texture 
 *
 * \param texture une texture
 * \return un entier correspondant à l'indice
 */
extern int current_frame_x(t_aff * texture);

/**
* \fn extern int current_frame_y(t_aff * texture);
 * \brief Fonction qui donne l'indice sur l'axe des ordonnées actuelle de la texture 
 *
 * \param texture une texture
 * \return un entier correspondant à l'indice
 */
extern int current_frame_y(t_aff * texture);

/**
* \fn extern void afficher_monstres(list * liste_monstre, joueur_t * joueur)
 * \brief Fonction qui affiche les monstres
 * \param liste_monstre une liste de monstres
 * \param joueur le joueur qui influe sur les monstres
 */
extern void afficher_monstres(list * liste_monstre, joueur_t * joueur);

/**
* \fn extern void afficher_sorts(list * liste_sorts, joueur_t * joueur);
 * \brief Fonction qui affiche les sorts
 * \param liste_sorts une liste de sorts
 * \param joueur le joueur qui influe sur les sorts
 */
extern void afficher_sorts(list * liste_sorts, joueur_t * joueur);

/**
 * \fn void placer_texture(t_aff *texture, int x, int y)
 * \brief Place une texture sur l'écran
 * \param texture Texture à placer
 * \param x Position horizontale
 * \param y Position verticale
 */
void placer_texture(t_aff *texture, int x, int y);

/**
 * \fn void init_animations(void)
 * \brief Initialise les textures des animations
 */
void init_animations(void);

/**
 * \fn t_aff * next_frame_animation(joueur_t * joueur)
 * \brief Fait évoluer les animations en jeu
 * \param joueur Le joueur sur lequel placer l'animation
 * \return La texture de l'animation
 */
t_aff * next_frame_animation(joueur_t * joueur);

/**
 * \fn void lister_animations(joueur_t ** joueurs, list * animations)
 * \brief Liste les animations en jeu
 * \param joueurs Les joueurs sur lesquels placer les animation
 * \param animations Liste regroupant les animations trouvées
 */
void lister_animations(joueur_t ** joueurs, list * animations);

/**
* \fn void afficher_coffres(list * liste_coffre)
 * \brief Fonction qui affiche les coffres
 * \param liste_monstre une liste de coffres
 */
void afficher_coffres(list * liste_coffre);

void rect_ecran_to_rect_map(SDL_Rect *ecran, SDL_Rect *r_map, int x, int y);

void rect_centre_rect_x(SDL_Rect *rectangle, SDL_Rect *rectangle_centre);

void rect_centre_rect_y(SDL_Rect *rectangle, SDL_Rect *rectangle_centre);

void rect_centre_rect(SDL_Rect *rectangle, SDL_Rect *rectangle_centre);

void afficher_animations(list * animations);

/**
 * \brief Fonction qui permet le déplacement d'une entité
 * \author Ange Despert
 * 
 * Cette fonction permet à une entité de se déplacer sur l'axe x. \n
 * Cette fonction gère les collisions et empêchera l'entité de sortir des limites de la map. \n
 * Cette dernière prend également les collisions définies dans la liste des collisions de la map : \ref s_map.liste_collisions "liste_collisions".  \n
 *
 * Il est a noté que pour éviter les déplacement trop rapides la fonction utilise l'entier \ref s_aff.duree_frame_anim "duree_frame_anim" qui permet d'êmpécher le déplacement tout les x frames.
 *
 * 
 * \param m La map actuelle
 * \param texture La texture de l'entité que l'on veut bouger
 * \param y La nouvelle coordonnée du rectangle de l'entité
 * \param r Le rectangle représentant la zone de collision de l'entité
 * \return vrai : Si l'entité a réussi à se déplacer
 * \return faux : Si l'entité n'a pas pu se déplacer
 */
bool deplacement_x_entite(t_map *m, t_aff *texture, int x, SDL_Rect *r);

/**
 * \brief Fonction qui permet le déplacement d'une entité
 * \author Ange Despert
 * 
 * Cette fonction permet à une entité de se déplacer sur l'axe y. \n
 * Cette fonction gère les collisions et empêchera l'entité de sortir des limites de la map. \n
 * Cette dernière prend également les collisions définies dans la liste des collisions de la map : \ref s_map.liste_collisions "liste_collisions".  \n
 *
 * Il est a noté que pour éviter les déplacement trop rapides la fonction utilise l'entier \ref s_aff.duree_frame_anim "duree_frame_anim" qui permet d'êmpécher le déplacement tout les x frames.
 *
 * \param m La map actuelle
 * \param texture La texture de l'entité que l'on veut bouger
 * \param y La nouvelle coordonnée du rectangle de l'entité
 * \param r Le rectangle représentant la zone de collision de l'entité
 * \return vrai : Si l'entité a réussi à se déplacer
 * \return faux : Si l'entité n'a pas pu se déplacer
 */
bool deplacement_y_entite(t_map *m, t_aff *texture, int y, SDL_Rect *r);

void detruire_collision_dans_liste(list * liste_collisions, SDL_Rect * collision);

/**
 * \brief Renvoie les coordonnées du centre du rectangle
 * 
 * Cette fonction contrairement à la fonction \ref get_rect_center_coord donne les coordonnées strictes du centre.
 *
 * \author Ange Despert
 * \param r Le rectangle dont on veut les coordonnées du milieu
 * \return Les coordonnées du milieu du rectangle
 */
extern SDL_Point get_rect_center(const SDL_Rect *const r);

/**
 * \brief Renvoie les coordonnées du centre du rectangle.
 * 
 * Cette fonction contrairement à la fonction \ref get_rect_center donne les coordonnées du centre en prenant en compte les coordonnées actuelles du rectangle.
 * 
 * Cette fonction est donc faite pour être utilisée conjointement à la fonction \ref place_rect_center_from_point(SDL_Rect *r, SDL_Point p)
 * \author Ange Despert
 * \param r Le rectangle dont on veut les coordonnées du milieu.
 * \return Les coordonnées du milieu du rectangle.
 */
extern SDL_Point get_rect_center_coord(const SDL_Rect *const r);

/**
 * \brief Fonction qui permet de placer le centre du rectangle donné en paramètre à un point précis.
 * 
 * Le but de cette fonction est de pouvoir placer plusieurs rectangles au même endroit peut importe leur taille.
 * C'est fonction est donc très puissante si elle est utilisée conjointement à la fonction \ref get_rect_center_coord(const SDL_Rect *const r)
 * 
 * \author Ange Despert
 * \param r Le rectangle que l'on veut déplacer
 * \param p Le point où on veut placer le milieu du rectangle
 */
extern void place_rect_center_from_point(SDL_Rect *r, SDL_Point p);

#endif