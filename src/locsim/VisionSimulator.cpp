#include "VisionSimulator.h"

VisionSimulator::VisionSimulator()
{
  map.push_back(FieldLandmark(LCORNER, 0, 0, 0));
  map.push_back(FieldLandmark(LCORNER, 0, 400, 90));
  map.push_back(FieldLandmark(LCORNER, 600, 0, -90));
  map.push_back(FieldLandmark(LCORNER, 600, 400, 180));
  map.push_back(FieldLandmark(LCORNER, 60, 90, -90));
  map.push_back(FieldLandmark(LCORNER, 60, 310, 180));
  map.push_back(FieldLandmark(LCORNER, 540, 90, 0));
  map.push_back(FieldLandmark(LCORNER, 540, 310, 90));

  map.push_back(FieldLandmark(TCORNER, 300, 0, -90));
  map.push_back(FieldLandmark(TCORNER, 300, 400, 90));
  map.push_back(FieldLandmark(TCORNER, 0, 90, 0));
  map.push_back(FieldLandmark(TCORNER, 0, 310, 0));
  map.push_back(FieldLandmark(TCORNER, 600, 90, 180));
  map.push_back(FieldLandmark(TCORNER, 600, 310, 180));

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
  /**
   * clear out all the old
   * observations
   */
  curCornerObs.clear();
  curPointObs.clear();
  
  // vector will hold visible landmarks
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
  /**
   * create components of unit vector in the 
   * direction of the robot's heading.
   */
  float i_u = std::cos(h);
  float j_u = std::sin(h);

  /**
   * create components of the robot->landmark
   * vector and determine its magnitude.
   */
  float i_rl = landmark.getX() - x;
  float j_rl = landmark.getY() - y;
  float mag = std::sqrt(i_rl*i_rl + j_rl*j_rl);

  
  /**
   * Dot product!
   */
  float dot = i_rl*i + j_rl*j;

  /**
   * Divide by the magnitude of the robot->
   * landmark vector (since the other is 
   * unit), and take the inverse cosine of the
   * quotient to get the angle between the 
   * vectors.
   */

  float angle = NBMath::safe_acos(dot/mag);

  /**
   * if the angle is <= BETA, then the landmark
   * is in the robots line of sight.
   */

  return BETA >= angle;
  
}
			
void
determineObservations(
	    std::vector<FieldLandmark> landmarks
		      )
{
  float dist;
  float bearing;
  int bGoalCounter = 0;
  int yGoalCounter = 0;
  for(int i= 0; i < landmarks.size() )
    {
      /**
       * determine the dist and bearing
       */
      dist  = std::sqrt( (landmark[i].getX() - x)*
			 (landmark[i].getX() - x) +
			 (landmark[i].getY() - y)*
			 (landmark[i].getY() - y) );
      /**
       * find the heading of the robot->landmark
       * vector and subtract it from the robot's
       * heading to determine bearing
       */
      bearing = h - NBMath::safe_acos( (landmark[i].getX() -
					x)/dist );

      int type = landmark[i].getType();
      if( type == BGP){
	++bGoalCounter;
      }else if(type == YGP){
	++yGoalCounter;
      }

      if( type < 4){
      }
    }
}
