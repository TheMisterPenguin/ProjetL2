INCLUDE = $(addprefix -I , include)
LDFLAGS = -L lib -lSDL2  -l m# Options d'édition de liens. 
GEN = $(addprefix $(BINDIR), jeux.prog test_monstres) # Executables
ODIRCMD = obj/
