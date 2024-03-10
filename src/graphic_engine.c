#include "../include/graphic_engine.h"

/**
 * @brief fucntion thaht will create a array of image for our game 
 * @param height int
 * @param width int
 * @return image_List MLV_Image ** list of image 
*/
MLV_Image ** int_image(const int height ,const  int width){
    int i ;
    MLV_Image ** image_List ,*monster1, *monster2,*monster3,*  monster , * road , *lawn , *tower_img , *road_tower , * tower_hydro,*tower_dendro,*tower_pyro,*tower_mixte,*image_mixte,*image_hydro,*image_pyro,*image_dendro ,*agile_monster , *boss;

    image_List = (MLV_Image ** ) malloc (sizeof(MLV_Image * )*10);
    for(i = 0 ; i < 10 ; i++){
        image_List[i] = (MLV_Image *) malloc (sizeof(MLV_Image * ));
    }
    monster = MLV_load_image("img/monster.png");
    agile_monster = MLV_load_image("img/monster_fast.png");
    boss = MLV_load_image("img/boss.png");

    lawn = MLV_load_image("img/ground.png");
    road = MLV_load_image("img/road.png");
    tower_img = MLV_load_image("img/tower.png");
    image_hydro = MLV_load_image("img/hydro.png");
    image_dendro = MLV_load_image("img/dendro.png");
    image_pyro = MLV_load_image("img/pyro.png");
    image_mixte = MLV_load_image("img/mixte.png");

    road_tower = MLV_create_image(300,300);
    tower_hydro = MLV_create_image(300,300);
    tower_dendro = MLV_create_image(300,300);
    tower_pyro = MLV_create_image(300,300);
    tower_mixte = MLV_create_image(300,300);
    monster1 = MLV_create_image(300,300);
    monster2 = MLV_create_image(300,300);
    monster3 = MLV_create_image(300,300);

    if( ! road || !monster || ! lawn || !tower_img || !image_dendro || !image_hydro || !image_pyro || !image_mixte || !boss || !agile_monster  ){
        fprintf( stderr, "Impossible de lire le fichier des images \n" );
        exit(0);
    }
    image_List[0] =  lawn;
    image_List[1] =  road;
    image_List[2] =  road_tower;
    image_List[3] =  tower_dendro;
    image_List[4] =  tower_hydro;
    image_List[5] =  tower_pyro;
    image_List[6] =  tower_mixte;
    image_List[7] =  monster1;
    image_List[8] =  monster2;
    image_List[9] =  monster3;

    MLV_resize_image(monster,300,300);
    MLV_resize_image(agile_monster,300,300);
    MLV_resize_image(boss,300,300);
    MLV_resize_image(road,300,300);
    MLV_resize_image(tower_img,300,300);
    MLV_resize_image(lawn,300,300);
    MLV_resize_image(image_hydro,300,300);
    MLV_resize_image(image_pyro,300,300);
    MLV_resize_image(image_dendro,300,300);
    MLV_resize_image(image_mixte,300,300);
    MLV_resize_image(monster,300,300);
    MLV_resize_image(agile_monster,300,300);
    MLV_resize_image(boss,300,300);

    for(i = 7 ; i < 10 ; i++ ){
        MLV_draw_image_on_image(road,image_List[i],0,0);
    }
    MLV_draw_partial_image_on_image(monster,100,100,200,200,image_List[7],100,100);
    MLV_draw_partial_image_on_image(agile_monster,100,100,200,200,image_List[8],100,100);
    MLV_draw_partial_image_on_image(boss,100,100,200,200,image_List[9],100,100);

    MLV_draw_image_on_image(image_List[0],image_List[2],0,0);
    MLV_draw_partial_image_on_image(tower_img,0,0,300,300,image_List[2],10,10);
    MLV_draw_image_on_image(image_List[2],image_List[4],0,0);
    MLV_draw_partial_image_on_image(image_hydro,0,0,300,300,image_List[4],10,10);
    MLV_draw_image_on_image(image_List[2],image_List[5],0,0);
    MLV_draw_partial_image_on_image(image_pyro,0,0,300,300,image_List[5],10,10);
    MLV_draw_image_on_image(image_List[2],image_List[3],0,0);
    MLV_draw_partial_image_on_image(image_dendro,0,0,300,300,image_List[3],10,10);
    MLV_draw_image_on_image(image_List[2],image_List[6],0,0);
    MLV_draw_partial_image_on_image(image_mixte,0,0,300,300,image_List[6],10,10);

    for(i = 0 ;i < 10 ; i++){
        MLV_resize_image(image_List[i],TAILLE_CASE,TAILLE_CASE);
    }
    MLV_free_image(image_dendro);
    MLV_free_image(image_hydro);
    MLV_free_image(image_pyro);
    MLV_free_image(image_mixte);
    MLV_free_image(tower_img);
    MLV_free_image(monster);
    MLV_free_image(agile_monster);
    MLV_free_image(boss);
    return image_List;
}


