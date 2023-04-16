#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

#include <definition_commun.hpp>
#include <macros.hpp>
#include <code_erreur.hpp>
#include <runtime.hpp>

#ifndef _WIN32
	#include <pwd.h>
	#include <unistd.h>
#else
	#include <direct.h>
	#include <windows.h>
#endif

FILE *logFile = NULL;

bool debug = vrai;
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
    void *newPath = NULL;

#ifndef _WIN32
    const char *dir = "/Bloody Sanada";
#else
    const char *dir = "\\AppData\\Local\\Bloody Sanada";
#endif

    callocate(newPath, sizeof(char), strlen(pathFromHome) + 50);

    strcpy((char *)newPath, pathFromHome);
    strcat((char *)newPath, dir);

    reallocate(newPath, sizeof (char) * (strlen((const char *)newPath) + 1));

    return ((char*)newPath);
}

char * dirs_bldsnd_exist_or_create(char **_logPath, char **_savePath){
    const char *homePath = get_home_path();
    void *dirPath = NULL;
    void *logPath = NULL;
    void *savePath = NULL;

    void *saveDir_auto = NULL;
    void *saveDir_0 = NULL;
    void *saveDir_1 = NULL;
    void *saveDir_2 = NULL;



    dirPath = get_path_to_save_folder(homePath);

    if(create_dir((char*) dirPath) == -1) /* On créer le dossier Bloody Sanada */
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));

    callocate(logPath , sizeof(char), strlen((const char *) dirPath) + 15);
    callocate(savePath, sizeof(char), strlen((const char *) dirPath) + 15);
    callocate(saveDir_auto, sizeof(char), strlen((const char *) dirPath) + 30);
    callocate(saveDir_0, sizeof(char), strlen((const char *) dirPath) + 30);
    callocate(saveDir_1, sizeof(char), strlen((const char *) dirPath) + 30);
    callocate(saveDir_2, sizeof(char), strlen((const char *) dirPath) + 30);



#ifndef _WIN32
    sprintf((char *)logPath , "%s/logs" , dirPath );
    sprintf((char *)savePath, "%s/saves", dirPath);
    sprintf((char *)saveDir_auto, "%s/auto", savePath);
    sprintf((char *)saveDir_0, "%s/save_0", savePath);
    sprintf((char *)saveDir_1, "%s/save_1", savePath);
    sprintf((char *)saveDir_2, "%s/save_2", savePath);
#else
    sprintf(logPath, "%s\\logs", dirPath);
    sprintf(savePath, "%s\\saves", dirPath);
    sprintf(saveDir_auto, "%s\\auto", savePath);
    sprintf(saveDir_0, "%s\\save_0", savePath);
    sprintf(saveDir_1, "%s\\save_1", savePath);
    sprintf(saveDir_2, "%s\\save_2", savePath);
#endif

    if(create_dir((char *)logPath) == -1) /* On créer le dossier Bloody Sanada/logs */
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));
    if (create_dir((char *)savePath) == -1) /* On créer le dossier Bloody Sanada/saves */
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));

    if(create_dir((char *)saveDir_auto) == -1)
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));
    if (create_dir((char *)saveDir_0) == -1)
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));
    if (create_dir((char *)saveDir_1) == -1)
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));
    if (create_dir((char *)saveDir_2) == -1)
        erreur("Impossible de créer le répertoire de sauvegarde : %s", ERR_CREATION_REPERTOIRE_SAUVEGARDE, strerror(errno));


    if(_logPath){
        reallocate(logPath, sizeof (char) * (strlen((char*)logPath) + 1));
        *_logPath = (char *) logPath;
    }
    else
        free(logPath);

    if(_savePath){
        reallocate(savePath, sizeof(char) * (strlen((char*) save_path) + 1));
        *_savePath = (char *)savePath;
    }
    else 
        free(savePath);

    free(saveDir_auto);
    free(saveDir_0);
    free(saveDir_1);
    free(saveDir_2);


    return ((char *)dirPath);
}


void _stop_log(void) {
    free(save_path);
    save_path = NULL;

    if (fclose(logFile)){
        logFile = NULL;

        erreur("Erreur lors de l'enregistrement du log", cerror(T_ERREUUR_FICHIER, ERREUR_FICHIER_FERMETURE))

    }

    printf("\n" "\e[0m\n\n");

}

err_t _init_log(void){
    time_t temps = time(NULL); /* On récupère le temps UNIX actuel */
    void *date = NULL;
    void *nom_fichier = NULL;
    void *logPath = NULL;

    /* On alloue les chaines de caracères */
    callocate(date,        sizeof(char), 500); 
    callocate(nom_fichier, sizeof(char), 1000);
    callocate(logPath, sizeof(char), 1000);

    if(!strftime((char *)date, 500, "%F %X", localtime(&temps))) /* On convertit ce temps en chaine de caractères */
        return EXIT_FAILURE;
    strcpy((char *) logPath, save_path);
    sprintf((char *) nom_fichier, "/logs/Bloody Sanada - %s.log", date);

    strcat((char *) logPath, (char *) nom_fichier);

    logFile = fopen((char *) logPath,"w");

    free(date);
    free(nom_fichier);

    if(!logFile)
        return EXIT_FAILURE;
    
    ajout_droit(f_close, (void *) _stop_log);
    printf("\e[40m\n\n\n");

    return EXIT_SUCCESS;
} 


char *get_current_time(void){
    time_t temps = time(NULL);

    void *date;

    callocate( date, sizeof(char), 500);
    
    if(!strftime((char *)date, 500, "%X", localtime(&temps))){
        free(date);
        return (NULL);
    }

    return (char *)(date);
}