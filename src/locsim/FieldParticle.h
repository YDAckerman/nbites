#ifndef FIELDPARTICLE_H
#define FIELDPARTICLE_H

#include <QGraphicsScene>
#include "CommonStructs.h"

class FieldParticle
{
public:
    FieldParticle();
    FieldParticle(int xPos, int yPos, int hPos, float w);
    ~FieldParticle();

    int getX() const { return x; }
    int getY() const { return y; }
    int getH() const { return h; }
    float getWeight() const { return weight; }

    void setX(int xPos) { x = xPos; }
    void setY(int yPos) { y = yPos; }
    void setH(int hPos) { h = hPos; }
    void setWeight(float w) { weight = w; }

    void draw(QGraphicsScene *field);

private:
    int x;
    int y;
    int h;
    float weight;
};

#endif // FIELDPARTICLE_H
