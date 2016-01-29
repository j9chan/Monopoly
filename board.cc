#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "board.h"
#include "cell.h"
#include "building.h"
#include "academic.h"
#include "residence.h"
#include "gym.h"
#include "nonProperty.h"
#include "slc.h"
#include "iraNeedles.h"
#include "osap.h"
#include "tuition.h"
#include "geese.h"
#include "coop.h"
#include "timsLine.h"
#include "goToTims.h"
#include "Player.h"

void Board::load(istream &loadf, int numPlayers, Player **players){

    int a[12] = {0, 2, 4, 7, 10, 17, 20, 22, 30, 33, 36, 38};

    int init[176] = {40, 50, 2, 10, 30, 90, 160, 250, 60, 50, 4, 20, 60, 180, 320, 450,
                    100, 50, 6, 30, 90, 270, 400, 550, 100, 50, 6, 30, 90, 270, 400, 550,
                    120, 50, 8, 40, 100, 300, 450, 600, 
                    140, 100, 10, 50, 150, 450, 625, 750, 140, 100, 10, 50, 150, 450, 625, 750, 
                    160, 100, 12, 60, 180, 500, 700, 900,
                    180, 100, 14, 70, 200, 550, 750, 950, 180, 100, 14, 70, 200, 550, 750, 950,
                    200, 100, 16, 80, 220, 600, 800, 1000,
                    220, 150, 18, 90, 250, 700, 875, 1050, 220, 150, 18, 90, 250, 700, 875, 1050,
                    240, 150, 20, 100, 300, 750, 925, 1100,
                    260, 150, 22, 110, 330, 800, 975, 1150, 260, 150, 22, 110, 330, 800, 975, 1150, 
                    280, 150, 24, 120, 360, 850, 1025, 1200, 
                    300, 200, 26, 130, 390, 900, 1100, 1275, 300, 200, 26, 130, 390, 900, 1100, 1275,
                    320, 200, 28, 150, 450, 1000, 1200, 1400, 
                    350, 200, 35, 175, 500, 1100, 1300, 1500,
                    400, 200, 50, 200, 600, 1400, 1700, 2000};

    cells[0] = new OSAP(0);
    cells[2] = new SLC(2);
    cells[4] = new Tuition(4);
    cells[7] = new IraNeedles(7);
    cells[10] = new TimsLine(10);
        
    cells[17] = new SLC(17);
        
    cells[20] = new Geese(20);
    cells[22] = new IraNeedles(22);
    cells[30] = new GoToTims(30);

    cells[33] = new SLC(33);
    cells[36] = new IraNeedles(36);
    cells[38] = new Coop(38);

    int academicCount = 0;
    for (int i = 0; i < 40; i++){
        bool preset = false;
        for (int j = 0; j < 12; j++){
            if (a[j] == i) { 
                preset = true; 
                break;
            }
//            if (a[j] == 1) { cout << "index one found, a[j] = " << a[j] << endl; }
        }
        if (preset == false){
            string buildLine;
            getline(loadf, buildLine);
            stringstream ssline(buildLine);

            string name;
            ssline >> name;
            int nImprove = -1;
            string owner;
            ssline >> owner;

            if (stringstream(owner) >> nImprove){
                owner = "BANK";
            }
            if (owner != "BANK"){
                ssline >> nImprove;

//                cout << "owner:  " << owner << "  Improvements:  " << nImprove << endl;
            }
            //cout << "making square " << i << endl;
            if ((name == "MKV")||(name == "UWP")||(name == "V1")||(name == "REV")){
                cells[i] = new Residence(i, name, 200, "Residence");
                addToBlock("Residence", name, owner);
            } else if ((name == "PAC")||(name == "CIF")){
                cells[i] = new Gym(i, name, 150, owner, "Gym");
                addToBlock("Gym", name, owner);
            } else {
      
                string block = "";
                if((name == "AL") || (name == "ML")) block = "Arts1";
                else if((name == "ECH") || (name == "PAS") || (name == "HH")) block = "Arts2";
                else if(name == "RCH" || name == "DWE" || name == "CPH") block = "Eng";
                else if(name == "LHI" || name == "BMH" || name == "OPT") block = "Health";
                else if(name == "EV1" || name == "EV2" || name == "EV3") block = "Env";
                else if(name == "PHYS" || name == "B1" || name == "B2") block = "Sci1";
                else if(name == "EIT" || name == "ESC" || name == "C2") block = "Sci2";
                else if(name == "MC" || name == "DC") block = "Math";
                cells[i] = new Academic(i, name, init[academicCount], init[academicCount+1], 
                    init[academicCount+2], init[academicCount+3], init[academicCount+4], init[academicCount+5], 
                    init[academicCount+6], init[academicCount+7], block,owner, nImprove);
                addToBlock(block, name, owner);
                //cells[i] = new Academic(i, name, init[academicCount], init[academicCount+1], init[academicCount+2], init[academicCount+3], init[academicCount+4], init[academicCount+5], init[academicCount+6], init[academicCount+7], block, owner, nImprove);
                
                academicCount += 8;
            }
        }
    }
        
        // add the players to a cell
        int i = 0;
        for (map<char, int>::iterator it = playerList.begin(); it != playerList.end(); ++it){
            cells[playerList[it->first]]->addPlayer(it->first, i);
            ++i;
        }
}

