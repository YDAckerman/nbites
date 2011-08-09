#include "VisionSimulator.h"

#include <iostream>

VisionSimulator::VisionSimulator()
    : curCornerObs(), curPointObs(), x(0), y(0), h(0)
{
    map.push_back(FieldLandmark(LCORNER, 0, 0, 0));
    map.push_back(FieldLandmark(LCORNER, 0, 400, 1));
    map.push_back(FieldLandmark(LCORNER, 600, 0, 2));
    map.push_back(FieldLandmark(LCORNER, 600, 400, 3));
    map.push_back(FieldLandmark(LCORNER, 60, 90, 4));
    map.push_back(FieldLandmark(LCORNER, 60, 310, 5));
    map.push_back(FieldLandmark(LCORNER, 540, 90, 6));
    map.push_back(FieldLandmark(LCORNER, 540, 310, 7));

    map.push_back(FieldLandmark(TCORNER, 300, 0, 8));
    map.push_back(FieldLandmark(TCORNER, 300, 400, 9));
    map.push_back(FieldLandmark(TCORNER, 0, 90, 10));
    map.push_back(FieldLandmark(TCORNER, 0, 310, 11));
    map.push_back(FieldLandmark(TCORNER, 600, 90, 12));
    map.push_back(FieldLandmark(TCORNER, 600, 310, 13));

    map.push_back(FieldLandmark(BGP, 0, 130, 14));
    map.push_back(FieldLandmark(BGP, 0, 270, 15));

    map.push_back(FieldLandmark(YGP, 600, 130, 16));
    map.push_back(FieldLandmark(YGP, 600, 270, 17));

    map.push_back(FieldLandmark(CROSS, 180, 200, 18));
    map.push_back(FieldLandmark(CROSS, 420, 200, 19));

    /*
    map[0] = FieldLandmark(LCORNER, 0, 0, 0);
    map[1] = FieldLandmark(LCORNER, 0, 400, 1);
    map[2] = FieldLandmark(LCORNER, 600, 0, 2);
    map[3] = FieldLandmark(LCORNER, 600, 400, 3);
    map[4] = FieldLandmark(LCORNER, 60, 90, 4);
    map[5] = FieldLandmark(LCORNER, 60, 310, 5);
    map[6] = FieldLandmark(LCORNER, 540, 90, 6);
    map[7] = FieldLandmark(LCORNER, 540, 310, 7);

    map[8] = FieldLandmark(TCORNER, 0, 90, 8);
    map[9] = FieldLandmark(TCORNER, 0, 310, 9);
    map[10] = FieldLandmark(TCORNER, 600, 90, 10);
    map[11] = FieldLandmark(TCORNER, 600, 310, 11);
    map[12] = FieldLandmark(TCORNER, 300, 0, 12);
    map[13] = FieldLandmark(TCORNER, 300, 400, 13);

    map[14] = FieldLandmark(BGP, 0, 130, 14);
    map[15] = FieldLandmark(BGP, 0, 270, 15);

    map[16] = FieldLandmark(YGP, 600, 130, 16);
    map[17] = FieldLandmark(YGP, 600, 270, 17);

    map[18] = FieldLandmark(CROSS, 180, 200, 18);
    map[19] = FieldLandmark(CROSS, 420, 200, 19);
    */

    // This is a "checklist" of what the player has seen, and is
    // used to determine whether an observation is ambiguous based
    // on correlations between true valued idices of the array.
    landmarkSeen[0] = false;     // Upper left LCORNER
    landmarkSeen[1] = false;     // Lower left LCORNER
    landmarkSeen[2] = false;     // Upper right LCORNER
    landmarkSeen[3] = false;     // Lower right LCORNER
    landmarkSeen[4] = false;     // Blue goal upper LCORNER
    landmarkSeen[5] = false;     // Blue goal lower LCORNER
    landmarkSeen[6] = false;     // Yellow goal upper LCORNER
    landmarkSeen[7] = false;     // Yellow goal lower LCORNER
    landmarkSeen[8] = false;     // Blue goal upper TCORNER
    landmarkSeen[9] = false;     // Blue goal lower TCORNER
    landmarkSeen[10] = false;    // Yellow goal upper TCORNER
    landmarkSeen[11] = false;    // Yellow goal lower TCORNER
    landmarkSeen[12] = false;    // Upper midfield TCORNER
    landmarkSeen[13] = false;    // Lower midfield TCORNER
    landmarkSeen[14] = false;    // Upper BGP
    landmarkSeen[15] = false;    // Lower BGP
    landmarkSeen[16] = false;    // Upper YGP
    landmarkSeen[17] = false;    // Lower YGP
    landmarkSeen[18] = false;    // Left CROSS
    landmarkSeen[19] = false;    // Right CROSS
}

