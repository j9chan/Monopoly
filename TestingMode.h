#ifndef __TestingMode_H__
#define __TestingMode_H__
#include "Mode.h"

class TestingMode: public Mode {
public:
    TestingMode();
    ~TestingMode();
    std::vector<int> roll();
};

#endif