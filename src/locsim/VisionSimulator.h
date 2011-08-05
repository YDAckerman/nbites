#ifndef VISIONSIMULATOR_H
#define VISIONSIMULATOR_H

#include "CommonStructs.h"
#include "FieldLandmark.h"

static const float BETA = 30.0f; /*<degrees!>*/ 

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

private:
    std::vector<FieldLandmark> detVisLandmarks();

    bool isVisible(FieldLandmark landmark);

    void determineObservations(std::vector<FieldLandmark> landmarks);

    template <class Observation>
    Observation addNoise(Observation obs);

    void detExtremes();

    std::vector<FieldLandmark> map;
    std::vector<CornerObservation> curCornerObs;
    std::vector<PointObservation> curPointObs;
    int x;
    int y;
    int h;

    /**
     * these house the extremes of our field of
     * vision. They will be used to determine what
     * landmarks we can see
     */
    int extreme_x1;
    int extreme_x2;
    int extreme_y1;
    int extreme_y2;
};

#endif // VISIONSIMULATOR_H
