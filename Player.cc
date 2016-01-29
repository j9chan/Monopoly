#include "Player.h"
#include "RegularMode.h"
#include "TestingMode.h"
#include "building.h"
#include "board.h"
#include "academic.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;


int Player::getWorth(){
    int totalWorth = 0;
    totalWorth += getMoney();
    for(map<string, Building*>::iterator it = properties.begin(); it != properties.end(); ++it) {
        Building* owned = it->second;
        if (!owned->getMortgage()) {
            totalWorth += owned->getCost();
            int improvements = owned->getImprove();
            if (improvements > 0){
                Academic *b = static_cast<Academic*>(owned);
                totalWorth += b->improveCosts();
            }
        } else {
            totalWorth += (0.5*owned->getCost());
        }
    }
    return totalWorth;
}

/********* Player ************
* Purpose: Fresh Initialization
* Return:
* Errors: 
*/
Player::Player(Board* board, bool testing)
    : position(0), board(board), money(1500), isBankrupt(false), numTimsLine(0), inTimsLine(false), cup(false) {
    cout << "Please enter a name: " << endl;
    cin >> name;
    if (testing) {
            mode = new TestingMode;
    } else {
            mode = new RegularMode;
    }
}

/* Load game constructor
*/
Player::Player(const string& playerInfo, char pieceSymbol, Board* board, bool testing)
    : pieceSymbol(pieceSymbol), board(board), isBankrupt(false), numTimsLine(0), inTimsLine(false), cup(false) {
    stringstream ss(playerInfo);
    string name;
    int money, position;
    ss >> name >> money >> position;
    if (position == 10) {
        int inLine;
        ss >> inLine;
        if(inLine == 1) {
            inTimsLine = true;
            ss >> numTimsLine;
        }
    }
    this->name = name;
    this->position = position;
    this->money = money;
    board->addPlayer(pieceSymbol, position);
    if (testing) {
        mode = new TestingMode;
    } else {
        mode = new RegularMode;
    }
}

/********** ~Player ***********
*/
Player::~Player(){
    // remove the players from the map
    /*for(map<string, Player*>::iterator it = players.begin(); it != players.end(); ++it) {
        it = 0;
    } // for -- may not need to delete the map since it is stack allocated*/ 

    // remove the buildings from properties
    /*for(map<string, Building*>::iterator it = properties.begin(); it != properties.end(); ++it) {
        it = 0;
    } // for*/
        delete mode;
}

/********* notifyOfTrade ***********
* Purpose: Asks the player whether they want to trade or not
* from = who the trade is coming from
* give =  what the trader is willing to give you
* receive = what the trader wants to receive in return
* Returns: true if the player will trade, false otherwise
* Errors: none
*/
bool Player::notifyOfTrade(const string& from, const string& give, const string& receive) {
    bool trade = false;
    cout << "Player " << pieceSymbol << ": Do wou want to trade " << receive << " for " << give << "? y/n" << endl;
    char response;
    cin >> response;
    if (response == 'y') {
        trade = true;
    }
    return trade;
} //notifyTrade

/************* addPlayer **************
* Purpose:
* Return:
* Errors:
*/
void Player::addPlayer(Player *add) {
    players.insert(pair<string, Player *>(add->getName(), add));
} // addPlayer

/************ removePlayer ************
* Purpose:
* Return:
* Errors:
*/
void Player::removePlayer(Player *remove) {
    players.erase(remove->name);
}

/*********** trade ***********
* Purpose: Buy buidings, sell buildings, trade stuff with other players
* name: bank - to buy or sell with bank
*       player name - to trade with another player
* give: What this player is willing to give for the trade
* receive: What the player wants to receive for the trade
* Return:
* Errors:
*/
bool Player::trade(const string& name, const string& give, const string& receive) {
    cout << "trade" << endl;
    bool trade =
    players[name]->notifyOfTrade(this->name, give, receive);
    if (trade) {
        cout << name <<" has accepted the trade" << endl;
        int cash;
        stringstream ss(receive);
        ss >> cash;
        // is it a building or a sum of money being received
        if (ss.fail()) {
            Building* b = board->getProperty(receive);
            b->setOwner(this->name);
            properties.insert(pair<string, Building*>(b->getName(), b));
            board->changeOwner(this->name, receive);
            players[name]->removeProperty(receive);
        } else {
            money += cash;
            players[name]->setMoney(players[name]->getMoney() - cash);
        }
        ss.clear();
        ss << give;
        ss >> cash;
        if (ss.fail()) {
            players[name]->addProperty(give);
            board->changeOwner(name, give);
            properties.erase(give);
        } else {
            money -= cash;
            players[name]->setMoney(players[name]->getMoney() + cash);
        }
    } else {
        cout << name << " refused the trade" << endl;
    }
    return trade;
}
/************ buy **********
* Purpose: Buying buildings from the bank
*/
bool Player::buy(const string& property) {
    Building *b = board->getProperty(property);

    if (money >= b->getCost() && (b->getOwner()== "" || b->getOwner() == "BANK")) {
        money -= b->buy(name);
        properties.insert(pair<string, Building*>(b->getName(), b));
        board->changeOwner(name, property);
        cout << name << " bought " << property << endl;
        return true;
    } else {
        //cout << "This building costs too much, or is already owned" << endl;
        return false;
    }
}
/************ sell ***********
* Purpose: Selling building to the bank
*/
bool Player::sell(const string& property) {
    Building * b = properties[property];
    properties.erase(property);
    money += b->sell();
    board->changeOwner("BANK", property);
    return true;
}

