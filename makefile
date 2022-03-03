ifeq ($(OS),Windows_NT)
include win.mk
else 
include gnuL.mk
endif

CC        = gcc # Nom du compilateur.
CFLAGS    =-Wall $(INCLUDE) # Options de compilation.
ODIR      = obj/# Répertoire des fichiers objets
SRC       = src/# Répertoire des fichiers sources
BINDIR    = bin/# Répertoire des exécutables
OBJ       = $(addprefix $(ODIR), main.o init_close.o event.o personnage.o affichage.o objet.o liste_objet.o)# Fichiers à compiler
OBJTEST = $(addprefix $(ODIR), monstres.o test_monstre.o)
rm        = rm -f

all : $(GEN)

$(BINDIR)jeux.prog : $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)test_monstre : $(OBJTEST)
	$(CC) $^ -o $@ $(LDFLAGS)
# Compilation de tout les fichiers source

$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $< -O3

# Génération des tests

#options de suppression

.PHONY: clean
clean:
	@$(rm) $(OBJ)
	@echo "Cleanup complete!"

.PHONY: mrproper
mrproper: clean
	@$(rm) $(GEN)
	@echo "Executable removed!"