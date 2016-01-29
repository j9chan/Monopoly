#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "cell.h"


Cell::Cell(int Num, string Name, string block): cellNumber(Num), cellName(Name), block(block) {
    int i = 0;              //initialized cell with no current players
    for(; i < 6; i++){ playerCh[i] = ' '; }
}

Cell::~Cell(){}

string Cell::currPlayers(){
    stringstream ss;
    for(int i = 0; i < 6; i++){
        ss << playerCh[i];
    }
    return ss.str();
}

void Cell::addPlayer(char playerSymbol, int playerNum){
    this->playerCh[playerNum] = playerSymbol;
}

void Cell::removePlayer(int playerNum){
    playerCh[playerNum] = ' ';
}
