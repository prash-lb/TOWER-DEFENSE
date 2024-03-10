#ifndef __MONSTER__
#define __MONSTER__

#include "../include/game_engine.h"

#define H 20
#define SPEED_AGILE 3
#define SPEED_DEFAULT 1

typedef enum _wavetype{
    NORMAL,
    CROWD,
    AGILE,
    BOSS
}WaveType;

typedef enum _residutype{
    RESIDU_NEUTRAL,
    RESIDU_PYRO,
    RESIDU_DENDRO,
    RESIDU_HYDRO,
    RESIDU_PYRO_HYDRO,
    RESIDU_DENDRO_HYDRO,
    RESIDU_DENDRO_PYRO
}ResiduType;

typedef struct _monster{
    int life_value_init ;
    int type;
    int life;
    int rgb;
    int time ;
    Case_Monster coord;
    int id_monster;
    int residu;
    int damage;
    Direction_case direction ;
    struct _monster *next;
}Monster;

typedef struct _Array_Monster{
    struct _monster *Monster;
}stack_Monster;

void  init_Array_Monster (stack_Monster * wawe);   
void  Create_Monster_Wave (stack_Monster * stack, const Plateau  board, int * id);
void free_all_monster(stack_Monster * stack);
void free_monster(stack_Monster * stack , Monster * monster);
Monster * find_monster(int id , stack_Monster* monster);
void effect_on_monster(stack_Monster * monster,int temps);

#endif