/**
 * @brief function to change the angle in color  to rgb 
 * @param tmp Monster the monster 
 * @param red int * 
 * @param gree int * 
 * @param blue int * 
*/
static void colors_monster_shoot(int rgb, int *red, int *green, int *blue) {
    float teinte2 = (float)(rgb % 360) / 360.0;
    float number = 1 - fabs((teinte2 * 6) - 1);
    float Red, Green, Blue;

    if (0 <= teinte2 && teinte2 < 1.0 / 6.0) {
        Red = 1; Green = number; Blue = 0;
    } 
    else if (1.0 / 6.0 <= teinte2 && teinte2 < 2.0 / 6.0) {
        Red = number; Green = 1; Blue = 0;
    }
    else if (2.0 / 6.0 <= teinte2 && teinte2 < 3.0 / 6.0) {
        Red = 0; Green = 1; Blue = number;
    } 
    else if (3.0 / 6.0 <= teinte2 && teinte2 < 4.0 / 6.0) {
        Red = 0; Green = number; Blue = 1;
    } 
    else if (4.0 / 6.0 <= teinte2 && teinte2 < 5.0 / 6.0) {
        Red = number; Green = 0; Blue = 1;
    } 
    else {
        Red = 1; Green = 0; Blue = number;
    }

    *red = (int)(Red * 255);
    *green = (int)(Green * 255);
    *blue = (int)(Blue * 255);
}



/**
 * @brief Function that displays graphically the stat of the monsters with a circle 
 * @param monster Monster 
*/
static void print_state_monster(Monster monster){
    switch (monster.residu) {
    case RESIDU_DENDRO_HYDRO:
        MLV_draw_filled_circle((monster.coord.y + 0.25) * TAILLE_CASE , (monster.coord.x + 0.25) * TAILLE_CASE, 0.20 * TAILLE_CASE , MLV_COLOR_YELLOW );
        break;
    case RESIDU_PYRO:
        MLV_draw_filled_circle((monster.coord.y + 0.25) * TAILLE_CASE , (monster.coord.x + 0.25) * TAILLE_CASE, 0.20 * TAILLE_CASE , MLV_COLOR_RED );
        break;
    case RESIDU_HYDRO:
        MLV_draw_filled_circle((monster.coord.y + 0.25) * TAILLE_CASE , (monster.coord.x + 0.25) * TAILLE_CASE, 0.20 * TAILLE_CASE , MLV_COLOR_BLUE );
        break;
    case RESIDU_DENDRO:
        MLV_draw_filled_circle((monster.coord.y + 0.25) * TAILLE_CASE , (monster.coord.x + 0.25) * TAILLE_CASE, 0.20 * TAILLE_CASE , MLV_COLOR_GREEN);
        break;
    case RESIDU_PYRO_HYDRO:
        MLV_draw_filled_circle((monster.coord.y + 0.25) * TAILLE_CASE , (monster.coord.x + 0.25) * TAILLE_CASE, 0.20 * TAILLE_CASE , MLV_COLOR_PURPLE );
        break;
    default:
        MLV_draw_filled_circle((monster.coord.y + 0.25) * TAILLE_CASE , (monster.coord.x + 0.25) * TAILLE_CASE, 0.20 * TAILLE_CASE , MLV_COLOR_WHITE );
        break;
    }

}

