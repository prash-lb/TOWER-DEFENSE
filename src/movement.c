#include "../include/movement.h"

/**
 * @brief function that will find the new position where the monster need to go
 * @param monster_pos Case of the monster
 * @param board Plateau game 
 * @param direction int  
 * @return Case the new position 
*/
static Case new_case_to_get_monster(const Case_Monster monster_pos , const Plateau board,const int direction){
    int i;
    Case newcase  ;
    for (i = 0 ; i < board.number ; i++){
        if(direction == LEFT && (((int) monster_pos.x) == board.road[i].x) && (((int) monster_pos.y ) == board.road[i].y)  && (monster_pos.y -  board.road[i].y > 0.1) ){
            newcase.x = board.road[i].x;
            newcase.y = board.road[i].y;
        }
        else if(direction == TOP && (((int) monster_pos.x) == board.road[i].x) && (((int) monster_pos.y ) == board.road[i].y)  && (monster_pos.x -  board.road[i].x > 0.1) ){
            newcase.x = board.road[i].x;
            newcase.y = board.road[i].y;
        }
        else if ((((int) monster_pos.x) == board.road[i].x) && (((int) monster_pos.y )== board.road[i].y)){
            newcase.x = board.road[i + 1 ].x;
            newcase.y = board.road[i + 1 ].y;
        }
    }
    return newcase;
}


/**
 * @brief Function that will change the direction of the monster 
 * @param monster pointeur of the Monster
 * @param board the board game
*/
static void change_direction(Monster * monster , const Plateau board){
    Case new_case;
    assert(monster != NULL);

    new_case = new_case_to_get_monster(monster->coord,board,monster->direction);
    if(new_case.x == (int) monster->coord.x  && new_case.y != (int) monster->coord.y){   
        if(new_case.y >  monster->coord.y){
            monster->direction = RIGHT;
        }
        else if(new_case.y < monster->coord.y){
            monster->direction = LEFT;
        }
    }
    else if(new_case.x != (int) monster->coord.x  && new_case.y == (int) monster->coord.y){
        if(new_case.x > monster->coord.x){
            monster->direction = BOTTOM;
        }
        else if(new_case.x <  monster->coord.x){
            monster->direction = TOP;
        }
    }
}





/**
 * @brief Function that will increment or decrement the actual position of the monster by his spees take randomly between a interval  and by his residu if he have one 
 * @param monster  Monster * pointeur on the Monster
*/
static void speed_calcule_monster( Monster * monster ){
    float random; 
    double speed;
    assert(monster != NULL);
    random = (float) rand() / (float) RAND_MAX;
    switch (monster->residu){
        case RESIDU_DENDRO_HYDRO : 
            speed = 0;/*Monster immobilized*/
            break;

        case RESIDU_PYRO_HYDRO : /*Monster slowed  his speed divised by 1.25*/
            speed = (monster->type == AGILE)  ?  (( 0.9 * SPEED_AGILE / 60) + (random  * ( (1.1 * SPEED_AGILE /60) - ( 0.9 * SPEED_AGILE / 60)))) / 1.25  :  (( 0.9 * SPEED_DEFAULT / 60) + (random  * ( (1.1 * SPEED_DEFAULT/60) - ( 0.9 * SPEED_DEFAULT / 60)))) / 1.25;
            break;

        case RESIDU_HYDRO:/*Monster slowed  his speed divised by 1.5*/
            speed = (monster->type == AGILE)  ?  (( 0.9 * SPEED_AGILE / 60) + (random  * ( (1.1 * SPEED_AGILE /60) - ( 0.9 * SPEED_AGILE / 60)))) / 1.5  :  (( 0.9 * SPEED_DEFAULT / 60) + (random  * ( (1.1 * SPEED_DEFAULT/60) - ( 0.9 * SPEED_DEFAULT / 60)))) / 1.5;
            break;
        
        default:/*Monster normal speed*/
            speed = (monster->type == AGILE)  ?  (( 0.9 * SPEED_AGILE / 60) + (random  * ( (1.1 * SPEED_AGILE /60) - ( 0.9 * SPEED_AGILE / 60)))) :   ( 0.9 * SPEED_DEFAULT / 60) + (random  * ( (1.1 * SPEED_DEFAULT/60) - ( 0.9 * SPEED_DEFAULT / 60)));
            break;
    }
    switch (monster->direction){
    case TOP:
        monster->coord.x -= speed; 
        break;
    case BOTTOM:
        monster->coord.x += speed; 
        break;
    case RIGHT:
        monster->coord.y += speed; 
        break;
    case LEFT:
        monster->coord.y -= speed ; 
        break;
    default:
        break;
    }
}

