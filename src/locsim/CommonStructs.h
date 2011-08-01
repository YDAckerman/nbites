#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

#include <cmath>

static const double PI = 3.141592653589793;
static const double TO_RADIANS = PI / 180;
static const double TO_DEGREES = 180 / PI;

struct WalkVector
{
    WalkVector(int _x, int _y, int _mag)
        : x(_x), y(_y), magnitude(_mag)
    {
        theta = std::atan2(y, x) * TO_DEGREES;
    }

    WalkVector(int _mag, int _theta)
        : magnitude(_mag), theta(_theta)
    {
        x = magnitude * std::cos(theta * TO_RADIANS);
        y = magnitude * std::sin(theta * TO_RADIANS);
    }

    WalkVector()
        : x(0), y(0), magnitude(0), theta(0)
    {
    }

    int x;
    int y;
    int magnitude;
    int theta;
};

struct Odometry
{
    Odometry(int _dx, int _dy, int _dtheta)
        : dx(_dx), dy(_dy), dtheta(_dtheta)
    {
    }

    int dx;
    int dy;
    int dtheta;
};

#endif // COMMONSTRUCTS_H
