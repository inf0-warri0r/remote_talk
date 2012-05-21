#Author :Tharindra Galahena
#Project:
#Date   :28/04/2012

CC    = gcc
FILES = listen.c
FLAGS = -lasound
GTK_LIBS = $(shell pkg-config --libs gtk+-2.0)
GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)

all:	
	$(CC) -o listen $(FILES) $(FLAGS) $(GTK_LIBS) $(GTK_FLAGS) 
