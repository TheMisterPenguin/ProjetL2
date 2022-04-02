#include <liste_objet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inventaire.h>

/**
 * \file liste_objet.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonctions relatives aux structures contenant les objets
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

lobjet_t * objets = NULL;

//creer la structure contenant la liste des objets avec au maximum CAPACITE_SAC objets
lobjet_t * creer_liste_objet(char * fichier_src){
    lobjet_t * liste_obj; //le pointeur sur structure contenant la liste d'objets que la fonction retourne
    FILE * obj; //fichier source contenant les objets


    t_item type;
    char nom[50];
    int i = 0;
    int niveau, att, def, vit;
    char c;
    int nb_obj = 0; //nombre d'objets dans le fichier source
    char imgsrc[100];

    if(( liste_obj= malloc(sizeof(lobjet_t))) == NULL )
    {
      fprintf( stderr , "creer_liste_objet: debordement memoire lors de la creation d'une structure lobjet_t\n");
      return((lobjet_t *)NULL);
    }

    obj = fopen(fichier_src, "r");

    if(obj == NULL){
        fprintf( stderr, "fichier source objet inaccessible\n") ;
        return((lobjet_t*)NULL);
    }

    liste_obj->nb = 0;
    liste_obj->liste = (objet_t **)NULL ;

    //compte les objets (1 par ligne)
    while(fscanf(obj, "%c", &c) == 1){
        if(c == ';') nb_obj++;
        if(nb_obj > CAPACITE_SAC){
            nb_obj = CAPACITE_SAC;
            break;
        }
    }

    fseek(obj,0,SEEK_SET); // le pointeur du fichier pointe à son début

    if( nb_obj > 0 ){
        if( (liste_obj->liste = malloc(sizeof(objet_t*) * nb_obj)) == NULL ){
            fprintf( stderr , "init_objet: debordement memoire lors de la creation d'une liste de [%d] liste_obj\n",
                nb_obj ) ;
            return((lobjet_t*)NULL);
        }


        while((fscanf(obj, "%s%d%49[^:]:%d%d%d%d;", imgsrc, (int *)&type, nom, &niveau, &att, &def, &vit) == 7) && i<nb_obj){
            liste_obj->liste[i] = creer_objet(imgsrc, type, nom, niveau, att, def, vit);
            i++;
        }

        liste_obj->nb = nb_obj;
    }

    fclose(obj);

    return liste_obj;
}

//creer une structure lobjet_t vide d'objets de maximum CAPACITE_SAC objets
lobjet_t * creer_liste_objet_vide(char * fichier_src){
    lobjet_t * liste_obj; //le pointeur sur structure contenant la liste d'objets que la fonction retourne
    FILE * obj; //fichier source contenant les objets

    int i;
    char c;
    int nb_obj = 0; //nombre d'objets dans le fichier source

    if(( liste_obj= malloc(sizeof(lobjet_t))) == NULL )
    {
      fprintf( stderr , "creer_liste_objet: debordement memoire lors de la creation d'une structure lobjet_t\n");
      return((lobjet_t *)NULL);
    }

    obj = fopen("../ressource/objet.txt", "r");

    if(obj == NULL){
        fprintf( stderr, "fichier source objet inaccessible\n") ;
        return((lobjet_t*)NULL);
    }

    liste_obj->nb = 0;
    liste_obj->liste = (objet_t **)NULL ;

    //compte les objets (1 par ligne)
    while(fscanf(obj, "%c", &c) == 1){
        if(c == ';') nb_obj++;
        if(nb_obj > CAPACITE_SAC){
            nb_obj = CAPACITE_SAC;
            break;
        }
    }
    fclose(obj);

    if( nb_obj > 0 ){
        if( (liste_obj->liste = malloc(sizeof(objet_t*) * nb_obj)) == NULL ){
            fprintf( stderr , "init_objet: debordement memoire lors de la creation d'une liste de [%d] liste_obj\n",
                nb_obj ) ;
            return((lobjet_t*)NULL);
        }

        for(i=0; i<nb_obj; i++){
            liste_obj->liste[i] = NULL;
        }
    }
    return liste_obj;
}

//creer une structure lobjet_t de 5 objets (un de chaque type)
lobjet_t * creer_liste_objet_equipe(){
    lobjet_t * liste_obj; //le pointeur sur structure contenant la liste d'objets que la fonction retourne

    int i;
    int nb_obj = NB_TYPE_OBJ; //nombre d'objets à contenir

    if(( liste_obj= malloc(sizeof(lobjet_t))) == NULL )
    {
      fprintf( stderr , "creer_liste_objet: debordement memoire lors de la creation d'une structure lobjet_t\n");
      return((lobjet_t *)NULL);
    }

    liste_obj->nb = 0;
    liste_obj->liste = (objet_t **)NULL ;

    if( (liste_obj->liste = malloc(sizeof(objet_t*) * nb_obj)) == NULL ){
            fprintf( stderr , "init_objet: debordement memoire lors de la creation d'une liste de [%d] liste_obj\n",
                nb_obj ) ;
            return((lobjet_t*)NULL);
        }

        for(i=0; i<nb_obj; i++){
            liste_obj->liste[i] = NULL;
        }

    return liste_obj;
}

/*
 * Destruction d'une liste d'objets
 */

