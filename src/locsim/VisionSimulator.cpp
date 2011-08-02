#include "VisionSimulator.h"

VisionSimulator::VisionSimulator()
{
  map.push_back(FieldLandmark(LCORNER, 0, 0));
  map.push_back(FieldLandmark(LCORNER, 0, 400));
  map.push_back(FieldLandmark(LCORNER, 600, 0));
  map.push_back(FieldLandmark(LCORNER, 600, 400));
  map.push_back(FieldLandmark(LCORNER, 60, 90));
  map.push_back(FieldLandmark(LCORNER, 60, 310));
  map.push_back(FieldLandmark(LCORNER, 540, 90));
  map.push_back(FieldLandmark(LCORNER, 540, 310));

  map.push_back(FieldLandmark(TCORNER, 300, 0));
  map.push_back(FieldLandmark(TCORNER, 300, 400));
  map.push_back(FieldLandmark(TCORNER, 0, 90));
  map.push_back(FieldLandmark(TCORNER, 0, 310));
  map.push_back(FieldLandmark(TCORNER, 600, 90));
  map.push_back(FieldLandmark(TCORNER, 600, 310));

  map.push_back(FieldLandmark(BGP, 0, 130));
  map.push_back(FieldLandmark(BGP, 0, 270));

  map.push_back(FieldLandmark(YGP, 600, 130));
  map.push_back(FieldLandmark(YGP, 600, 270));

  map.push_back(FieldLandmark(CROSS, 180, 200));
  map.push_back(FieldLandmark(CROSS, 420, 200));
}

VisionSimulator::~VisionSimulator()
{}

void 
VisionSimulator::updateVisionSim(
			     int x,
			     int y,
			     int h)
{
  
  std::vector<FieldLandmark> visLandmarks;

  /**
   * update position
   */
  this.x = x;
  this.y = y;
  this.h = h;
  
  /**
   * determine visible landmarks
   */
  visLandmarks = detVisLandmarks();
  
  /**
   * update observation vectors
   */
  determineObservations(visLandmarks);
  
}

std::vector<FieldLandmark> 
VisionSimulator::detVisLandmarks()
{
  std::vector<FieldLandmark> visibleLandmarks;

  for(int i=0; i < map.size(); ++i)
    {
      if(isVisible(map[i]))
	{
	  visibleLandmarks.push_back(map[i]);
	}
    }

  return visibleLandmarks;
}

bool
VisionSimulator::isVisible(
			   FieldLandmark landmark
			   )
{
  
}
			
