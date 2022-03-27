INCLUDE = $(addprefix -I , include)
GEN = jeux.exe # Executables
LDFLAGS = -L lib_win -l json-c -lmingw32 -lSDL2main -lSDL2# Options d'édition de liens. 
ODIRCMD = obj/
EXT = .exe
JSON-LIB-PATH = info.res icone.res