/**
 * @brief Function that will verify if the monster can enter on the road if they are enough case 
 * @param monster Monster the monster
 * @param stack stack_Monster the stack of monster
 * @param board Platear the board game 
*/
static int monster_last_advance(const Monster monster ,stack_Monster stack, const Plateau board){
    while (stack.Monster){
        if(stack.Monster->id_monster != monster.id_monster && (stack.Monster->coord.x != board.road[0].x || stack.Monster->coord.y != board.road[0].y  )){

            switch (stack.Monster->type){
            case AGILE:
                if(sqrt( pow((monster.coord.x - stack.Monster->coord.x),2) +  pow(( monster.coord.y - stack.Monster->coord.y),2)) < 1.5){
                    return 1;
                }
                break;
            case CROWD:
                if(sqrt( pow((monster.coord.x - stack.Monster->coord.x),2) +  pow(( monster.coord.y - stack.Monster->coord.y),2)) < 1.5){
                    return 1;
                }
                break;
            default:
                if(sqrt( pow((monster.coord.x - stack.Monster->coord.x),2) +  pow(( monster.coord.y - stack.Monster->coord.y),2)) < 2){
                    return 1;
                }
                break;
            }
        }
        stack.Monster = stack.Monster->next;
    }
    return 0;
}

/**
 * @brief Function that will move the last monster with a latence 
 * @param monster Monster * pointeur on the  Monster
 * @param board board game
 * @param wawe stack_Monster the stack of monster  
*/
static void last_monster_move(Monster * monster , const Plateau board,stack_Monster wawe){
    assert(monster != NULL);
    change_direction( monster,board);
    if( monster->next == NULL){
        speed_calcule_monster( monster);
    }
    else{
        if(monster_last_advance(*monster,wawe,board) == 0){
            speed_calcule_monster(monster);
        }
    }   
       
}

/**
 * @brief Function that make the monster move 
 * @param board  Plateau * pointeur on the board game
 * @param wawe stack_Monster * pointeur on the stack of monster
*/
void monster_move(Plateau * board, stack_Monster * wawe){
    Monster * tmp ;
    Monster * tmp2;
    assert(board != NULL);
    assert(wawe != NULL);
    tmp = wawe->Monster;
    tmp2 = NULL;
    while(tmp != NULL){
        change_direction(tmp,*board);
        if((tmp->coord.x == board->road[0].x) && (tmp->coord.y == board->road[0].y) ){/*we keep the monster that will enter the path */
            tmp2 = tmp;
        }
        else if(((int) (tmp->coord.y )== board->road[board->number - 1].y) && ((int)(tmp->coord.x) == board->road[board->number - 1].x) ){/*if the monster has arrived at the final square we leave it at the final squaree à part si il est sur la case finale */
            tmp->coord.y =  board->road[board->number -1].y;
            tmp->coord.x =  board->road[board->number -1].x;
        }
        else if((( tmp->coord.x != board->road[0].x) || ( tmp->coord.y != board->road[0].y)) ){/*we move each monster forward unless they are on the starting square */
            speed_calcule_monster(tmp);
        }
        tmp = tmp->next;
    }
    if(tmp2 != NULL){/*we move the monster that are going to enter in the path  */
        last_monster_move(tmp2,*board,*wawe);
    } 
}

/**
 * @brief Function to detect if a monster is  around the tower
 * @param pos_tower Case position of the tower
 * @param pos_monster Case_Monster  position of the monster
 * @return int 0 if the monster is around else 1 
*/
static int Monster_around_tower(Case pos_tower,Case_Monster pos_monster){
    if(sqrt( pow(( pos_tower.x - pos_monster.x),2) + pow((pos_tower.y - pos_monster.y),2)) <= 3){/* at a distance of 3 case */
        return 0;
    }
    return 1;
}


