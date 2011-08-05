#ifndef VISIONSIMULATOR_H
#define VISIONSIMULATOR_H

#include "CommonStructs.h"
#include "FieldLandmark.h"

static const float BETA = 30.0f; /*<degrees!>*/ 

class VisionSimulator
{

 public:
  VisionSimulator();
  ~VisionSimulator();

  void updateVisionSim(
			  int x,
			  int y,
			  int h
		       );

  std::vector<CornerObservation> 
    getCurCornerObs() const {
    return curCornerObs;
  }

  std::vector<PointObservation> 
    getCurPointObs() const {
    return curPointObs;
  }


 private:

  std::vector<FieldLandmark> 
    detVisLandmarks();
  
  bool isVisible(
	FieldLandmark landmark
		 );

  void determineObservations(
    std::vector<FieldLandmark> landmarks
			     );

  template <class Observation>
    Observation addNoise( 
		     Observation obs
			  );

  
  

  std::vector<FieldLandmark> map;
  std::vector<CornerObservation>
    curCornerObs;
  std::vector<PointObservation>
    curPointObs;
  int x;
  int y;
  int h;
  
};
