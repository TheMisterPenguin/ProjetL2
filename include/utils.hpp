#ifndef __UTILS_H__
#define __UTILS_H__

#include "macros.hpp"
#include <cstring>

extern char *get_executable_directory(const char *argv);

static inline char *catAlloc(const char *_des, const char *_src) {
    void *retour = NULL;

    callocate(retour, sizeof(char), strlen(_src) + strlen(_des) + 1);

    return (strcat(strcat((char *)retour, _des), _src));
}


extern char *execDir;

#endif