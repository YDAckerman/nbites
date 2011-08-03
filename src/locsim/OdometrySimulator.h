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
      * @param prevX The previous x position of the player.
      * @param prevY The previous y position of the player.
      * @param prevH The previous heading of the player.
      *
      * @return The simulated odometry measurement with noise.
      */
    Odometry estimateOdometry(Odometry &vec);

    float sampleNormalDistribution(float standardDeviation);
};

#endif // ODOMETRYSIMULATOR_H
