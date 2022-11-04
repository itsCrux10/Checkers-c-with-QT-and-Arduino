#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#define WHITE 1
#define BLACK 2

using namespace std;

class Backtracking {
public:
    struct Move{ // Struct that contains the information of a specific checker move
        int selectedChecker[2]; // Coords of selected checker
        int placeToMove[2]; // Coords of place to move
        int allMove[4]; // Coords of the last two together
    };


    // Function that create a struct Move and set their parameters
    Move* createMove(int a, int b, int c, int d){ // Receive a and b (Coords of selected checker), also c and d (Coords of place to move)
        Move *move = new Move;
        // Set struct parameters using a loop
        for (int i = 0; i < 4; ++i) {
            if (i == 0){
                move->allMove[i] = a;
                move->selectedChecker[i] = a;
                move->placeToMove[i] = c;
            }
            if (i == 1){
                move->allMove[i] = b;
                move->selectedChecker[i] = b;
                move->placeToMove[i] = d;
            }
            if (i == 2) move->allMove[i] = c;
            if (i == 3) move->allMove[i] = d;
        }
        return move;
    }

    // Struct that contains parameters related of checker
    struct Checker{
        int team; // white or black
        int getCrown = false; // is cross the board and get crowned
    };

    // Parameters of backtracking class
    vector<Move*> moves; // vector that contains normals move of checkers
    vector<Move*> killerMoves; // vector that contains moves that eliminated an enemy checker
    vector<Move*> discardMoves; // vector that contains normals moves discarded by backtracking algorithm
    Checker* board[8][8]; // matrix that contains checkers structs simulating the game board

