#ifndef __TOWER__
#define __TOWER__

#include "../include/gem.h"

typedef struct _tower{
    Gem gem ;     
    Case position;
    struct _tower *next;
}Tower;

typedef struct _list_tower{
    Tower * tower;
}List_Tower;

void add_tower( List_Tower * tower , const Case case_tower);
int number_of_tower ( List_Tower tower);
void free_tower_player(List_Tower * list_tower  ,  const Tower tower_delete);


#endif