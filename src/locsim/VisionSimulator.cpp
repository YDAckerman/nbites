#include "VisionSimulator.h"

VisionSimulator::VisionSimulator()
{
    map.push_back(FieldLandmark(LCORNER, 0, 0));
    map.push_back(FieldLandmark(LCORNER, 0, 400));
    map.push_back(FieldLandmark(LCORNER, 600, 0));
    map.push_back(FieldLandmark(LCORNER, 600, 400));
    map.push_back(FieldLandmark(LCORNER, 60, 90));
    map.push_back(FieldLandmark(LCORNER, 60, 310));
    map.push_back(FieldLandmark(LCORNER, 540, 90));
    map.push_back(FieldLandmark(LCORNER, 540, 310));

    map.push_back(FieldLandmark(TCORNER, 300, 0));
    map.push_back(FieldLandmark(TCORNER, 300, 400));
    map.push_back(FieldLandmark(TCORNER, 0, 90));
    map.push_back(FieldLandmark(TCORNER, 0, 310));
    map.push_back(FieldLandmark(TCORNER, 600, 90));
    map.push_back(FieldLandmark(TCORNER, 600, 310));

    map.push_back(FieldLandmark(BGP, 0, 130));
    map.push_back(FieldLandmark(BGP, 0, 270));

    map.push_back(FieldLandmark(YGP, 600, 130));
    map.push_back(FieldLandmark(YGP, 600, 270));

    map.push_back(FieldLandmark(CROSS, 180, 200));
    map.push_back(FieldLandmark(CROSS, 420, 200));
}

VisionSimulator::~VisionSimulator()
{
}

void VisionSimulator::updateVision(int x,
                                   int y,
                                   int h)
{
    std::vector<FieldLandmark> visLandmarks;

    // update position
    this->x = x;
    this->y = y;
    this->h = h;

    // determine visible landmarks
    visLandmarks = detVisLandmarks();

    // update observation vectors
    determineObservations(visLandmarks);
}

std::vector<FieldLandmark> VisionSimulator::detVisLandmarks()
{
    std::vector<FieldLandmark> visibleLandmarks;

    for(int i=0; i < map.size(); ++i)
    {
        if(isVisible(map[i]))
	{
            visibleLandmarks.push_back(map[i]);
	}
    }

    return visibleLandmarks;
}

bool VisionSimulator::isVisible(FieldLandmark landmark)
{
    /**
     * create components of unit vector in the
     * direction of the robot's heading.
     */
    float i_u = std::cos(h);
    float j_u = std::sin(h);

    /**
      * create components of the robot->landmark
      * vector and determine its magnitude.
      */
    float i_rl = landmark.getX() - x;
    float j_rl = landmark.getY() - y;
    float mag = std::sqrt(i_rl*i_rl + j_rl*j_rl);

    /**
      * Dot product!
      */
    float dot = i_rl*i_u + j_rl*j_u;

    /**
      * Divide by the magnitude of the robot->
      * landmark vector (since the other is
      * unit), and take the inverse cosine of the
      * quotient to get the angle between the
      * vectors.
      */
    float angle = NBMath::safe_acos(dot/mag);

    /**
     * if the angle is <= BETA, then the landmark
     * is in the robots line of sight.
     */
    return BETA >= angle;
}

void VisionSimulator::determineObservations(std::vector<FieldLandmark> landmarks)
{

}
