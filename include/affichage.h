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

typedef struct s_map t_map; /*Cette définition est la pour éviter une inclusion mutuelle des fichiers affichage.h et map.h*/

typedef struct joueur_s joueur_t; /* Cette définition est la pour éviter une inclusion mutuelle des fichiers affichage.h et personnage.h */

/**
 * \brief Type énuméré renseignant sur la texture personnage à utiliser
 * \author Antoine Bruneau
*/
typedef enum { TEXT_MARCHER, /**<La texture du personnage qui marche */
                TEXT_ATTAQUE, /**<La texture du personnage qui attaque */
                TEXT_ATTAQUE_CHARGEE, /**<La texture du personnage qui fait une attaque chargée */
                TEXT_CHARGER, /**< La texture du personnage qui charge son attaque */
                TEXT_MARCHER_BOUCLIER /**<La texture du personnage qui marche avec son bouclier équipé */
             } t_texture_perso;

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
extern list *listeDeTextures; /**< La liste de toutes les textures qui ont été crées. Sert à leur destruction */
extern long int compteur; /**< Un compteur d'ips qui va de 0 à \ref NB_FPS */
extern SDL_Rect tx; /**<Rectangle servant au déplacement du personnage principal en x*/
extern SDL_Rect ty; /**<Rectangle servant au déplacement du personnage principal en y*/
extern float multiplicateur_x; /**< Multiplicateur qui dépend de la résolution (longueur), vaut 1 pour 1920 */
extern float multiplicateur_y; /**< Multiplicateur qui dépend de la résolution (largeur), vaut 1 pour 1080 */
extern t_aff * heal; /**<La texture de l'animation de heal */
extern t_aff * bloquer; /**<La texture de l'animation de blocage*/
extern t_aff * fenetre_finale; /**<La texture de la fenêtre de jeu finale sans l'interface */
extern list * liste_animations; /**<La liste des animation à jouer */

/* Définition des fonctions */

/**
 * \fn void detruire_texture(t_aff **texture)
 * \brief Fonction qui détruit une structure d'affichage de texture passée en paramètre
 * \author Despert Ange
 * 
 * Libère la mémoire allouée à la texture et la mets à NULL.
 * \param texture L'adresse du pointeur sur la structure à détruire
 */
extern void detruire_texture(t_aff **texture); /**<La liste des textures créées */

/**
 * \brief Fonction qui détruit une liste de textures
 * \author Ange Despert
 *
 * \param l_texture L'adresse de la liste de texture à détruire
 */
extern void detruire_liste_textures(t_l_aff **l_texture);

/**
 * \brief Fonction qui détermine si la structure SDL_Rect ne dépasse pas la taille de la texture.
 * \author Ange Despert
 * 
 * Cette fonction est appellée par les fonction de déplacement de frame tel que \ref next_frame_x pour s'assurer qu'il n'y a aucune erreur.   
 *
 * \param to_verify La structure SDL_Rect à vérifier
 * \param width La longueur de la texture
 * \param height La largeur de la texture
 * \return Un booléen
 */
extern _Bool rect_correct_texture(const SDL_Rect *const to_verify, const int width, const int height);

/**
 * \brief Fonction qui renvoie, charge une texture et la prépare à se faire afficher
 * \author Ange Despert 
 * 
 * Fonction qui permet de créer un texture sous forme d'un type personnalisé \ref s_aff "t_aff" qui contient pleins d'informations sur la texture. \n
 * 
 * ## Déroulement
 * Le fichier de la texture est chargé dans une surface. \n
 * 
 * On va converir cette surface en texture. \n
 * On va remplir les informations de la structure \ref s_aff "t_aff" avec les information en entrée et des informations obtenues via requêtes SDL. \n
 * Bien entendu, on testera pour être sur qu'il n'y a aucune erreur.
 * 
 * ## Lors d'une erreur
 * Contrairement à la plupart des fonctions qui gèrent les textures, celle-ci affichera surement un warning à l'écran si l'on ne peut pas créer la texture. Il est donc important de ce rendre compte que cette fonction ne ferme pas le programme lors d'une erreur. C'est donc au développeur de décider si une impossibilité de créer une texture est une raison de fermer le programme.
 * 
 * ## A noter
 * Si l'on donne -1 et -1 pour les paramètres taille_t_x et taille_t_y le rectangle \ref s_aff.frame_anim "frame_anim" de la structure \ref s_aff "t_aff" sera NULL. \n Il est donc important de prendre cela en compte pour ne pas causer des erreurs de segmentation.
 * \n Donner NULL en nom de texture ne la créra pas mais créra tout les autres attributs de la structure \ref s_aff "t_aff". \n \n
 * Donner 0 en multiplicateur de taille agrandira la texture pour qu'elle face la taille de l'écran.
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
 * \author Ange Despert
 *
 * Cette fonction permet d'afficher à l'écran une texture utilisant le type personalisé \ref s_aff "t_aff" à l'écran avec le rendu donné en paramètre. \n
 * 
 * Rien ne sera afficher si la texture donnée en entrée est égalle à NULL.
 * 
 * \param texture La texture à afficher
 * \param rendu Le rendu sur lequel afficher la texture à l'écran
 * \return 0 s'il n'y a pas eu d'erreur sinon un entier négatif
 */
