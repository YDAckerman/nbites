#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include <string>
#include <QGraphicsScene>
#include "CommonStructs.h"
#include "OdometrySimulator.h"
//#include "VisionSimulator.h"
#include "LocalizationSimulator.h"

class FieldPlayer
{
public:
    FieldPlayer(int x, int y, int theta, std::string name, int team, int player);
    ~FieldPlayer();

    std::string getName() const { return playerName; }
    int getTeamNumber() const { return teamNumber; }
    int getPlayerNumber() const { return playerNumber; }

    void setName(std::string name) { playerName = name; }
    void setTeamNumber(int team) { teamNumber = team; }
    void setPlayerNumber(int player) { playerNumber = player; }

    int getTrueX() const { return trueX; }
    int getTrueY() const { return trueY; }
    int getTrueHeading() const { return trueHeading; }

    void setTrueX(int x) { trueX = x; }
    void setTrueY(int y) { trueY = y; }
    void setTrueHeading(int theta) { trueHeading = theta; }

    int getEstimateX() const { return estimateX; }
    int getEstimateY() const { return estimateY; }
    int getEstimateHeading() const { return estimateHeading; }

    void setEstimateX(int x) { estimateX = x; }
    void setEstimateY(int y) { estimateY = y; }
    void setEstimateHeading(int theta) { estimateHeading = theta; }

    WalkVector getWalkVector() const { return trueWalkVector; }
    void setWalkVector(WalkVector &vec) { trueWalkVector = vec; }

    /**
      * Advances the player one frame forward in time. Updates the player
      * position (estimate and actual), grabs observations from the vision
      * simulator according to the current pose, and updates the localization
      * system using this information. Finally, particles and player positions
      * are rendered to the field.
      */
    void nextFrame();

    void movePlayer(WalkVector &vec);
    void movePlayer(Odometry &odo);

    void draw(QGraphicsScene *field);

    /**
      * Draws the estimated player as a circle with a radius larger
      * than that of the true player.
      *
      * @param field The graphics scene to draw to.
      */
    void drawEstimatedPlayer(QGraphicsScene *field);

    /**
      * Draws the true player as a circle with a radius smaller than
      * that of the estimated player.
      *
      * @param field The graphics scene to draw to.
      */
    void drawTruePlayer(QGraphicsScene *field);

protected:
    std::string playerName;
    int teamNumber;
    int playerNumber;

    int trueX;
    int trueY;
    int trueHeading;

    WalkVector trueWalkVector;

    int estimateX;
    int estimateY;
    int estimateHeading;

    OdometrySimulator odometry;
    //VisionSimulator vision;
    LocalizationSimulator localization;

};

#endif // FIELDPLAYER_H
