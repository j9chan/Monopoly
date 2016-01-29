#ifndef __BOARD_H__
#define __BOARD_H__
#include "cell.h"
#include "Player.h"
#include <map>
class Building;

class Board{
    std::map<std::string, std::map<std::string, std::string> > propertyBlock;
    void addToBlock(const std::string block, const std::string building, const std::string owner);
    public:
    Cell *cells[40];
    std::map<char, int> playerList;
    int cups;
    public:
    void draw();
    void Top(int starting, int cellW, int cellN);
    void Bottom(int starting, int cellW, int cellN);

    void save(std::ostream &savef);
    void load(std::istream &loadFile, int inumPlayers, Player** players);
//    int getBankrupt(){ return numBankrupt; }
    //void load(std::istream &loadFile, int numPlayers);
    ~Board();

    // stuff for the player movements / game
    void declareBankrupt(char sym); //need to remove ownership from the cells
    void removeFromBoard(char sym, int position);
    bool getBankrupt() { return playerList.size() == 1; }
    void addPlayer(char sym, int position) { playerList.insert(std::pair<char, int> (sym, position)); }
    int movePlayer(Player *player, int rollSum); // returns the new position
    void addPlayerToCell(char sym, int position);
    void removePlayerFromCell(char sym, int position);
    int goToTims(Player *player);
    void changeOwner(const std::string& name, const std::string& property);
    Building* getProperty(std::string property);

    Cell* getCell(int position){ return cells[position]; }
};

#endif
