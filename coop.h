#ifndef __COOP_H__
#define __COOP_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"

class Coop: public NonProperty{
    //std::string Name2;
    public:
    Coop(int Num): NonProperty(Num, "COOP", "FEE") {} //, std::string Name1, std::string Name2): NonProperty(Num, Name1, Name2) {} 
    int action(Player *player){ 
    	if (player->getMoney() >= 200){ player->setMoney(player->getMoney() - 200); }
    	else { player->debt("BANK", 200); }
        return 0;
    }
};

#endif
