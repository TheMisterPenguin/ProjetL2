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
OBJ = $(addprefix $(ODIR), main.o init_close.o event.o monstre.o personnage.o)# Fichiers à compiler


all : $(BINDIR)$(GEN)

$(BINDIR)$(GEN) : $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compilation de tout les fichiers source

$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $<



