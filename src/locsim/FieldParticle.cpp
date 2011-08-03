#include "FieldParticle.h"

#include <iostream>

FieldParticle::FieldParticle()
    : x(0), y(0), h(0), weight(0.0f)
{
}

FieldParticle::FieldParticle(int xPos, int yPos, int hPos, float w)
    : x(xPos), y(yPos), h(hPos), weight(w)
{
    std::cout << "Particle created (" << x << ", " << y << ", "
              << h << ") with weight " << weight << "." << std::endl;
}

FieldParticle::~FieldParticle()
{
}

void FieldParticle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(x, y, 10, 10);

    painter->setBrush(Qt::black);
    painter->drawLine(x + 5,
                     y + 5,
                     (x + 5) + 10 * std::cos(h * TO_RADIANS),
                     (y + 5) + 10 * std::sin(h * TO_RADIANS));
}
