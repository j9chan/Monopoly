#include "Human.h"
#include "board.h"
#include "building.h"
#include <vector>

using namespace std;

Human::Human(map<char,bool>& pieces, Board* board, bool testing): Player(board, testing) {
    char sym;
    cout << "Choose a symbol to represent your player (G,B,D,P,S,$,L,T): " << endl;
    cin >> sym;
    while (pieces[sym]) {
        cout << "This piece is taken. Enter another one." << endl;
        cin >> sym;
    }
    pieces[sym] = true;
    setSymbol(sym);
    getBoard()->addPlayer(sym, getPosition());
}
// need to provide
Human::Human(const string& playerInfo, char pieceSymbol, Board* board, bool testing)
    : Player(playerInfo, pieceSymbol, board, testing){
        cout << "load human from file";
    }

void Human::execute(){
    bool same = false;
    // Get the responses from user input, exits when the user cannot make any more moves and enters "next"
    while (true) {
        if(inTimsLine) {
            if(!same) timsLine();
        }
        cout << getName() << ": Please enter a command: (menu shows a list of commands)" << endl;
        string command;
        cin >> command;
        if(command == "next") { // when no roll can be made
            break;

        } else if (command == "roll" && !inTimsLine) {
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
                //getBoard()->draw();
            } // while
            if(doubles == 3) {
                cout << "3 doubles were rolled: sent to DC Tims Line" << endl;
                setPosition(getBoard()->goToTims(this));
                setInTimsLine(true);
                same = true;
            }
        } else if (command == "buy") {
            cout << "Enter a property name: ";
            string property;
            cin >> property;
            buy(property);
        } else if (command == "sell") {
            cout << "Enter property name: ";
            string property;
            cin >> property;
            sell(property);
        } else if (command == "trade") {
            string name, give, receive;
            cin >> name >> give >> receive;
            trade(name, give, receive);
        } else if (command == "improve") {
            cout << "Enter a property and enter (buy/sell): ";
            string property, action; // action is buy or sell
            cin >> property >> action;
            improve(property, action);
        } else if (command == "mortgage") {
            string property;
            cin >> property;
            mortgage(property);
        } else if (command == "unmortgage") {
            string property;
            cin >> property;
            unmortgage(property);
        } else if (command == "bankrupt") {
            bankrupt();
            break;
        } else if (command == "assets") {
            assets();
        } else if (command == "save") {
            string file;
            cout << "Enter filename: " << endl;
            cin >> file;
            fileSave(file);
        } else if (command == "status") {
            cout << "Enter a property name: ";
            string name;
            cin >> name;
            string person = getBoard()->getProperty(name)->getOwner();
            if(person == "" || person == "BANK") cout << "Unowned" << endl;
            else cout << "Owner: " << person << endl;
            cout << "Cost: " << getBoard()->getProperty(name)->getCost() << endl;
            if(getBoard()->getProperty(name)->getMortgage()) cout << "This building is mortgaged" << cout;
        } else if (command == "menu") {
            cout << "Commands: " << endl;
            cout << "roll, next, trade, improve, mortgage, unmortgage, bankrupt, assets, save" << endl;
            cout << "others: status (owner,cost of a building)" << endl;
        }
        getBoard()->draw();
    }// while
} //execute

/************ timsLine ***********
* Purpose: Interaction for if the Player is in the Tims Line
*/
bool Human::timsLine(){
    cout << "You are in the Tims Line" << endl; // need to add code to pay up $50 or use roll up the rim
    vector<int> roll = this->roll();
    if (roll.at(0) == roll.at(1)) {
        setPosition(getBoard()->movePlayer(this, roll.at(0) + roll.at(1)));
        numTimsLine = 0;
        inTimsLine = false;
    } else if (numTimsLine == 3) {
        if(getMoney() < 50) {
            cout << "Not enough money to pay for the line" << endl;
            debt("BANK", 50);
        } else {
            cout << "You must pay(p) up or use the roll up the rim cup(c): " << endl;
            char c;
            cin >> c;
            switch(c){
                case 'p': setMoney(getMoney() - 50);
                case 'c': setCup(false);
            }
        }
        numTimsLine = 0;
        inTimsLine = false;
        setPosition(getBoard()->movePlayer(this, lastRoll));
    } else {
        cout << "Pay(p) $50 or use cup (c) or wait(w): " << endl;
        char c;
            cin >> c;
            switch(c){
                case 'w': ++numTimsLine;
                case 'p': setMoney(getMoney() - 50);
                case 'c': setCup(false);
            }
        if(c == 'c' || c == 'p') {
            numTimsLine = 0;
            inTimsLine = false;
            setPosition(getBoard()->movePlayer(this, lastRoll));
        }
    } // if-else
    return true;
} // timsline
