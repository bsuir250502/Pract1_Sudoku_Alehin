all:
	gcc -Wall -std=c99 -o main_gtk main_gtk.c `pkg-config --cflags --libs gtk+-2.0`