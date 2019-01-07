#ifndef BALL_H
#define BALL_H

struct Ball
{
    float confidence;
    unsigned area;
    float x;
    float y;
    float z;
    float pixel_x;
    float pixel_y;
};

#endif