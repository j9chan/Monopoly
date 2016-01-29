#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <string>
#include "Player.h"
class Player;

class Cell{
    protected:
    int cellNumber;
    std::string cellName;
    char playerCh[6];
    std::string block;

    public:
    Cell(int Num, std::string Name, std::string block = "");
    virtual ~Cell();
    virtual int getImprove() = 0;
    virtual std::string getName() = 0;
    virtual std::string getName2() = 0;
    virtual std::string getOwner() = 0;
    virtual int getCost() = 0;
    std::string currPlayers();

    void addPlayer(char playSymbol, int playerNum);
    void removePlayer(int playerNum);
    virtual int action(Player *player) = 0;
    virtual void save(std::ostream &out) = 0;

    // player stuff
    int getCellNumber() { return cellNumber; };
    std::string getBlock(){ return block; }
};

#endif
