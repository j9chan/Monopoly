//#ifndef __IRANEEDLES_H__
//#define __IRANEEDLES_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"
#include "iraNeedles.h"
#include "board.h"
#include "cup.h"

using namespace std;
int IraNeedles::action(Player *player){
    srand(time(0));
    int randCup = rand() % 100 + 1;
    //int randCup = 1;
    Cup *currentCup = NULL;

    if (randCup == 1){ 
        currentCup = currentCup->getInstance();
        if (currentCup != NULL){
            cout << "instance of cup available" << endl;
            player->changeCup(1);
            cout << player->getName() << " got a tims cup!" << endl;
        } else { cout << "There are no Tims cups available" << endl; }
    }
    if /*((randCup != 1)||*/(currentCup == NULL){
        srand(time(0));     //debt(bank)
        int random = rand() % 18 + 1;
        int money = player->getMoney();
        cout << "You have $" << money << endl;
        if (random == 1){ 
            cout << "Ira Needles Hall Card: you owe $200" << endl;
            if ((money -200) > 0){ player->setMoney(money - 200); }
            else{ player->debt("BANK", 200); }
        } else if ((random > 1)&&(random <= 3)) { 
            cout << "Ira Needles Hall Card: you owe $100" << endl;
            if ((money -100) > 0){ player->setMoney(money - 100); }
            else{ player->debt("Bank", 100); }
        } else if ((random > 3)&&(random <= 6)) {
            cout << "Ira Needles Hall Card: you owe $50" << endl;
            if ((money - 50) > 0){ player->setMoney(money - 50); }        
            else{ player->debt("Bank", 50); }
        }
        else if ((random > 6)&&(random <= 12)) { 
            cout << "Ira Needles Hall Card: you get $25" << endl;
            player->setMoney(money + 25); }
        else if ((random > 12)&&(random <= 15)) { 
            cout << "Ira Needles Hall Card: you get $50" << endl;
            player->setMoney(money + 50); }
        else if ((random > 15)&&(random <= 17)) { 
            cout << "Ira Needles Hall Card: you get $100" << endl;
            player->setMoney(money + 100); }
        else if (random == 18) { 
            cout << "Ira Needles Hall Card: you get $200" << endl;
            player->setMoney(money + 200); }
        cout << "You now have $" << player->getMoney() << endl;
    }
    return 1;
}
//};

