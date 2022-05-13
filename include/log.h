
#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>

extern _Bool debug;

extern char *get_current_time(void);
extern int _init_log(void);
extern char *dirs_bldsnd_exist_or_create(char **_logPath, char **_savePath);

extern FILE *logFile;
extern char *save_path; /**<Le répertoire complet de sauvegarde du jeu*/


#define log_warn(message, ...) {    \
    printf("\033[0;33m");           \
    printf("\e[40m");               \
    char *t = get_current_time();   \
    printf("(%s)[ATTENTION] ", t);  \
    if(logFile){                    \
        fprintf(logFile, "(%s)[ATTENTION] " message "\n", t, ##__VA_ARGS__); \
        fflush(logFile);            \
    }                               \
    free(t);                        \
    printf(message "\n", ##__VA_ARGS__); \
    fflush(stdout);                 \
}

#define log_error(message, ...) {   \
    printf("\033[0;31m");           \
    printf("\e[40m");               \
    char *t = get_current_time();   \
    printf("(%s)[ERREUR] ", t);     \
    if(logFile){                    \
        fprintf(logFile, "(%s)[ERREUR] " message "\n", t, ##__VA_ARGS__); \
        fflush(logFile);            \
    }                               \
    free(t);                        \
    printf(message "\n", ##__VA_ARGS__); \
    fflush(stdout);                 \
}

#define log_info(message, ...) {    \
    printf("\033[0;37m");           \
    printf("\e[40m");               \
    char *t = get_current_time();   \
    printf("(%s)[INFO] ", t);       \
    if(logFile){                    \
        fprintf(logFile, "(%s)[INFO] " message "\n", t, ##__VA_ARGS__); \
        fflush(logFile);            \
    }                               \
    free(t);                        \
    printf(message "\n", ##__VA_ARGS__); \
    fflush(stdout);                 \
}

#define log_debug(message, ...) {       \
    char *t = get_current_time();       \
    if(logFile){                        \
        fprintf(logFile, "(%s)[DEBUG] " message "\n", t, ##__VA_ARGS__); \
        fflush(logFile);                \
    }                                   \
    if(debug){                          \
        printf("\033[0;92m");           \
        printf("\e[40m");               \
        printf("(%s)[DEBUG] ", t);      \
        printf(message "\n", ##__VA_ARGS__); \
        fflush(stdout);                 \
    }                                   \
    free(t);  \
}

#endif