/**
 * @brief Function to use the effect of PYRO on  the monster 
 * @param monster  Monster the monster
 * @param shoot_monster Shoot the shoot 
 * @param stack stack_Monster * pointeur on the stack of monster
*/
static void pyro_effect(Monster  monster , Shoot shoot_monster, stack_Monster * stack){
    Monster * tmp ;
    tmp = stack->Monster;
    while(tmp!= NULL){
        if(monster.id_monster != tmp->id_monster && sqrt( pow((shoot_monster.position.x - tmp->coord.x),2) + pow((shoot_monster.position.y - tmp->coord.y ),2)) < 2){
            tmp->life -=  ((2  * pow(2,shoot_monster.gem.niveau) * (1 - cos(shoot_monster.gem.niveau - tmp->rgb) / 2))* 15 ) / 100; /* damade the monster arrounf of the shoot at 2 case of distace*/
        }
        tmp = tmp->next;
    }
}

/**
 * @brief Function to use the effect of PYRO + HYDRO on the monster
 * @param monster Monster the monster 
 * @param shoot_monster Shoot the shoot
 * @param stack stack_Monster * pointeur on the stack of monster 
 * @param new_time int time when the effect begin 
*/
static void pyro_hydro_effect(Monster  monster , Shoot shoot_monster, stack_Monster * stack ,int new_time){
    Monster * tmp ;
    tmp = stack->Monster;
    while(tmp!= NULL){
        if(monster.id_monster != tmp->id_monster && sqrt( pow((shoot_monster.position.x - tmp->coord.x),2) + pow((shoot_monster.position.y - tmp->coord.y ),2)) < 3.5){/* damage the monster arround of the shoot of 3.5 case*/
            tmp->life -=  ((2  * pow(2,shoot_monster.gem.niveau) * (1 - cos(shoot_monster.gem.teinte - tmp->rgb) / 2))* 3 ) / 100;
            tmp->residu = RESIDU_PYRO_HYDRO;
            tmp->time = new_time;
        }
        tmp = tmp->next;
    }
}


/**
 * @brief Function that set the residu on the monster by which tower shoot on him
 * @param tmp3 Shoot the shoot 
 * @param target Monster * pointeur on monster
 * @param time_begin int time of effect begin
 * @param stack stack_Monster * pointeur on stack of monster 
*/
static void set_residu_on_monster(Shoot tmp3,Monster * target,int time_begin,stack_Monster * stack){
    
    switch (tmp3.gem.element){
        case PYRO:
            if(target->residu == RESIDU_NEUTRAL ){
                pyro_effect(*target,tmp3,stack);
                target->residu = RESIDU_PYRO;
            }
            else if(target->residu == RESIDU_HYDRO){
                pyro_hydro_effect(*target,tmp3,stack,time_begin);
                target->residu = RESIDU_PYRO_HYDRO;
            }
            else if(target->residu == RESIDU_DENDRO){
                target->life -= tmp3.damage * 2;
                target->residu = RESIDU_NEUTRAL;
            }
            break;
        case HYDRO:
            if(target->residu == RESIDU_NEUTRAL ){
                target->residu = RESIDU_HYDRO;
                target->time = time_begin;
            }
            else if(target->residu == RESIDU_PYRO){
                pyro_hydro_effect(*target,tmp3,stack,time_begin);
                target->residu = RESIDU_PYRO_HYDRO;
            }
            else if(target->residu == RESIDU_DENDRO){
                target->residu = RESIDU_DENDRO_HYDRO;
                target->time = time_begin;
            }
            break;
        case DENDRO:
            if(target->residu == RESIDU_NEUTRAL ){
                target->residu = RESIDU_DENDRO;
                target->time = time_begin;
                target->damage = (int) ((tmp3.damage * 2.5) / 100);
            }
            else if(target->residu == RESIDU_PYRO){
                target->life -= tmp3.damage * 2;
                target->residu = RESIDU_NEUTRAL;
            }
            else if(target->residu == RESIDU_HYDRO){
                target->residu = RESIDU_DENDRO_HYDRO;
                target->time = time_begin;
            }
            break;
        default:
            break;
    }
} 

