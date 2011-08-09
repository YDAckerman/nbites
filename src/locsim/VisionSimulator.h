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

    /**
      * Determines whether or not a landmark is visible given the current
      * pose of the player.
      *
      * @param landmark The landmark in question.
      *
      * @return True if visible; otherwise, false.
      */
    bool isVisible(FieldLandmark landmark);

    void determineObservations(std::vector<FieldLandmark> landmarks);

    void clearSeen();

    /**
      * Determines whether or not a landmark is ambiguous based on the
      * stored list of landmarks that have been seen.
      *
      * @param landmark The landmark in question.
      *
      * @return True if ambiguous; otherwise, false.
      */
    bool isAmbiguous(FieldLandmark landmark);

    std::vector<FieldLandmark> map;
    bool landmarkSeen[20];
    std::vector<CornerObservation> curCornerObs;
    std::vector<PointObservation> curPointObs;
    int x;
    int y;
    int h;
};

#endif // VISIONSIMULATOR_H
