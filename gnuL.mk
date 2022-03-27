INCLUDE = $(addprefix -I , include)
GEN = $(addprefix $(BINDIR), jeux.prog test_listes.bin test_affichage.bin test_personnage.bin test_liste_objet.bin test_inventaire.bin) # Executables
LDFLAGS = -L lib -lSDL2 -l m# Options d'édition de liens. 
ODIRCMD = obj/
DIRMAKE = gen_dos.sh
JSON-LIB-PATH = lib/libjson-c.a
EXT = .bin

