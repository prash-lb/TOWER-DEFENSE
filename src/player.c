#include "../include/player.h"

/**
 * @brief This function will init the player and his pile of tower 
 * @param player pointeur
*/
void player_init (Player * player){
    player->tower_player = (List_Tower *) malloc(sizeof(List_Tower));
    if (!player->tower_player){
        fprintf (stderr, "ERREUR MALLOC LISTE TOWER PLAYER \n");
        return;
    }
    player->gem_player = (List_Gem_Avaible * )malloc(sizeof(List_Gem_Avaible));
    if (!player->gem_player){
        fprintf (stderr, "ERREUR MALLOC LISTE GEM PLAYER \n");
        return;
    }
    player->list_shoots = (List_Shoot* )malloc(sizeof(List_Shoot));
    if (!player->list_shoots){
        fprintf (stderr, "ERREUR MALLOC LISTE Gshoot player  \n");
        return;
    }
    player->list_shoots->shoots = NULL;
    player->tower_player->tower= NULL;
    player->gem_player->gem_list = NULL;
    player->level = 0;
    player->mana = 150;
}


/**
 * @brief function that verify that the player are going to put the tower aboard the road
 * @param spot the case that we  are going to check
 * @param raod the case of the road 
 * @param board the board game 
 * @return 0 if it s good and 1 if not 
*/
static int verification_case_road ( const Case spot, const Case road ,const Plateau board){
    if((spot.x == road.x - 1 && spot.y == road.y) || (spot.x == road.x + 1 && spot.y == road.y) || (spot.x == road.x && spot.y == road.y + 1) || (spot.x == road.x && spot.y == road.y - 1)){
        return 0 ;
    }
    return 1;
}

/**
 * @brief the function that verify that on the board  the case that the player want to put his tower is  avaible  
 * @param board pointeur 
 * @param spot_tower Case
 * @return 1 if he can't buy
 * @return 0 if it's good and he will put  the tower on the board 
*/
static int tower_on_board(const Case spot_tower , Plateau * board ){
    int i;
    assert(board != NULL);
    for(i = 2; i < board->number - 2 ; i++){
        if(board->plateau[spot_tower.x][spot_tower.y] == VIDE && verification_case_road(spot_tower, board->road[i], *board) == 0 ){
            board->plateau[spot_tower.x][spot_tower.y] = TOWER_VOID ; 
            return 0;
        }
    }
    return 1;
}

/**
 * @brief the function that verify if he can buy a tower or not 
 * @param player pointeur
 * @param board pointeur 
 * @param spot Case
 * @return 1 if he can't buy
 * @return 0 if it's good and he will buy the tower
*/
int buy_tower(Player * player , Plateau * board , const Case spot){
    int number_tower,price;
    assert(player != NULL);
    assert(board != NULL);
    number_tower = number_of_tower(*player->tower_player);

    if(number_tower < 3  && (tower_on_board(spot,board) == 0)){
        add_tower(player->tower_player,spot);  
        return 0;      
    }
    price = 100 * (pow(2,(number_tower - 4)));
    if(player->mana >= price && (tower_on_board(spot,board) == 0)){
        player->mana -= price;
        add_tower(player->tower_player,spot);  
        return 0;
    }
    return 1;
}

/**
 * @brief Update the board with the actuel tower and gem put on them on the board
 * @param tower List tower of the player
 * @param board pointeur on the board
*/
static void updade_tower_board(List_Tower tower, Plateau * board){
    assert(board != NULL);
    while (tower.tower){
        switch (tower.tower->gem.element)
        {
            case NEUTRAL:
                board->plateau[tower.tower->position.x][tower.tower->position.y] = TOWER_VOID;
                break;
            case PYRO:
                board->plateau[tower.tower->position.x][tower.tower->position.y] = TOWER_PYRO;
                break;
            case DENDRO:
                board->plateau[tower.tower->position.x][tower.tower->position.y] = TOWER_DENDRO;
                break;
            default:
                board->plateau[tower.tower->position.x][tower.tower->position.y] = TOWER_HYDRO;
                break;
        }
        if(tower.tower->gem.type == MIXED){
            board->plateau[tower.tower->position.x][tower.tower->position.y] = TOWER_MIXTE;
        }
        tower.tower = tower.tower->next;
    }
}

/**
 * @brief Function that allow to buy a gem randomly
 * @param player pointeur on Player
 * @param board Plateau 
 * @param level int level of gem 
 * @return 1 if he can't buy and 0 if it's okay 
*/
int buy_gem(Player * player,const Plateau board , int level){
    if(player->mana >= (100 * pow(2,level))){
        add_gem(player->gem_player,level);
        player->mana -=  (100 * pow(2,level));
        return 0;
    }
    return 1;
}

