#include <affichage.h>

void RenderHPBar(int x, int y, int w, int h, float pourcent, SDL_Color vie, SDL_Color jauge) {
    int pw;

    if(pourcent>1) pourcent = 1;
    else if(pourcent<0) pourcent = 0;
    pw = (int)(pourcent * (float)w);
    
    SDL_Color base;
    SDL_GetRenderDrawColor(rendu_principal, &base.r, &base.g, &base.b, &base.a);
    
    SDL_Rect bgrect = { x-4, y-4, w+8, h+8 };
    SDL_SetRenderDrawColor(rendu_principal, jauge.r, jauge.g, jauge.b, jauge.a);
    SDL_RenderFillRect(rendu_principal, &bgrect);
    SDL_SetRenderDrawColor(rendu_principal, vie.r, vie.g, vie.b, vie.a);

    SDL_Rect fgrect = { x, y, pw, h };
    SDL_RenderFillRect(rendu_principal, &fgrect);
    SDL_SetRenderDrawColor(rendu_principal, base.r, base.g, base.b, base.a);
}