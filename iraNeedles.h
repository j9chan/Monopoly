#ifndef __IRANEEDLES_H__
#define __IRANEEDLES_H__
#include <iostream>
#include <string>
#include "nonProperty.h"
#include "Player.h"

class IraNeedles: public NonProperty{
    public:
    IraNeedles(int Num): NonProperty(Num, "NEEDLES", "HALL") {}
    int action(Player *player);//{ return 1; }
    
};

#endif
