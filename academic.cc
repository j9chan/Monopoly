#include "academic.h"
#include <iostream>
#include <string>
using namespace std;

void Academic::save(ostream &out){
	if (this->getOwner() == "BANK"){ out << this->getName() << " " << this->getOwner() << endl; } 
	else { out << this->getName() << " " << this->getOwner() << " " << this->getImprove() << endl; }
}

int Academic::getTuition(int index){
//    cout << index << " improvements" << endl;
    return tuitionCost[index];
}