/**
 * @brief Function thaht make the shoot move 
 * @param shoot_player List_shoot * stack shoot 
 * @param monster stack_monster * stack of the monster
 * @param time_begin int effect begin time
*/
void mouvement_shoot(List_Shoot * shoot_player, stack_Monster * monster,int time_begin ){
    Monster* target ;
    Shoot * tmp3;
    double xv,yv;
    tmp3 = shoot_player->shoots;

    while(tmp3 != NULL){
        target = find_monster(tmp3->id_monster,monster);
        if(target != NULL){
            xv = ((target->coord.x - tmp3->position.x) / (sqrt( pow((target->coord.x - tmp3->position.x),2) +  pow((target->coord.y - tmp3->position.y),2) )));
            yv = ((target->coord.y - tmp3->position.y) / (sqrt( pow((target->coord.x - tmp3->position.x),2) +  pow((target->coord.y - tmp3->position.y),2) )));
            if((sqrt( pow((target->coord.x - tmp3->position.x),2) + pow((target->coord.y - tmp3->position.y),2) )) < 0.5  ){ /*the shoot get his target */
                tmp3->position.x = target->coord.x;
                tmp3->position.y = target->coord.y;
                if(tmp3->gem.element == NEUTRAL){
                    target->life -= (tmp3->damage * 2);
                }
                else{
                    target->life -= tmp3->damage;
                }
                set_residu_on_monster(*tmp3,target,time_begin,monster);
                free_shoot_end(shoot_player,target->coord);
            }
            else{/* we move the shoot */
                tmp3->position.x += xv * 0.5;
                tmp3->position.y += yv * 0.5;
            }
        }
        tmp3 = tmp3->next;
    }
         
}


/**
 * @brief Function thath will look if the monster have already a shoot from this tower  who target him if 0 no and 1 if yes
 * @param player_shoot List_shoot the stack of shoot 
 * @param id_monster int the id of the monster to find him
 * @param tower_position the position of the tower that are going to attack the monster 
*/
static  int check_attack(List_Shoot player_shoot ,int id_monster,Case tower_position  ){
    List_Shoot tmp ;
    tmp = player_shoot;

    while(tmp.shoots != NULL){
        if(tmp.shoots->id_monster == id_monster && tmp.shoots->position_tower.x == tower_position.x  && tmp.shoots->position_tower.y == tower_position.y){
            return 1;
        }
        tmp.shoots = tmp.shoots->next;
    }
    return 0;
}


/**
 * @brief fuction thaht will create the shoot  by tower when the tower detect monster around 
 * @param tower List_Tower * pointeur the stack of tower
 * @param player_shoot List_Shoot * pointeur  the stack of shoot
 * @param monster stack_Monster * pointeur on the stack of monster
*/
void tower_attack(List_Tower * tower,List_Shoot * player_shoot,stack_Monster * monster){
    Tower * tmp ;
    Monster * tmp2;
    Monster * target ; 
    tmp = tower->tower;
    while(tmp!= NULL){
        target = NULL;
        tmp2 = monster->Monster;

        if(tmp->gem.element != NEUTRAL || tmp->gem.type != PURE){/* only the gem mixte or  with a element other than NEUTRAL can shoot */
            while (tmp2 != NULL){
                if(target == NULL &&  (Monster_around_tower(tmp->position, tmp2->coord) == 0 )){
                    target = tmp2;
                }
                else if( target != NULL &&  (Monster_around_tower(tmp->position, tmp2->coord) == 0 ) && (target->life < tmp2->life)){/*we are going to take as target the monster that have the biggest life arround the tower*/
                    target = tmp2;
                }
                tmp2 = tmp2->next;
            }
            if(target !=NULL && check_attack(*player_shoot, target->id_monster ,tmp->position) == 0 &&  number_of_shoot(*player_shoot ,tmp->position) < 2){/*initialize the shoot only if the tower whee he is from have less than 2 shoot and if he doesn't have already a shoo on the monster target from the same tower*/
                add_shoot(player_shoot);
                player_shoot->shoots->id_monster = target->id_monster;
                player_shoot->shoots->damage = 4  * pow(2,tmp->gem.niveau) * (1 - cos(tmp->gem.teinte - target->rgb)/2);
                player_shoot->shoots->position.x = tmp->position.x + 0.5;
                player_shoot->shoots->position.y = tmp->position.y + 0.5;
                player_shoot->shoots->gem.teinte = tmp->gem.teinte;
                player_shoot->shoots->gem.element = tmp->gem.element;
                player_shoot->shoots->gem.niveau = tmp->gem.niveau;
                player_shoot->shoots->position_tower.x = tmp->position.x;
                player_shoot->shoots->position_tower.y = tmp->position.y;
            } 
        }
        tmp = tmp->next;
    }

}

