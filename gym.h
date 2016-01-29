#ifndef __GYM_H__
#define __GYM_H__
#include <iostream>
#include <string>

#include "building.h"

class Gym: public Building{
    public:
    Gym(int Num, std::string Name, int cost, std::string owner, const std::string& block): Building(Num, Name, cost, owner, block) {} 
    int getImprove(){ return -1; }
    int action(Player *player){ return 1; }
    void save(std::ostream &out){ out << this->getName() << " " << this->getOwner() << std::endl; }    
};

#endif
