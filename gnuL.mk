INCLUDE = $(addprefix -I , include)
GEN = $(addsuffix .bin, $(addprefix $(BINDIR), jeux test_map test_listes test_affichage test_personnage test_liste_objet test_inventaire))
LDFLAGS = -L lib -lSDL2 -l m# Options d'édition de liens. 
ODIRCMD = obj/
DIRMAKE = gen_dos.sh
JSON-LIB-PATH = lib/libjson-c.a
EXT = .bin
rm = rm -f obj/*.o


