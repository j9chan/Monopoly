#include <iostream>
#include <string>
#include <cstdlib>
#include "nonProperty.h"
#include "slc.h"
#include "board.h"
#include "cup.h"
#include "Player.h"

using namespace std;

int SLC::action(Player *player){

    Board *board = player->getBoard();

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
    if /*(randCup != 1)||*/(currentCup == NULL){
        srand(time(0));
        int random = rand() % 24 + 1;
        if (random <= 3) { 
            cout << "SLC Card: move back 3 spaces" << endl;
            board->movePlayer(player, -3); }
        else if ((random > 3)&&(random <= 7)) { 
            cout << "SLC Card: move back 2 spaces" << endl;
            board->movePlayer(player, -2); }
        else if ((random > 7)&&(random <= 11)) { 
            cout << "SLC Card: move back 1 space" << endl;
            board->movePlayer(player, -1); }
        else if ((random > 11)&&(random <= 14)) { 
            cout << "SLC Card: move forward 1 space" << endl;
            board->movePlayer(player, 1); }
        else if ((random > 14)&&(random <= 18)) { 
            cout << "SLC Card: move forward 2 spaces" << endl;
            board->movePlayer(player, 2); }
        else if ((random > 18)&&(random <= 22)) { 
            cout << "SLC Card: move forward 3 spaces" << endl;
            board->movePlayer(player, 3); }
        else if (random == 23) { 
            player->setPosition(board->goToTims(player));
            cout << "GO TO DC TIMS LINE" << endl; }
        else if (random == 24) { cout << "COLLECT OSAP" << endl; }
    }
    return 1;
}

