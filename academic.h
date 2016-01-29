#ifndef __ACAD_H__
#define __ACAD_H__
#include <iostream>
#include <string>
#include "cell.h"
#include "building.h"

class Academic: public Building{
    int tuitionCost[6];
    int Improve;
    int improveCost;

    public:
    Academic(int Num, std::string Name, int cost, int improveCost, 
        int tuition1, int tuition2, int tuition3, int tuition4, int tuition5, int tuition6, 
         std::string block, std::string owner = " ", int Improve = 0)
    : Building(Num, Name, cost, owner, block), Improve(Improve), improveCost(improveCost) {
        tuitionCost[0] = tuition1;//{tuition1, tuition2, tuition3, tuition4, tuition5, tuition6};
        tuitionCost[1] = tuition2;
        tuitionCost[2] = tuition3;
        tuitionCost[3] = tuition4;
        tuitionCost[4] = tuition5;
        tuitionCost[5] = tuition6;
    } 
    int getImprove(){ return Improve; }
    int getTuition(int index);//{ return tuitionCost[index]; }
    int buyImprove(){ ++Improve; return improveCost; }
    int improveCosts() { return improveCost; }
    int sellImprove(){ --Improve; return improveCost / 2; }
    int action(Player *player){ return 1; }
    void save(std::ostream &out);
};

#endif
