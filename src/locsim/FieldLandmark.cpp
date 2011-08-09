#include "FieldLandmark.h"

FieldLandmark::FieldLandmark(VisualLandmarkType type, int x, int y, int id, int o)
    : landmarkType(type), xPos(x), yPos(y), ID(id), orientation(o)
{
}

FieldLandmark::FieldLandmark()
    : landmarkType(CROSS), xPos(0), yPos(0), ID(0), orientation(-1)
{
}

FieldLandmark::~FieldLandmark()
{
}
