INCLUDE = $(addprefix -I , include)
GEN = $(addprefix $(BINDIR), jeux.prog test_listes test_affichage test_personnage test_liste_objet test_inventaire) # Executables
LDFLAGS = -L lib -lSDL2 -l m# Options d'édition de liens. 
ODIRCMD = obj/
DIRMAKE = gen_dos.sh
