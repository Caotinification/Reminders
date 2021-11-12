EXE_NAME = reminder
FILES = main.cpp DateClass/Date.cpp
OBJ_FILES = Date.o main.o
CC = g++
FLAGS = -Wall -pedantic -Wfatal-errors -fmax-errors=1

make: main.o Date.o
	$(CC) $(FLAGS) -o $(EXE_NAME) $(OBJ_FILES)
main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp
Date.o: DateClass/Date.cpp
	$(CC) $(FLAGS) -c DateClass/Date.cpp
run:
	./$(EXE_NAME)
clean:
	rm $(EXE_NAME) *.o