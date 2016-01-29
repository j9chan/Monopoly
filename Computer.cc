#include "Computer.h"
#include "board.h"
#include <cstdlib>
#include <vector>

using namespace std;

Computer::Computer(map<char,bool>& pieces, Board *board, bool testing): Player(board, testing) {
    // randomly generate char character
    vector<char> v;
    for(map<char, bool>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
        if (!it->second) v.push_back(it->first);
    }
    srand(time(0));
    int i = rand() % v.size();
    pieces[v[i]] = true;
    getBoard()->addPlayer(v[i], getPosition());
    cout << "Computer player: " << getName() << " chose symbol " << v[i] << endl;
    // need to find a better way to get the ownable buildings
    string temp[] = {"AL", "ML", "ECH", "PAS", "HH", "RCH", "DWE", "CPE", "LHI", "BMH", "OPT", "EV1", "EV2",
                            "EV3", "PHYS", "B1", "B2", "EIT", "ESC", "C2", "MC", "DC", "MKV", "UWP", "V1", "REV", "CIF", "PAC"};
    for(int i = 0; i < 28; ++i) ownable[i] = temp[i];
    setSymbol(v[i]);
}
Computer::~Computer(){}