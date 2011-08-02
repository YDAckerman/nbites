#include "LocalizationSimulator.h"

LocalizationSimulator::LocalizationSimulator()
{
    localizationSystem = new AugmentedMCL(100, 600, 400);

    // Add all the particles.
    std::vector<Particle<PoseEst> > p = ((AugmentedMCL *)localizationSystem)->getParticleSet();
}

LocalizationSimulator::~LocalizationSimulator()
{
    delete localizationSystem;
    localizationSystem = 0;
}

void LocalizationSimulator::updateLocalization(std::vector<PointObservation> &pointObs,
                                               std::vector<CornerObservation> &cornerObs,
                                               Odometry &odometry)
{
    MotionModel motion(odometry.dx, odometry.dy, odometry.dtheta);

    // Update localization with new odometry, point & corner observations.
    localizationSystem->updateLocalization(motion,
                                           pointObs,
                                           cornerObs);

    // Update pose estimates.
    xEst = localizationSystem->getCurrentEstimate().x;
    yEst = localizationSystem->getCurrentEstimate().y;
    hEst = localizationSystem->getCurrentEstimate().h;

    // Update pose estimate uncertainties.
    xUncert = localizationSystem->getCurrentUncertainty().x;
    yUncert = localizationSystem->getCurrentUncertainty().y;
    hUncert = localizationSystem->getCurrentUncertainty().h;

    // Update the particles.
}
