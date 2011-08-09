#ifndef VISIONSIMULATOR_H
#define VISIONSIMULATOR_H

#include "CommonStructs.h"
#include "FieldLandmark.h"
#include "Probability.h"

// Field of vision constant (in degrees!)
static const float BETA = 30.0f;

class VisionSimulator
{
public:
    VisionSimulator();
    ~VisionSimulator();

    void updateVision(int x,
                      int y,
                      int h);

    std::vector<CornerObservation> getCurCornerObs() const { return curCornerObs; }

    std::vector<PointObservation> getCurPointObs() const { return curPointObs; }

    void printVision();

private:
    std::vector<FieldLandmark> detVisLandmarks();

    bool isVisible(FieldLandmark landmark);

    void determineObservations(std::vector<FieldLandmark> landmarks);

    void clearSeen();

    //void detExtremes();

    std::vector<FieldLandmark> map;
    //FieldLandmark map[20];
    bool landmarkSeen[20];
    std::vector<CornerObservation> curCornerObs;
    std::vector<PointObservation> curPointObs;
    int x;
    int y;
    int h;
};

#endif // VISIONSIMULATOR_H
