#ifndef __REGULARMODE_H__
#define __REGULARMODE_H__

#include "Mode.h"

class RegularMode: public Mode {
public:
    RegularMode();
    ~RegularMode();
    std::vector<int> roll();
};
#endif