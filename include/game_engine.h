#ifndef __GAME_ENGINE__
#define __GAME_ENGINE__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define WIDTH_PLATEAU 22
#define LENGHT_PLATEAU 28
#define LENGHT_WAY 600


typedef enum _direction_case {
    TOP,
    BOTTOM,
    RIGHT,
    LEFT
}Direction_case;

typedef enum _element_de_jeu {
    VIDE,
    ROAD,
    TOWER_VOID,
    TOWER_MIXTE,
    TOWER_PYRO,
    TOWER_DENDRO,
    TOWER_HYDRO
}GameElement;


typedef struct _case {
    int x;
    int y;
}Case;


typedef struct _case_monster{
    double x;
    double y;
}Case_Monster;

typedef struct _plateau {
    int number;
    int turn;
    int plateau[WIDTH_PLATEAU][LENGHT_PLATEAU];
    Case road [LENGHT_WAY];
}Plateau;



void print_board(Plateau  board);
int Creation_road (Plateau * board);
void print_array(Plateau board,int number);



#endif