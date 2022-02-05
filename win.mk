INCLUDE = $(addprefix -I , include SDL_win/include)
GEN = jeux.exe # Executables
LDFLAGS = -L SDL_win/lib -lmingw32 -lSDL2main -lSDL2# Options d'édition de liens. 
ODIRCMD = obj/
