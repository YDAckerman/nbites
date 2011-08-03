#ifndef FIELDLANDMARK_H
#define FIELDLANDMARK_H

#include "CommonStructs.h"

class FieldLandmark
{
public:
    FieldLandmark(VisualLandmarkType type, int x, int y);
    ~FieldLandmark();

    int getX() const { return xPos; }
    int getY() const { return yPos; }
    VisualLandmarkType getType() const { return landmarkType; }

    void setX(int x) { xPos = x; }
    void setY(int y) { yPos = y; }
    void setType(VisualLandmarkType type) { landmarkType = type; }

protected:
    VisualLandmarkType landmarkType;
    int xPos;
    int yPos;
};

#endif // FIELDLANDMARK_H
