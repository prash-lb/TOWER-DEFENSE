#ifndef __SHOOT__
#define __SHOOT__

#include "../include/gem.h"


typedef struct _shoot {
    int damage ;
    int id_monster;/*the target */
    Case position_tower;/* where he is from*/
    Case_Monster position ;/*his actual position*/
    Gem gem;
    struct _shoot* next;
}Shoot;

typedef struct _list_shoot{
    Shoot * shoots;
}List_Shoot;


void add_shoot( List_Shoot * list_shoot );
void free_shoot(List_Shoot * List_Shoot , int target);
void free_shoot_end(List_Shoot * List_Shoot, Case_Monster position);
int number_of_shoot(List_Shoot shoots_tower , Case pos_tower);
int  shoot_in_monster_present (List_Shoot list_Shoot , int monster);
#endif