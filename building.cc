#include "building.h"

// when building is sold: unMortgage the building
// is the building was mortgaged set the mortgage to false and return the amount
// of money that mortgaging gave the player
int Building::sell() { 
    owner = "";
    int payout = 0;
    if(!isMortgage) {
        payout = cost;
    } else {
        payout = cost - cost / 2 + cost * 0.1;
        isMortgage = false;
    }
    return payout;
}