/**
 * @brief function that will display the monsters
 * @param board board game Plateau
 * @param List_image MLV_Image** a list of different image for the game
 * @param stack stack_monster stack of our monster 
*/
static void graphic_monster(const Plateau board,MLV_Image ** List_image,stack_Monster stack ){
    double pourcent;
    int taille_life , red, green , blue ;
    MLV_Color color;
    stack_Monster  tmp;
    tmp = stack;
    assert( List_image != NULL);
    while (tmp.Monster != NULL){
        if(tmp.Monster->coord.x != board.road[0].x || tmp.Monster->coord.y != board.road[0].y ){
            pourcent = (tmp.Monster->life * 100 )/ tmp.Monster->life_value_init;
            taille_life = (int) (pourcent * 40 / 100);
            colors_monster_shoot(tmp.Monster->rgb ,&red,&green,&blue);
            color = MLV_rgba(red,green,blue,255);
            switch (tmp.Monster->type){
                case BOSS:
                    MLV_draw_image(List_image[9],  tmp.Monster->coord.y * TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE );
                    break;
                case AGILE:
                    MLV_draw_image(List_image[8], tmp.Monster->coord.y * TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE );
                    break;
                default:
                    MLV_draw_image(List_image[7], tmp.Monster->coord.y * TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE );
                    break;

            }
            print_state_monster(*tmp.Monster);
            /*the color of the monster*/
            MLV_draw_rectangle(tmp.Monster->coord.y * TAILLE_CASE - 1,  tmp.Monster->coord.x * TAILLE_CASE  , TAILLE_CASE, TAILLE_CASE, color);
            MLV_draw_rectangle(tmp.Monster->coord.y * TAILLE_CASE - 2,  tmp.Monster->coord.x * TAILLE_CASE  , TAILLE_CASE, TAILLE_CASE, color);
            MLV_draw_rectangle(tmp.Monster->coord.y * TAILLE_CASE - 3,  tmp.Monster->coord.x * TAILLE_CASE  , TAILLE_CASE, TAILLE_CASE, color);
            /*the lif bar*/
            MLV_draw_line( tmp.Monster->coord.y * TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE, tmp.Monster->coord.y *  TAILLE_CASE  + TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE  , MLV_COLOR_WHITE);
            MLV_draw_line( tmp.Monster->coord.y * TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE, tmp.Monster->coord.y *  TAILLE_CASE  + taille_life , tmp.Monster->coord.x * TAILLE_CASE  , MLV_COLOR_BLACK);
            MLV_draw_line( tmp.Monster->coord.y * TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE -1 , tmp.Monster->coord.y *  TAILLE_CASE  + TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE - 1  , MLV_COLOR_WHITE);
            MLV_draw_line( tmp.Monster->coord.y * TAILLE_CASE , tmp.Monster->coord.x * TAILLE_CASE -1 , tmp.Monster->coord.y *  TAILLE_CASE  + taille_life , tmp.Monster->coord.x * TAILLE_CASE - 1, MLV_COLOR_BLACK);
        }
        tmp.Monster = tmp.Monster->next;
    }
}



/**
 * @brief function to free the list of image
 * @param list MLV_Image **
*/
void free_image_List(MLV_Image ** list){
    int i;
    assert(list != NULL);
    for (i = 0; i < 10; i++){
        MLV_free_image(list[i]);
    }
    free(list);
}


/**
 * @brief function that displays the differences button and information   for the player on the main menu 
 * @param player Player
 * @param temp time before the new wawe begin
 * @param good to know if the game have begin 
 * @param level_gem the level of the gem 
 * @param turn the turn , the nulber of wawe 
*/
static void print_info_to_player(const Player player ,const int temp , const int good, const int level_gem ,const int turn ){
    char * tmp ;
    int nb_tower;
    tmp = (char *) malloc (sizeof(char) * 50);
    nb_tower = number_of_tower(*player.tower_player);
    if(!tmp ){
        printf("erreur malloc print inforo player \n");
        return ;
    }
    /*info mana reserve mana and time and turn  */
    sprintf(tmp,"Mana  : %d ",player.mana);
    MLV_draw_text( LENGHT_WINDOW  - 300 , 20 ,tmp, player.mana,MLV_COLOR_BLACK);
    sprintf(tmp,"time before the new wawe : %d s ",  (35 -temp) );
    if(good == 0) {
        MLV_draw_text( LENGHT_WINDOW  - 300 , WIDTH_WINDOW - 20 ,tmp, player.mana,MLV_COLOR_BLACK);
    }
    sprintf(tmp,"numberof turn : %d ",  turn );
    MLV_draw_text(LENGHT_WINDOW - 300,WIDTH_WINDOW - 180,tmp,MLV_COLOR_BLACK);

    sprintf(tmp,"Mana reserve : %d level of reserve : %d ",(int) (2000  * pow(1.4,player.level)), player.level);
    MLV_draw_text( LENGHT_WINDOW  - 300 , 10 ,tmp,MLV_COLOR_BLACK);
    /*button begin wawe*/
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , WIDTH_WINDOW - 90,300,50,MLV_COLOR_ORANGE1);
    MLV_draw_text(LENGHT_WINDOW - 200,WIDTH_WINDOW - 70,"BEGIN WAWE  ",MLV_COLOR_BLACK);
    if(nb_tower < 3){
        MLV_draw_text(LENGHT_WINDOW - 300,WIDTH_WINDOW - 170,"cost tower : 0",MLV_COLOR_BLACK);
    }
    else{
        sprintf(tmp,"cost tower : %d ",(int) (100 * pow(2,(nb_tower - 4))));
        MLV_draw_text(LENGHT_WINDOW - 300,WIDTH_WINDOW - 170,tmp,MLV_COLOR_BLACK);

    }
    /*button buy tower */
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , WIDTH_WINDOW - 150,300,50,MLV_COLOR_GREEN1);
    MLV_draw_text(LENGHT_WINDOW - 200,WIDTH_WINDOW - 130,"BUY TOWER ",MLV_COLOR_BLACK);
    /*button upgrade reserve */
    sprintf(tmp,"UPGRADE THE RESERVE : %d ",  (int)(500 * pow(1.4, player.level)) );
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , 70 , 300 , 50,MLV_COLOR_YELLOW1);
    MLV_draw_text(LENGHT_WINDOW - 300 + 30,90,tmp,MLV_COLOR_BLACK);

    /*button buy gme and button for level */
    sprintf(tmp,"BUY A GEM OF LEVEL : %d : %d", level_gem ,(int) (100 * pow(2,level_gem)) );
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , 130 , 300 , 50,MLV_COLOR_RED1);
    MLV_draw_text(LENGHT_WINDOW - 300 + 10,150,tmp,MLV_COLOR_BLACK);
    sprintf(tmp,"CHANGE THE LEVEL OF GEM  : %d", level_gem  );
    MLV_draw_text(LENGHT_WINDOW - 300 + 10,190,tmp,MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 280 , 230 , 50 , 70,MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 80 , 230 , 50 , 70,MLV_COLOR_BLACK);
    MLV_draw_text(LENGHT_WINDOW - 300 + 40,250,"+",MLV_COLOR_WHITE);
    MLV_draw_text(LENGHT_WINDOW - 100 + 40,250,"-",MLV_COLOR_WHITE);

    /*button pos gem*/
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , 330 , 300 , 70,MLV_COLOR_BLUE1);
    MLV_draw_text(LENGHT_WINDOW - 300 + 100,350,"POS GEM ",MLV_COLOR_BLACK);

    /*button fusion gem */
    MLV_draw_text(LENGHT_WINDOW - 300 , 410 , "fusion cost  100 mana ",MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , 430 , 300 , 70,MLV_COLOR_PURPLE);
    MLV_draw_text(LENGHT_WINDOW - 300 + 100,450,"FUSION GEM ",MLV_COLOR_BLACK);

    free(tmp);
}


