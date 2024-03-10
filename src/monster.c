#include "../include/monster.h"

/**
 * @brief Function that will generate the type of the wawe of monster randomly
 * @param Plateau board
 * @return int  the type of the wawe of monster 
*/
static int type_wawe_monster(const Plateau board){
    int random;

    random = (rand()%101);

    if(random<= 50){
        return AGILE;
    }
    else if (random <= 70) {
        return CROWD;
    }
    else if (random <= 90){
        return AGILE;
    }
    else if ( board.turn > 4 && random <= 100){
        return BOSS;
    }
    return type_wawe_monster(board);
}

/**
 * @brief Function to initialize a monster 
 * @param WaveType int to identifies the type of monster we need to create 
 * @param board board game
 * @return new_monster Monster*
 */
static Monster* init_Monster (const int WaveType, const Plateau  board) {
    Monster* new_monster;

    new_monster = (Monster*) malloc(sizeof(Monster));

    if(NULL == new_monster) {
        fprintf(stderr, "Error, malloc in newMonser");
        return new_monster;
    }

    switch (WaveType) {
        case BOSS:
            new_monster->life = 12 * H * pow(1.2, board.turn);
            new_monster->life_value_init = 12 * H * pow(1.2, board.turn);
            break;

        case AGILE:
            new_monster->life =  H * pow(1.2, board.turn);
            new_monster->life_value_init =  H * pow(1.2, board.turn);
            break;
        
        default:
            new_monster->life = H * pow(1.2, board.turn);
            new_monster->life_value_init =  H * pow(1.2, board.turn);
            break;
    }  
    new_monster->type = WaveType;
    new_monster->rgb = rand()% 360;
    new_monster->residu = RESIDU_NEUTRAL;
    new_monster->time = 0;
    new_monster->damage = 0; 
    new_monster->next = NULL;
    new_monster->coord.x = board.road[0].x;
    new_monster->coord.y = board.road[0].y;

    return new_monster;
    
}

/**
 * @brief Function to malloc the stack of monster
 * @param  wawe stackMonster* pointeur on the satck of monster
 */
void init_Array_Monster (stack_Monster * wawe) {    
    wawe = (stack_Monster*) malloc(sizeof(stack_Monster));
    if(wawe == NULL) {
        fprintf(stderr, "Error, malloc in stack_Monster");
        return ;
    }
    wawe->Monster = NULL;
}


/**
 * @brief Function to free a Monster on the stack
 * @param stack_Wawe * stack_Wawe on the stack of monster
 * @param monster * monster pointeur on the monster
*/
void free_monster(stack_Monster * stack , Monster * monster){
    Monster * tmp ; 
    Monster * tmp2 ;

    tmp = stack->Monster;
    tmp2 = NULL;

    while(tmp != NULL && tmp->id_monster != monster->id_monster){/*we are going to find where is the monster on the stack*/
        tmp2 = tmp;
        tmp = tmp->next;
    }
    if(!tmp2 ){/*if he is the head of the stack */
        stack->Monster = tmp->next;
    }
    else{
        tmp2->next = tmp->next;
    }
    free(tmp);
}

/**
 * @brief Function to delete all the monster on the stack and free the stack at the end of the game 
 * @param stack stack_monster * pointeur on the stack of monster 
*/
void free_all_monster(stack_Monster * stack){
    Monster * tmp;

    tmp = stack->Monster;
    while (tmp != NULL){
        free_monster(stack,tmp);
        tmp = tmp->next;
    }
    if(stack->Monster == NULL){
        free(stack->Monster);
    }
    
}
/**
 * @brief Function to wreate the wawe of monster on the stack of monster 
 * @param stack stack_Monster * pointeur on the stack of monster
 * @param board: Plateau board game 
 * @param id int * pointeur to the id it help to identify the monster after on the stack
 */
void  Create_Monster_Wave (stack_Monster * stack, const Plateau  board,int * id) {
    int index,type_wawe;
    Monster *tmp;
        
    type_wawe = type_wawe_monster(board);
    switch (type_wawe) {
        case CROWD:
            for(index = 0; index < 24; index++) {
                tmp = init_Monster(CROWD, board);
                *id += 1 ;
                tmp->id_monster = *id;
                tmp->next = stack->Monster;
                stack->Monster = tmp;
            }
            break;
        
        case AGILE:
            for(index = 0; index <  12; index++) {
                tmp = init_Monster(AGILE, board);        
                *id += 1 ;
                tmp->id_monster = *id;
                tmp->next = stack->Monster;
                stack->Monster = tmp;
            }
            break;
        
        case BOSS:
            for(index = 0; index < 2; index++) {
                tmp = init_Monster(BOSS, board);
                *id += 1 ;
                tmp->id_monster = *id;
                tmp->next = stack->Monster;
                stack->Monster = tmp;
            }
            break;
        
        default:
            for(index = 0; index <  12; index++) {
                tmp = init_Monster(NORMAL, board);
                *id += 1 ;
                tmp->id_monster = *id;
                tmp->next = stack->Monster;
                stack->Monster = tmp;
            }
            break;
    }
}

/**
 * @brief function to find  a monster on the stack 
 * @param id int id of the monster
 * @param monster stack_monster * stack of monster
 * @return Monster  the monster that we have find else NULL
*/
Monster * find_monster(int id , stack_Monster* monster){
    Monster * tmp;
    Monster * tmp2 ;
    tmp2 = NULL;
    tmp = monster->Monster;
    while(tmp != NULL  ){
        if(tmp->id_monster == id){
            tmp2 = tmp;
            return tmp2;
        }
        tmp = tmp->next;
    }
    return tmp2 ;
}


/**
 * @brief Function to look the time of the effect of the residue on the monster and make the effect (Dendro)
 * @param monster stack_Monster * stack of the monster
 * @param time int time of seconde of the game 
*/
void effect_on_monster(stack_Monster * monster,int time){
    Monster * tmp;
    tmp = monster->Monster;
    while(tmp != NULL){
        switch (tmp->residu){
            case RESIDU_HYDRO:
                if(time - tmp->time >= 10 ){ /* working during 10 seconde */
                    tmp->residu = RESIDU_NEUTRAL;
                }
                break;
            case RESIDU_DENDRO:
                if(time - tmp->time >= 10 ){/* working during 10 seconde */
                    tmp->residu = RESIDU_NEUTRAL;
                }
                tmp->life -= tmp->damage;
                break;
            case RESIDU_PYRO_HYDRO :
                if(time - tmp->time >= 5 ){/* working during 5 seconde */
                    tmp->residu = RESIDU_NEUTRAL;
                }
                break;
            case RESIDU_DENDRO_HYDRO:
                if(time - tmp->time >= 3 ){/* working during 3 seconde */
                    tmp->residu = RESIDU_NEUTRAL;
                }
                break;
            default:
                break;
        }
        tmp = tmp->next;
    }
}
