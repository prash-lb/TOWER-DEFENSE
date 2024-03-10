#define _GNU_SOURCE
#define _POSIX_C_SOURCE 1999309L
#define AJUSTEMENT_EXTRATIME 3

#include "../include/graphic_engine.h"

int main(int argc, char * argv[]){
    Plateau  board;
    Player player;
    MLV_Image ** list_image;
    stack_Monster   wawe;
    struct timespec start_game ,end , new_time , new_time_effect ;
    int good ,begin , begin_wawe , tower_buy,gem_buy , gem_fusion ,upgrade_mana, level_gem, pos_gem,id;
    unsigned int  width ,height;
    double frametime ,extratime , seconde ;
    Gem  gem1, gem2 ;
    Case new_pos;
    width = LENGHT_WINDOW;
    height = WIDTH_WINDOW; 
    good = begin = begin_wawe = gem_buy = tower_buy = gem_fusion = upgrade_mana = pos_gem = 1;
    level_gem = id  = 0;
    new_pos.x = new_pos.y = -1;
    
    srand(time(NULL));
    player_init (&player);
    init_Array_Monster(&wawe);
    while(good){
        good = Creation_road(&board);
    }   
    MLV_create_window( "towerdefense", "TD", width, height);
    list_image = int_image(height,width);
    clock_gettime(CLOCK_REALTIME,&start_game);
    gem1.teinte = gem2.teinte = -1; 
    /*We are done with the initialization*/
    while ( monster_on_player(&wawe,board,&player) != 1){
        clock_gettime(CLOCK_REALTIME,&end);
        clock_gettime(CLOCK_REALTIME,&new_time_effect);
        graphic_map(board,wawe,height , width,list_image,player,(int) seconde,begin,tower_buy,gem_fusion,upgrade_mana,level_gem,pos_gem,gem1,gem2);
        if(begin == 0 && ((begin_wawe == 0) || ((end.tv_sec != start_game.tv_sec) && (end.tv_sec - start_game.tv_sec ) % 35  == 0)) ){/*we begin the wawe if he click on the button or the timer get 0*/
            if(begin_wawe == 0){
                player.mana +=  ( (seconde ) * (2000 * pow(1.4,player.level))) / 100;
                if(player.mana > (2000 * pow(1.4,player.level))){
                    player.mana = (2000 * pow(1.4,player.level));
                }
            }
            tower_buy = begin_wawe = 1;
            board.turn ++ ;
            Create_Monster_Wave(&wawe,board, &id);
            start_game.tv_sec = end.tv_sec;
        }

        if(pos_gem == 1 && gem_fusion == 1){
            gestion_click(&begin,&begin_wawe,&tower_buy,&gem_buy,&gem_fusion,&upgrade_mana,&level_gem,&pos_gem, player, board);
        }

        if(upgrade_mana == 0){
            upgrade_level_mana(&player);
            upgrade_mana = 1;
        }

        if(gem_buy == 0){ 
            buy_gem(&player,board,level_gem);
            gem_buy = 1;
        }
        if(pos_gem == 0 ){ /*put gem on tower graphic */
            graphic_map(board,wawe,height , width,list_image,player,(int) seconde,begin,tower_buy,gem_fusion,upgrade_mana,level_gem,pos_gem,gem1,gem2);
            tower_buy = 1;
            new_pos.y = new_pos.x = -1;
            gestion_click_gem_pose(player ,&pos_gem ,&gem_fusion ,&gem1 ,&gem2,&new_pos);
            if(gem1.teinte != -1 && new_pos.x != -1){
                if(put_gem_on_tower(&player,&board,new_pos,gem1) == 0 ){
                    pos_gem = 1;
                    gem1.teinte = -1; 
                }
            }  
        }
        if(gem_fusion == 0){
            graphic_map(board,wawe,height , width,list_image,player,(int) seconde,begin,tower_buy,gem_fusion,upgrade_mana,level_gem,pos_gem,gem1,gem2);
            gestion_click_gem_pose(player ,&pos_gem ,&gem_fusion ,&gem1 ,&gem2,&new_pos);
            if(gem_fusion == 2 ){
                fusion_gem(player.gem_player,gem1,gem2);
                gem_fusion = 1;
                gem1.teinte = gem2.teinte = -1;
                player.mana -= 100;
            }
        }
        if(tower_buy == 0) { /*buy tower graphic */
            graphic_map(board,wawe,height , width,list_image,player,(int) seconde,begin,tower_buy,gem_fusion,upgrade_mana,level_gem,pos_gem,gem1,gem2);
            new_pos = gestion_click_Tower_pose(board,player);
            if(buy_tower(&player,&board,new_pos) == 0){
                tower_buy = 1; 
            }
        }

        /*tower and shoot gestion */
        tower_attack(player.tower_player , player.list_shoots,&wawe);
        mouvement_shoot(player.list_shoots,&wawe,new_time.tv_sec);
        /*monster gestion*/
        monster_gain_mana(&wawe ,&player , board);
        effect_on_monster(&wawe,new_time.tv_sec);
        monster_move(&board,&wawe);
        seconde = end.tv_sec - start_game.tv_sec  ;
        clock_gettime(CLOCK_REALTIME,&new_time);
        frametime = new_time.tv_sec - end.tv_sec;
        frametime += (new_time.tv_sec - end.tv_sec) / 1.0E9;
        extratime = 1.0 / 60 - frametime;
        if(extratime > 0){
            MLV_wait_milliseconds((int) (extratime * 1000));
        }
    }
    /*end game */
    end_graphic(board);
    MLV_wait_seconds(5);
    /*we free all he malloc */
    free_all_monster(&wawe);
    wawe.Monster = NULL;
    free_player(&player );
    player.gem_player = NULL;
    player.list_shoots = NULL;
    player.tower_player = NULL;
    free_image_List(list_image);
    MLV_free_window();
    return 0;
}