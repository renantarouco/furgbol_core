#ifndef SENSOR_LOADER_H
#define SENSOR_LOADER_H

#include <virtual_sensors/isensor.h>

#include <string>
#include <map>
#include <utility>
#include <vector>

using CreateSensorFunc = ISensor* (*) ();
using GetInputNamesFunc = std::string (*) ();

class SensorLibLoader
{
public:
    void load_sensor_lib(std::string, std::string);
    std::map<std::string, void*> _sensor_classes;
};

#endif