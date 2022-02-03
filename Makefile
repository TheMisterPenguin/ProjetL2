CC = gcc # Nom du compilateur.
CFLAGS =-Wall -I include # Options de compilation.
LDFLAGS = -L lib -lSDL2 # Options d'édition de liens. 
ODIR = obj/# Répertoire des fichiers objets
SRC = src/# Répertoire des fichiers sources
BINDIR = bin/# Répertoire des exécutables
OBJ = $(addprefix $(ODIR), main.o init.o close.o event.o)# Fichiers à compiler
GEN = jeux.prog # Executables


all : $(BINDIR)$(GEN)

$(BINDIR)jeux.prog : $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compilation de tout les fichiers source

$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Nettoyage
clean : 
	rm -rf $(ODIR)*.o

mrproper : clean
	rm -rf $(BINDIR)*
