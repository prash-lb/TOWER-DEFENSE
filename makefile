CC = gcc
CFLAGS =  -Wall -std=c17 -pedantic
LDFLAGS =-lm -lrt
MLV= -lMLV
OBJ = obj/main.o obj/game_engine.o obj/monster.o obj/tower.o obj/movement.o obj/player.o obj/graphic_engine.o obj/gem.o obj/shoot.o
DIR_SRC = src
DIR_OBJ = obj
DIR_HEADER = include
DIR_BIN = bin
TARGET = exe

all: $(DIR_BIN)/$(TARGET)

$(DIR_BIN)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@  $^ $(LDFLAGS) $(MLV)

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.c  $(DIR_HEADER)/graphic_engine.h 
	$(CC) -c $< -o $(DIR_OBJ)/main.o $(CFLAGS)

$(DIR_OBJ)/game_engine.o: $(DIR_SRC)/game_engine.c $(DIR_HEADER)/game_engine.h 
	$(CC) -c $< -o $(DIR_OBJ)/game_engine.o $(CFLAGS)

$(DIR_OBJ)/gem.o: $(DIR_SRC)/gem.c $(DIR_HEADER)/gem.h $(DIR_HEADER)/game_engine.h
	$(CC) -c $< -o $(DIR_OBJ)/gem.o $(CFLAGS)

$(DIR_OBJ)/monster.o: $(DIR_SRC)/monster.c $(DIR_HEADER)/monster.h $(DIR_HEADER)/game_engine.h
	$(CC) -c $< -o $(DIR_OBJ)/monster.o $(CFLAGS)

$(DIR_OBJ)/shoot.o: $(DIR_SRC)/shoot.c $(DIR_HEADER)/shoot.h $(DIR_HEADER)/game_engine.h
	$(CC) -c $< -o $(DIR_OBJ)/shoot.o $(CFLAGS)

$(DIR_OBJ)/tower.o: $(DIR_SRC)/tower.c $(DIR_HEADER)/tower.h $(DIR_HEADER)/game_engine.h $(DIR_HEADER)/gem.h
	$(CC) -c $< -o $(DIR_OBJ)/tower.o $(CFLAGS)

$(DIR_OBJ)/movement.o: $(DIR_SRC)/movement.c $(DIR_HEADER)/movement.h $(DIR_HEADER)/tower.h $(DIR_HEADER)/monster.h $(DIR_HEADER)/shoot.h $(DIR_HEADER)/game_engine.h
	$(CC) -c $< -o $(DIR_OBJ)/movement.o $(CFLAGS)

$(DIR_OBJ)/player.o: $(DIR_SRC)/player.c $(DIR_HEADER)/movement.h $(DIR_HEADER)/player.h 
	$(CC) -c $< -o $(DIR_OBJ)/player.o $(CFLAGS)

$(DIR_OBJ)/graphic_engine.o: $(DIR_SRC)/graphic_engine.c $(DIR_HEADER)/player.h  $(DIR_HEADER)/graphic_engine.h 
	$(CC) -c $< -o $(DIR_OBJ)/graphic_engine.o $(CFLAGS)




clean:
	rm -f $(OBJ) $(DIR_BIN)/$(TARGET)
