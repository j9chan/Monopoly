#ifndef __SLC_H__
#define __SLC_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"

class SLC: public NonProperty{
    //std::string Name2;
    public:
    SLC(int Num): NonProperty(Num, "SLC", "") {} //, std::string Name1, std::string Name2): NonProperty(Num, Name1, Name2) {} 
    int action(Player *player);
    //std::string getName(){ return cellName; }
    //std::string getName2(){ return Name2; }
  //  public:
    //Cell(int Num, std::string Name): cellNumber(Num), cellName(Name) {}
    
};

#endif
