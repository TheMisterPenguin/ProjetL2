#include "code_erreur.hpp"
#include <cstdlib>

#define allocate(ptr,size) {                            \
    ptr = malloc(size);                                 \
    if(!ptr)                                            \
        erreur("Erreur : plus de mémoire", OUT_OF_MEM); \
}

#define callocate(ptr, size, elementCount) {            \
    ptr = calloc(elementCount, size);                   \
    if(!ptr)                                            \
        erreur("Erreur : plus de mémoire", OUT_OF_MEM); \
}

#define reallocate(ptr, size) {                         \
    ptr = realloc(ptr, size);                           \
    if(!ptr)                                            \
        erreur("Erreur : plus de mémoire", OUT_OF_MEM); \
}
