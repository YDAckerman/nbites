#ifndef ODOMETRYSIMULATOR_H
#define ODOMETRYSIMULATOR_H

#include "CommonStructs.h"

class OdometrySimulator
{
public:
    OdometrySimulator();
    ~OdometrySimulator();

    /**
      * Simulates an odometry measurement given a walk vector
      * over one frame.
      *
      * @param vec The walk vector of the player.
      *
      * @return The simulated odometry measurement with noise.
      */
    Odometry estimateOdometry(WalkVector &vec);
};

#endif // ODOMETRYSIMULATOR_H