/**
 * @brief will take two fem a mixed them 
 * @param player pointeur on Player
 * @param gem1 Gem 
 * @param gem2 Gem 
 * @return 1 if he can't mixed them and 0 if it's good
*/
int gem_fusion_player (Player * player , const Gem gem1,const Gem gem2){
    assert(player != NULL);
    if(player->mana < 100){
        fprintf(stdout,"pas assez de mana pour fusionner les gems \n");
        return 1;
    }
    if(gem1.niveau != gem2.niveau){
        fprintf(stdout,"Les deux gemme à fusionner ne sont pas du même niveau \n");
        return 1;
    }
    fusion_gem(player->gem_player,gem1,gem2);
    delete_gem_player(player->gem_player,gem1);
    delete_gem_player(player->gem_player,gem2);
    player->mana -= 100;
    return 0;

}

/**
 * @brief Function who will put the gem wanted on the tower wanted 
 * @param player pointeur on Player
 * @param board pointeur on Plateau
 * @param spot position of the tower
 * @param new_gem gem that will be put on the tower
 * @return 1 if it's not good and 0 if it's good
*/
int put_gem_on_tower(Player * player ,   Plateau * board , const Case spot ,const Gem new_gem){
    Tower * tmp ;
    assert(player != NULL);
    assert(board != NULL);
    tmp =  player->tower_player->tower;    
    while ((tmp  != NULL )){
        if( tmp->position.x == spot.x  && tmp->position.y == spot.y){
            tmp->gem = new_gem;
            updade_tower_board(*player->tower_player,board);
            delete_gem_player(player->gem_player,new_gem);
            return 0 ;
        }
        tmp = tmp->next;
    }
    fprintf(stdout,"Il n y a pas cette tour\n");
    return 1;
}

/**
 * @brief the function that will upgrade the mana of the player if it's possible 
 * @param player pointeur
 * @return 1 if he can't upgrade 
 * @return 0 if it's good and he will upgrade
*/
int upgrade_level_mana(Player *player){
    int price ;
    assert(player != NULL);
    price = 500 * pow(1.4,player->level);
    if( player->mana >= price ){
        player->level += 1;
        player->mana -= price;
        return 0;
    }
    return 1;
}


/**
 * @brief that will free the monster when he reach the payer camp on the memory  and make the damage on the mana 
 * @param  stack pointeur on the pile of wawe
 * @param board Plateau
 * @param int 0 or 1 if 1 a monster is passed 
*/
int monster_on_player(stack_Monster * stack,const Plateau board, Player * player){
    Monster * tmp;
    assert(stack != NULL);
    assert(player != NULL);

    tmp = stack->Monster;
    while (tmp != NULL){
        if(((tmp->coord.x == board.road[board.number -1  ].x) && (tmp->coord.y == board.road[board.number - 1 ].y))){
            player->mana -= (int) (((tmp->life_value_init * 15 ) / 100) * pow(1.3,player->level)) ;
            if(player->mana <= 0){
                return 1;
            } 
            tmp->coord.x = board.road[0].x;
            tmp->coord.y = board.road[0].y;
        }
        tmp = tmp->next;
    }
    return 0;
    
}

/**
 * @brief Function that will gave the mana after that we have killed a monster 
 * @param monster stack_monster the stack of monster
 * @param player pointeur on Player
 * @param board the Plateau 
*/
void monster_gain_mana(stack_Monster * monster , Player * player , Plateau board){
    Monster * tmp ;
    tmp = monster->Monster;
    while (tmp != NULL){
        if(tmp->life <= 0 ){
            player->mana += (int) ((tmp->life_value_init * 10) / 100) * pow(1.3,player->level);
            if(player->mana > (MAX_MANA * pow(1.4,player->level))){
                player->mana = (MAX_MANA * pow(1.4,player->level));
            }
            while(shoot_in_monster_present (*player->list_shoots,tmp->id_monster) == 0){
                free_shoot(player->list_shoots,tmp->id_monster);
            }
            free_monster(monster,tmp);
        }
        tmp = tmp->next;
    }
}

/**
 * @brief function to free player
 * @param player Player * pointeur on player
*/
void free_player(Player * player ){
    Gem_Avaible * gem;
    Tower * tower ;
    Shoot * shoot1;
    shoot1 = player->list_shoots->shoots;
    gem = player->gem_player->gem_list;
    tower = player->tower_player->tower; 
    while(gem != NULL){
        delete_gem_player(player->gem_player,gem->gem);
        gem = gem->next;
    }
    if(player->gem_player->gem_list == NULL){
        free(player->gem_player->gem_list);
        free(player->gem_player);
    }
    while(tower != NULL){
        free_tower_player(player->tower_player,*tower);
        tower = tower->next;
    }
    if(player->tower_player->tower == NULL){
        free(player->tower_player->tower);
        free(player->tower_player);
    }
    while(shoot1 != NULL){
        free_shoot(player->list_shoots,shoot1->id_monster);
        shoot1 = shoot1->next;
    }
    if(player->list_shoots->shoots == NULL){
        free(player->list_shoots->shoots);
        free(player->list_shoots);
    }
    
}