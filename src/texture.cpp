#include <SDL2/SDL.h>
#include <string>
#include <definition_commun.h>
#include <utils.h>

namespace BloodySanada {
    class Texture {
        private:
            SDL_Texture *visual_texture;
            SDL_Rect texture_selection;
            int sizeX, sizeY;
            int pixelsX, pixelsY;
        
        public:
            Texture(const char *path_to_texture) : Texture(std::string(path_to_texture)) {}

            Texture(std::string path_to_texture){
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
                    free(visual_texture);
                    throw ERREUR_FICHIER;
                }

                if(SDL_QueryTexture(visual_texture, NULL, NULL, &pixelsX, &pixelsY)){
                    warning("Erreur lors de la création de la texture : %s", ERREUR_FICHIER, SDL_GetError());
                    free(visual_texture);
                    throw ERREUR_FICHIER;
                }   
        }
    };
} // namespace BloodySanada