extern err_t afficher_texture(t_aff *texture, SDL_Renderer *rendu);

/**
 * \fn void next_frame_y(t_aff *texture);
 * \brief Fonction qui positionne la texture au sprite d'après sur l'axe des y
 * \author Ange Despert
 *
 * Fonction qui passe au sprite suivant dans l'axe y. Cette fonction fera une boucle complête de l'image, il n'y a donc pas à s'inquiéter d'arriver à la fin de l'image. \n
 * Comme les fonction à indice, cette fonction fait appel au rectangle \ref s_aff.frame_anim "frame_anim" de la structure \ref s_aff "d'affichage".
 * \param texture* une texture joueur
 */
extern void next_frame_y(t_aff* texture);

/**
 * \fn void next_frame_x(t_aff *texture);
 * \brief Fonction qui positionne la texture au sprite d'après sur l'axe des x
 * \author Ange Despert
 * 
 * Fonction qui passe au sprite suivant dans l'axe x. Cette fonction fera une boucle complête de l'image, il n'y a donc pas à s'inquiéter d'arriver à la fin de l'image. \n
 * Comme les fonction à indice, cette fonction fait appel au rectangle \ref s_aff.frame_anim "frame_anim" de la structure \ref s_aff "d'affichage".  
 * 
 * \param texture* une texture joueur
 */
extern void next_frame_x(t_aff *texture);

/**
 * \fn void next_frame_indice(t_aff *texture, const unsigned int x, const unsigned int y);
 * \brief Fonction qui positionne la texture au n-ème sprite sur l'axe des x
 * \author Despert Ange
 *
 * Fonction qui permet de choisir le sprite a un cetain indice de l'image. \n Cette fonction est concue pour être utiliser avec une texture qui contient plusieurs sprites de même taille. \n
 * La fonction utilisera la taille du \ref s_aff.frame_anim "rectangle" charger d'afficher qu'une partie d'une image. \n
 *
 * Cette fonction est la pour éviter deux appels de fonctions, en l'ocurence \ref next_frame_x_indice et \ref next_frame_y_indice 
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
 * \author Ange Despert
 * 
 * Fonction qui permet de choisir le sprite a un cetain indice de l'image. \n Cette fonction est concue pour être utiliser avec une texture qui contient plusieurs sprites de même taille. \n
 * La fonction utilisera la taille du \ref s_aff.frame_anim "rectangle" charger d'afficher qu'une partie d'une image.
 * 
 * 
 * \param texture* une texture joueur
 * \param indice unsigned int qui correspond au n-ème sprite sur l'axe des x ou l'on souhaite positionner la texture
 * \return err_t un entier pour savoir si il y a eu une erreur
 */
extern err_t next_frame_x_indice(t_aff *texture, const unsigned int indice);

/**
 * \fn void next_frame_y_indice(t_aff *texture, const unsigned int indice)
 * \brief Fonction qui positionne la texture au n-ème sprite sur l'axe des y
 *
 * \param texture Une texture joueur
 * \param  indice Correspond au n-ème sprite sur l'axe des y ou l'on souhaite positionner la texture
 * \return err_t un entier pour savoir si il y a eu une erreur
 */
extern err_t next_frame_y_indice(t_aff *texture, const unsigned int indice);

/**
 * \fn void *ajout_text_liste(void *t)
 * \brief Fonction qui ajoute une texture dans une liste générique
 * \author Ange Despert
 *
 * Cette fonction sert juste à rérérencer les textures dans la \ref listeDeTextures "liste de textures".
 *
 * \param t une texture
 * \return void * l'element à ajouter à la liste
 */
