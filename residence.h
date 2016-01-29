#ifndef __RES_H__
#define __RES_H__
#include <iostream>
#include <string>
#include "cell.h"
#include "building.h"

class Residence: public Building{
    public:
    Residence(int Num, std::string Name, int cost,const std::string& block, std::string owner="BANK", int rent = 25): Building(Num, Name, cost, owner, block) {} 
    int getImprove(){ return -1; }
    int action(Player *player){ return 1; }    
    void save(std::ostream &out){ out << this->getName() << " " << this->getOwner() << endl; }
};

#endif