    // Fuction that initialize the bord matrix as default (begin of the game)
    int fillboard(){
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                // Put the black checkers on top of the board
                if ((i==0 || i==2) && j%2 != 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = BLACK;
                } else if (i==1 && j%2 == 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = BLACK;

                    // Put the white checkers on bottom of the board
                }else if ((i==5 || i==7) && j%2 != 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = WHITE;
                } else if (i==6 && j%2 == 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = WHITE;

                    // Set the others position on board as NULL
                } else board[i][j] = NULL;
            }
        }
    }

    // Function that travel the board searching the black checkers and gets their posible moves
    int getMoves(){
        cleanVectors();
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if(board[i][j] != NULL){ // There is a checker in this coords
                    if(board[i][j]->team == BLACK){ // Is a checker from black team
                        // Gets Normal Moves and Killer Moves
                        if (board[i][j]->getCrown == true){
                            if (isOnBoard(i-1,j-1)){ // If the checker its crowned and the space one up and one left its free (normal move)
                                if (board[i-1][j-1] == NULL) moves.push_back(createMove(i, j, i - 1, j - 1));
                                else if (board[i-1][j-1]->team == WHITE){
                                    if (isOnBoard(i-2,j-2)){
                                        if (board[i-2][j-2] == NULL){
                                            killerMoves.push_back(createMove(i, j, i - 2, j - 2));
                                        }
                                    }
                                }
                            }
                            if (isOnBoard(i-1,j+1)){ // If the checker its crowned and the space one up and one right its free (normal move)
                                if (board[i-1][j+1] == NULL) moves.push_back(createMove(i, j, i - 1, j + 1));
                                else if (board[i-1][j+1]->team == WHITE){
                                    if (isOnBoard(i-2,j+2)){
                                        if (board[i-2][j+2] == NULL){
                                            killerMoves.push_back(createMove(i, j, i - 2, j + 2));
                                        }
                                    }
                                }
                            }
                        }
                        if (isOnBoard(i+1,j-1)){ // If the space one down and one left its free (Normal Move)
                            if (board[i+1][j-1] == NULL) moves.push_back(createMove(i, j, i + 1, j - 1));
                            else if (board[i+1][j-1]->team == WHITE){
                                if (isOnBoard(i+2,j-2)){
                                    if (board[i+2][j-2] == NULL){
                                        killerMoves.push_back(createMove(i, j, i + 2, j - 2));
                                    }
                                }
                            }
                        }
                        if (isOnBoard(i+1,j+1)){ // If the space one down and one right its free (Normal Move)
                            if (board[i+1][j+1] == NULL) moves.push_back(createMove(i, j, i + 1, j + 1));
                            else if (board[i+1][j+1]->team == WHITE){
                                if (isOnBoard(i+2,j+2)){
                                    if (board[i+2][j+2] == NULL){
                                        killerMoves.push_back(createMove(i, j, i + 2, j + 2));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Function that travel along all the moves and discard the moves if the player cant attack the checker
    int eliminateBadMoves(){
        int a,b;
        for (int i = 0; i < moves.size(); ++i) {
            a = moves[i]->allMove[2];
            b = moves[i]->allMove[3];
            if (isOnBoard(a+1, b+1)){
                if(board[a+1][b+1] != NULL){
                    if(board[a+1][b+1]->team == WHITE && isOnBoard(a-1,b-1)){
                        if(board[a-1][b-1] == NULL){
                            discardMoves.push_back(moves[i]);
                            moves.erase(moves.begin()+i);
                            i--;
                        }
                    }
                }
            }else if (isOnBoard(a+1, b-1)){
                if(board[a+1][b-1] != NULL){
                    if(board[a+1][b-1]->team == WHITE && isOnBoard(a-1,b+1)){
                        if(board[a-1][b-1] == NULL){
                            discardMoves.push_back(moves[i]);
                            moves.erase(moves.begin()+i);
                            i--;
                        }
                    }
                }
            } else if (isOnBoard(a-1, b+1)){
                if(board[a-1][b+1] != NULL){
                    if(board[a-1][b+1]->team == WHITE && board[a-1][b+1]->getCrown == true && isOnBoard(a+1,b-1)){
                        if(board[a-1][b-1] == NULL){
                            discardMoves.push_back(moves[i]);
                            moves.erase(moves.begin()+i);
                            i--;
                        }
                    }
                }
            } else if (isOnBoard(a-1, b-1)){
                if(board[a-1][b-1] != NULL){
                    if(board[a-1][b-1]->team == WHITE && board[a-1][b-1]->getCrown == true && isOnBoard(a+1,b+1)){
                        if(board[a+1][b+1] == NULL){
                            discardMoves.push_back(moves[i]);
                            moves.erase(moves.begin()+i);
                            i--;
                        }
                    }
                }
            } else{}
        }
        return 0;
    }


    // Function that gets a move between all calculated before
    int* chooseMove(){
        getMoves();
        int i;
        unsigned seed = time(0);
        srand(seed);
        if (killerMoves.size() > 0){ // if are killer moves, return one
            i = rand()%killerMoves.size();
            return killerMoves[i]->allMove;
        } else if (killerMoves.size() == 0 && moves.size() == 0){ // if
            i = rand()%discardMoves.size();
            return moves[i]->allMove;
        } else {
            eliminateBadMoves();
            i = rand()%moves.size();
            return moves[i]->allMove;
        }
    }

    // Function that return if a combination of coords is on the board
    int isOnBoard (int a, int b){
        if (a >= 0 && a <= 7 && b >= 0 && b <= 7) return true;
        else return false;
    }

    // Clean all the moves contain by the vectors
    int cleanVectors(){
        moves.clear();
        killerMoves.clear();
        discardMoves.clear();
    }

    // Function that receives a specific move and update the board in respond
    int updateBoard(int* move){
        board[move[2]][move[3]] = board[move[0]][move[1]];
        board[move[0]][move[1]] = NULL;
        if (abs(move[2]-move[0]) == 2){
            int a = (move[0]+move[2]) / 2;
            int b = (move[1]+move[3]) / 2;
            board[a][b] == NULL;
        }
    }
};

