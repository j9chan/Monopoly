#include "RegularMode.h"
#include <cstdlib>
#include <iostream>
using namespace std;

RegularMode::RegularMode(){}
RegularMode::~RegularMode(){}

vector<int> RegularMode::roll(){
    srand(time(0));
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    cout << "A "<< die1 << " and " << die2 << " were rolled" << endl;
    vector<int> roll;
    roll.push_back(die1);
    roll.push_back(die2);
    return roll;
}