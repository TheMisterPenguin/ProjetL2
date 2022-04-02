/**
 * \file test_SDL.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test des fonctions principales de la SDL
 * \version 0.1
 * \date 1/04/2022
 * \copyright Copyright (c) 2022
 */

#include "definition_commun.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;
SDL_Window *fenetre_Principale;
SDL_Renderer *rendu_principal;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void test_SDL_init(void) {
    SDL_DisplayMode m;

    CU_ASSERT_EQUAL(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER), 0);
    CU_ASSERT_EQUAL(SDL_GetCurrentDisplayMode(0, &m), 0);
    FENETRE_LONGUEUR = m.w;
    FENETRE_LARGEUR = m.h;
    CU_ASSERT_NOT_EQUAL(fenetre_Principale = SDL_CreateWindow("Test SDL", 0, 0, FENETRE_LONGUEUR, FENETRE_LARGEUR, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL), NULL);
    CU_ASSERT_NOT_EQUAL(SDL_CreateRenderer(fenetre_Principale, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE), NULL);
}

void test_SDL_close(void) {
    SDL_DestroyRenderer(rendu_principal);
    CU_ASSERT_EQUAL(rendu_principal, NULL);
}


int main(){
    
    CU_pSuite pSuite = NULL;
    
    if ( CUE_SUCCESS != CU_initialize_registry() )
        return CU_get_error();

    pSuite = CU_add_suite( "SDL_test_suite", init_suite, clean_suite );
    if ( NULL == pSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ( (NULL == CU_add_test(pSuite, "test_SDL_init", test_SDL_init)) ||
        (NULL == CU_add_test(pSuite, "test_SDL_close", test_SDL_close))
        )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    SDL_DestroyWindow(fenetre_Principale);
    SDL_Quit();

    CU_cleanup_registry();
    return CU_get_error();
}