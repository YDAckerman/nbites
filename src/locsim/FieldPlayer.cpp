#include "FieldPlayer.h"

FieldPlayer::FieldPlayer(int x, int y, int theta, std::string name, int team, int player, QPointer<QGraphicsScene> field)
    : odometry(), vision(), localization(), trueX(x), trueY(y), trueHeading(theta),
      playerName(name), teamNumber(team), playerNumber(player)
{
    estimateX = 0;
    estimateY = 0;
    estimateHeading = 0;

    truePlayer = new PlayerIndicator(trueX, trueY, trueHeading, 20);
    estimatePlayer = new PlayerIndicator(0, 0, 0, 30);

    field->addItem(truePlayer);
    field->addItem(estimatePlayer);

    std::vector<FieldParticle *> particles = getLocalizationParticles();
    for(int i = 0; i < particles.size(); ++i)
    {
        field->addItem(particles[i]);
    }
}

FieldPlayer::~FieldPlayer()
{

}

void FieldPlayer::nextFrame()
{
    // First, update the real position.
    movePlayer(walkOdometry);

    // Calculate simulated odometry measurements.
    Odometry odo = odometry.estimateOdometry(walkOdometry);

    // Update the vision system and form lists of observed landmarks to feed
    // to the localization system.
    // ...
    vision.updateVision(trueX, trueY, trueHeading);
}

void FieldPlayer::movePlayer(Odometry &odo)
{
    // Advance the player one frame according to the provided odometry.
    trueX += odo.dx;
    trueY += odo.dy;
    trueHeading += odo.dtheta;

    truePlayer->setX(trueX);
    truePlayer->setY(trueY);
    truePlayer->setAngle(trueHeading);
}
