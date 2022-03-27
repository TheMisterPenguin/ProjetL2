ifeq ($(OS),Windows_NT)
include win.mk
else 
include gnuL.mk
endif


CC = gcc # Nom du compilateur.
CFLAGS =-Wall $(INCLUDE) # Options de compilation.
ODIR = obj/# Répertoire des fichiers objets
SRC = src/# Répertoire des fichiers sources
BINDIR = bin/# Répertoire des exécutables
ALLOBJ = $(addprefix $(ODIR), main.o init_close.o event.o monstres.o personnage.o affichage.o objet.o liste_objet.o listes.o map.o menus.o interface.o inventaire.o test_affichage.o test_inventaire.o test_liste_objet.o test_listes.o test_map.o test_monstre.o test_personnage.o)
OBJ = $(addprefix $(ODIR), main.o init_close.o event.o monstres.o personnage.o affichage.o objet.o liste_objet.o listes.o map.o menus.o interface.o)
OBJ_TEST_MONSTRES = $(addprefix $(ODIR), test_monstres.o monstres.o)
OBJ_TEST_MAP = $(addprefix $(ODIR), test_map.o map.o affichage.o init_close.o event.o listes.o personnage.o menus.o)
OBJ_TEST_LISTE_OBJET = $(addprefix $(ODIR), test_liste_objet.o liste_objet.o objet.o affichage.o listes.o personnage.o)
OBJ_TEST_INVENTAIRE = $(addprefix $(ODIR), test_inventaire.o inventaire.o liste_objet.o objet.o personnage.o affichage.o listes.o init_close.o)
OBJ_TEST_PERSONNAGE = $(addprefix $(ODIR), test_personnage.o personnage.o affichage.o listes.o init_close.o)
OBJ_TEST_AFFICHAGE = $(addprefix $(ODIR), test_affichage.o affichage.o listes.o init_close.o personnage.o)
OBJ_TEST_LISTES = $(addprefix $(ODIR), test_listes.o listes.o affichage.o personnage.o init_close.o)
rm = rm -f

default : $(BINDIR)jeux$(EXT) # Génération par défault

all : makedir $(GEN) # Génération de tout les fichiers

#programme principal

$(BINDIR)jeux$(EXT) : $(OBJ)
	$(CC) $^ $(JSON-LIB-PATH) -o $@  $(LDFLAGS) 
	
# Compilation de tout les fichiers source

$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $< -g

# Génération des tests

$(BINDIR)test_map.bin : $(OBJ_TEST_MAP)
	$(CC) $^ -o $@  lib/libjson-c.a $(LDFLAGS)

$(BINDIR)test_monstres.bin : $(OBJ_TEST_MONSTRES)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)test_liste_objet.bin : $(OBJ_TEST_LISTE_OBJET)
	$(CC) $^ -o $@ lib/libjson-c.a $(LDFLAGS)

$(BINDIR)test_inventaire.bin : $(OBJ_TEST_INVENTAIRE)
	$(CC) $^ -o $@ lib/libjson-c.a $(LDFLAGS)

$(BINDIR)test_personnage.bin : $(OBJ_TEST_PERSONNAGE)
	$(CC) $^ -o $@ lib/libjson-c.a $(LDFLAGS)

$(BINDIR)test_affichage.bin : $(OBJ_TEST_AFFICHAGE)
	$(CC) $^ -o $@ lib/libjson-c.a $(LDFLAGS)

$(BINDIR)test_listes.bin : $(OBJ_TEST_LISTES)
	$(CC) $^ -o $@ lib/libjson-c.a $(LDFLAGS)

# Création de l'arboressence 
.PHONY: makedir
makedir :
	@chmod a+x $(DIRMAKE)
	@./$(DIRMAKE)
#options de suppression

.PHONY: clean
clean:
	@$(rm) $(ALLOBJ)
	@echo "Cleanup complete!"

.PHONY: mrproper
mrproper: clean
	@$(rm) $(GEN)
	@echo "Executable removed!"