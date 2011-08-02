#ifndef FIELDLANDMARK_H
#define FIELDLANDMARK_H

#include "CommonStructs.h"

class FieldLandmark
{
public:
    FieldLandmark(VisualLandmarkType type, int x, int y);
    ~FieldLandmark();

protected:
    int xPos;
    int yPos;
    VisualLandmarkType landmarkType;
};

#endif // FIELDLANDMARK_H
