#include "LocalizationSimulator.h"

//#include <iostream>

LocalizationSimulator::LocalizationSimulator()
{
    localizationSystem = new AugmentedMCL(100, 600, 400);

    // Add all the particles.
    std::vector<Particle<PoseEst> > p = ((AugmentedMCL *)localizationSystem)->getParticleSet();

    //std::cout << "Counted " << p.size() << " particles." << std::endl;

    for(int i = 0; i < p.size(); ++i)
    {
        particles.push_back(new FieldParticle(p[i].getState().x,
                                              p[i].getState().y,
                                              p[i].getState().h*TO_DEGREES,
                                              p[i].getWeight()));
    }
}

LocalizationSimulator::~LocalizationSimulator()
{
    delete localizationSystem;
    localizationSystem = 0;
    clearParticles();
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
    std::vector<Particle<PoseEst> > p = ((AugmentedMCL *)localizationSystem)->getParticleSet();

    //std::cout << "Counted " << p.size() << " particles." << std::endl;

    clearParticles();

    for(int i = 0; i < p.size(); ++i)
    {
        particles.push_back(new FieldParticle(p[i].getState().x,
                                              p[i].getState().y,
                                              p[i].getState().h*TO_DEGREES,
                                              p[i].getWeight()));
    }
}

void LocalizationSimulator::clearParticles()
{
    for(int i = 0; i < particles.size(); ++i)
    {
        if(particles[i] != 0)
        {
            // Pointer exists, delete memory and remove from vector.
            delete particles[i];
            particles[i] = 0;
        }
    }
    particles.clear();
}
