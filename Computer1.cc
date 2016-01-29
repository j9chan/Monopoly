#include "Computer1.h"
#include <cstdlib>
#include "cell.h"
#include "board.h"
using namespace std;

Computer1::Computer1(map<char,bool>& pieces, Board *board, bool testing): Computer(pieces, board, testing) {

}
Computer1::~Computer1() {
}

void Computer1::execute(){
    cout << "Computer Player: " << getName() << "'s turn" << endl;
    if(getMoney() < 0) bankrupt();
    if(inTimsLine) {
        timsLine();
    }
    if(!getBankrupt()){
        int doubles = 0;
        int die1 = 0;
        int die2 = 0;
        while(doubles < 3) {
            vector<int> v = roll();
            die1 = v.at(0);
            die2 = v.at(1);
            setLastRoll(die1 + die2);
            if(doubles < 2) setPosition(getBoard()->movePlayer(this, die1 + die2));
            if(die1 != die2) break;
            ++doubles;
            getBoard()->draw();
        } // while
        if(doubles == 3) {
            cout << "3 doubles were rolled: Sent to DC Tims Line" << endl;
            setPosition(getBoard()->goToTims(this));
            setInTimsLine(true);
            getBoard()->draw();
        }
        if (getBoard()->getCell(getPosition())->getBlock() != "") {
            string property = getBoard()->getCell(getPosition())->getName();
            buy(property);
            getBoard()->draw();
        }
    }
} //execute

bool Computer1::timsLine() {
    vector<int> roll = this->roll();
    if (roll.at(0) == roll.at(1)) {
        setPosition(getBoard()->movePlayer(this, roll.at(0) + roll.at(1)));
        numTimsLine = 0;
        inTimsLine = false;
    } else if (numTimsLine == 3) {
        if(getMoney() < 50) {
            debt("BANK", 50);
        } else if(!getCup()) {
            setMoney(getMoney() - 50);
        } else {
            setCup(false);
        }
        numTimsLine = 0;
        inTimsLine = false;
        setPosition(getBoard()->movePlayer(this, lastRoll));
    } else {
        if(getMoney() >= 50){
            setMoney(getMoney() - 50);
            numTimsLine = 0;
            inTimsLine = false;
            setPosition(getBoard()->movePlayer(this, lastRoll));
        } else if (getCup()){
            setCup(false);
            numTimsLine = 0;
            inTimsLine = false;
            setPosition(getBoard()->movePlayer(this, lastRoll));
        } else {
            ++numTimsLine;
        }
    } // if-else
    return true;
} // timsline
// sells all of it's stuff pronto
void Computer1::debt(const string& owner, int payment) {
    if(!properties.empty()) {
        for(map<string, Building*>::iterator it = properties.begin(); it != properties.end(); ++it) {
            if(owner != "BANK") {
                getOtherPlayer(owner)->addProperty(it->first);
            } else {
                sell(it->first);
            }
            removeProperty(it->first);
        }
    }
    if(owner != "BANK") getOtherPlayer(owner)->setMoney(getOtherPlayer(owner)->getMoney() + getMoney());
    setMoney(0);
    bankrupt();
}
bool Computer1::notifyOfTrade(const string& from, const string& give, const string& receive) {
    return false;
}
void Computer1::payTuition(){
    int totalWorth = getWorth();
        int payment = 0.1*totalWorth;
        if (getMoney() >= payment){ setMoney(getMoney() - payment); }
        else { debt("BANK", payment); }
}