extern void *ajout_text_liste(void *t);

/**
 * \brief Fonction qui affiche les textures contenues dans la liste en paramètre. 
 * \author Ange Despert
 * 
 * Les premiers éléments seront en arrière plan et les derniers seront en 1er plan.
 * 
 * \param buffer La liste de textures que l'on veut afficher
 * \param rendu Le rendu sur lequel on veut afficher ces textures
 * \return Une valeur différente à 0 lors d'une erreur
 */
extern err_t afficher_buffer(list *buffer, SDL_Renderer *rendu);

/**
 * \brief Déplace la texture pour que son centre soit au centre de l'écran
 * \author Ange Despert
 *
 * \deprecated Cette fonction ne devrait plus être appelée car elle aurait un comportement imprévisible. \n Utilisez \ref place_rect_center_from_point à l'aide du rectangle \ref s_aff.frame_anim "frame_anim" de la varaible \ref fenetre_finale .
 * 
 * @param texture la texture à déplacer
 * @param x La coordonnée x du centre de la texture.
 * @param y La coordonnée y du centre de la texture.
 */
extern void deplacer_texture_centre(t_aff *texture, int x, int y);

/**
 * \brief Déplace un rectangle depuis l'origine de l'écran
 * 
 * \author Ange Despert
 * \param r Le rectangle à déplacer
 * \param x La position horizontale du rectangle
 * \param y La position verticale du rectangle
 * \return Une valeur différente à 0 lors d'une erreur
 */
extern void deplacer_rect_origine(SDL_Rect *r, int x, int y);

/**
 * \brief Déplace l'origine de la texture aux coordonnées données.
 *
 * \author Ange Despert
 * \param texture La texture à déplacer
 * \param x La coordonnée x de l'origine de la texture.
 * \param y La coordonnée y de l'origine de la texture.
 */
extern void deplacer_texture_origine(t_aff *texture, int x, int y);

/**
 * \brief Place un rectangle en haut à droite de l'écran puis le replace à partir de cette origine
 * \author Ange Despert
 * 
 * @param r Le rectangle à placer
 * @param x La coordonnée x du rectangle depuis la nouvelle origine.
 * @param y La coordonnée y du rectangle depuis la nouvelle origine.
 */
extern void deplacer_rect_haut_droit(SDL_Rect *r, int x, int y);

/**
 * \brief La texture est déplacée vers la droite et vers le haut
 * \author Ange Despert
 * 
 * @param texture la texture à déplacer
 * @param x La coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche du rectangle.
 */
extern void deplacer_texture_haut_droit(t_aff *texture, int x, int y);

/**
 * \brief La texture est déplacée vers le coin inférieur gauche de l'écran
 * \author Ange Despert
 * 
 * @param texture la texture à déplacer
 * @param x La coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche de la texture.
 */
extern void deplacer_texture_bas_gauche(t_aff *texture, int x, int y);

/**
 * \brief La texture est déplacée vers le coin inférieur droit de la fenêtre
 * \author Ange Despert
 * 
 * @param texture la texture à déplacer
 * @param x Coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche de la texture.
 */
extern void deplacer_texture_bas_droit(t_aff *texture, int x, int y);

/**
 * \brief Modifie le rectangle qui définit la zone de l'écran qui sera utilisée pour le rendu de la texture
 * \author Ange Despert
 * 
 * @param texture La texture à modifier.
 * @param r Le rectangle à appliquer.
 */
extern void modif_affichage_rect(t_aff *texture, SDL_Rect r);

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
 * \brief Fonction qui renvoie la texture de départ du personnage (joueur)
 * \author Antoine Bruneau
 * \param textures_joueur Liste de textures personnage
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
 * \brief Permet de déplacer le personnage de x unités horizontales sur la map
 * \author Ange Despert
 *
 * Cette fonction utilise un rectangle \ref tx pour savoir quand elle doit bouger le personnage ou bien déplacer la camera. \n
 * Elle prendra en compte les collisions de la \ref s_map.liste_collisions "liste de collisions de la map". \n
 * Elle empêche le personnage de sortir des bordures de la map. \n
 * 
 * \param map La map sur laquelle le personnage se déplace
 * \param joueurs Les joueurs en jeu
 * \param nb_joueurs Le nombre de joueurs en jeu
 * \param x Le nombre d'unités de déplacements
 * \param objets Les objets du jeu
 * \return vrai : Si le joueur s'est téléporté
 * \return faux : Si le joueur ne s'est pas téléporté
 */
