INCLUDE = $(addprefix -I , include)
GEN = $(addprefix $(BINDIR), jeux.prog test_map test_liste_objet) # Executables
LDFLAGS = -L lib -lSDL2 -l m# Options d'édition de liens. 
ODIRCMD = obj/
DIRMAKE = gen_dos.sh
