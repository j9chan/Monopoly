#ifndef __TIMSLINE_H__
#define __TIMSLINE_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"

class TimsLine: public NonProperty{
    //std::string Name2;
    public:
    TimsLine(int Num): NonProperty(Num, "DC Tims", "Line") {} //, std::string Name1, std::string Name2): NonProperty(Num, Name1, Name2) {} 
    int action(Player *player){ return 1; }
    //std::string getName(){ return cellName; }
    //std::string getName2(){ return Name2; }
  //  public:
    //Cell(int Num, std::string Name): cellNumber(Num), cellName(Name) {}
    
};

#endif
