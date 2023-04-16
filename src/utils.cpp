#include <cstring>
#include <SDL2/SDL_messagebox.h>

#include <definition_commun.hpp>
#include <macros.hpp>
#include <log.hpp>

char * execDir = NULL;

char * get_executable_directory(const char *argv){
    const char * lastOccur = rindex(argv, (int)'/');
    void * execDir = NULL;

    callocate(execDir, sizeof(char), strlen(argv) + 1);

    strncpy((char *)execDir, argv, lastOccur - argv + 1);

    log_info("Répertoire d'éxécution : '%s'", execDir);

    return ((char *)execDir);
}

