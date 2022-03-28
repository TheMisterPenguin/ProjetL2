#include <liste_objet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inventaire.h>

lobjet_t * objets = NULL;

//creer la structure contenant la liste des objets
lobjet_t * creer_liste_objet(){
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
    }

    fseek(obj,0,SEEK_SET); // le pointeur du fichier pointe à son début

    if( nb_obj > 0 ){
        if( (liste_obj->liste = malloc(sizeof(objet_t*) * nb_obj)) == NULL ){
            fprintf( stderr , "init_objet: debordement memoire lors de la creation d'une liste de [%d] liste_obj\n",
                nb_obj ) ;
            return((lobjet_t*)NULL);
        }


        while(fscanf(obj, "%s%d%49[^:]:%d%d%d%d;", imgsrc, (int *)&type, nom, &niveau, &att, &def, &vit) == 7){
            liste_obj->liste[i] = creer_objet(imgsrc, type, nom, niveau, att, def, vit);
            i++;
        }

        liste_obj->nb = nb_obj;
    }

    fclose(obj);

    return liste_obj;
}

//creer une structure lobjet_t vide d'objets
lobjet_t * creer_liste_objet_vide(){
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
    int nb_obj = 5; //nombre d'objets à contenir

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
    int i ;
    int nb_obj ;

    if( liste_obj == NULL )
    {
        printf("(liste d'objets inexistante)\n" );
        return ;
    }

    nb_obj = liste_obj->nb ;

    if( nb_obj == 0 )
    {
        printf("(liste d'objets vide)\n" );
        return ;
    }

    printf( "Nombre d'objets: %d\n" , nb_obj );
    printf( "{ " ) ;
    for( i=0 ; i<nb_obj ; i++ )
    {
        while(liste_obj->liste[i] == NULL)
            i++;
        afficher_objet(liste_obj->liste[i]);
        printf("\n");
    }
    printf( " }\n" ) ;
}

void placer_objet_sac(objet_t * objet, int slot){
    placer_texture(objet->texture, 285+((slot%5) * 73), 317+((slot/5) * 61));
}

void afficher_textures_sac( inventaire_t * const inventaire )
{
    int i, j ;
    int nb_obj ;

    if( inventaire == NULL )
    {
        printf("inventaire inexistant\n" );
        return ;
    }

    nb_obj = inventaire->sac->nb ;

    if( nb_obj != 0 ){
        for( i=0, j=0 ; i<nb_obj ; i++, j++)
        {
            while(inventaire->sac->liste[i] == NULL)
                i++;
            placer_objet_sac(inventaire->sac->liste[i], j);
            afficher_texture(objets->liste[i]->texture, rendu_principal);
        }
    }
}

void afficher_textures_equipe( inventaire_t * const inventaire )
{
    int i;
    objet_t * objet = NULL;

    if( inventaire == NULL )
    {
        printf("inventaire inexistant\n" );
        return ;
    }

    for( i=1; i<5 ; i++)
    {
        objet = inventaire->equipe->liste[i];
        if(objet != NULL){
            switch(i){
                case arme: placer_texture(objet->texture, 312, 205); break;
                //faire les autres types d'objets
            }
            afficher_texture(objet->texture, rendu_principal);
        }
    }
}