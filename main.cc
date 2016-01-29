#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

#include "board.h"
#include "cell.h"
#include "Player.h"
#include "Computer1.h"
#include "Human.h"

/*********** insertPieces **********
* Purpose: put all the symbols in a map to be accessed at a later time
* Also need map so the computer knows which ones are taken
*/
map<char, bool> insertPieces() {
    map<char, bool> map;
    map.insert(pair<char,bool>('G', false));
    map.insert(pair<char,bool>('B', false));
    map.insert(pair<char,bool>('D', false));
    map.insert(pair<char,bool>('P', false));
    map.insert(pair<char,bool>('S', false));
    map.insert(pair<char,bool>('$', false));
    map.insert(pair<char,bool>('L', false));
    map.insert(pair<char,bool>('T', false));
    return map;
}

int main(int argc, char* argv[]) { // need to add command line messages
    bool testing = false;
    string loadFile;
    bool loading = false;
    if(argc == 2) {
        cout << "Testing mode is on: " << endl;//<< argv[0] << endl;
        testing = true;
    } else if (argc == 3) {
        cout << "Loading mode is on: " << endl;
        loading = true;
        loadFile = argv[2];
        cout << loadFile << endl;
    } else if (argc == 4) {
        testing = true;
        loading = true;
        string cmd = argv[2];
        if (cmd == "-testing") {
            loadFile = argv[3];
        } else {
            loadFile = argv[2];
        }
    }

    Board *board = new Board();
    int numPlayers;
    Player *players[6];
    map<char, bool> pieces = insertPieces();

    if(loading){ // Load file response
        ifstream f(loadFile.c_str());
        f >> numPlayers;
        cout << "loading file: " << loadFile << endl;
        map<char, bool>::iterator it = pieces.begin();
        string temp;
        getline(f, temp);
        for (int i = 0; i < numPlayers; ++i) {
            string line;
            getline(f, line);
            pieces[it->first] = true;
            players[i] = new Human(line, it->first, board, testing);
            ++it;
            //cout << line << ":  " << players[i]->getSymbol() << endl;
        }
        cout << numPlayers << endl;
        board->load(f, numPlayers, players);
        board->draw();

        for(int i = 0; i < numPlayers; ++i) {
        for(int j = 0; j < numPlayers; ++j) {
            players[i]->addPlayer(players[j]);
        }
    }
        // set the properties for the player
        ifstream file(loadFile.c_str());
        string line;
        for(int i = 0; i < numPlayers + 1; ++i) getline(file, line);
        for(int i = 0; i < 28; ++i) {
            getline(file, line);
            stringstream ss(line);
            string building, owner;
            ss >> building >> owner;
            if(owner != "BANK") {
                players[0]->getOtherPlayer(owner)->addProperty(building);
            }

        }

    } else { // Use input from user to create players --> fresh install
        cout << "Please enter the number of players: " << endl;
        cin >> numPlayers;
        // Creates the players for the game
        for (int i = 0; i < numPlayers; ++i) {
            cout << "Is the player human or computer (h/c): " << endl;
            char type;
            cin >> type;
            if(type == 'h') {
                cout << "Human player created" << endl;
                players[i] = new Human(pieces , board, testing);
            } else {
                cout << "Computer player will be created"<< endl;
                players[i] = new Computer1(pieces, board, testing);
            }
        } // for
        ifstream init("init.txt");
        board->load(init, numPlayers, players);
        board->draw(); 

        for(int i = 0; i < numPlayers; ++i) {
        for(int j = 0; j < numPlayers; ++j) {
            players[i]->addPlayer(players[j]);
        }
    }
    }
    // Adds all player to the player map -- includes self (for saving purposes)
    

    // Enter Game Play
    bool endGame = false;
    // Commence game
    while((!board->getBankrupt()) && (!endGame)) {
    // iterate through each player's turn
        for(int i = 0; i < numPlayers; ++i) {
            if(players[i]->getBankrupt()) continue;
            players[i]->execute();
            if(board->getBankrupt()) break;
            cout << "Would you like to end the game? y/n" << endl;
            char c;
            cin >> c; // see if they want to end the game
            if (c == 'y') {
                endGame = true;
                break;
            }
        } // for
    } // while
    if(board->getBankrupt()) {
        for(int i = 0; i < numPlayers; ++i) {
            if(!players[i]->getBankrupt()) cout << players[i]->getName() << " won!" << endl;
        }
    }

    cout << "Game finished" << endl;
    // delete all the players
    for (int i = 0; i < numPlayers; ++i) {
        delete players[i];
    }
    delete board;
    
}
