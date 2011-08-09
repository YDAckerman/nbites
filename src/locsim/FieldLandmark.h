#ifndef FIELDLANDMARK_H
#define FIELDLANDMARK_H

#include "CommonStructs.h"

/**
  * Note that IDs must range from 0 to 19, and identifies the unique
  * field landmark to which the object corresponds.
  */

class FieldLandmark
{
public:
    FieldLandmark(VisualLandmarkType type, int x, int y, int ID, int o = -1);
    FieldLandmark();
    ~FieldLandmark();

    int getX() const { return xPos; }
    int getY() const { return yPos; }
    int getO() const { return orientation; }
    int getID() const { return ID; }
    VisualLandmarkType getType() const { return landmarkType; }

    void setX(int x) { xPos = x; }
    void setY(int y) { yPos = y; }
    void setO(int o) { orientation = o; }
    void setID(int id) { ID = id; }
    void setType(VisualLandmarkType type) { landmarkType = type; }

protected:
    VisualLandmarkType landmarkType;
    int xPos;
    int yPos;
    int ID;
    int orientation;
};

#endif // FIELDLANDMARK_H
