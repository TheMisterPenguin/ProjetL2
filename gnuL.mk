INCLUDE = $(addprefix -I , include)
GEN = $(addprefix $(BINDIR), jeux.prog test_map) # Executables
LDFLAGS = -L lib -lSDL2 -l m# Options d'édition de liens. 
ODIRCMD = obj/
DIRMAKE = gen_dos.sh
