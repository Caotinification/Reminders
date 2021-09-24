EXE_NAME = reminder
FILES = Date.cpp main.cpp
CC = g++
FLAGS = -Wall -o $(reminder) -pedantic -Wfatal-errors

compile:$(FILES)
	$(CC) -c $(FILES)
