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
    struct Move{
        int selectedChecker[2];
        int placeToMove[2];
        int allMove[4];
    };

    Move* createMove(int a, int b, int c, int d){
        Move *move = new Move;
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

    struct Checker{
        int team;
        int getCrown = false;
    };

    vector<Move*> moves;
    vector<Move*> killerMoves;
    vector<Move*> discardMoves;
    Checker* board[8][8];

    int fillboard(){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((i==0 || i==2) && j%2 != 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = BLACK;
                }
                if (i==1 && j%2 == 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = BLACK;
                }
            }
        }
        for (int i = 5; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((i==5 || i==7) && j%2 != 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = WHITE;
                }
                if (i==6 && j%2 == 0){
                    board[i][j] = new Checker;
                    board[i][j]->team = WHITE;
                }
            }
        }
    }

    int getMoves(){
        cleanVectors();
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if(board[i][j] != NULL){
                    if(board[i][j]->team == BLACK){
                        // Normal Moves and Killer Moves
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

    int* chooseMove(){
        getMoves();
        int i;
        unsigned seed = time(0);
        srand(seed);
        if (killerMoves.size() > 0){
            i = rand()%killerMoves.size();
            return killerMoves[i]->allMove;
        } else if (killerMoves.size() == 0 && moves.size() == 0){
            i = rand()%discardMoves.size();
            return moves[i]->allMove;
        } else {
            eliminateBadMoves();
            i = rand()%moves.size();
            return moves[i]->allMove;
        }
    }

    int isOnBoard (int a, int b){
        if (a >= 0 && a <= 7 && b >= 0 && b <= 7) return true;
        else return false;
    }

    int cleanVectors(){
        moves.clear();
        killerMoves.clear();
    }
};


