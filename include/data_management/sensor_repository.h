#ifndef SENSOR_REPOSITORY_H
#define SENSOR_REPOSITORY_H

#include <string>
#include <map>

#include <data_management/sensor_type.h>
#include <data_management/sensor_instance.h>

using GetInputNamesFunc = std::string (*) ();

class SensorRepository
{
public:
    template<typename T> void load_type(std::string, std::string);
    template<typename T> void instantiate_sensor(std::string, std::string);
private:
    std::map<std::string, SensorType> _sensor_types;
    std::map<std::string, SensorInstance> _sensor_instances;
};

#endif