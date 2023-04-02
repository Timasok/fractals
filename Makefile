FLAGS := -g -fsanitize=address  # NO-SSE
FLAGS :=   # SSE

MAIN  := fractal

all: compile link run

compile:
	@g++ -c $(MAIN).cpp $(FLAGS) -I/usr/include/

link:
	@g++ $(MAIN).o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

run:
	@./sfml-app

clear:
	@rm -f $(MAIN).o