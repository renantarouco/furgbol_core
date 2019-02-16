#ifndef ISENSOR_H
#define ISENSOR_H

struct ISensor
{
    virtual void update_output() = 0;
};

#endif