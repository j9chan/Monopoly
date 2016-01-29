#ifndef __GOTOTIMS_H__
#define __GOTOTIMS_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"

class GoToTims: public NonProperty{
    //std::string Name2;
    public:
    GoToTims(int Num): NonProperty(Num, "GO TO", "TIMS") {} //, std::string Name1, std::string Name2): NonProperty(Num, Name1, Name2) {} 
    int action(Player *player){ player->getBoard()->goToTims(player); return 0;}
    
};

#endif
