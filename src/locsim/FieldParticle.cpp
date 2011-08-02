#include "FieldParticle.h"

FieldParticle::FieldParticle()
    : x(0), y(0), h(0), weight(0.0f)
{
}

FieldParticle::FieldParticle(int xPos, int yPos, int hPos, float w)
    : x(xPos), y(yPos), h(hPos), weight(w)
{
}

FieldParticle::~FieldParticle()
{
}

void FieldParticle::draw(QGraphicsScene *field)
{
    field->addEllipse(x, y, 10, 10, QPen(Qt::black), QBrush(Qt::black));

    field->addLine(x + 5,
                   y + 5,
                   (x + 5) + 10 * std::cos(h * TO_RADIANS),
                   (y + 5) + 10 * std::sin(h * TO_RADIANS));
}
