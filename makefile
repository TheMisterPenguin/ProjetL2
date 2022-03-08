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
OBJ = $(addprefix $(ODIR), main.o init_close.o event.o monstres.o personnage.o affichage.o objet.o liste_objet.o)# Fichiers à compiler
OBJ_TEST_MONSTRES = $(addprefix $(ODIR), test_monstres.o monstres.o)

all : $(GEN)

$(BINDIR)jeux.prog : $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)test_monstres : $(OBJ_TEST_MONSTRES)
	$(CC) $^ -o $@ $(LDFLAGS)
# Compilation de tout les fichiers source

$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Génération des tests




