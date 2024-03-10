#include "../include/shoot.h"


/**
 * @brief will put a new shoot on the tower list shoot
 * @param list_shoot pointeur  on the list shoot of the tower
*/
void add_shoot( List_Shoot * list_shoot ){
    Shoot * new_shoot;
    new_shoot =  (Shoot * )malloc(sizeof(Shoot));
    if(new_shoot == NULL){
        fprintf(stderr,"Malloc shoot pas bon \n");
        return ;
    }
    new_shoot->next = list_shoot->shoots;
    list_shoot->shoots = new_shoot;
    return ;
}

/**
 * @brief to see if a shoot target a monster  who is death to free 
 * @param list_Shoot List_Shoot  stack of shoot 
 * @param monster int 
*/
int  shoot_in_monster_present (List_Shoot list_Shoot , int monster){
    List_Shoot tmp;
    tmp = list_Shoot;
    while( tmp.shoots != NULL){
        if (tmp.shoots->id_monster == monster){
            return 0;
        }
        tmp.shoots = tmp.shoots->next;
    }
    return 1;
}

/**
 * @brief function to free the shoot when he get his targe 
 * @param List_Shoot List_Shoot * stack of the shoot 
 * @param position Case_Monster the position of the monster target 
*/
void free_shoot_end(List_Shoot * list_Shoot, Case_Monster position){
    Shoot * tmp ;
    Shoot * tmp2;
    tmp = list_Shoot->shoots;
    tmp2 = NULL;
    while(tmp != NULL && tmp->position.x != position.x && tmp->position.y != position.y ){
        tmp2 = tmp;
        tmp = tmp->next;
    }
    if(tmp2 == NULL){
        list_Shoot->shoots = tmp->next;
    }
    else{
        tmp2->next = tmp->next;
    }
    free(tmp);
}

/**
 * @brief function to free all the shoot for a monster if the monster is dead and doesn't exit anuymore
 * @param list_shoot List_Shoot * stack of the shoot 
 * @param target int id of the monster 
*/
void free_shoot(List_Shoot * list_Shoot , int target){
    Shoot * tmp;
    Shoot * tmp2;
    assert(list_Shoot != NULL);
    tmp = list_Shoot->shoots;
    tmp2 = NULL;
    while (tmp != NULL  && tmp->id_monster != target){
        tmp2 = tmp;
        tmp = tmp->next;
    }
    if(tmp2 == NULL){
        list_Shoot->shoots = tmp->next;
    }
    else{
        tmp2->next = tmp->next;
    }
    free(tmp);
}

int number_of_shoot(List_Shoot shoots_tower , Case pos_tower){
    List_Shoot tmp;
    int cpt ;
    cpt = 0;
    while(tmp.shoots != NULL){
        if(tmp.shoots->position_tower.x == pos_tower.x && tmp.shoots->position_tower.y == pos_tower.y){
            cpt +=1;
        }
        tmp.shoots = tmp.shoots->next;
    }
    return cpt;
}