extern bool deplacement_x_pers(t_map *map, joueur_t ** joueurs, unsigned short int nb_joueurs, int x, lobjet_t * objets);

/**
 * \brief Permet de déplacer le personnage principal de y unités verticales sur la map
 * \author Ange Despert
 * 
 * Cette fonction utilise un rectangle \ref ty pour savoir quand elle doit bouger le personnage ou bien déplacer la camera. \n
 * Elle prendra en compte les collisions de la \ref s_map.liste_collisions "liste de collisions de la map". \n
 * Elle empêche le personnage de sortir des bordures de la map. \n
 * 
 * \param map La map sur laquelle le personnage se déplace
 * \param joueurs Les joueurs en jeu
 * \param nb_joueurs Le nombre de joueurs en jeu
 * \param y Le nombre d'unités de déplacements
 * \param objets Les objets du jeu
 * \return vrai : Si le joueur s'est téléporté
 * \return faux : Si le joueur ne s'est pas téléporté
 */
extern bool deplacement_y_pers(t_map *map, joueur_t ** joueurs, unsigned short int nb_joueurs, int y, lobjet_t * objets);

/**
 * \brief Permet de déplacer un joueur secondaire de y unités verticales sur la map
 *
 * \param map La map sur laquelle le personnage se déplace
 * \param joueur Le joueur qui se déplace
 * \param y Le nombre d'unités de déplacements
 * \param r La zone de collision du joueur
 * \param objets Les objets du jeu
 * \return vrai : Si le joueur a réussi à se déplacer
 * \return faux : Si le joueur n'a pas pu se déplacer
 */
extern bool deplacement_y_joueur_secondaire(t_map *map, joueur_t * joueur, int y, SDL_Rect *r, lobjet_t * objets);

/**
 * \brief Permet de déplacer un joueur secondaire de x unités horizontales sur la map
 *
 * \param map La map sur laquelle le personnage se déplace
 * \param joueur Le joueur qui se déplace
 * \param x Le nombre d'unités de déplacements
 * \param r La zone de collision du joueur
 * \param objets Les objets du jeu
 * \return vrai : Si le joueur a réussi à se déplacer
 * \return faux : Si le joueur n'a pas pu se déplacer
 */
extern bool deplacement_x_joueur_secondaire(t_map *map, joueur_t * joueur, int x, SDL_Rect *r, lobjet_t * objets);

/**
 * \brief Fonction qui permet de définir exactement la taille de la texture
 * \author Ange Despert
 * 
 * \deprecated L'utilisation de cette fonction n'a plus trop de sens étant donné que le moteur gère automatiquement la taille des textures.
 * 
 * Fonction qui permet de modifier le rectangle de la structure \ref s_aff "t_aff" : \ref s_aff.aff_fenetre "aff_fenetre" avec de nouvelles valeurs. 
 * 
 * \param a_modifier La texture à modifier
 * \param longueur La nouvelle longueure en pixel à appliquer
 * \param largeur La nouvelle largeur en pixel à appliquer
 */
extern void def_texture_taille(t_aff *a_modifier, const int longueur, const int largeur);

/**
 * \brief Fonction qui permet de placer 2 textures aux mêmes endroit à l'écran
 * 
 * \author Max Descomps
 * \param a_modifier La texture dont on veut modifier la position
 * \param original La texture dont on veut copier la position
 */
extern void text_copier_position(t_aff *a_modifier, const t_aff *const original);

/**
 * \brief Fonction qui permet de placer un rectangle au centre de l'écran sur l'axe des x
 * \author Ange Despert
 *
 * \deprecated Cette fonction ne devrait plus être appelée car elle aurait un comportement imprévisible. \n Utilisez \ref place_rect_center_from_point à l'aide du rectangle \ref s_aff.frame_anim "frame_anim" de la varaible \ref fenetre_finale .
 *
 * \param rectangle Le rectangle à placer
 */
extern void rect_centre_x(SDL_Rect *rectangle);

/**
 * \brief Fonction qui permet de placer un rectangle au centre de l'écran sur l'axe des y
 * \author Ange Despert
 *
 * \deprecated Cette fonction ne devrait plus être appelée car elle aurait un comportement imprévisible. \n Utilisez \ref place_rect_center_from_point à l'aide du rectangle \ref s_aff.frame_anim "frame_anim" de la varaible \ref fenetre_finale .
 *
 * \param rectangle Le rectangle à placer
 */
