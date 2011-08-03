#include "FieldLandmark.h"

FieldLandmark::FieldLandmark(VisualLandmarkType type, int x, int y)
    : landmarkType(type), xPos(x), yPos(y)
{
}

FieldLandmark::~FieldLandmark()
{
}
