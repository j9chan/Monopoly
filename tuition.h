#ifndef __GOTIMS_H__
#define __GOTIMS_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"

class Tuition: public NonProperty{
    public:
    Tuition(int Num): NonProperty(Num, "TUITION", "") {} 
    int action(Player *player);
    
};

#endif