extern void rect_centre_y(SDL_Rect *rectangle);

/**
 * \brief Fonction qui permet de placer un rectangle au centre de l'écran
 * \author Ange Despert
 *
 * \deprecated Cette fonction ne devrait plus être appelée car elle aurait un comportement imprévisible. \n Utilisez \ref place_rect_center_from_point à l'aide du rectangle \ref s_aff.frame_anim "frame_anim" de la varaible \ref fenetre_finale .
 *
 * \param rectangle Le rectangle à placer
 * \return Un booléen
 */
extern void rect_centre(SDL_Rect *rectangle);

/**
 * \brief Fonction qui permet de savoir si deux rectangles sont égaux sur l'axe x
 * \author Ange Despert
 *
 * Cette fonction permet de savoir si deux rectangles sont égaux mais en prenant seulement en compte l'axe x. \n
 * Cette fonction est utilisée par la fonction \ref deplacement_x_pers "la fonction de déplacement de personnage".
 * \param r1 Le premier rectangle à comparer
 * \param r2 Le deuxième rectangle à comparer
 * \return Un booléen
 */
extern bool rects_egal_x(const SDL_Rect *const r1, SDL_Rect const *const r2);

/**
 * \brief Fonction qui permet de savoir si deux rectangles sont égaux sur l'axe y
 * \author Ange Despert
 * 
 * Cette fonction permet de savoir si deux rectangles sont égaux mais en prenant seulement en compte l'axe y. \n
 * Cette fonction est utilisée par la fonction \ref deplacement_y_pers "la fonction de déplacement de personnage".
 * 
 * \param r1 Le premier rectangle à comparer
 * \param r2 Le deuxième rectangle à comparer
 * \return Un booléen
 */
extern bool rects_egal_y(const SDL_Rect *const r1, SDL_Rect const *const r2);

/**
 * \fn SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
 * \brief Fonction qui permet de choisir une couleur SDL
 * \author Max Descomps
 * \param r niveau de rouge
 * \param g niveau de vert
 * \param b niveau de bleu
 * \param a niveau d'opacité
 * \return SDL_Color une couleur SDL
 */
extern SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/**
 * \fn void info_texture(t_aff * texture)
 * \brief Affiche des informations en console sur une texture
 * \author Max Descomps
 * \param texture la texture sur laquelle on se renseigne
 */
extern void info_texture(t_aff * texture);

/**
 * \fn int current_frame_x(t_aff * texture);
 * \brief Fonction qui donne l'indice sur l'axe des abscisses actuelle de la texture 
 * \author Bruneau Antoine
 * \param texture une texture
 * \return int un entier correspondant à l'indice
 */
extern int current_frame_x(t_aff * texture);

/**
 * \fn int current_frame_y(t_aff * texture);
 * \brief Fonction qui donne l'indice sur l'axe des ordonnées actuelle de la texture 
 * \author Bruneau Antoine
 * \param texture une texture
 * \return int un entier correspondant à l'indice
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
 * \author Max Descomps
 * \param texture Texture à placer
 * \param x Position horizontale
 * \param y Position verticale
 */
extern void placer_texture(t_aff *texture, int x, int y);

/**
 * \fn void init_animations(void)
 * \brief Initialise les textures des animations
 * \author Max Descomps
 */
extern void init_animations(void);

/**
 * \fn t_aff * next_frame_animation(joueur_t * joueur)
 * \brief Fait évoluer les animations en jeu
 * \author Max Descomps
 * \param joueur Le joueur sur lequel placer l'animation
 * \return La texture de l'animation
 */
extern t_aff * next_frame_animation(joueur_t * joueur);

/**
 * \fn void lister_animations(joueur_t ** joueurs, list * animations)
 * \brief Liste les animations en jeu
 * \author Max Descomps
 * \param joueurs Les joueurs sur lesquels placer les animation
 * \param animations Liste regroupant les animations trouvées
 */
extern void lister_animations(joueur_t ** joueurs, list * animations);

/**
* \fn void afficher_coffres(list * liste_coffre)
 * \brief Fonction qui affiche la texture des coffres
 * \author Max Descomps
 * \param liste_coffre Une liste de coffres
 */
extern void afficher_coffres(list * liste_coffre);

/**
 * \brief Fonction qui permet de placer un rectangle au centre d'un autre sur l'axe des x
 * \author Ange Despert
 *
 * Fonction qui fonctionne de la même manière que la fonction \ref rect_centre_rect mais permet de seulement centrer l'axe x.
 * \param rectangle Le rectangle à centrer
 * \param rectangle_centre Le rectangle dans lequel en centre un autre
 */
