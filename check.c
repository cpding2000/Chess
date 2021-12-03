#include "chess.h"

int check_move(int color, int x_from, int y_from, int x_to, int y_to)
{
    if(the_board_color[y_from][x_from]==the_board_color[y_to][x_to])
    {
        return INVALID_MOVE;
    }
    if( the_board_color[y_from][x_from]!=color)
    {
        return INVALID_MOVE;
    }
    if((x_from==x_to) && (y_from==y_to)){
        return INVALID_MOVE;
    }
    if(!((x_from<=7 && x_from>=0) &&(x_to<=7 && x_to>=0) &&(y_from<=7 && y_from>=0) &&(y_to<=7 && y_to>=0))){
        return INVALID_MOVE;
    }

    if(the_board_piece[y_from][x_from]==1){
        return check_pawn_move(color,x_from, y_from, x_to, y_to);
    }
    if(the_board_piece[y_from][x_from]==3){
        return check_bishop_move(color,x_from, y_from, x_to, y_to);
    }
    if(the_board_piece[y_from][x_from]==4){
        return check_rook_move(color,x_from, y_from, x_to, y_to);
    }
    if(the_board_piece[y_from][x_from]==2){
        return check_knight_move(color,x_from, y_from, x_to, y_to);
    }
    if(the_board_piece[y_from][x_from]==5){
        return check_queen_move(color,x_from, y_from, x_to, y_to);
    }
    if(the_board_piece[y_from][x_from]==6){
        return check_king_move(color,x_from, y_from, x_to, y_to);
    }


    return VALID_MOVE;



}
int check_pawn_move(int color, int x_from, int y_from, int x_to, int y_to) {   // allows for pawn to take pieces diagonally
    if ((x_from + 1 == x_to || x_from - 1 == x_to) &&((y_from + 1 == y_to && color == WHITE) || (y_from - 1 == y_to && color == BLACK))) {
        if (check_opposite_color(color, x_to, y_to)) {
            return VALID_MOVE;
        }
    }   //  Stop pawn from moving forward when piece of opposite color is in front
    if ((y_from + 1 == y_to && color == WHITE) || (y_from - 1 == y_to && color == BLACK)) {
        if (check_opposite_color(color, x_to, y_to)) {

            return INVALID_MOVE;
        }

    }
    if ((y_from + 2 == y_to && color == WHITE) || (y_from - 2 == y_to && color == BLACK)) {
        if (check_opposite_color(color, x_to, y_to)) {

            return INVALID_MOVE;
        }

    }//stops pawn from moving diagonally
    if (x_to != x_from) {
        return INVALID_MOVE;
    } // stopping piece from moving backwards
    if ((y_to - y_from < 1 && color == WHITE) || (y_from - y_to < 1 && color == BLACK)) {
        return INVALID_MOVE;
    } // Code to move up two spaces
    if (y_from != 1 && color == WHITE) {
        if (y_to - y_from != 1)
            return INVALID_MOVE;
    } else if (y_from != 6 && color == BLACK) {
        if ( y_from - y_to != 1)
            return INVALID_MOVE;
    }
    if(y_to-y_from>2 && color==WHITE){
        return INVALID_MOVE;
    }else if(y_from-y_to>2 && color==BLACK){
        return INVALID_MOVE;
    }
    int negative=1;

    if(y_to-y_from<0){
        negative=-1;
    }
    int  distance=0;
    if(y_to - y_from != 0){
        distance = y_to - y_from;
    }

    int i;
    for(i=1;i<(distance)*negative;i++) {
        if ((y_to > y_from) && (the_board_color[y_to - i][x_to]) != EMPTY) {
            return INVALID_MOVE;
        } else if ((y_to < y_from) && (the_board_color[y_to + i][x_to]) != EMPTY) {
            return INVALID_MOVE;
        }
    }


    return VALID_MOVE;



}
int check_bishop_move(int color, int x_from, int y_from, int x_to, int y_to)

