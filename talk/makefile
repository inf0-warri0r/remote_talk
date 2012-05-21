#Author :Tharindra Galahena
#Project:walkie-talkie application for linux
#Date   :28/04/2012

CC    = gcc
FILES = talk.c
FLAGS = -lasound
GTK_LIBS = $(shell pkg-config --libs gtk+-2.0)
GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)

all:	
	$(CC) -o talk $(FILES) $(FLAGS) $(GTK_LIBS) $(GTK_FLAGS) 