/**
 * @brief function that will detect if the user click on a button and change the value of the int associate  (boolean system )
 * @param player Player
 * @param board Plateau 
 * @param begin int * a boolan to know if the game have begining 
 * @param begine_wawe int * a boolean to know if the user have click on the button to  start the wawe 
 * @param buy_tower int * a boolean to know if the user have click on the button to buy a tower
 * @param buy_gem int *  a boolean to know if the user have click on the button to buy a gem 
 * @param gem_fusion int *  a boolean to know if the user have click on the button to fusion two gem 
 * @param upgrade_mana int *  a boolean to know if the user have click on the button to upgrade his reserve 
 * @param level_gem int *the level gem that we are goin to create
 * @param pos_gem int * a boolean to know if the user have cliked on the button to place a gem on tower 

*/
void gestion_click( int * begin ,int * begin_wawe ,int * buy_tower , int * buy_gem , int * gem_fusion , int * upgrade_mana , int  * level_gem,int * pos_gem, const Player player, const Plateau board  ){
    int x_mouse ,y_mouse ;
    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED ){
        MLV_get_mouse_position(&x_mouse,&y_mouse);
        if(( WIDTH_WINDOW - 90  <=  y_mouse && y_mouse <= WIDTH_WINDOW - 40 ) && (LENGHT_WINDOW  - 300 <=  x_mouse && x_mouse <= LENGHT_WINDOW )){ /* sbutton tart wawe */
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *begin = 0;
            *begin_wawe = 0;               
        }
        else if(((player.mana >= (100 * (int) pow(2,(number_of_tower(*player.tower_player) - 4)))) &&  WIDTH_WINDOW - 150  <=  y_mouse && y_mouse <= WIDTH_WINDOW - 100 ) && (LENGHT_WINDOW  - 300 <=  x_mouse && x_mouse <= LENGHT_WINDOW )){ /* button tower buy*/
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *buy_tower = 0;
        }

        else if(( (player.mana >= (int)(500 * pow(1.4, player.level))) &&  70  <=  y_mouse && y_mouse <= 120 ) && (LENGHT_WINDOW  - 300 <=  x_mouse && x_mouse <= LENGHT_WINDOW )){ /* button upgrade the reserve  */
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *upgrade_mana = 0;
        }  
        else if(( (player.mana >= (int) (100 * pow(2,*level_gem))) &&  130  <=  y_mouse && y_mouse <= 180 ) && (LENGHT_WINDOW  - 300 <=  x_mouse && x_mouse <= LENGHT_WINDOW )){ /* button upgrade the reserve  */
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *buy_gem = 0;
        }  
        else if( ( 230  <=  y_mouse && y_mouse <= 300 ) && (LENGHT_WINDOW  - 280 <=  x_mouse && x_mouse <= (LENGHT_WINDOW - 230))){ /* button upgrade the reserve  */
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *level_gem  += 1 ;
        }  
        else if(( (*level_gem > 0)) &&  (230  <=  y_mouse && y_mouse <= 300) && (LENGHT_WINDOW  - 80 <=  x_mouse && x_mouse <= LENGHT_WINDOW  - 30)){ /* button upgrade the reserve  */
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *level_gem -= 1;
        }     
        else if((330  <=  y_mouse && y_mouse <= 400) && (LENGHT_WINDOW  - 300 <=  x_mouse && x_mouse <= LENGHT_WINDOW )){ /* button upgrade the reserve  */
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *pos_gem = 0;
        }     

        else if (player.mana >= 101 &&  (430  <=  y_mouse && y_mouse <= 500) && (LENGHT_WINDOW  - 300 <=  x_mouse && x_mouse <= LENGHT_WINDOW ))   {
            while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED){
                continue;
            }
            *gem_fusion = 0;
        }

    }
}


