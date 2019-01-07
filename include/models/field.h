#ifndef FIELD_H
#define FIELD_H

#include <models/line.h>
#include <models/arc.h>

#include <string>
#include <vector>

struct FieldShape
{
    std::string name;
    float thickness;
};

struct FieldLine : public FieldShape, public Line
{};

struct FieldArc : public FieldShape, public Arc
{};

struct Field
{
    int length;
    int width;
    int goal_length;
    int goal_width;
    int boundary_width;
    std::vector<FieldLine> lines;
    std::vector<FieldArc> arcs;
};

#endif