{  int negative=1;
    // code to prevent bishop from moving forward like a pawn
    if(x_from==x_to || y_from==y_to){
        return INVALID_MOVE;
    } // code for diagonal direction
    if(!((x_to-x_from)==(y_to-y_from)||(x_to-x_from)==(-(y_to-y_from)))){
        return INVALID_MOVE;
    }
    if(y_to-y_from<0){
        negative=-1;
    }
    int i;
    for(i=1;i<(y_to-y_from)*negative;i++){
        if((y_to>y_from && x_to>x_from) && (the_board_color[y_to-i][x_to-i])!=EMPTY){
            return INVALID_MOVE;
        }else if((y_to<y_from && x_to<x_from) && (the_board_color[y_to+i][x_to+i])!=EMPTY){
            return INVALID_MOVE;
        }else if((y_to>y_from && x_to<x_from) && (the_board_color[y_to-i][x_to+i])!=EMPTY){
            return INVALID_MOVE;
        }else if((y_to<y_from && x_to>x_from) && (the_board_color[y_to+i][x_to-i])!=EMPTY){
            return INVALID_MOVE;
        }
    }

    return VALID_MOVE;
}

int check_opposite_color(int color, int x_to, int y_to) {
    if (color == WHITE && the_board_color[y_to][x_to] == BLACK) {
        return 1;
    } else if (color == BLACK && the_board_color[y_to][x_to] == WHITE) {
        return 1;
    } else return 0;
}
int check_rook_move(int color, int x_from, int y_from, int x_to, int y_to){
    int negative=1;
    if(!(x_to==x_from|| y_from==y_to)){
        return INVALID_MOVE;
    }
    if(y_to-y_from<0){
        negative=-1;
    }
    int  distance;
    if(x_to - x_from != 0){
        distance = x_to - x_from;
    }

    else{
        distance = y_to - y_from;
    }
    int i;
    for(i=1;i<distance*negative;i++){
        if((y_to>y_from && x_to==x_from) && (the_board_color[y_to-i][x_to])!=EMPTY){
            return INVALID_MOVE;
        }else if((y_to<y_from && x_to==x_from) && (the_board_color[y_to+i][x_to])!=EMPTY){
            return INVALID_MOVE;
        }else if((y_to==y_from && x_to<x_from) && (the_board_color[y_to][x_to+i])!=EMPTY){
            return INVALID_MOVE;
        }else if((y_to==y_from && x_to>x_from) && (the_board_color[y_to][x_to-i])!=EMPTY){
            return INVALID_MOVE;
        }
    }
    return VALID_MOVE;
}
int check_knight_move(int color, int x_from, int y_from, int x_to, int y_to){
    if(!((y_from+2==y_to && x_from+1==x_to) ||
         (y_from+2==y_to && x_from-1==x_to)||
         (y_from-2==y_to && x_from+1==x_to)||
         (y_from-2==y_to && x_from-1==x_to)||
         (x_from+2==x_to && y_from+1==y_to)||
         (x_from+2==x_to && y_from-1==y_to)||
         (x_from-2==x_to && y_from+1==y_to)||
         (x_from-2==x_to && y_from-1==y_to))){
        return INVALID_MOVE;
    }
    return VALID_MOVE;
}
int check_queen_move(int color, int x_from, int y_from, int x_to, int y_to) {
    if(check_rook_move( color, x_from, y_from, x_to,y_to) == VALID_MOVE ||
       check_bishop_move( color, x_from, y_from, x_to,y_to) == VALID_MOVE){
        return VALID_MOVE;
    }
    else
        return INVALID_MOVE;

}
int check_king_move(int color, int x_from, int y_from, int x_to, int y_to) {
    if(!((y_from+1==y_to && x_from+1==x_to)||
         (y_from+1==y_to && x_from-1==x_to)||
         (y_from+1==y_to && x_from==x_to)||
         (y_from-1==y_to && x_from+1==x_to)||
         (y_from-1==y_to && x_from-1==x_to)||
         (y_from-1==y_to && x_from==x_to)||
         (x_from-1==x_to && y_from==y_to)||
         (x_from+1==x_to && y_from==y_to))){
        return INVALID_MOVE;
    }
    return VALID_MOVE;
