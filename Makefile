CC = gcc # Nom du compilateur.
CFLAGS =-Wall -I include# Options de compilation.
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2# Edition de liens. 
ODIR = obj
SRC = src

#Compilation de tout les fichiers source

%.o: $(SRC)\%.compilateur
	$(CC) $(CFLAGS) -o $(ODIR)\$@ -c $<