VisionSimulator::~VisionSimulator()
{
}

void VisionSimulator::printVision()
{
    std::cout << "At pose (" << x << ", " << y << ", " << h
              << ")." << std::endl;
    std::cout << "Corner observations: " << std::endl;
    for(int i = 0; i < curCornerObs.size(); ++i)
    {
        switch(curCornerObs[i].getType())
        {
        case YGP:
            std::cout << "YGP ";
            break;
        case BGP:
            std::cout << "BGP ";
            break;
        case CROSS:
            std::cout << "CROSS ";
            break;
        case LCORNER:
            std::cout << "LCORNER ";
            break;
        case TCORNER:
            std::cout << "TCORNER ";
            break;
        default:
            std::cout << "UNKNOWN ";
            break;
        }
        std::cout << "Ambiguous? ";
        std::cout << curCornerObs[i].isAmbiguous() ? "YES " : "NO ";
        std::cout << "Distance: " << curCornerObs[i].getVisDistance();
        std::cout << std::endl;
    }
}

void VisionSimulator::updateVision(int x,
                                   int y,
                                   int h)
{
    curCornerObs.clear();
    curPointObs.clear();
    clearSeen();

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

    for(int i = 0; i < 20; ++i)
    {
        // If the landmark is visible, add it to the list.
        if(isVisible(map[i]))
	{
            visibleLandmarks.push_back(map[i]);
            // Indicate that this unique landmark as been seen.
            landmarkSeen[i] = true;
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
    return BETA >= angle*TO_DEG;
}

void VisionSimulator::determineObservations(std::vector<FieldLandmark> landmarks)
{
    float dist;
    float bearing;
    for(int i= 0; i < landmarks.size(); ++i)
    {
        // @todo IMPORTANT give these measurements noise!!
        // (probably should use Probability::addGaussianNoise())

        /*
         * determine the dist and bearing
         */
        dist  = std::sqrt( (landmarks[i].getX() - x) *
                           (landmarks[i].getX() - x) +
                           (landmarks[i].getY() - y) *
                           (landmarks[i].getY() - y) );
        /*
         * find the heading of the robot->landmark
         * vector and subtract it from the robot's
         * heading to determine bearing
         */
        bearing = h - NBMath::safe_acos( (landmarks[i].getX() -
                                          x)/dist );

        // Determine whether to create a PointObservation object or a
        // CornerObservation object.
        bool pointObs = false;
        if(landmarks[i].getType() == YGP ||
           landmarks[i].getType() == BGP ||
           landmarks[i].getType() == CROSS)
                pointObs = true;

        // Use correlations between seen landmarks to determine
        // ambiguity.
        if(isAmbiguous(landmarks[i]))
        {
            // Ambiguous, so make a new observation, where possibilities include
            // all landmarks of the same type.
            if(pointObs)
            {
                PointObservation obs(dist, bearing, /* @todo */0.0f, /* @todo */0.0f,
                                     landmarks[i].getType());
            }
            else
            {
                CornerObservation obs(dist, bearing, /* @todo */0.0f, /* @todo */0.0f,
                                      /* @todo */0.0f, /* @todo */0.0f);
            }
        }
        else
        {
            // Not ambiguous, so no need to add all possible landmarks of the
            // same type.
            // @todo
        }
    }
}

void VisionSimulator::clearSeen()
{
    for(int i = 0; i < 20; ++i)
        landmarkSeen[i] = false;
}

bool VisionSimulator::isAmbiguous(FieldLandmark landmark)
{
    // @todo
    return false;
}
