#include "../include/gem.h"

/**
 * @brief Function to delete a gem on the  player's GEM stack
 * @param list_gem_player List_Gem_Avaible *  pointeur on the stack of the gem  player 
 * @param gem_delete  Gem gem that we want to delete of the stack
*/
void delete_gem_player(List_Gem_Avaible * list_gem_player ,  const Gem gem_delete){
    Gem_Avaible * tmp ;
    Gem_Avaible * tmp2 ;
    tmp = list_gem_player->gem_list;
    tmp2 = NULL;
    while (tmp != NULL && (tmp->gem.niveau != gem_delete.niveau || tmp->gem.element != gem_delete.element || tmp->gem.teinte != gem_delete.teinte || tmp->gem.type != gem_delete.type)){ /*we are going to find where is the gem on the stack*/
        tmp2 = tmp;
        tmp = tmp->next;  
    }
    if(!tmp2){/*if he is the head of the stack */
        list_gem_player->gem_list = tmp->next;
    }
    else{
        tmp2->next = tmp->next;
    }
    free(tmp);
}

/**
 * @brief Creation of a new gem randomly
 * @param gem pointeur of Gem
 * @param level level of gem 
*/
static void create_gem( Gem * gem, int level){
    int random_type;

    assert(gem != NULL);

    gem->type = PURE;
    gem->niveau  = level;
    random_type = (rand() % 3) + 1 ;
    
    switch (random_type){
        case PYRO:
            gem->element = PYRO;
            gem->teinte = (rand() % 2 == 0) ?  rand() % 31 :  (rand() % (360 - 330) + 330 );
            break;
        case DENDRO:
            gem->element = DENDRO;
            gem->teinte = (rand() % (151 - 90) + 90) ;
            break;
        default:
            gem->element = HYDRO;
            gem->teinte = (rand() % (271 - 210) + 210) ;
            break;
    }
}

/**
 * @brief function that will fusion two gem choiced and add that gem at the player's gemstack
 * @param gem_player List_Gem_Avaible pointeur on the player's gem_stack
 * @param gem1 Gem 
 * @param gem2 Gem
*/
void fusion_gem( List_Gem_Avaible * gem_player, Gem gem1 , Gem  gem2){
    int new_teinte = (int) ((gem1.teinte + gem2.teinte)/2);
    if(gem1.niveau == gem2.niveau){
        add_gem(gem_player,gem1.niveau + 1);
        if(gem1.type == PURE && gem2.type == PURE && (gem1.element == gem2.element)){ 
            gem_player->gem_list->gem.element = gem2.element;
            gem_player->gem_list->gem.type = PURE; 
            gem_player->gem_list->gem.niveau = gem1.niveau + 1 ; 
            gem_player->gem_list->gem.teinte = new_teinte;
        }
        else{
            gem_player->gem_list->gem.type = MIXED;
            gem_player->gem_list->gem.element = NEUTRAL;
            gem_player->gem_list->gem.niveau = gem1.niveau + 1 ; 
            gem_player->gem_list->gem.teinte = new_teinte;
        }
        delete_gem_player(gem_player,gem1);
        delete_gem_player(gem_player,gem2);
    }
    
}
/**
 * @brief Function to calculate the number of the same gem than the gem giving in the parameter of the function in the player's gem stack
 * @param gem Gem
 * @param gem_player List_Gem_Avaible the player's gem stack 
 * @return cpt the number 
*/
int number_of_a_gem(Gem gem , List_Gem_Avaible gem_player){
    List_Gem_Avaible tmp;
    int cpt ;

    tmp = gem_player;
    cpt = 0;
    while (tmp.gem_list != NULL){
        if(tmp.gem_list->gem.element == gem.element && tmp.gem_list->gem.niveau == gem.niveau && tmp.gem_list->gem.teinte == gem.teinte && tmp.gem_list->gem.type == gem.type){
            cpt += 1;
        }
        tmp.gem_list = tmp.gem_list->next;
    }
    return cpt;
    
}

/**
 * @brief Add a new gem on  the player's gem stack
 * @param gem_player List_Gem_Avaible *  pointeur on the player's gem stack
 * @param level int  level of the gem bought 
*/
void add_gem( List_Gem_Avaible * gem_player, int level){
    Gem_Avaible * new_gem = (Gem_Avaible * )malloc(sizeof(Gem_Avaible));
    if(!new_gem){
        fprintf(stderr,"Malloc Gem Avaible not malloc\n");
        return ;
    }
    create_gem(&new_gem->gem,level) ;  
    new_gem->next = gem_player->gem_list;
    gem_player->gem_list = new_gem;
}