/**
 * @brief function that displays the case avaible where the user can put the new tower 
 * @param board the board game 
*/
static void print_tower_pose( const Plateau board  ){
    int i;
    for(i = 2 ; i <= board.number - 3  ; i ++){
        if(board.plateau[board.road[i].x - 1][board.road[i].y] == VIDE){
            MLV_draw_filled_rectangle(board.road[i].y * TAILLE_CASE , (board.road[i].x - 1) * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLUE);
            MLV_draw_rectangle(board.road[i].y * TAILLE_CASE , (board.road[i].x - 1) * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLACK);
        }
        if(board.plateau[board.road[i].x + 1][board.road[i].y] == VIDE){
            MLV_draw_filled_rectangle(board.road[i].y * TAILLE_CASE , (board.road[i].x + 1) * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLUE);
            MLV_draw_rectangle(board.road[i].y * TAILLE_CASE , (board.road[i].x + 1) * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLACK);

        }
        if(board.plateau[board.road[i].x][board.road[i].y + 1] == VIDE){
            MLV_draw_filled_rectangle((board.road[i].y + 1) * TAILLE_CASE , board.road[i].x  * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLUE);
            MLV_draw_rectangle((board.road[i].y + 1) * TAILLE_CASE , board.road[i].x  * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLACK);

        }
        if(board.plateau[board.road[i].x][board.road[i].y - 1] == VIDE){
            MLV_draw_filled_rectangle((board.road[i].y - 1) * TAILLE_CASE , board.road[i].x  * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLUE);
            MLV_draw_rectangle((board.road[i].y - 1) * TAILLE_CASE , board.road[i].x  * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLACK);
        }
    }
}

/**
 * @brief function to displays the gem menu 
 * @param player Player the player 
 * @param gem1 Gem  the gem choiced by the player
 * @param gem2 Gem the second gem choiced by the player
 * @param gem_fusion int a boolean to know if he want to fuion or just pose a gem on a tower 

*/
static void affiche_gem(const Player player, const Gem gem1 , const Gem gem2,int gem_fusion){
    List_Gem_Avaible gems ;
    int x , y  ;
    char * tmp ;
    tmp = (char *) malloc (sizeof(char) * 50);
    gems = *player.gem_player;
    MLV_draw_text( LENGHT_WINDOW  - 300 , 20 ,"GEM (red : pyro , green : dendro , blue: hydro): ",MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , WIDTH_WINDOW - 90,300,50,MLV_COLOR_RED);
    MLV_draw_text(LENGHT_WINDOW - 200,WIDTH_WINDOW - 70," CANCEL  ",MLV_COLOR_BLACK);
    if(gem_fusion == 0){
        MLV_draw_filled_rectangle(LENGHT_WINDOW - 300 , WIDTH_WINDOW - 150,300,50,MLV_COLOR_GREEN);
        MLV_draw_text(LENGHT_WINDOW - 200,WIDTH_WINDOW - 120," FUSION  ",MLV_COLOR_BLACK);
    }
    x = LENGHT_WINDOW - 300 ;
    y =  50 ;
    while (gems.gem_list != NULL){
        sprintf(tmp,"n : %d", gems.gem_list->gem.niveau);
        if(x + TAILLE_CASE > LENGHT_WINDOW  && y + TAILLE_CASE> WIDTH_WINDOW -70 ){
                return ;
        }
        else if( x  +  TAILLE_CASE > LENGHT_WINDOW && y + TAILLE_CASE < WIDTH_WINDOW -70 ){
            x = LENGHT_WINDOW - 300;
            y += TAILLE_CASE;
        }
        MLV_draw_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_BLACK);
        switch (gems.gem_list->gem.element){
        case  DENDRO:
            MLV_draw_filled_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_GREEN);
            break;
        case  HYDRO:
            MLV_draw_filled_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_BLUE);
            break;
        case  PYRO :
            MLV_draw_filled_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_RED);
            break;
        default:
            MLV_draw_filled_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_PURPLE);
            break;
        }
        MLV_draw_text(x + 2, y + 15 ,tmp,MLV_COLOR_BLACK);
        MLV_draw_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_WHITE);
        if(gem1.element == gems.gem_list->gem.element && gem1.niveau == gems.gem_list->gem.niveau && gem1.teinte == gems.gem_list->gem.teinte && gem1.type == gems.gem_list->gem.type){
            MLV_draw_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_BLACK);
        }
        if(gem2.element == gems.gem_list->gem.element && gem2.niveau == gems.gem_list->gem.niveau && gem2.teinte == gems.gem_list->gem.teinte && gem2.type == gems.gem_list->gem.type){
            MLV_draw_rectangle(x,y,TAILLE_CASE,TAILLE_CASE,MLV_COLOR_BLACK);
        }
        x += TAILLE_CASE;
        gems.gem_list = gems.gem_list->next;
    }
    free(tmp);
}


