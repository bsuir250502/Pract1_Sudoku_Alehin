OBJ_MAIN = main_engine.o main.o
OBJ_GTK = main_engine.o main_gtk.o
GTK_FLAGS = `pkg-config --cflags --libs gtk+-2.0`
CFLAGS = -Wall -std=c99
all: main
.PHONY: all 

main: $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o main

gtk: $(OBJ_GTK)
	$(CC) $(CFLAGS) $(OBJ_GTK) -o gtk $(GTK_FLAGS)

main_gtk.o: main_gtk.c
	gcc $(GTK_FLAGS) -c $<

.PHONY: clean_all clean_main clean_gtk 
clean_all: 
	rm gtk main *.o
    
clean_main:   
	rm main $(OBJ_MAIN)
    
clean_gtk:   
	rm gtk $(OBJ_GTK)
$(OBJ_MAIN) $(OBJ_GTK) : main_engine.h