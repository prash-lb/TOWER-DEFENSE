#ifndef __GEM__
#define __GEM__

#include "../include/game_engine.h"

typedef enum _gem_element {
    NEUTRAL,
    PYRO,
    DENDRO,
    HYDRO
}GemElement;

typedef enum _type_gem {
    PURE,
    MIXED
}GemType;

typedef struct _gem{
    int niveau;
    int type ; /*pure or mixte*/
    int element; /*dendro or hydro or pyro */
    int teinte; /*between 0 an 360*/
}Gem;

typedef struct gem_avaible{
    Gem gem;
    struct gem_avaible * next;
}Gem_Avaible;

typedef struct _list_gem_avaible{
    Gem_Avaible * gem_list;
}List_Gem_Avaible;

void fusion_gem( List_Gem_Avaible *gem_player, Gem gem1 , Gem  gem2);
void delete_gem_player(List_Gem_Avaible * delete_gem_player , Gem gem_delete);
void add_gem( List_Gem_Avaible * gem_player,int level );
int number_of_a_gem(Gem gem , List_Gem_Avaible gem_player);

#endif