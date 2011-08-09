#ifndef ODOMETRYSIMULATOR_H
#define ODOMETRYSIMULATOR_H

#include "CommonStructs.h"
#include "Probability.h"

class OdometrySimulator
{
public:
    OdometrySimulator();
    ~OdometrySimulator();

    /**
      * Simulates a noisy odometry measurement given an exact
      * measurement over one frame.
      *
      * @param odo The odometry of the player.
      * @param prevX The previous x position of the player.
      * @param prevY The previous y position of the player.
      * @param prevH The previous heading of the player.
      *
      * @return The simulated odometry measurement with noise.
      */
    Odometry estimateOdometry(Odometry &odo);
};

#endif // ODOMETRYSIMULATOR_H
