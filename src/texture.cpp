#include <SDL2/SDL.h>
#include <string>
#include <utils.h>


namespace BloodySanada {
    class Texture {
    private:
        SDL_Texture *visual_texture;
        SDL_Rect texture_selection;
        int sizeX, sizeY;
        int pixelsX, pixelsY;
    
    public:
        Texture(const char *path_to_texture, SDL_Renderer *rendu) : Texture(std::string(path_to_texture, rendu)) {}

        Texture(std::string path_to_texture, SDL_Renderer *rendu){
            SDL_Surface * chargement = NULL;

            /* Chargement de la texture dans une surface */
            path_to_texture += std::string(execDir);

            log_debug("Création de la texture à partir du fichier : '%-75s', adresse : %p", path_to_texture.c_str(), this);

            chargement = SDL_LoadBMP(path_to_texture.c_str());
            if(! chargement){
                warning("Erreur lors de la création de la texture : %s", ERREUR_FICHIER, SDL_GetError());
                throw ERREUR_FICHIER;
            }

            /* Copie de la ressource dans une structure SDL_Texture */
            visual_texture = SDL_CreateTextureFromSurface(rendu_principal, chargement);
            SDL_FreeSurface(chargement); 
            if(! visual_texture){
                warning("Erreur lors de la création de la texture : %s", ERREUR_FICHIER, SDL_GetError());
                throw ERREUR_FICHIER;
            }

            if(SDL_QueryTexture(visual_texture, NULL, NULL, &pixelsX, &pixelsY)){
                warning("Erreur lors de la création de la texture : %s", ERREUR_FICHIER, SDL_GetError());
                throw ERREUR_FICHIER;
            }   
        }

        ~Texture(){
            /* On désalloue la SDL_Texture*/
            SDL_DestroyTexture(visual_texture);
        }

        bool changeSize(const int width, const int height){
            sizeX = width;
            sizeY = height;

            return true;
        }

        bool changeWidth(const int width){return changeSize(width, sizeY);}

        bool changeHeight(const int height){return changeSize(sizeX, height);}
    };
} // namespace BloodySanada