/**
 * @brief Function to detect which gem the user have clicked and on which tower he clicked also 
 * @param player Player 
 * @param pos_gem int * the boolean to know if he have canceled the operation 
 * @param gem_fusion int * boolean to know if the user want to fusion his gem
 * @param gem1 Gem * the gem that he have choiced
 * @param gem2 Gem * the gem that the have choiced
 * @param spot Case * the case of the towet that he have choiced

*/
void gestion_click_gem_pose(const Player player , int * pos_gem ,int * gem_fusion ,Gem * gem1 , Gem *gem2 ,Case  * spot){
    List_Gem_Avaible gems ;
    List_Tower tmp ;
    int x_mouse ,y_mouse,x ,y ;

    tmp = *player.tower_player;
    x = LENGHT_WINDOW - 300 ;
    y =  50 ;
    gems = *player.gem_player;

    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED ){
        MLV_get_mouse_position(&x_mouse,&y_mouse);
        while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED ){
        }
    }
    if( (WIDTH_WINDOW - 90 <= y_mouse && y_mouse <=WIDTH_WINDOW - 40) && ( LENGHT_WINDOW - 300 <= x_mouse && x_mouse <= LENGHT_WINDOW) ){/*bouton cancel click*/
        *pos_gem = 1;
        *gem_fusion = 1;
        gem2->teinte = -1;
        gem1->teinte = -1;

        return ;
    }
    if( gem1->niveau == gem2->niveau  && gem1->teinte != -1 && gem2->teinte != -1 && (WIDTH_WINDOW - 150 <= y_mouse && y_mouse <=  WIDTH_WINDOW - 100 ) && (LENGHT_WINDOW - 300 <= x_mouse && x_mouse <= LENGHT_WINDOW)){/*button fusion click */
        *gem_fusion = 2;
    }

    while (gems.gem_list != NULL){/*check if he click on a gem  */
        if (x + TAILLE_CASE >  LENGHT_WINDOW && y + TAILLE_CASE < WIDTH_WINDOW -70){
            x = LENGHT_WINDOW - 300 ;
            y += TAILLE_CASE;
        }
        if(*gem_fusion == 0  && (x <=  x_mouse  && x_mouse <= x + TAILLE_CASE)  && (50   <= y_mouse && y_mouse <= y + TAILLE_CASE  )){/*two gem because of fusion he can select two gem*/
            if(gem1->teinte != -1 && gem1->teinte == gems.gem_list->gem.teinte && number_of_a_gem(gems.gem_list->gem,*player.gem_player) >= 2 ) {
                *gem2 = gems.gem_list->gem;
                return ;
            } 
            else if ( gem1->teinte == -1){
                *gem1 = gems.gem_list->gem;
            }
            else{
                if(gem1->element != gems.gem_list->gem.element || gem1->niveau != gems.gem_list->gem.niveau || gem1->teinte != gems.gem_list->gem.teinte || gem1->type != gems.gem_list->gem.type ){
                    *gem2 = gems.gem_list->gem;
                }
            }
            return ;
        }   
        
        if((x <=  x_mouse  && x_mouse <= x + TAILLE_CASE)  && (50   <= y_mouse && y_mouse <= y + TAILLE_CASE  )){
            *gem1 = gems.gem_list->gem;
            return ;
        }
        x += TAILLE_CASE;
        gems.gem_list = gems.gem_list->next;
    }   
    if(*pos_gem == 0){/*to  know which tower the player want to put his gem  */
        while(tmp.tower != NULL){ 
            if( tmp.tower->position.x == y_mouse / TAILLE_CASE && tmp.tower->position.y == x_mouse / TAILLE_CASE){
                spot->x =  tmp.tower->position.x;
                spot->y =  tmp.tower->position.y;
                return ;
            }
            tmp.tower = tmp.tower->next;
        }
    }
    
}

