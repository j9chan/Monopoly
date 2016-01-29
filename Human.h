#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <string>
#include "Player.h"

class Human: public Player{
    bool timsLine();
public:
    Human(std::map<char,bool>& pieces , Board* board, bool testing);
    Human(const std::string& playerInfo, char pieceSymbol, Board* board, bool testing);
    void execute();
    bool inTims(){ return timsLine(); }
};
#endif
