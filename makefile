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
ALLOBJ = $(addsuffix .o, $(addprefix $(ODIR), main init_close event monstres personnage affichage objet liste_objet listes map menus interface inventaire test_affichage test_inventaire test_liste_objet test_listes test_map test_monstre test_personnage))
OBJ = $(addsuffix .o, $(addprefix $(ODIR), main init_close event monstres personnage affichage objet liste_objet listes map menus interface inventaire))
OBJ_TEST_MONSTRES = $(addsuffix .o, $(addprefix $(ODIR), test_monstres monstres))
OBJ_TEST_MAP = $(addsuffix .o, $(addprefix $(ODIR), test_map map affichage init_close event listes personnage menus liste_objet objet inventaire))
OBJ_TEST_LISTE_OBJET = $(addsuffix .o, $(addprefix $(ODIR), test_liste_objet liste_objet objet affichage listes personnage init_close))
OBJ_TEST_INVENTAIRE = $(addsuffix .o, $(addprefix $(ODIR), test_inventaire inventaire liste_objet objet personnage affichage listes init_close))
OBJ_TEST_PERSONNAGE = $(addsuffix .o, $(addprefix $(ODIR), test_personnage personnage affichage listes init_close inventaire objet liste_objet map))
OBJ_TEST_AFFICHAGE = $(addsuffix .o, $(addprefix $(ODIR), test_affichage affichage listes init_close personnage))
OBJ_TEST_LISTES = $(addsuffix .o, $(addprefix $(ODIR), test_listes listes affichage personnage init_close))


default : $(BINDIR)jeux$(EXT) # Génération par défault

all : makedir $(GEN) # Génération de tout les fichiers

#programme principal

$(BINDIR)jeux$(EXT) : $(OBJ)
	$(CC) $^ $(JSON-LIB-PATH) -o $@  $(LDFLAGS) 
	
# Compilation de tout les fichiers source

$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $< -g -D __LOG

# Génération des tests

$(BINDIR)test_map.bin : $(OBJ_TEST_MAP)
	$(CC) $^ -o $@  $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_monstres.bin : $(OBJ_TEST_MONSTRES)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)test_liste_objet.bin : $(OBJ_TEST_LISTE_OBJET)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_inventaire.bin : $(OBJ_TEST_INVENTAIRE)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_personnage.bin : $(OBJ_TEST_PERSONNAGE)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_affichage.bin : $(OBJ_TEST_AFFICHAGE)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_listes.bin : $(OBJ_TEST_LISTES)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

# Création de l'arboressence 
.PHONY: makedir
makedir :
	@chmod a+x $(DIRMAKE)
	@./$(DIRMAKE)
#options de suppression

.PHONY: clean
clean:
	@$(rm) 
	@echo "Cleanup complete!"

.PHONY: mrproper
mrproper: clean
	@$(rm) $(GEN)
	@echo "Executable removed!"