/**
 * @brief Display the towers where he can put the gem
 * @param player Player 
*/
static void print_graphic_gem_on_tower(const Player player ){
    List_Tower tmp ;
    tmp = *player.tower_player;
    while (tmp.tower != NULL){
        MLV_draw_filled_rectangle(tmp.tower->position.y * TAILLE_CASE , tmp.tower->position.x * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_WHITE);
        MLV_draw_rectangle(tmp.tower->position.y * TAILLE_CASE , tmp.tower->position.x * TAILLE_CASE , TAILLE_CASE, TAILLE_CASE,MLV_COLOR_BLACK);
        tmp.tower = tmp.tower->next;
    }      
}



/**
 * @brief Function that we allow to take the click on the board and return the case where the player want to put the tower
 * @param board Plateau the bord game
 * @param player Player 
 * @return new_pos Case the case where the player want to put the tower 
*/
Case gestion_click_Tower_pose(const Plateau board, const Player player){
    int x_mouse ,y_mouse,i ;
    Case new_pos;
    new_pos.x = 0 ;
    new_pos.y = 0;
    if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED ){
        MLV_get_mouse_position(&x_mouse,&y_mouse);
        while (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_RELEASED ){
        }
    }
    
    for(i = 2 ; i <= board.number - 2 ; i ++){
        if(((board.road[i].x + 1)  == y_mouse / TAILLE_CASE) && ( (board.road[i].y) == x_mouse / TAILLE_CASE ) && (board.plateau[board.road[i].x + 1][board.road[i].y ] == VIDE) ){
            new_pos.x  = board.road[i].x + 1;
            new_pos.y =  board.road[i].y ;
        }
        else if(((board.road[i].x - 1)  == y_mouse / TAILLE_CASE ) && ( (board.road[i].y)  == x_mouse / TAILLE_CASE ) && (board.plateau[board.road[i].x - 1][board.road[i].y] == VIDE) ){
            new_pos.x  = board.road[i].x - 1;
            new_pos.y =  board.road[i].y ;
        }
        else if(((board.road[i].x)  == y_mouse  / TAILLE_CASE) && ((board.road[i].y + 1)  == x_mouse / TAILLE_CASE) && (board.plateau[board.road[i].x ][board.road[i].y + 1 ] == VIDE) ){
            new_pos.x  = board.road[i].x ;
            new_pos.y =  board.road[i].y + 1 ;
        }
        else if(((board.road[i].x) == y_mouse / TAILLE_CASE) && ((board.road[i].y - 1) == x_mouse / TAILLE_CASE)  && (board.plateau[board.road[i].x ][board.road[i].y  - 1] == VIDE) ){
            new_pos.x  = board.road[i].x ;
            new_pos.y =  board.road[i].y - 1;
        }
    }
    return new_pos;
}

