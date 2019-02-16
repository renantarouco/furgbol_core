#ifndef S_ASSEMBLY_INTERNALS_H
#define S_ASSEMBLY_INTERNALS_H

#include <models/point.h>
#include <models/line.h>
#include <models/arc.h>
#include <models/field.h>
#include <models/camera_calibration.h>
#include <models/ball.h>
#include <models/robot.h>

#define CLASS_NAME(name) name ## _sensor

#define CAST_SENSOR(name) CLASS_NAME(name) *this_sensor = (CLASS_NAME(name)*) sensor;

#define PRIV_IN_NAME(name) __ ## name

#define INPUT_DECL(type,name) type *PRIV_IN_NAME(name);

#define INPUT_LINK_FN(type,name) void link_ ## name(type *src) { this->PRIV_IN_NAME(name) = src; }

#endif