void Board::save(ostream &savef){
    for (int i = 0; i < 40; i++){
        cells[i]->save(savef);
    }
}

void outName(Cell *cp, int cellW, int o){
    int j = 0;
    if (o == 2){
        j = (cp->getName2()).length()+1;
        cout << "|" << cp->getName2();
    } else {
        j = (cp->getName()).length()+1;
        cout << "|" << cp->getName(); 
    }
    for (; j < cellW; j++) { cout << " "; }
}

void outImp(Cell *cp, int cellW, int numImproves){
    int j = 1;
    cout << "|";
    for(; j < numImproves+1; j++){ cout << "I"; }
    for(; j < cellW; j++){ cout << " "; }
}

void outCurr(Cell *cp, int cellW){
    int j = (cp->currPlayers()).length()+1;
    cout << "|" << cp->currPlayers();
    for (; j < cellW; j++){ cout << " "; }    
}

void Board::draw(){
    int starting = 20;
    int cellW = 8;
    int cellN = starting + 11;
    Top(starting, cellW, cellN);

    string centre;
    for (int i = 0; i < 71; i++){ centre = centre + " "; }
    string done;
    for (int i = 0; i < 71; i++){ done = done + "_"; }
    cellN--;
    while (cellN < 39){
        starting--;
        cellN ++;
        if (this->cells[starting]->getImprove() == -1){ outName(this->cells[starting], cellW, 1); }
        else {outImp(this->cells[starting], cellW, this->cells[starting]->getImprove()); }
        cout << "|" << centre;

        if (this->cells[cellN]->getImprove() == -1){ outName(this->cells[cellN], cellW, 1); }
        else {outImp(this->cells[cellN], cellW, this->cells[cellN]->getImprove()); }
        cout << "|" << endl;

        if (this->cells[starting]->getImprove() == -1){ outName(this->cells[starting], cellW, 2); }
        else{ cout << "|-------"; }
        cout << "|" << centre;

        if (this->cells[cellN]->getImprove() == -1){ outName(this->cells[cellN], cellW, 2); }
        else{ cout << "|-------"; }
        cout << "|" << endl;

        if (this->cells[starting]->getImprove() != -1){ outName(this->cells[starting], cellW, 1); }
        else{ cout << "|       "; }
        cout << "|" << centre;

        if (this->cells[cellN]->getImprove() != -1){ outName(this->cells[cellN], cellW, 1); }
        else{ cout << "|       "; }
        cout << "|" << endl;

        outCurr(this->cells[starting], cellW);
        cout << "|" << centre;
        outCurr(this->cells[cellN], cellW);
        cout << "|" << endl;

        if (cellN != 39){ cout << "|_______|" << centre << "|_______|" << endl; }
        else { cout << "|_______|" << done << "|_______|" << endl; }
    }
//    starting = 10;
    cellN = 0;
    Bottom(0, cellW, cellN);
}

