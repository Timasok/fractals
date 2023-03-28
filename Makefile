MAIN = NO-SSE

all: compile link run

compile:
	@g++ -c $(MAIN).cpp -I/usr/include/

link:
	@g++ $(MAIN).o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

run:
	@./sfml-app

clear:
	@rm -f $(MAIN).o