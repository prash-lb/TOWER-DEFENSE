#ifndef __PLAYER__
#define __PLAYER__

#include "../include/movement.h"

#define MAX_MANA 2000


typedef struct _player{
    int level;
    int mana;
    List_Tower * tower_player ; 
    List_Gem_Avaible * gem_player;
    List_Shoot * list_shoots;
}Player;

int gem_fusion_player (Player * player , const Gem gem1,const Gem gem2);
void player_init ( Player * player);
int buy_tower(Player * player , Plateau * board , const Case spot);
int buy_gem(Player * player,const Plateau board,int level );
int  upgrade_level_mana(Player * player);
int put_gem_on_tower(Player * player ,   Plateau * board , const Case spot ,const Gem new_gem);
int monster_on_player(stack_Monster * stack,const Plateau board, Player * player);
void monster_gain_mana(stack_Monster * monster , Player * player , Plateau board);
void free_player(Player * player );
#endif