OBJ_DIR := ./obj/
LOGS_DIR:= ./logs/	
SRC_DIR	:= ./
I_FLAG 	:= -I/usr/include/ -I./
CC 		:= g++
CFLAGS  := -Wno-format -g -fsanitize=address
CFLAGS_NO_SANITIZER := -Wno-format -g

SRC    := $(wildcard $(SRC_DIR)*.cpp)
OBJ    := $(patsubst $(SRC_DIR)%.cpp,  $(OBJ_DIR)%.o, $(SRC))

FRAC_EXE  := FRAC

all : $(FRAC_EXE)

$(FRAC_EXE): $(OBJ) 
	@$(CC) $(I_FLAG) $(CFLAGS) $(OBJ) -o $(FRAC_EXE)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	@$(CC) $(I_FLAG) -c $< -o $@

mkdir :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LOGS_DIR)

clean :
	@rm $(FRAC_EXE) $(OBJ_DIR)*.o 
