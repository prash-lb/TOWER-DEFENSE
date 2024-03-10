#ifndef __MOVEMENT__
#define __MOVEMENT__

#include "../include/monster.h"
#include "../include/tower.h"
#include "../include/shoot.h"

#include "MLV/MLV_all.h"


void monster_move(Plateau * board, stack_Monster * wawe);
void tower_attack(List_Tower * tower,List_Shoot * player_shoot,stack_Monster * monster);
void mouvement_shoot(List_Shoot * shoot_player, stack_Monster * monster,int time_begin );
#endif