CC = g++
EXEC = Quad
FLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
STD = -std=c++17
S = src
O = obj
B = bin

all: $(O) $(B) $(O)/main.o
	$(CC) $(O)/*.o -o $(B)/$(EXEC) $(LIBS)

$(O)/main.o: $(O)/Engine.o $(O)/QuadTree.o
	$(CC) $(S)/main.cpp -c -o $(O)/main.o $(STD) $(FLAGS)

$(O)/Engine.o:
	$(CC) $(S)/Engine.cpp -c -o $(O)/Engine.o $(STD) $(FLAGS)

$(O)/QuadTree.o:
	$(CC) $(S)/QuadTree.cpp -c -o $(O)/QuadTree.o $(STD) $(FLAGS)

clean: $(O) $(B)
	rm -r $(O)
	rm -r $(B)

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)
