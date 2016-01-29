#ifndef __CUP_H__
#define __CUP_H__
#include "Player.h"

const int maxCups = 4;
class Cup{
//    const int maxCups = 4;
    static Cup *cups[maxCups];
    Cup() {}
    ~Cup() {}//{ delete[] this->cups; }
    public:
    bool getCup(Player *player);
    Cup *getInstance();
};

#endif
