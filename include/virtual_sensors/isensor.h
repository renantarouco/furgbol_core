#ifndef ISENSOR_H
#define ISENSOR_H

#include <vector>
#include <string>

struct ISensor
{
    virtual void update_output() = 0;
};

#endif