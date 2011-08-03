#ifndef LOCALIZATIONSIMULATOR_H
#define LOCALIZATIONSIMULATOR_H

#include "../../man/noggin/LocSystem.h"
#include "AugmentedMCL.h"
#include "CommonStructs.h"
#include "FieldParticle.h"
#include <QGraphicsScene>
#include <QPointer>
#include <vector>

class LocalizationSimulator
{
public:
    LocalizationSimulator();
    ~LocalizationSimulator();

    /**
      * Updates the localization based on the provided point, corner,
      * and odometry measurements.
      *
      * @param pointObs The point observations.
      * @param cornerObs The corner observations.
      * @param odometry The odometry observations.
      */
    void updateLocalization(std::vector<PointObservation> &pointObs,
                            std::vector<CornerObservation> &cornerObs,
                            Odometry &odometry);

    std::vector<FieldParticle *> getParticles() const { return particles; }

    int getXEst() const { return xEst; }
    int getYEst() const { return yEst; }
    int getHEst() const { return hEst; }

    int getXUncert() const { return xUncert; }
    int getYUncert() const { return yUncert; }
    int getHUncert() const { return hUncert; }

private:
    void clearParticles();

    LocSystem *localizationSystem;

    int xEst;
    int yEst;
    int hEst;

    int xUncert;
    int yUncert;
    int hUncert;

    std::vector<FieldParticle *> particles;
};

#endif // LOCALIZATIONSIMULATOR_H