/**
 * @brief Function to display the board game on the windows
 * @param board Plateau the board game
 * @param List_image MLV_Image ** the list of image for the game
*/
static void print_board_graphic(const Plateau board, MLV_Image ** List_image ){
    int i ,j ;
    assert(List_image != NULL);
    for(i = 0; i < WIDTH_PLATEAU ; i++){
        for(j = 0 ; j < LENGHT_PLATEAU  ;j++){
            switch (board.plateau[i][j] ){
            case VIDE :
                MLV_draw_image(List_image[0],j * TAILLE_CASE,i * TAILLE_CASE);
                break;
            case ROAD:
                if(board.road[0].x == i  && board.road[0].y == j){
                    MLV_draw_filled_rectangle(j * TAILLE_CASE,i * TAILLE_CASE, TAILLE_CASE,TAILLE_CASE,MLV_COLOR_RED1);
                }
                else if (board.road[board.number - 1].x == i  && board.road[board.number - 1].y == j){
                    MLV_draw_filled_rectangle(j * TAILLE_CASE,i * TAILLE_CASE, TAILLE_CASE,TAILLE_CASE,MLV_COLOR_YELLOW1);
                }
                else{
                    MLV_draw_image(List_image[1],j * TAILLE_CASE,i * TAILLE_CASE);
                }
                break;
            case TOWER_VOID :
                MLV_draw_image(List_image[2],j * TAILLE_CASE,i * TAILLE_CASE);
                break;
            
            case TOWER_MIXTE :
                MLV_draw_image(List_image[6],j * TAILLE_CASE,i * TAILLE_CASE);
                break;
            
            case TOWER_PYRO :
                MLV_draw_image(List_image[5],j * TAILLE_CASE,i * TAILLE_CASE);
                break;

            case TOWER_DENDRO :
                MLV_draw_image(List_image[3] ,j * TAILLE_CASE,i * TAILLE_CASE);
                break;
            case TOWER_HYDRO:
                MLV_draw_image(List_image[4] ,j * TAILLE_CASE,i * TAILLE_CASE);
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief function to dsiplay the shoot 
 * @param shoot_player List_Shoot stack of shoot 
*/
static void graphic_shoot (List_Shoot shoot_player){
    int red, green , blue ;
    MLV_Color color;
    List_Shoot tmp ;
    tmp = shoot_player;
    while (tmp.shoots != NULL){
        colors_monster_shoot(tmp.shoots->gem.teinte ,&red,&green,&blue);
        color = MLV_rgba(red,green,blue,255);
        MLV_draw_filled_circle(tmp.shoots->position.y * TAILLE_CASE ,tmp.shoots->position.x * TAILLE_CASE, 5 , color );
        MLV_draw_circle(tmp.shoots->position.y * TAILLE_CASE ,tmp.shoots->position.x * TAILLE_CASE, 5 , MLV_COLOR_BLACK );

        tmp.shoots = tmp.shoots->next;
    }
}


/**
 * @brief Function that will display the range of the towers
 * @param player Player the player 
*/
static void graphic_tower_distance(Player player){
    List_Tower tmp;
    tmp = *player.tower_player;
    while(tmp.tower != NULL){
        MLV_draw_circle((tmp.tower->position.y + 0.5)  * TAILLE_CASE  ,(tmp.tower->position.x + 0.5 ) * TAILLE_CASE, 3 * TAILLE_CASE,MLV_COLOR_BLACK);
        tmp.tower = tmp.tower->next;
    }
}

/**
 * @brief Function to display the windows end with the number of wawe survived 
 * @param board Plateau the board game
*/
void end_graphic(Plateau board){
    char * tmp ;
    tmp = (char *) malloc (sizeof(char) * 50);
    sprintf(tmp,"You have lose at the wawe number  %d ",board.turn);
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text((LENGHT_WINDOW -300) / 2,WIDTH_WINDOW / 2 , tmp,MLV_COLOR_WHITE);
    MLV_actualise_window();
    free(tmp);
}
/**
 * @brief function that will make the graphic of the game 
 * @param board board game Plateau
 * @param stack stack_monster stack of our monster 
 * @param height int
 * @param width int
 * @param List_image MLV_Image** a list of different image for the game
 * @param player Player
 * @param temp int the time before the new wawe of monster 
 * @param begin the boolean to know if the player have cliked on the button the first time to begin the game 
 * @param begin_wawe the boolean to know if the user have begin a new wawe of monster 
 * @param buy_tower the boolean to know if the user have bought a new tower
 * @param buy_gem the boolean to know if the user have bought a new gem
 * @param gem_fusion the boolean to know if the user want to fusion his gems
 * @param upgrade_mana  the boolean to know if the user want to upgrade his reserve
 * @param level_gem number of the level of the gem 
 * @param pos_gem the boolean to know if the user want to put a gem on a tower
 * @param gem1 Gem to know  what gem he have selected 
*/
void graphic_map(const Plateau board , const stack_Monster stack,const int height ,const  int width, MLV_Image ** List_image ,const Player player,const int temp , const int  begin ,const int buy_tower , const int gem_fusion , const int  upgrade_mana,const int  level_gem ,const int pos_gem,Gem gem1, Gem gem2){
    assert(List_image != NULL);
    MLV_clear_window(MLV_COLOR_WHITE);
    print_board_graphic(board,List_image);
    if(pos_gem == 0){
        affiche_gem(player,gem1,gem2,gem_fusion);
        print_graphic_gem_on_tower(player );
    }
    if(gem_fusion == 0){
        affiche_gem(player,gem1,gem2,gem_fusion);

    }
    else if(pos_gem == 1 ){
        print_info_to_player(player,temp,begin,level_gem,board.turn);
    }
    if(buy_tower == 0){
        print_tower_pose(board);
    }
    graphic_monster(board,List_image,stack);

    graphic_tower_distance(player);
    graphic_shoot(*player.list_shoots);
    MLV_actualise_window();

}

