#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

#include <definition_commun.h>
#include <macros.h>
#include <code_erreur.h>

#ifndef _WIN32
	#include <pwd.h>
	#include <unistd.h>
#else
	#include <direct.h>
	#include <windows.h>
#endif

FILE *logFile = NULL;

bool debug = faux;
char *save_path = NULL;


const char * get_home_path(void){
#ifndef _WIN32 /* Plateforme UNIX */ 
    return (getpwuid(getuid())->pw_dir);
#else /* Platefrome WINDOWS NT */
    return (getenv("HOMEPATH"));
#endif
}

bool dir_exist(const char *dirPath){
    struct stat stats;

    stat(dirPath, &stats); /* On récupère les informations sur l'élément */

    return (S_ISDIR(stats.st_mode)); /* On regarde s'il s'agit d'un répertoire existant */
}

err_t create_dir(const char * const dirPath){
    int error = 0;

#ifdef _WIN32
    error = mkdir(dirPath);
#else
    error = mkdir(dirPath, S_IRWXU);
#endif

    if(error){
        if(errno == EEXIST)
            return (1);
        else
            return (-1);
    }

    if(dir_exist(dirPath))
        return (EXIT_SUCCESS);

    return (-1);
}

char *get_path_to_save_folder(const char *pathFromHome){
    char *newPath = NULL;

#ifndef _WIN32
    const char *dir = "/Bloody Sanada";
#else
    const char *dir = "\\AppData\\Local\\Bloody Sanada";
#endif

    callocate(newPath, sizeof(char), strlen(pathFromHome) + 50);

    strcpy(newPath, pathFromHome);
    strcat(newPath, dir);

    reallocate(newPath, sizeof (char) * (strlen(newPath) + 1));

    return (newPath);
}

char * dirs_bldsnd_exist_or_create(char **_logPath, char **_savePath){
    const char *homePath = get_home_path();
    char *dirPath = NULL;
    char *logPath = NULL;
    char *savePath = NULL;


    dirPath = get_path_to_save_folder(homePath);

    if(create_dir(dirPath) == -1) /* On créer le dossier Bloody Sanada */
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));

    callocate(logPath , sizeof(char), strlen(dirPath) + 15);
    callocate(savePath, sizeof(char), strlen(dirPath) + 15);

#ifndef _WIN32
    sprintf(logPath , "%s/logs" , dirPath );
    sprintf(savePath, "%s/saves", dirPath);
#else
    sprintf(logPath, "%s\\logs", dirPath);
    sprintf(savePath, "%s\\saves", dirPath);
#endif

    if(create_dir(logPath) == -1) /* On créer le dossier Bloody Sanada/logs */
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));
    if (create_dir(savePath) == -1) /* On créer le dossier Bloody Sanada/saves */
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));

    if(_logPath){
        reallocate(logPath, sizeof (char) * (strlen(logPath) + 1));
        *_logPath = logPath;
    }
    else
        free(logPath);

    if(_savePath){
        reallocate(savePath, sizeof(char) * (strlen(save_path) + 1));
        *_savePath = savePath;
    }
    else 
        free(savePath);

    return (dirPath);
}

err_t _init_log(void){
    time_t temps = time(NULL); /* On récupère le temps UNIX actuel */
    char *date = NULL;
    char *nom_fichier = NULL;
    char *logPath = NULL;

    /* On alloue les chaines de caracères */
    callocate(date,        sizeof(char), 500); 
    callocate(nom_fichier, sizeof(char), 1000);
    callocate(logPath, sizeof(char), 1000);

    if(!strftime(date, 500, "%F %X", localtime(&temps))) /* On convertit ce temps en chaine de caractères */
        return EXIT_FAILURE;
    strcpy(logPath, save_path);
    sprintf(nom_fichier, "/logs/Bloody Sanada - %s.log", date);

    strcat(logPath, nom_fichier);

    logFile = fopen(logPath,"w");

    free(date);
    free(nom_fichier);

    if(!logFile)
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
} 

char *get_current_time(void){
    time_t temps = time(NULL);

    char *date;

    callocate(date, sizeof(char), 500);
    
    if(!strftime(date, 500, "%X", localtime(&temps))){
        free(date);
        return (NULL);
    }

    return (date);
}