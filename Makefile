EXE_NAME = reminder
FILES = main.cpp Date.cpp
OBJ_FILES = Date.o main.o
CC = g++
FLAGS = -Wall -pedantic -Wfatal-errors

make: main.o Date.o
	$(CC) -o $(EXE_NAME) $(OBJ_FILES)
main.o: main.cpp Date.cpp Date.hpp
	$(CC) $(FLAGS) -c main.cpp Date.cpp Date.hpp
Date.o: Date.cpp Date.hpp
	$(CC) $(FLAGS) -c Date.cpp Date.hpp
run:
	./$(EXE_NAME)
clean:
	rm $(EXE_NAME) *.o