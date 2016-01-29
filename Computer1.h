#ifndef __COMPUTER1_H__
#define __COMPUTER1_H__
#include "Computer.h"
class Computer1: public Computer {
    bool timsLine();
    void debt(const std::string& owner, int payment);
    bool notifyOfTrade(const std::string& from, const std::string& give, const std::string& receive);
public:
    Computer1(std::map<char,bool>& pieces, Board *board, bool testing);
    ~Computer1();
    void execute();
    void payTuition();
};

#endif
