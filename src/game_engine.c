#include "../include/game_engine.h"



/**
 * @brief Initialise the board of the game with 0
 * @param board: pointer on the Plateau 
 */
static void init_board(Plateau * board) {
    int i, j;
    assert(board != NULL);
    
    for(i = 0; i < WIDTH_PLATEAU; i++){
        for(j = 0; j < LENGHT_PLATEAU; j++)
            board->plateau[i][j] = VIDE;
    }
}



/**
 * @brief Function that will choice the nest ont the board randomly
 * @return CASE 
 */
static Case nest_source() {
    int x, y ;
    Case MonsterNest ;

    x = rand() % WIDTH_PLATEAU;
    y = rand() % LENGHT_PLATEAU;
    
    while ((x < 3 || x > WIDTH_PLATEAU - 4) || ( y < 3 || y > LENGHT_PLATEAU - 4)){
        x = rand() % WIDTH_PLATEAU;
        y = rand() % LENGHT_PLATEAU;
    }
    MonsterNest.x = x;
    MonsterNest.y = y;
    return MonsterNest;   
}


/**
 * @brief Function that will verify if around the spot there is an obstacle on the board
 * @param board: the game board
 * @param direction: the direction that we have actually
 * @return 1 if there is an obstacle around 
 * @return 0 if it's good 
 */
static int calcule_case (const Plateau board, const Case spot, const int direction){
    int j;

    for (j = 1; j <= 2; j++){
        if(direction != BOTTOM && (board.plateau[spot.x - j][spot.y] == 1))
            return 1;
        
        if(direction != TOP && (board.plateau[spot.x + j][spot.y] == 1))
            return 1;
        
        if(direction != RIGHT && (board.plateau[spot.x][spot.y - j] == 1))
            return 1;
        
        if(direction != LEFT && (board.plateau[spot.x][spot.y + j] == 1))
            return 1;
        
    }
    
    if (
    (board.plateau[spot.x - 1][spot.y - 1] == 1 && direction != BOTTOM && direction != RIGHT) || 
    (board.plateau[spot.x + 1][spot.y + 1] == 1 && direction != TOP && direction != LEFT) || 
    (board.plateau[spot.x - 1][spot.y + 1] == 1 && direction != BOTTOM && direction != LEFT) || 
    (board.plateau[spot.x + 1][spot.y - 1] == 1 && direction != TOP && direction != RIGHT)
    )
        return 1;
    
    return 0;
}

/**
 * @brief This function will give the number of case avaible on this direction on this case on the board
 * @param board: the game board
 * @param direction : the actually direction that we will move on 
 * @param spot : the case 
 * @return a int that will represent the value of the case avaible  
 */
static int Extent(const Plateau board, Case spot,const  int direction ){
    
    if((spot.x == 2 && direction == TOP) || (spot.x == 19 && direction == BOTTOM) || (spot.y == 25 && direction == RIGHT) || (spot.y == 2 && direction == LEFT) ){
        return 0;
    }

    switch (direction){
    
        case LEFT:
            spot.y -= 1;
            if(calcule_case(board, spot, direction) == 1)
                return 0;
            
            return  Extent(board, spot, LEFT) + 1;
        
        case RIGHT:
            spot.y += 1;
            if(calcule_case(board, spot, direction) == 1)
                return 0;
            
            return  Extent(board, spot, RIGHT) + 1;
        
        case BOTTOM:
            spot.x += 1;
            if(calcule_case(board, spot, direction) == 1)
                return 0;
            
            return  Extent(board, spot, BOTTOM) + 1;
        
        case TOP:
            spot.x -= 1;
            if(calcule_case(board, spot, direction) == 1)
                return 0;
            
            return  Extent(board, spot, TOP) + 1;
        
        default:
            break;
    }
    return 0;
    
}

/**
 * @brief This function  will choice a direction when we start at the nest proportionnaly with the number of case avaible at each direction 
 * @param nest: the nest of the monster 
 * @param board: the game board
 * @return  a int that represent the direction 
 */
