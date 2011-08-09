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
Odometry OdometrySimulator::estimateOdometry(Odometry &odo)
{
    std::cout << "True odometry: (" << odo.dx << ", " << odo.dy << ", "
              << odo.dtheta << ")." << std::endl;

    // Add Gaussian noise to the odometry measurement.
    float x_n =  odo.dx  + Probability::sampleNormalDistribution(0.33*std::abs(odo.dx));
    float y_n =  odo.dy  + Probability::sampleNormalDistribution(0.33*std::abs(odo.dy));
    float theta_n =  odo.dtheta + Probability::sampleNormalDistribution(0.33*std::abs(odo.dtheta));

    std::cout << "Noisy odometry: (" << x_n << ", " << y_n << ", "
              << theta_n << ")." << std::endl;

    return Odometry(x_n, y_n, theta_n);
}
