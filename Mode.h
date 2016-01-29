#ifndef __MODE_H__
#define __MODE_H__

#include <vector>

class Mode {
public:
    Mode();
    virtual ~Mode() = 0;
    virtual std::vector<int> roll() = 0;
};

#endif