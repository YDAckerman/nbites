#include "LocalizationSimulator.h"

LocalizationSimulator::LocalizationSimulator()
{
    localizationSystem = new AugmentedMCL(100, 600, 400);
}

LocalizationSimulator::~LocalizationSimulator()
{
    delete localizationSystem;
    localizationSystem = 0;
}
