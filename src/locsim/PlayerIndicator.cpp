#include "PlayerIndicator.h"

PlayerIndicator::PlayerIndicator(int x, int y, int theta, int side)
    : QGraphicsItem(), xPos(x), yPos(y), angle(theta), sideLength(side)
{
}

PlayerIndicator::~PlayerIndicator()
{
}

void PlayerIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(xPos,
                         yPos,
                         sideLength,
                         sideLength);

    painter->setBrush(Qt::black);
    painter->drawLine(xPos + sideLength/2,
                      yPos + sideLength/2,
                      (xPos + sideLength/2) + sideLength/2 * std::cos(angle * TO_RADIANS),
                      (yPos + sideLength/2) + sideLength/2 * std::sin(angle * TO_RADIANS));
}
