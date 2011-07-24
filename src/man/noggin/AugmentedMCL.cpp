#include "AugmentedMCL.h"

AugmentedMCL::AugmentedMCL(int particles, int width, int height)
    : ParticleFilter(particles), fieldWidth(width), fieldHeight(height), lastOdo(0, 0, 0)
{
    // Randomly (and uniformly?) distribute M particles over the entire
    // pose space initially.
    srand(time(0));
    for(int i = 0; i < M; ++i)
    {
	PoseEst randomPose;
	randomPose.x = (rand() % fieldWidth)*1.0f;
	randomPose.y = (rand() % fieldHeight)*1.0f;
	bool negative = (bool)(rand() % 2);
	if(negative)
	    randomPose.h = (-(rand() % 91)*1.0f)*TO_RAD;
	else
	    randomPose.h = ((rand() % 91)*1.0f)*TO_RAD;

	X_t.push_back(randomPose);
    }
}

AugmentedMCL::~AugmentedMCL()
{ }

void AugmentedMCL::updateLocalization(const MotionModel& u_t,
				      const std::vector<PointObservation>& pt_z,
				      const std::vector<CornerObservation>& c_z)
{
    // @todo
    lastPointObservations = pt_z;
    lastCornerObservations = c_z;
}

void AugmentedMCL::reset()
{
    // @todo
    /*
      resetLocTo(INIT_X_LOC, INIT_Y_LOC, INIT_H_LOC);
     */
}

void AugmentedMCL::blueGoalieReset()
{
    // @todo
}

void AugmentedMCL::redGoalieReset()
{
    // @todo
}

void AugmentedMCL::resetLocTo(float x, float y, float h)
{
    currPoseEstimate.x = x;
    currPoseEstimate.y = y;
    currPoseEstimate.h = h;

    // @todo set some sort of initial uncertainty.
    /*
      currPoseUncertainty.x = INITIAL_UNCERT_X;
      currPoseUncertainty.y = INITIAL_UNCERT_Y;
      currPoseUncertainty.h = INITIAL_UNCERT_H;
     */
}

PoseEst AugmentedMCL::prediction(MotionModel u_t, PoseEst x_t_1)
{
    // Update with last odometry.
    lastOdo = u_t;

    // @todo IMPORTANT these variances are wrong! But if the gait is going to 
    // change soon, we should remeasure variances and adjust accordingly.
    u_t.deltaF -= sampleNormalDistribution(std::fabs(u_t.deltaF));
    u_t.deltaL -= sampleNormalDistribution(std::fabs(u_t.deltaL));
    u_t.deltaR -= sampleNormalDistribution(std::fabs(u_t.deltaR));

    x_t += u_t;
    x_t.h = NBMath::subPIAngle(x_t.h);

    return x_t;
}

float AugmentedMCL::measurementUpdate(std::vector<PointObservation> z_t,
				      std::vector<CornerObservation> c_t,
				      PoseEst x_t)
{
    // @todo
    // Find the weight of all observations (including all possible landmarks if
    // the observation is ambiguous, then choose the observation with the
    // highest weight.
    float maxWeight = 0.0f;
    float w = 0.0f;
    for(int i = 0; i < z_t.size(); ++i)
    {
	// Making the assumption that we receive either a PointObservation or a 
	// CornerObservation.
	std::vector<Observation> landmarkPossibilies;
	if(c_t.size() == 0)
	    landmarkPossibilies = z_t[i].getPosibilities();
	else
	    landmarkPossibilies = c_t[i].getPosibilities();
	    
	for(int j = 0; j < z_t[i].getPossibilities(); ++j)
	{
	    if(c_t.size() == 0)
		w = findCorrespondence<PointObservation, PointLandmark>
		    (z_t[i],
		     z_t[i].getPossibilities()[j],
		     x_t);
	    else 
		w = findCorrespondence<CornerObservation, CornerLandmark>
		    (c_t[i],
		     c_t[i].getPossibilities()[j],
		     x_t);	

	    if(w > maxWeight)
		maxWeight = w;
	}
    }

    return maxWeight;
}

float AugmentedMCL::sampleNormalDistribution(float standardDeviation)
{
    float sum = 0;
    for(int i = 0; i < 12; ++i)
    {
	// Generates a random value in the range [-b, b].
	sum += rand() % 2*standardDeviation - standardDeviation;
    }

    return 0.5*sum;
}

float AugmentedMCL::probabilityNormalDistribution(float a, float standardDeviation)
{
    return 1/std::sqrt(2*NBMath::M_PI_FLOAT*standardDeviation*standardDeviation)
	* std::exp(-(a*a)/(2*standardDeviation*standardDeviation));
}
