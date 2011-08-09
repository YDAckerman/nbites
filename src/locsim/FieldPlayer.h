#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include <string>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPointer>
#include "CommonStructs.h"
#include "PlayerIndicator.h"
#include "OdometrySimulator.h"
#include "VisionSimulator.h"
#include "LocalizationSimulator.h"

class FieldPlayer
{
public:
    FieldPlayer(int x, int y, int theta, std::string name, int team, int player, QPointer<QGraphicsScene> field);
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

    void setTrueX(int x) { trueX = x; truePlayer->setX(x); }
    void setTrueY(int y) { trueY = y; truePlayer->setY(y); }
    void setTrueHeading(int theta) { trueHeading = theta; truePlayer->setAngle(theta); }

    int getEstimateX() const { return estimateX; }
    int getEstimateY() const { return estimateY; }
    int getEstimateHeading() const { return estimateHeading; }

    void setEstimateX(int x) { estimateX = x; estimatePlayer->setX(x); }
    void setEstimateY(int y) { estimateY = y; estimatePlayer->setY(y); }
    void setEstimateHeading(int theta) { estimateHeading = theta; estimatePlayer->setAngle(theta); }

    Odometry getWalkOdometry() const { return walkOdometry; }
    void setWalkOdometry(Odometry &odo) { walkOdometry = odo; }

    std::vector<FieldParticle *> getLocalizationParticles() const { return localization.getParticles(); }

    /**
      * Advances the player one frame forward in time. Updates the player
      * position (estimate and actual), grabs observations from the vision
      * simulator according to the current pose, and updates the localization
      * system using this information. Finally, particles and player positions
      * are rendered to the field.
      */
    void nextFrame();

    void movePlayer(Odometry &odo);

protected:
    OdometrySimulator odometry;
    VisionSimulator vision;
    LocalizationSimulator localization;

    std::string playerName;
    int teamNumber;
    int playerNumber;

    int trueX;
    int trueY;
    int trueHeading;

    PlayerIndicator *truePlayer;

    Odometry walkOdometry;

    int estimateX;
    int estimateY;
    int estimateHeading;

    PlayerIndicator *estimatePlayer;
};

#endif // FIELDPLAYER_H
