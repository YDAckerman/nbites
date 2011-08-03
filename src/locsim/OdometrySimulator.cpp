#include "OdometrySimulator.h"

#include <iostream>

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
    std::cout << "True odometry: (" << vec.dx << ", " << vec.dy << ", "
              << vec.dtheta << ")." << std::endl;

    float x_n =  vec.dx  + sampleNormalDistribution(0.33*std::abs(vec.dx));
    float y_n =  vec.dy  + sampleNormalDistribution(0.33*std::abs(vec.dy));
    float theta_n =  vec.dtheta + sampleNormalDistribution(0.33*std::abs(vec.dtheta));

    std::cout << "Noisy odometry: (" << x_n << ", " << y_n << ", "
              << theta_n << ")." << std::endl;

    return Odometry(x_n, y_n, theta_n);
}

/**
  * Method to sample a value from a normal distribution with mean 0 and
  * variance standardDeviation^2. Appears also in AugmentedMCL.cpp, so
  * at some point we should consolidate everything into one Probabilistic
  * functions class. @todo
  */
float OdometrySimulator::sampleNormalDistribution(float standardDeviation)
{
    float sum = 0;
    for(int i = 0; i < 12; ++i)
    {
        // Generates a random value in the range [-b, b].
        float random = ((float)rand()) / (float)RAND_MAX;
        float range = 2*standardDeviation;

        sum += random*range - standardDeviation;
    }

    return 0.5*sum;
}