static int road_start(const Case nest, const Plateau board){
    int max1, max2, max, rand_right, rand_left, rand_up, rand_down;

    rand_down = rand() % (Extent(board,nest,BOTTOM) + 1);
    rand_up = rand() % (Extent(board,nest,TOP) +1 );
    rand_right = rand() % (Extent(board,nest,RIGHT) + 1);
    rand_left = rand() % (Extent(board,nest,LEFT) + 1 );
    max1 = ((rand_down) > (rand_up)) ? (rand_down) : (rand_up);
    max2 = ((rand_left) > (rand_right)) ? (rand_left) : (rand_right);
    max = ((max1) > (max2)) ? (max1) : (max2);
    
    if(max == rand_down){
        return BOTTOM;
    }
    if(max == rand_up){
        return TOP;
    }
    if(max == rand_left){
        return LEFT;
    }
    return RIGHT;
    
}

/**
 * @brief This function  will put the case that follow the direction compared with the nest  on the list
 * @param nest: the nest of the monster 
 * @param board: pointeur Plateau
 * @param direction : the actual direction
 * @param number : represent the index on the list it's where we will put the case 
 */
static void put_road(Plateau * board ,const  Case nest , const int direction, const int number){
   
    switch (direction){
        
        case BOTTOM:
            board->plateau[nest.x + 1][nest.y] = ROAD;
            board->road[number].x  = nest.x + 1;
            board->road[number].y = nest.y;
            break;
        
        case TOP:
            board->plateau[nest.x - 1][nest.y] = ROAD;
            board->road[number].x = nest.x - 1;
            board->road[number].y  = nest.y;
            break;
        
        case LEFT:
            board->plateau[nest.x][nest.y - 1] = ROAD;
            board->road[number].x = nest.x ;
            board->road[number].y  = nest.y - 1;
            break;
        
        case RIGHT:
            board->plateau[nest.x][nest.y + 1] = ROAD;
            board->road[number].x  = nest.x;
            board->road[number].y = nest.y + 1;
            break;

        default:
            break;
    }
}


/**
 * @brief This function will give a new direction at 90 degrees compared with the actual direction 
 * @param nest: the nest of the monster 
 * @param board: the game board
 * @param direction : the actual direction
 * @return a int that represent the new direction that we will follow
 */
static int new_direction(const Plateau board, int direction, const Case nest){
    if(direction == LEFT || direction == RIGHT){
        direction = (Extent(board, nest, TOP) > Extent(board, nest, BOTTOM)) ? TOP: BOTTOM;
        return direction;
    }
    direction = (Extent(board, nest, RIGHT) > Extent(board, nest, LEFT)) ? RIGHT : LEFT ;
    return direction;
    
}

/**
 * @brief This function will a road for the monster that respect the norms asked on the subject recursively
 * @param nest: the last case (when we start the first time it's the nest )
 * @param board: pointeur Plateau
 * @param direction : the actual direction
 * @param number_case : the length of the road
 * @param number_variation : count the time when the direction change 
 * @return 0 when the road respect the norms
 * @return 1 when the road doesn't respect the norms
 */
static int creation_road_rec ( Plateau * board, int direction, int number_case, int number_variation, Case nest){
    int length, new_road, i;
    
    length = Extent(*board, nest, direction); 
    if(length < 3 && number_case > 74 && (number_variation -1 ) >= 7){
        board->number = number_case;
        return 0;
    }
    if(length < 3 ) {
        return 1;
    }
    new_road = (length == 3) ? (rand() % (length)) : (rand() % (length - 3)) +3 ;
    new_road = (new_road == 0) ? new_road+1 : new_road;
    for(i = 0 ; i < new_road ; i++){
        put_road(board,nest,direction,number_case);
        nest.x = board->road[number_case].x;
        nest.y = board->road[number_case].y;
        number_case ++;
    }
    number_variation ++;
    direction = new_direction(*board, direction, nest); 

    return creation_road_rec(board, direction, number_case, number_variation, nest);    
}


/**
 * @brief This function will make the road of the monsters from their nest until the end  
 * @param board: pointeur Plateau
 * @return 0 when the road respect the norms
 * @return 1 when the road doesn't respect the norms
 */
int  Creation_road (Plateau * board){
    Case nest;
    int direction;
    init_board(board);
    nest = nest_source();
    direction = road_start(nest, *board);
    if (creation_road_rec(board, direction, 0, 0, nest) != 0)
        return 1;
    
    return 0;
}