void detruire_liste_objet( lobjet_t ** liste_obj)
{
     int i = 0;

    /*on detruit les objet_t de la liste lobjet_t*/
    while(i < (*liste_obj)->nb){
        detruire_objet((*liste_obj)->liste+i);
    i++;
    }

    free((*liste_obj)->liste);
    (*liste_obj)->liste = NULL;

    /*on detruit lobjet_t*/
    free(*liste_obj);
    *liste_obj = NULL;
}

/*
 * Effacement d'une liste d'objets vide (destruction superficielle)
 */

void effacer_liste_objet( lobjet_t ** liste_obj)
{
    free((*liste_obj)->liste);
    (*liste_obj)->liste = NULL;

    /*on detruit lobjet_t*/
    free(*liste_obj);
    *liste_obj = NULL;
}

/*
 * Affichage d'une liste contenue dans une structure lobjet_t
 */

void afficher_liste_objet( lobjet_t * const liste_obj )
{
    int num_obj, next_obj ;
    int tt_obj ;

    if( liste_obj == NULL )
    {
        printf("(liste d'objets inexistante)\n" );
        return ;
    }

    tt_obj = liste_obj->nb ;

    if( tt_obj == 0 )
    {
        printf("(liste d'objets vide)\n" );
        return ;
    }

    printf( "Nombre d'objets: %d\n" , tt_obj );
    printf( "{ " ) ;
    for( num_obj=0, next_obj=0 ; num_obj<tt_obj && next_obj<CAPACITE_SAC ; num_obj++, next_obj++ )
    {
        //on cherche le prochain objet dans la liste
        while(liste_obj->liste[next_obj] == NULL && next_obj < CAPACITE_SAC)
            next_obj++;

        //si on n'est pas sorti de la liste
        if(next_obj<CAPACITE_SAC){
            afficher_objet(liste_obj->liste[next_obj]);
            printf("\n");
        }
    }
    printf( " }\n" ) ;
}

void placer_objet_sac(objet_t * objet, int slot){
    placer_texture(objet->texture, 285+((slot%5) * 73), 317+((slot/5) * 61));
}

void afficher_textures_sac( inventaire_t * const inventaire )
{
    int num_obj, next_obj, slot ;
    int tt_obj ;

    if( inventaire == NULL )
    {
        printf("inventaire inexistant\n" );
        return ;
    }

    tt_obj = inventaire->sac->nb ;

    for( num_obj=0, next_obj=0, slot=0 ; num_obj<tt_obj && next_obj<CAPACITE_SAC ; num_obj++, next_obj++, slot++)
    {
        //on cherche le prochain objet dans la liste
        while(inventaire->sac->liste[next_obj] == NULL && next_obj < CAPACITE_SAC)
            next_obj++;
        
        //si on n'est pas sorti de la liste
        if(next_obj<CAPACITE_SAC){
            placer_objet_sac(inventaire->sac->liste[next_obj], slot);
            afficher_texture(inventaire->sac->liste[next_obj]->texture, rendu_principal);
        }
    }
}

void afficher_textures_equipe( inventaire_t * const inventaire )
{
    int type_obj;
    objet_t * objet = NULL;

    if( inventaire == NULL )
    {
        printf("inventaire inexistant\n" );
        return ;
    }

    for( type_obj=0; type_obj<NB_TYPE_OBJ ; type_obj++)
    {
        objet = inventaire->equipe->liste[type_obj];
        if(objet != NULL){
            switch(type_obj){
                case quete:
                    deplacer_rect_origine(objet->texture->aff_fenetre, floor(696 * multiplicateur_x), floor(292 * multiplicateur_y));
                    break;
                case arme:
                    deplacer_rect_origine(objet->texture->aff_fenetre, floor(662 * multiplicateur_x), floor(435 * multiplicateur_y));
                    break;
                case bouclier:
                    deplacer_rect_origine(objet->texture->aff_fenetre, floor(1163 * multiplicateur_x), floor(432 * multiplicateur_y));
                    break;
                case protection:
                    deplacer_rect_origine(objet->texture->aff_fenetre, floor(916 * multiplicateur_x), floor(350 * multiplicateur_y));
                    break;
                case consommable: deplacer_rect_origine(objet->texture->aff_fenetre, floor(1126 * multiplicateur_x), floor(293 * multiplicateur_y)); break;
                case amulette: deplacer_rect_origine(objet->texture->aff_fenetre, floor(913 * multiplicateur_x), floor(134 * multiplicateur_y)); break;
            }
            afficher_texture(objet->texture, rendu_principal);
        }
    }
}

void creer_textures_objets(lobjet_t * liste_obj){
    int i;

    for(i=0; i<liste_obj->nb; i++){
        liste_obj->liste[i]->texture = creer_texture(liste_obj->liste[i]->texture_src, 46, 48, 0, 0, ((FENETRE_LONGUEUR * 0.022f) / 16 * 0.8) * multiplicateur_y);
    }
}