extern void rect_centre_rect_x(SDL_Rect *rectangle, SDL_Rect *rectangle_centre);

/**
 * \brief Fonction qui permet de placer un rectangle au centre d'un autre sur l'axe des y
 * \author Ange Despert
 * 
 * Fonction qui fonctionne de la même manière que la fonction \ref rect_centre_rect mais permet de seulement centrer l'axe y.
 * 
 * \param rectangle Le rectangle à centrer
 * \param rectangle_centre Le rectangle dans lequel en centre un autre
 */
extern void rect_centre_rect_y(SDL_Rect *rectangle, SDL_Rect *rectangle_centre);

/**
 * \brief Fonction qui permet de placer un rectangle au centre d'un autre
 * \author Ange Despert 
 * 
 * Fonctionnement simillaire à l'utilisation conjointe des fonctions \ref place_rect_center_from_point et \ref get_rect_center_coord .
 * 
 * \param rectangle Le rectangle à centrer
 * \param rectangle_centre Le rectangle dans lequel en centre un autre
 */
extern void rect_centre_rect(SDL_Rect *rectangle, SDL_Rect *rectangle_centre);

/**
* \fn void afficher_animations(list * animations)
 * \brief Fonction qui affiche la texture des animations
 * \author Max Descomps
 * \param animations Une liste d'animations
 */
extern void afficher_animations(list * animations);

/**
 * \brief Fonction qui permet le déplacement d'une entité
 * \author Ange Despert
 *
 * Cette fonction permet à une entité de se déplacer sur l'axe x. \n
 * Cette fonction gère les collisions et empêchera l'entité de sortir des limites de la map. \n
 * Cette dernière prend également les collisions définies dans la liste des collisions de la map : \ref s_map.liste_collisions "liste_collisions".  \n
 *
 * Il est a noté que pour éviter les déplacement trop rapides la fonction utilise l'entier \ref s_aff.duree_frame_anim "duree_frame_anim" qui permet d'êmpécher le déplacement tout les x frames. \n
 *
 * On peut récupérer l'élément que l'entité a touché en regardant l'élément courant de la \ref s_map.liste_collisions "liste de collisions" de la map.
 * 
 * \param m La map actuelle
 * \param texture La texture de l'entité que l'on veut bouger
 * \param x La nouvelle coordonnée du rectangle de l'entité
 * \param r Le rectangle représentant la zone de collision de l'entité
 * \return vrai : Si l'entité a réussi à se déplacer
 * \return faux : Si l'entité n'a pas pu se déplacer
 */
extern bool deplacement_x_entite(t_map *m, t_aff *texture, int x, SDL_Rect *r);

/**
 * \brief Fonction qui permet le déplacement d'une entité
 * \author Ange Despert
 * 
 * Cette fonction permet à une entité de se déplacer sur l'axe y. \n
 * Cette fonction gère les collisions et empêchera l'entité de sortir des limites de la map. \n
 * Cette dernière prend également les collisions définies dans la liste des collisions de la map : \ref s_map.liste_collisions "liste_collisions".  \n
 *
 * Il est a noté que pour éviter les déplacement trop rapides la fonction utilise l'entier \ref s_aff.duree_frame_anim "duree_frame_anim" qui permet d'êmpécher le déplacement tout les x frames. \n
 * 
 * On peut récupérer l'élément que l'entité a touché en regardant l'élément courant de la \ref s_map.liste_collisions "liste de collisions" de la map.
 *
 * \param m La map actuelle
 * \param texture La texture de l'entité que l'on veut bouger
 * \param y La nouvelle coordonnée du rectangle de l'entité
 * \param r Le rectangle représentant la zone de collision de l'entité
 * \return vrai : Si l'entité a réussi à se déplacer
 * \return faux : Si l'entité n'a pas pu se déplacer
 */
extern bool deplacement_y_entite(t_map *m, t_aff *texture, int y, SDL_Rect *r);

/**
* \fn void detruire_collision_dans_liste(list * liste_collisions, SDL_Rect * collision)
 * \brief Fonction qui détruit une collision donnée dans une liste de collisions
 * \param liste_collisions Une liste de collisions
 * \param collision La collision à détruire dans la liste
 */
extern void detruire_collision_dans_liste(list * liste_collisions, SDL_Rect * collision);

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