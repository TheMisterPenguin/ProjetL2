CC = gcc # Nom du compilateur.
CFLAGS =-Wall -I include# Options de compilation.
LDFLAGS = -L lib -lSDL2# Edition de liens. 
ODIR = obj/
SRC = src/
BINDIR = bin/
OBJ = main.o
GEN = jeux.prog

#Compilation de tout les fichiers source

all : $(BINDIR)$(GEN)

$(BINDIR)jeux : $(ODIR)$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(ODIR)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean : 
	rm -rf $(ODIR)*.o

mrproper : clean
	rm -rf $(BINDIR)*
