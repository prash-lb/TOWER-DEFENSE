#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "../include/player.h"

#define TAILLE_CASE 40
#define TAILLE_CASE_GEM_MENU 30

#define LENGHT_WINDOW (LENGHT_PLATEAU * TAILLE_CASE) + 300
#define WIDTH_WINDOW (WIDTH_PLATEAU* TAILLE_CASE)

MLV_Image ** int_image(int height , int width);
void gestion_click( int * begin ,int * begin_wawe ,int * buy_tower , int * buy_gem , int * fusion_gem  ,int * upgrade_mana,  int  *level_gem, int * pos_gem ,const Player player, const Plateau board  );
Case gestion_click_Tower_pose(const Plateau board, const Player player);
void graphic_map(const Plateau board , const stack_Monster stack,const int height ,const  int width, MLV_Image ** List_image ,const Player player,const int temp , const int  begin ,const int buy_tower , const int fusion_gem , const int  upgrade_mana,const int  level_gem ,const int pos_gem,Gem gem1, Gem gem2);
void free_image_List(MLV_Image ** list);
void gestion_click_gem_pose(const Player player , int * pos_gem ,int * fusion_gem ,Gem * gem1 , Gem *gem2 ,Case  * spot);
void end_graphic(Plateau board);

#endif