#ifndef SENSOR_INSTANCE_H
#define SENSOR_INSTANCE_H

#include <string>

#include <virtual_sensors/isensor.h>

template<typename T> using LinkInputFunc = void (*) (T*);

template<typename OutT>
class SensorInstance
{
public:
    SensorInstance(ISensor*, std::string);
    ~SensorInstance();
    template<typename InT> void link_input(std::string, InT*);
    OutT get_output();
    OutT *get_output_src();
private:
    ISensor *_sensor;
    std::string _type_name;
};

#endif