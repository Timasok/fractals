MAIN 	  = fractal

# O_FLAGS   = -O2
# O_FLAGS   = -O3
O_FLAGS   = -Ofast
# O_FLAGS = 

SSE_FLAGS = -msse

all: compile link run

compile:
	@g++ -c $(SSE_FLAGS) $(O_FLAGS) $(MAIN).cpp -I/usr/include/

link:
	@g++ $(MAIN).o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

run:
	@./sfml-app

clear:
	@rm -f $(MAIN).o