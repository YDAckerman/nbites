#include "OdometrySimulator.h"

OdometrySimulator::OdometrySimulator()
{
}

OdometrySimulator::~OdometrySimulator()
{
}


/**
  * Method to take a true odometry and return a noise
  * vector approximate to be used by the simulated robot.
  */

Odometry OdometrySimulator::estimateOdometry(Odometry &vec)
{
    float x_n =  vec.x  + sampleNormalDistribution(std::sqrt(vec.x));
    float y_n =  vec.y  + sampleNormalDistribution(std::sqrt(vec.y));
    float theta_n =  vec.theta + sampleNormalDistribution(std::sqrt(vec.theta))
    return Odometry(x_n, y_n, theta_n);
}
/**
  * Method to sample a value from a normal distribution with mean 0 and
  * variance standardDeviation^2. Appears also in AugmentedMCL.cpp, so
  * at some point we should consolidate everything into one Probabilistic
  * functions class. @todo
  */
float sampleNormalDistribution(float standardDeviation)
{
    float sum = 0;
    for(int i = 0; i < 12; ++i)
    {
        // Generates a random value in the range [-b, b].
        sum += rand() % 2*standardDeviation - standardDeviation;
    }

    return 0.5*sum;
}
