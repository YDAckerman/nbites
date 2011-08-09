#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <cstdlib>

namespace Probability
{
    /**
      * Method to sample a value from a normal distribution with mean 0 and
      * variance standardDeviation^2.
      */
    static float sampleNormalDistribution(float standardDeviation)
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

    /**
     * Adds Gaussian noise to the given quantity.
     */
    static float addGaussianNoise(float value, float standardDeviation)
    {
        return value + sampleNormalDistribution(standardDeviation);
    }
};

#endif // PROBABILITY_H
