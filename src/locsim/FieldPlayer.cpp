#include "FieldPlayer.h"

FieldPlayer::FieldPlayer(int x, int y, int theta, std::string name, int team, int player)
    : trueX(x), trueY(y), trueHeading(theta), playerName(name), teamNumber(team), playerNumber(player)
{
    estimateX = 0;
    estimateY = 0;
    estimateHeading = 0;
}

FieldPlayer::~FieldPlayer()
{
}

void FieldPlayer::movePlayer(WalkVector &vec)
{
    // @todo
}

void FieldPlayer::movePlayer(Odometry &odo)
{
    // @todo
}

void FieldPlayer::draw(QGraphicsScene *field)
{
    drawEstimatedPlayer(field);

    drawTruePlayer(field);
}

void FieldPlayer::drawEstimatedPlayer(QGraphicsScene *field)
{
    field->addEllipse(estimateX,
                      estimateY,
                      30,
                      30,
                      QPen(Qt::black),
                      QBrush(Qt::white));

    field->addLine(estimateX + 15,
                   estimateY + 15,
                   (estimateX + 15) + 15 * std::cos(estimateHeading * TO_RADIANS),
                   (estimateY + 15) + 15 * std::sin(estimateHeading * TO_RADIANS));
}

void FieldPlayer::drawTruePlayer(QGraphicsScene *field)
{
    field->addEllipse(trueX,
                      trueY,
                      20,
                      20,
                      QPen(Qt::black),
                      QBrush(Qt::white));

    field->addLine(trueX + 10,
                   trueY + 10,
                   (trueX + 10) + 10 * std::cos(trueHeading * TO_RADIANS),
                   (trueY + 10) + 10 * std::sin(trueHeading * TO_RADIANS));
}
