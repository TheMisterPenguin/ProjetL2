#include <string.h>
#include <SDL2/SDL_messagebox.h>

#include <definition_commun.h>
#include <macros.h>
#include <log.h>

char * execDir = NULL;

char * get_executable_directory(const char *argv){
    char * lastOccur = rindex(argv, (int)'/');
    char * execDir = NULL;

    callocate(execDir, sizeof(char), strlen(argv) + 1);

    strncpy(execDir, argv, lastOccur - argv + 1);

    log_info("Répertoire d'éxécution : '%s'", execDir);

    return (execDir);
}