void Board::Top(int starting, int cellW, int cellN){
    for (int i = starting*cellW; i < cellW*cellN; i++){ cout << "_"; }
    cout << endl;

    for (int i = starting; i < cellN; i++){
        if (this->cells[i]->getImprove() == -1){ outName(this->cells[i], cellW, 1); } 
        else { outImp(this->cells[i], cellW, this->cells[i]->getImprove()); }
    }
    cout << "|" << endl;

    for (int i = starting; i < cellN; i++){
        if (this->cells[i]->getImprove() == -1){ outName(this->cells[i], cellW, 2); }
        else{ cout << "|-------"; }//for (int j = 1; i < cellW; i++){ cout << "-"; } }
    }
    cout << "|" << endl;

    for (int i = starting; i < cellN; i++) {
        if (this->cells[i]->getImprove() != -1){  outName(this->cells[i], cellW, 1); }
        else { cout << "|       "; }
    }
    cout << "|" << endl;
    
    for (int i = starting; i < cellN; i++) {
        outCurr(this->cells[i], cellW);
    }
    cout << "|" << endl;

    for (int i = starting*cellW; i < cellW*cellN; i++){
        if(i%cellW == 0){ cout << "|"; }
        else { cout << "_"; }
    }
    cout << "|" << endl;
    
}

void Board::Bottom(int starting, int cellW, int cellN){
    //for (int i = starting*cellW; i > cellN; i--){ cout << "_"; }
    //cout << endl;

    for (int i = starting; 10 - i >= cellN; i++){
        if (this->cells[10 - i]->getImprove() == -1){ outName(this->cells[10 - i], cellW, 1); } 
        else { outImp(this->cells[10 - i], cellW, this->cells[10 - i]->getImprove()); }
    }
    cout << "|" << endl;

    for (int i = starting; 10 - i >= cellN; i++){
        if (this->cells[10 - i]->getImprove() == -1){ outName(this->cells[10 - i], cellW, 2); }
        else{ cout << "|-------"; }
    }
    cout << "|" << endl;

    for (int i = starting; 10 - i >= cellN; i++) {
        if (this->cells[10 - i]->getImprove() != -1){  outName(this->cells[10 - i], cellW, 1); }
        else { cout << "|       "; }
    }
    cout << "|" << endl;
    
    for (int i = starting; 10 - i >= cellN; i++) {
        outCurr(this->cells[10 - i], cellW);
    }
    cout << "|" << endl;

    for (int i = starting*cellW; (10 * cellW) - i < cellW*cellN; i++){
        if(i%cellW == 0){ cout << "|"; }
        else { cout << "_"; }
    }
    //cout << "|" << endl;
    for (int i = 0; i < 11*cellW; i++){
        if (i%cellW == 0){ cout << "|"; }
        else{ cout << "_"; }
    }
    cout << endl;
}

Board::~Board(){
    for (int i = 0; i < 40; i++){
        delete cells[i];
    }
}
void Board::addToBlock(string block, string building, string owner) {
    if(propertyBlock.count(block) > 0) {
        propertyBlock[block].insert(pair<string,string>(building, owner));
    } else {
        map<string,string> inner;
        inner.insert(pair<string,string>(building, owner));
        propertyBlock.insert(pair<string, map<string,string> >(block, inner));
    }
}

// what happens when the player is bankrupt
void Board::declareBankrupt(char sym) {
    removeFromBoard(sym, playerList[sym]);
    playerList.erase(sym);
    //cout << "size of the list: " << playerList.size() <<endl;
}
// need to remove ownership as well
void Board::removeFromBoard(char sym, int position) {
    removePlayerFromCell(sym, position);
}
void Board::removePlayerFromCell(char sym, int position) {
    int i = 0;
    for (map<char, int>::iterator it = playerList.begin(); it != playerList.end(); ++it) {
        if(sym == it->first) break;
        ++i;
    }
    cells[position]->removePlayer(i);
}

void Board::addPlayerToCell(char sym, int position) {
    int i = 0;
    for(map<char,int>::iterator it = playerList.begin(); it != playerList.end(); ++it) {
        if(it->first == sym) break;
        ++i;
    }
    cells[position]->addPlayer(sym, i);
}

