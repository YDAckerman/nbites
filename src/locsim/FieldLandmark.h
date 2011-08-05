#ifndef FIELDLANDMARK_H
#define FIELDLANDMARK_H

#include "CommonStructs.h"

class FieldLandmark
{
public:
  FieldLandmark(VisualLandmarkType type, int x, int y, int orientation = -1);
    ~FieldLandmark();

    int getX() const { return xPos; }
    int getY() const { return yPos; }
    int getO() const { return orientation; }
    VisualLandmarkType getType() const { return landmarkType; }

    void setX(int x) { xPos = x; }
    void setY(int y) { yPos = y; }
    void setType(VisualLandmarkType type) { landmarkType = type; }

protected:
    VisualLandmarkType landmarkType;
    int xPos;
    int yPos;
    int orientation;
};

#endif // FIELDLANDMARK_H
