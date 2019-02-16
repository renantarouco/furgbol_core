#ifndef SENSOR_TYPE_H
#define SENSOR_TYPE_H

#include <vector>
#include <string>

#include <virtual_sensors/isensor.h>
#include <data_management/sensor_instance.h>

using CreateSensorFunc = ISensor* (*) ();

template<typename T>
class SensorType
{
public:
    SensorType(CreateSensorFunc, std::vector<std::string>);
    SensorInstance<T> create_sensor();
    std::vector<std::string> get_input_names();
private:
    CreateSensorFunc _create_sensor;
    std::vector<std::string> _input_names;
};

#endif