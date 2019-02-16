#ifndef SENSOR_ASSEMBLY_H
#define SENSOR_ASSEMBLY_H

#include <virtual_sensors/internals.h>
#include <virtual_sensors/isensor.h>

#include <string>

#define BEGIN_SENSOR(class,inputs) \
            extern "C" std::string get_input_names() { return #inputs; }\
            struct CLASS_NAME(class) : public ISensor  \
            {                 \
            

#define END_SENSOR(class,type) \
                type *__output = new type;\
                type __get_output() { return *this->__output; }\
                type *__get_output_src() { return this->__output; }\
            };\
            extern "C" ISensor *create_sensor() { return new CLASS_NAME(class); }\
            extern "C" type get_output(ISensor *sensor) {\
                CAST_SENSOR(class)\
                return this_sensor->__get_output();\
            }\
            extern "C" type *get_output_src(ISensor *sensor) {\
                CAST_SENSOR(class)\
                return this_sensor->__get_output_src();\
            }

#define IN(type,name) \
            INPUT_DECL(type,name) \
            INPUT_LINK_FN(type,name)

#define I(name) \
            *PRIV_IN_NAME(name)

#define BEGIN_IO(type,params...) \
            type behaviour(params) {

#define END_IO(args...) \
            }    \
            void update_output() { *this->__output = behaviour(args); }

#define EXTERN_INPUT(class,type,name) \
            extern "C" void link_ ## name(ISensor *sensor, type *src) { \
                CAST_SENSOR(class)\
                this_sensor->__link_ ## name(src);\
            }

#endif