# = $(wildcard PATH/*.c) (recupere tout les fichier .c dans PATH)

tickettorideapi_path = $(wildcard tickettorideapi/*.c)
structures_path = $(wildcard structures/sources/*.c)
utilities_path = $(wildcard utilities/sources/*.c)
interface_path = $(wildcard interface/sources/*.c)
bot_path = $(wildcard bot/sources/*.c)

SRC= does_it_work.c $(tickettorideapi_path) $(structures_path) $(utilities_path) $(interface_path) $(bot_path)

OBJ= $(SRC:.c=.o)

bot_quentin_LV : $(OBJ)
	gcc -o $@ $^
	
%.o : %.c
	gcc -c -O0 -o $@ $^ -Wall -g3

.PHONY : clean
clean : 
	rm -f $(OBJ)