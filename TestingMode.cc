#include "TestingMode.h"
#include <iostream>
using namespace std;

TestingMode::TestingMode(){}
TestingMode::~TestingMode(){}
/*********** rollTest ***********
* Purpose: for testing mode
*/
std::vector<int> TestingMode::roll(){
    cout << "Enter your rolls (separated by spaces please): " << endl;
    vector<int> roll;
    int die1, die2;
    cin >> die1 >> die2;
    roll.push_back(die1);
    roll.push_back(die2);
    return roll;
}