// move the player a certain sum
// remove player from previous cell and add to the new one
int Board::movePlayer(Player* player, int rollSum) {
    //cout << "Moving player " << player->getName() << " " << rollSum << " spaces" << endl;
    if(player->getPosition() + rollSum >= 40) player->setMoney(player->getMoney() + 200); // when passing OSAP
    removePlayerFromCell(player->getSymbol(), playerList[player->getSymbol()]);
    playerList[player->getSymbol()] = (playerList[player->getSymbol()] + rollSum) % 40; // set to 0 if at 40
    addPlayerToCell(player->getSymbol(), playerList[player->getSymbol()]);
    // charge rent here too
    string type = cells[playerList[player->getSymbol()]]->getBlock();
    Building *b = static_cast<Building*>(cells[playerList[player->getSymbol()]]);
    string owner = cells[playerList[player->getSymbol()]]->getOwner();
    if (type != "" && owner != "" && owner != "BANK" && owner != player->getName() && !b->getMortgage()) { // charge rent/tuition/work out fees
        cout << owner << endl;
        int numProp = 1;
        int payment = 0;
        if(type == "Gym") {
            map<string,string> gym = propertyBlock[type];
            for(map<string, string>::iterator it = gym.begin(); it != gym.end(); ++it) {
                if(it->second == owner) ++numProp;
            }
            if(numProp == 1) payment = rollSum * 4;
            else payment = rollSum * 10;
            cout << player->getName() << " pay gym fee: " << payment <<endl;
        } else if (type == "Residence"){
            payment = 25;
            map<string,string> rez = propertyBlock[type];
            for(map<string,string>::iterator it = rez.begin(); it != rez.end(); ++it) {
                if(it->second == owner) payment *= 2; // numProp becomes the detractor
            }
            cout << player->getName() <<" pay rent:" << payment << endl;
        } else {
            map<string,string> aca = propertyBlock[type];
            int num = 0; //number of total buildings in the monopoly
            numProp = 0;
            for(map<string,string>::iterator it = aca.begin(); it != aca.end(); ++it) {
                if(it->second == owner) ++numProp;
                ++num;
            }
            Academic *a = static_cast<Academic*> (cells[playerList[player->getSymbol()]]);
            int imp = a->getImprove();
            //cout << "imp: " << imp << " numprop: " << numProp << " num: " << num << endl;
            if(numProp==num && imp == 0) { // building has no improvements
                payment = a->getTuition(imp) * 2;
            } else { // building has improvements
                payment = a->getTuition(imp);
            }
            cout << player->getName() << " pay tuition: " << payment << endl;
        }
        if(player->getMoney() < payment) {
            player->debt(owner, payment);
        }
        player->setMoney(player->getMoney() - payment);
        if (owner != "BANK") {
            Player* own = player->getOtherPlayer(owner);
            own->setMoney(own->getMoney() + payment);
        }
    }
    cells[playerList[player->getSymbol()]]->action(player);
    return playerList[player->getSymbol()];
    
}

Building* Board::getProperty(string property) {
    for(int i = 0; i < 40; ++i) {
        //cout << cells[i]->getName() << endl;
        //cout << "getProperty loop" << endl;//cells[i]->getName() << endl;
        if (cells[i]->getName() == property) {
            //cout << property << " adding to map" << endl;
            return static_cast<Building*>(cells[i]);
        }
    }
    cout << "Not found" << endl;
    return 0;
}
//switches the ownership in the propertyBlock
void Board::changeOwner(const string& name, const string& property) {
    for(map<string, map<string,string> >::iterator it = propertyBlock.begin(); it != propertyBlock.end(); ++it) {
        //cout << "block " << it->first << endl;
        //for(map<string,string>::iterator i = it->second.begin(); i != it->second.end(); ++i) cout << i->first << endl;
        if(it->second.count(property) > 0) { it->second[property] = name; }
    }
}

int Board::goToTims(Player *player) {
    player->setInTimsLine(true);
    removePlayerFromCell(player->getSymbol(), playerList[player->getSymbol()]);
    playerList[player->getSymbol()] = 10;
    addPlayerToCell(player->getSymbol(), playerList[player->getSymbol()]);
    return 10;
}