/************* improve ************
* Purpose: Buy or sell an improvement for a building 
* Return:
* Errors:
*/
bool Player::improve(const string& property, const string& action) {
    Academic *b = static_cast<Academic*>(properties[property]);
    if(action == "buy") {
         money -= b->buyImprove();
    } else {
         money += b->sellImprove();
    }
    return true;
} // improve

bool Player::unmortgage(const string& property) {
    Building *b = properties[property];
    money -= b->unmortgage();
    return true;
} // unmortgage

/************* mortgage ************
* Purpose: Allows the player to mortgage the building
* Returns: Whether the building successfully mortgaged or not
* Errors: Will not mortgage if the property still has improvements
*/
bool Player::mortgage(const string& property) {
    Building *b = properties[property];
    money += b->mortgage();
    return true;
} // mortgage

/*
* Options for owing money:
* sell a building
* declare bankruptcy
* trade
* mortgage
* sell improvements
*/
void Player::debt (const string& owner, int payment) {
    string com;
    while (money < payment) {
        cout << "In debt: " << "Money: "<< money << " Debt: "<< payment << endl;
        cout << "Assets:" << endl;
        assets();
        cout << "Options: sell (building/improvement), trade, mortgage, bankrupt" << endl;
        cin >> com;
        if(com == "sell") {
            string name;
            cout << "Enter a property name: " << endl;
            cin >> name;
            cout << "Building: sell/improve (make sure all improvements are sold before selling the building)" << endl;
            cin >> com;
            if (com == "sell") sell(name);
            else improve(name, "sell");
        } else if(com == "trade") {
            string name, give, receive;
            cout << "Enter a player name, give, receive: " << endl;
            cin >> name >> give >> receive;
            trade(name, give, receive);
        } else if(com == "mortgage") {
            string name;
            cout << "Enter a property name: " << endl;
            cin >> name;
            mortgage(name);
        } else if(com == "bankrupt") {
            if(!properties.empty()) {
                for(map<string, Building*>::iterator it = properties.begin(); it != properties.end(); ++it) {
                    if(owner != "BANK")players[owner]->addProperty(it->first);
                    removeProperty(it->first);
                }
            }
            if(owner != "BANK") players[owner]->setMoney(players[owner]->getMoney() + money);
            money = 0;
            bankrupt();
            break;
        }
    }
    if(com != "bankrupt"){
        if (owner != "BANK") { 
            money -= payment;
        } else {
            players[owner]->setMoney(players[owner]->getMoney() + payment);
            money -= payment;
        }
    }
}

/*********** bankrupt ***********
* Purpose:
* Returns: void
* Errors: 
*/
bool Player::bankrupt() {
    // sell buildings if no owed money
    if(!properties.empty()) {
        for(map<string, Building*>::iterator it = properties.begin(); it != properties.end(); ++it) {
            sell(it->first);
        }
    }
    board->declareBankrupt(pieceSymbol);
    // Have this player removed from the other active player's lists
    for (map<string, Player*>::iterator it = players.begin(); it != players.end(); ++it) {
        if(it->second != this) it->second->removePlayer(this);
    } //for
    isBankrupt = true;
    return true;
} // bankrupt

/************ assets ***********
* Purpose: Displays the assets for the player
*          First outputs the money, then the names of buildings and values of the buildings
* Return:
* Errors:
*/
void Player::assets() {
    cout << "The assets for " << this->name << " is:" << endl;
    cout << "$" << this->money << endl;
    for(map<string, Building*>::iterator it = properties.begin(); it != properties.end(); ++it) {
        cout << it->first << endl;
    }
}

/************* save ************
* Purpose:
* Return:
* Errors:
*/
ostream& Player::save(ostream& os) {
    os << this->name << " " << this->money << " " << this->position;
    if(this->position == 10 && !inTimsLine) {
        os << " " << 0;
    } //else {
        //os << " " << 1 << " " << numTimsLine;
    //}
    os << endl;
    return os;
}

void Player::fileSave(const string& file) {
    bool save = false;
    ofstream f(file.c_str());
//*****first line of save file is the number of players*****
    f << players.size() << endl;
    for (map<string, Player*>::iterator it = players.begin(); it != players.end(); ++it) {
        if(it->second == this) save = true;
        if(save && !it->second->getBankrupt()){
            it->second->save(f);
            //numPlayers++;
            //cout << it->first << endl;
        }
    }
    //cout << numPlayers << endl;
    for (map<string, Player*>::iterator it = players.begin(); it != players.end(); ++it) {
        if(it->second == this) break;
        it->second->save(f);
    }
    board->save(f);
}

void Player::addProperty(const string& property) {
    properties.insert(pair<string, Building*>(property, board->getProperty(property)));
}
void Player::removeProperty(const string& property) {
    properties.erase(property);
}

void Player::changeCup(int change){
    cup = cup + change;
    cout << "cup changed: " << cup << endl;
}
void Player::payTuition(){
    cout << "Pay Tuition: pay $300 (enter 'pay') or 10% all savings and assets (enter 'assets')" << endl;   
    string choice;
    cin >> choice;

    if (choice == "pay"){
        if (getMoney() >= 300){ setMoney(getMoney() - 300); 
            cout << "you payed $300" << endl; 
            cout << "current balance is $" << getMoney() << endl; }
        else { debt("BANK", 300); }
    } else if (choice == "assets"){
        int totalWorth = getWorth();
        int payment = 0.1*totalWorth;
        if (getMoney() >= payment){ 
            setMoney(getMoney() - payment);
            cout << "you payed $" << payment << endl; 
            cout << "current balance is $" << getMoney() << endl;
        } else { 
            debt("BANK", payment);
        }
    }
}