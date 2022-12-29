#include <SDL.h>
#include <macros.h>

typedef struct texture {
    SDL_Texture *texture;  /**<Texture utilisée*/
    SDL_Rect *picker_rect;  /**<Désigne la zone de la texture à afficher*/
    SDL_Rect *display_rect; /**<Désigne l'emplacement et la taille de l'objet à l'écran */
    int width; /**< Longueur de la texture */
    int height; /**< Hauteur de la texture */
    float x_multiplier; /**<Sauvegarde du multiplicateur de taille de la texture*/
    float y_multiplier;
    /*unsigned int duree_frame_anim; /**<Durée d'une frame*/
    /*unsigned int compteur_frame_anim; /**<Stade de l'animation*/
}texture;

texture * textureFromSDLTexture(SDL_Texture *_in){
    texture *_return = NULL;
    allocate(_return, sizeof(texture));

    if(!_in){
        free(_return);
        return (NULL);
    }

    _return->texture = _in;
    _return->picker_rect = NULL;
    _return->display_rect = NULL;

    if(SDL_QueryTexture(_in, NULL, NULL, _return->width, _return->height))
        erreur("Erreur lors de la création de la texture %s", ERREUR_TEXTURE, SDL_GetError());

    _return->x_multiplier = 0;
    _return->y_multiplier = 0;

    return (_return);
}

texture * textureFromPath(char * _file_path){
    texture *_return = NULL;
    allocate(_return, sizeof(texture));

    if (!_file_path){
        free(_return);
        return (NULL);
    }

    _return->texture = SDL_bmp;
    _return->picker_rect = NULL;
    _return->display_rect = NULL;

    if (SDL_QueryTexture(_in, NULL, NULL, _return->width, _return->height))
        erreur("Erreur lors de la création de la texture %s", ERREUR_TEXTURE, SDL_GetError());

    _return->x_multiplier = 0;
    _return->y_multiplier = 0;

    return (_return);
}