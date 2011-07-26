#include "AugmentedMCL.h"

AugmentedMCL::AugmentedMCL(int particles, int width, int height)
    : ParticleFilter<PoseEst, MotionModel, Observation, PF::PoseDimensions>(particles), fieldWidth(width), fieldHeight(height), lastOdo(0, 0, 0)
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
    float pointWeight = 0.0f;
    float cornerWeight = 0.0f;

    if(z_t.size() != 0)
	pointWeight = measurementUpdate<PointObservation, PointLandmark>(z_t, x_t);

    if(c_t.size() != 0)
	cornerWeight = measurementUpdate<CornerObservation, CornerLandmark>(c_t, x_t);

    if(pointWeight > cornerWeight)
	return pointWeight;
    else 
	return cornerWeight;
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
    return 1/std::sqrt(2*M_PI_FLOAT*standardDeviation*standardDeviation)
	* std::exp(-(a*a)/(2*standardDeviation*standardDeviation));
}
