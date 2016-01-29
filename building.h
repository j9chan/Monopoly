#ifndef __BUILD_H__
#define __BUILD_H__

#include "cell.h"
class Player;
class Cell;

class Building: public Cell{
    int cost;
    std::string owner;
    bool isMortgage;
    public:
    Building(int Num, std::string Name, int cost, std::string Owner, std::string block): Cell(Num, Name, block), cost(cost), owner(Owner) {
        isMortgage = false;
    }
    //virtual ~Building() = 0;
    virtual int getImprove() = 0;  
    std::string getName(){ return cellName; }
    std::string getName2(){ return ""; }
    std::string getOwner(){ return owner; }
    int getCost(){ 
        //std::cout << cellName <<": " << cost << std::endl;
        return cost; }
    void setOwner(std::string name) { owner = name; }
    bool getMortgage() { return isMortgage; }

    virtual int action(Player *player) = 0;
    virtual void save(std::ostream &out) = 0;
    virtual int sell();
    virtual int buy(std::string name) { owner = name; return cost; }
    int mortgage() { isMortgage = true; return cost / 2 + cost * 0.1; } // returns the cost of unmortgaging the building
    int unmortgage() { isMortgage = false; return cost / 2; }
};

#endif
