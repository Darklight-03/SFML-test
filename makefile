LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -lglut
all:
	g++ main.cpp -c
	g++ -o exec main.o ${LIBS}