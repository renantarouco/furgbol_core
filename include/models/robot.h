#ifndef ROBOT_H
#define ROBOT_H

struct Robot
{
    float confidence;
    unsigned id;
    float x;
    float y;
    float orientation;
    float pixel_x;
    float pixel_y;
    float height;
};

#endif