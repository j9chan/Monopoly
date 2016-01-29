#ifndef __NONPROPERTY_H__
#define __NONPROPERTY_H__
#include <iostream>
#include <string>
#include "cell.h"

class NonProperty: public Cell{
    //Cell::int cellNumber;
    //Cell::std::string cellName;
    //Building::std::string owner;
    //int Improve;
    std::string Name2;
    public:
    NonProperty(int Num, std::string Name1, std::string Name2): Cell(Num, Name1), Name2(Name2) {} 
    int getImprove(){ return -1; }
    std::string getName(){ return cellName; }
    std::string getName2(){ return Name2; }
    std::string getOwner(){ return ""; }
    virtual int getCost(){ return 0; }

    virtual int action(Player *player) = 0;//{ return 0; } 
    void save(std::ostream &out){ out << ""; }
};

#endif
