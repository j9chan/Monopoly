#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <map>
#include <vector>
#include "Player.h"

class Computer: public Player{
protected:
    std::string ownable[28];
public:
    Computer(std::map<char,bool>& pieces, Board *board, bool testing);
    virtual ~Computer();
    // don't forget for the computer to add lastRoll after the player rolled
    virtual void execute()=0;
    virtual bool timsLine()=0;
    virtual bool notifyOfTrade(const std::string& from, const std::string& give, const std::string& receive)=0;
    virtual void payTuition()=0;
};
#endif