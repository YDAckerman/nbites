#ifndef LOCALIZATIONSIMULATOR_H
#define LOCALIZATIONSIMULATOR_H

#include "../../man/noggin/LocSystem.h"
#include "AugmentedMCL.h"
#include <vector>

class LocalizationSimulator
{
public:
    LocalizationSimulator();
    ~LocalizationSimulator();

    void updateLocalization(std::vector<PointObservation> pointObs,
                            std::vector<CornerObservation> cornerObs,
                            Odometry &odometry);

    int getXEst() const { return xEst; }
    int getYEst() const { return yEst; }
    int getHEst() const { return hEst; }

    int getXUncert() const { return xUncert; }
    int getYUncert() const { return yUncert; }
    int getHUncert() const { return hUncert; }

private:
    LocSystem *localizationSystem;

    int xEst;
    int yEst;
    int hEst;

    int xUncert;
    int yUncert;
    int hUncert;
};

#endif // LOCALIZATIONSIMULATOR_H
