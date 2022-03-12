INCLUDE = $(addprefix -I , include)
GEN = $(addprefix $(BINDIR), jeux.prog) # Executables
LDFLAGS = -L lib -lSDL2  -l json-c -l m# Options d'édition de liens. 
ODIRCMD = obj/
DIRMAKE = gen_dos.sh
