#include "../include/tower.h"

/**
 * @brief Function to add a new Tower on the player's tower  stack
 * @param tower List_tower * pointeur on the player's tower stack
 * @param case_tower Case  position of the new tower
*/
void add_tower( List_Tower * tower ,const  Case case_tower){
    Tower * new_tower ;
    new_tower = (Tower * )malloc(sizeof(Tower));
    if(new_tower == NULL){
        fprintf(stderr,"Malloc tower pas bon \n");
        return ;
    }
    new_tower->position = case_tower;
    new_tower->next = tower->tower;
    tower->tower = new_tower;
    new_tower->gem.element = NEUTRAL;/*we initialize a gem voi*/
    new_tower->gem.niveau = 0 ; 
    new_tower->gem.teinte = 0 ;
    new_tower->gem.type = PURE;
    return ;
}


/**
 * @brief Function to know the number of tower ont the playr's tower stack
 * @param tower List_Tower stack of tower
 * @return number int  the number of tower 
*/
int number_of_tower (  List_Tower tower){
    int number ;
    number = 0;
    while (tower.tower != NULL){
        number += 1 ;
        tower.tower = tower.tower->next;
    }
    return number;    
}

/**
 * @brief Function to a tower from the stack of tower 
 * @param list_tower List_Tower *  pointeur on the stack of tower 
 * @param tower_delete  TOWER gem that we want to delete of the stack
*/
void free_tower_player(List_Tower * list_tower  ,  const Tower tower_delete){
    Tower * tmp ;
    Tower * tmp2 ;
    
    tmp = list_tower->tower;
    tmp2 = NULL;
    while (tmp != NULL && (tmp->position.x != tower_delete.position.x || tmp->position.y != tower_delete.position.y)){ 
        tmp = tmp->next;  
    }
    if(!tmp2){
        list_tower->tower = tmp->next;
    }
    else{
        tmp2->next = tmp->next;
    }
    free(tmp);
}