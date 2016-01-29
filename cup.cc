#include <iostream>
#include "cup.h"
#include "Player.h"

using namespace std;

Cup *Cup::cups[maxCups] = {NULL, NULL, NULL, NULL};

Cup *Cup::getInstance(){
    for (int num = 0; num < 4; num++){
        if ((num <= maxCups)&&(!cups[num])){
        	cout << "new Cup" << endl;
                //activeCups[i] = 1;
            cups[num] = new Cup();
            return cups[num];
        } //else { return NULL; }
    }
    return NULL;
}
