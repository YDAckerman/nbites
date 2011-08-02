#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

#include <cmath>
#include <iostream>
#include <vector>
#include "NBMath.h"
using namespace NBMath;

//static const double PI = 3.141592653589793;
static const double TO_RADIANS = PI / 180;
static const double TO_DEGREES = 180 / PI;

struct Odometry
{
    Odometry(int _dx, int _dy, int _dtheta)
        : dx(_dx), dy(_dy), dtheta(_dtheta)
    {
    }

    Odometry()
        : dx(0), dy(0), dtheta(0)
    {
    }

    int dx;
    int dy;
    int dtheta;
};

typedef enum
{
    YGP,
    BGP,
    LCORNER,
    TCORNER,
    CROSS
} VisualLandmarkType;

//////////////////////////////////////////////////
// CODE DUPLICATED FOR OFFLINE TESTING PURPOSES //
//////////////////////////////////////////////////

class MotionModel
{
public:
    MotionModel(float f = 0.0f, float l = 0.0f, float r = 0.0f)
        : deltaF(f), deltaL(l), deltaR(r) { }
    MotionModel(const MotionModel& other)
        : deltaF(other.deltaF), deltaL(other.deltaL), deltaR(other.deltaR) { }
    float deltaF;
    float deltaL;
    float deltaR;

    friend std::ostream& operator<< (std::ostream &o, const MotionModel &u) {
        return o << "(" << u.deltaF << ", " << u.deltaL << ", " << u.deltaR
                 << ")";
    }

};

class PoseEst
{
public:
    PoseEst(float _x, float _y, float _h)
        : x(_x), y(_y), h(_h)
    {
    }

    PoseEst(const PoseEst& other)
        : x(other.x), y(other.y), h(other.h)
    {
    }

    PoseEst()
    {
    }

    float x;
    float y;
    float h;

    PoseEst operator+ (const PoseEst o)
    {
        return PoseEst(o.x + x,
                       o.y + y,
                       o.h + h);
    }

    PoseEst operator* (const float m)
    {
        x = x*m;
        y = y*m;
        h = h*m;

        return PoseEst(x, y, h);
    }

    PoseEst& operator+= (const PoseEst o)
    {
        x += o.x;
        y += o.y;
        h += o.h;

        return *this;
    }

    PoseEst operator+ (const MotionModel u_t)
    {
        // Translate the relative change into the global coordinate system
        // And add that to the current estimate
        float sinh, cosh;
        sincosf(h, &sinh, &cosh);
        return PoseEst(x + u_t.deltaF * cosh -
                       u_t.deltaL * sinh,
                       y + u_t.deltaF * sinh +
                       u_t.deltaL * cosh,
                       h + u_t.deltaR);
    }

    void operator+= (const MotionModel u_t)       
    {
        float sinh, cosh;
        sincosf(h, &sinh, &cosh);

        // Translate the relative change into the global coordinate system
        // And add that to the current estimate
        x += u_t.deltaF * cosh - u_t.deltaL * sinh;
        y += u_t.deltaF * sinh + u_t.deltaL * cosh;
        h += u_t.deltaR;
    }

    float distanceTo( const PoseEst o)
    {
      float d_y = y - o.y;
      float d_x = x - o.x;
      float d_h = subPIAngle(h - o.h);

      return sqrt( d_y*d_y + d_x*d_x + d_h*d_h );
    }
    friend std::ostream& operator<< (std::ostream &o, const PoseEst &c)
        {
            return o << "(" << c.x << ", " << c.y << ", " << c.h << ")";
        }


};

struct PointLandmark
{
    PointLandmark(float _x, float _y) : x(_x), y(_y) {}
    PointLandmark() {}
    float x;
    float y;
    friend std::ostream& operator<< (std::ostream &o, const PointLandmark &c)
        {
            return o << c.x << " " << c.y;
        }
};

struct CornerLandmark
{
    CornerLandmark(float _x, float _y, float _a) : x(_x), y(_y), angle(_a) {}
    CornerLandmark() {}
    float x;
    float y;
    float angle;
    friend std::ostream& operator<< (std::ostream &o, const CornerLandmark &c)
    {
        return o << c.x << " " << c.y << " " << c.angle;
    }

};

template<class LandmarkT>
class Observation
{
public:
    Observation(float _visDist, float _visBearing, float _sigma_d,
                float _sigma_b, VisualLandmarkType _t)
        : visDist(_visDist), visBearing(_visBearing), sigma_d(_sigma_d),
          sigma_b(_sigma_b), type(_t)
    {
    }

    virtual ~Observation()
    {
    }

    float getVisDistance() const { return visDist; }
    float getVisBearing() const { return visBearing; }
    float getVisBearingDeg() const { return TO_DEGREES * visBearing; }
    float getDistanceSD() const { return sigma_d; }
    float getBearingSD() const { return sigma_b; }
    VisualLandmarkType getType() const { return type; }
    int getNumPossibilities() const { return possibilities.size(); }
    bool isAmbiguous() const { return  getNumPossibilities() > 1; }
    std::vector<LandmarkT> getPossibilities() const { return possibilities; }

    void setVisDistance(float _d) { visDist = _d; }
    void setVisBearing(float _b) { visBearing = _b; }
    void setDistanceSD(float _sdD) { sigma_d = _sdD; }
    void setBearingSD(float _sdB) { sigma_b = _sdB; }
    void setType(VisualLandmarkType _t) { type = _t; }

    friend std::ostream& operator<< (std::ostream &o, const Observation &c)
    {
        return o << "Obs " << c.id << ": (" << c.visDist << ", " << c.visBearing
                 << ", " << c.sigma_d << ", " << c.sigma_b << ")";
    }

protected:
    // Vision information
    float visDist, visBearing;
    float sigma_d, sigma_b;

    // Identity information
    VisualLandmarkType type;
    std::vector<LandmarkT> possibilities;
};

typedef Observation<PointLandmark> PointObservation;

class CornerObservation : public Observation<CornerLandmark>
{
public:
    CornerObservation(float _visDist, float _visBearing, float _sigma_d,
                      float _sigma_b, float _visOrientation, float _sigma_o) :
        Observation<CornerLandmark>(_visDist, _visBearing, _sigma_d,
                _sigma_b, LCORNER), visOrientation(_visOrientation),
        sigma_o(_sigma_o)
    {

        // Ensure that the sd is not zero (will cause errors later)
        if (sigma_o == 0.0)
        {
            std::cout << "Zero standard deviation is ZERO for obs: "
                      << *this << std::endl;
        }
    }

    virtual ~CornerObservation()
    {
    }

    float getVisOrientation() const { return visOrientation; }
    float getOrientationSD() const { return sigma_o; }

    friend std::ostream& operator<< (std::ostream &o,
                                     const CornerObservation &c)
    {
        return o << "Obs " << c.getType() << ": (" << c.visDist << ", " << c.visBearing
                 << ", " << c.visOrientation << ", "
                 << c.sigma_d << ", " << c.sigma_b
                 << ", " << c.sigma_o <<  ")";
    }

private:
    float visOrientation;
    float sigma_o;
};

#endif // COMMONSTRUCTS_H
