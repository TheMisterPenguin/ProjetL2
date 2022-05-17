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
ALLOBJ = $(addsuffix .o, $(addprefix $(ODIR), main log init_close event monstres personnage affichage objet liste_objet listes map menus interface inventaire sorts test_affichage test_inventaire test_liste_objet test_listes test_map test_monstre test_personnage coffres))
OBJ = $(addsuffix .o, $(addprefix $(ODIR), main utils log init_close event monstres personnage affichage objet liste_objet listes map menus interface inventaire sorts coffres))
OBJ_TEST_LISTE_OBJET = $(addsuffix .o, $(addprefix $(ODIR), test_liste_objet liste_objet objet affichage listes personnage init_close inventaire map interface monstres sorts event menus coffres))
OBJ_TEST_INVENTAIRE = $(addsuffix .o, $(addprefix $(ODIR), test_inventaire inventaire liste_objet objet personnage affichage listes init_close map interface monstres sorts event menus coffres))
OBJ_TEST_PERSONNAGE = $(addsuffix .o, $(addprefix $(ODIR), test_personnage personnage affichage listes init_close inventaire objet liste_objet map interface monstres sorts event menus coffres))
OBJ_TEST_LISTES = $(addsuffix .o, $(addprefix $(ODIR), test_listes listes affichage personnage init_close inventaire liste_objet objet interface map monstres sorts event menus coffres))
OBJ_TEST_SDL = $(addsuffix .o, $(addprefix $(ODIR), test_SDL))

default : $(BINDIR)jeux$(EXT) # Génération par défault

all : makedir $(GEN) # Génération de tout les fichiers

test : makedir $(TEST) # Génération des tests

#programme principal

$(BINDIR)jeux$(EXT) : $(OBJ)
	$(CC) $^ $(JSON-LIB-PATH) -o $@  $(LDFLAGS) 
	
# Compilation de tout les fichiers source

$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $< -g

# Génération des tests

$(BINDIR)test_map$(EXT) : $(OBJ_TEST_MAP)
	$(CC) $^ -o $@  $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_monstres$(EXT) : $(OBJ_TEST_MONSTRES)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)test_liste_objet$(EXT) : $(OBJ_TEST_LISTE_OBJET)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_inventaire$(EXT) : $(OBJ_TEST_INVENTAIRE)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(CUNIT-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_personnage$(EXT) : $(OBJ_TEST_PERSONNAGE)
	$(CC) $^ -o $@ $(CUNIT-LIB-PATH) $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_affichage$(EXT) : $(OBJ_TEST_AFFICHAGE)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_listes$(EXT) : $(OBJ_TEST_LISTES)
	$(CC) $^ -o $@ $(JSON-LIB-PATH) $(LDFLAGS)

$(BINDIR)test_SDL$(EXT) : $(OBJ_TEST_SDL)
	$(CC) $^ -o $@ $(CUNIT-LIB-PATH) $(LDFLAGS)

# Création de l'arboressence 

#options de suppression

.PHONY: clean
clean:
	@$(rm) 
	@echo "Cleanup complete!"

.PHONY: mrproper
mrproper: clean
	@$(rm) $(GEN)
	@echo "Executable removed!"

.PHONY: makedir
ifeq ($(OS),Windows_NT)
makedir :
	@echo "Dossier obj: crée"
else 
makedir :
	@chmod a+x $(DIRMAKE)
	@./$(DIRMAKE)

endif