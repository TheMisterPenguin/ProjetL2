INCLUDE = $(addprefix -I , include)
GEN = jeux.exe # Executables
LDFLAGS = -mwindows -L lib_win -l json-c -lmingw32 -l SDL2main -l SDL2# Options d'édition de liens. 
ODIRCMD = obj/
EXT = .exe
JSON-LIB-PATH = info.res icone.res
rm = del obj\*.o 

