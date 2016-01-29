#ifndef __GEESE_H__
#define __GEESE_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"

class Geese: public NonProperty{
    //std::string Name2;
    public:
    Geese(int Num): NonProperty(Num, "Goose", "Nesting") {} //, std::string Name1, std::string Name2): NonProperty(Num, Name1, Name2) {} 
    int action(Player *player){ cout << "GOOSE ATTACK!!" << endl; return 0; }
    //std::string getName(){ return cellName; }
    //std::string getName2(){ return Name2; }
  //  public:
    //Cell(int Num, std::string Name): cellNumber(Num), cellName(Name) {}
    
};

#endif
