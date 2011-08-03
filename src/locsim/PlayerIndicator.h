#ifndef PLAYERINDICATOR_H
#define PLAYERINDICATOR_H

#include <QGraphicsItem>
#include <QPainter>
#include "CommonStructs.h"

class PlayerIndicator : public QGraphicsItem
{
public:
    PlayerIndicator(int x, int y, int theta, int side);
    ~PlayerIndicator();

    QRectF boundingRect() const { return QRectF(xPos, yPos, sideLength, sideLength); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getX() const { return xPos; }
    int getY() const { return yPos; }
    int getAngle() const { return angle; }

    void setX(int x) { xPos = x; }
    void setY(int y) { yPos = y; }
    void setAngle(int theta) { angle = theta; }

private:
    int xPos;
    int yPos;
    int angle;
    int sideLength;
};

#endif // PLAYERINDICATOR_H
