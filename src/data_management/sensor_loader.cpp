#include <data_management/sensor_loader.h>

#include <iostream>

#include <dlfcn.h>

void SensorLibLoader::load_sensor_lib(std::string dir, std::string name)
{
    std::string sensor_lib_path = dir + "/lib" + name + ".so";
    void *handle = dlopen(sensor_lib_path.c_str(), RTLD_NOW);
    char *error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    CreateSensorFunc create_sensor = (CreateSensorFunc) dlsym(handle, "create_sensor");
    error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    ISensor *sensor = create_sensor();

    GetInputNamesFunc get_input_names = (GetInputNamesFunc) dlsym(handle, "get_input_names");
    error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    std::cout << get_input_names() << std::endl;
    /*
    CreateSensorFunc create_sensor = (CreateSensorFunc) dlsym(handle, "create_sensor");
    error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    ISensor *sensor = create_sensor();
    
    GetInNamesFunc get_input_names = (GetInNamesFunc) dlsym(handle, "get_input_names");
    error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
    }
    std::string inputs = get_input_names();
    std::stringstream input_stream(inputs);
    std::vector<std::string> input_names;
    std::string input_name;
    while (!input_stream.eof()) {
        input_stream >> input_name;
        input_names.push_back(input_name);
    }

    SensorHandler *handler = new SensorHandler(handle, sensor, input_names);
    _sensor_classes.insert(std::make_pair(name, handler));
    

    LinkInFunc<float> link_x =
        (LinkInFunc<float>) dlsym(sensor_handle, "link_in_x");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", dlerror());
    }
    float *data = new float;
    *data = 5.0;
    link_x(sensor, data);

    sensor->in_to_out();

    GetOutFunc<float> get_y =
        (GetOutFunc<float>) dlsym(sensor_handle, "get_out_y");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", dlerror());
    }
    float my = *get_y(sensor);
    std::cout << my << std::endl;*/
}