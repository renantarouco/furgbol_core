#include <data_management/sensor_repository.h>

#include <iostream>
#include <sstream>

#include <dlfcn.h>

template<typename T>
void SensorRepository::load_type(std::string dir, std::string name)
{
    std::string sensor_lib_path = dir + "/lib" + name + ".so";
    void *handle = dlopen(sensor_lib_path.c_str(), RTLD_NOW);
    char *error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    CreateSensorFunc create_sensor_func = (CreateSensorFunc) dlsym(handle, "create_sensor");
    error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    GetInputNamesFunc get_input_names_func = (GetInputNamesFunc) dlsym(handle, "get_input_names");
    error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    std::stringstream inputs_stream(get_input_names_func());
    std::string input_name;
    std::vector<std::string> input_names;
    while (!inputs_stream.eof()) {
        inputs_stream >> input_name;
        input_names.push_back(input_name);
    }
    SensorType<T> sensor_type(create_sensor_func, input_names);
    _sensor_types.insert(std::make_pair(name, sensor_type));
}

template<typename T>
void SensorRepository::instantiate_sensor(std::string type_name, std::string sensor_id)
{
    SensorInstance<T> sensor_instance = _sensor_types[type_name].create_sensor<T>();
    _sensor_instances.insert(std::make_pair(std::string, sensor_instance));
}