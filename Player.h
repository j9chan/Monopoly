#ifndef __PLAYER_H__
#define __PLAYER_H__

//#include "board.h"
//#include "building.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Mode.h"
class Building;
class Board;

class Player {
    std::string name;
    char pieceSymbol;
    int position;
    Board *board;
    int money;
    bool isBankrupt;
    std::map<std::string, Player *> players;

    // Player commands
    Mode * mode;
protected:
    std::map<std::string, Building *> properties;
    int numTimsLine;
    int lastRoll; // if stuck in the tims line
    bool inTimsLine;
    int cup;
    bool testing;
    bool notifyOfTrade(const std::string& from, const std::string& give, const std::string& receive);

    std::vector<int> roll() { return mode->roll(); }
    bool trade(const std::string& name, const std::string& give, const std::string& receive);
    bool sell(const std::string& property);
    bool improve(const std::string& property, const std::string& action);
    bool unmortgage(const std::string& property);
    bool mortgage(const std::string& property);
    bool bankrupt();
    void assets();
    void fileSave(const std::string& file);
public:
    Player(Board* board, bool testing);
    Player(const std::string& playerInfo, char pieceSymbol , Board* board, bool testing);
    virtual ~Player() = 0;
    virtual void execute() = 0;

    void addPlayer(Player *add);
    void removePlayer(Player *remove);
    std::ostream& save(std::ostream& file);
    bool buy(const std::string& property);
    void debt (const std::string& owner, int payment);

    // getters and setters
    void setCup(bool status){cup = status;}
    bool getCup(){ return cup; }
    std::string getName() { return name; }
    void setName(std::string name) {this->name = name; }
    int getMoney() { return money; }
    void setMoney(const int money) { this->money = money; }
    int getPosition() { return position; }
    void setPosition(int position) { this->position = position%40;}
    char getSymbol() { return pieceSymbol; }
    void setSymbol(char pieceSymbol) { this->pieceSymbol = pieceSymbol; }
    int getNumTimsLine() { return numTimsLine; }
    void setNumTimsLine(int numTimsLine) { this->numTimsLine = numTimsLine; }
    bool getInTimsLine() { return inTimsLine; }
    void setInTimsLine(bool inTimsLine) { this->inTimsLine = inTimsLine; }
    bool getBankrupt() { return isBankrupt; }
    void setLastRoll(const int rollSum) { lastRoll = rollSum; }
    Board* getBoard() { return board; }
    void removeProperty(const std::string& property);
    void addProperty(const std::string& property);
    void changeCup(int change);
    Player* getOtherPlayer(const std::string& name) { return players[name]; }

    int getWorth();
    virtual void payTuition();
};
#endif
