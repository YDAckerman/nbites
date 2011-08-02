#include "AugmentedMCL.h"

AugmentedMCL::AugmentedMCL(int particles, int width, int height)
    : ParticleFilter<PoseEst, PointObservation, CornerObservation, MotionModel, PF::PoseDimensions>(particles), fieldWidth(width), fieldHeight(height), lastOdo(0, 0, 0)
{
    // Randomly (and uniformly?) distribute M particles over the entire
    // pose space initially.
    srand(time(0));
    for(int i = 0; i < M; ++i)
    {
	PoseEst randomPose;
	randomPose.x = (rand() % fieldWidth)*1.0f;
	randomPose.y = (rand() % fieldHeight)*1.0f;
       	randomPose.h = ((rand() % 361)*1.0f)*TO_RAD;
	randomPose.h = NBMath::subPIAngle(randomPose.h);

	Particle<PoseEst> randomParticle(randomPose, 0.0f);
	
	X_t.push_back(randomParticle);
    }
}

AugmentedMCL::~AugmentedMCL()
{ }

void AugmentedMCL::updateLocalization(MotionModel& u_t,
				      std::vector<PointObservation>& pt_z,
				      std::vector<CornerObservation>& c_z)
{
    lastPointObservations = pt_z;
    lastCornerObservations = c_z;

    // If are no new observations, do not update localization.
    if(lastPointObservations.size() == 0 && lastCornerObservations.size() == 0)
	return;
   
    std::vector<Particle<PoseEst> > X_t_1 = X_t;

    std::vector<Particle<PoseEst> > X_t_bar = updateRule(X_t_1,
							 u_t,
							 lastPointObservations,
							 lastCornerObservations);

    w_slow += ALPHA_SLOW*(averageWeight - w_slow);
    w_fast += ALPHA_FAST*(averageWeight - w_fast);

    X_t = resample(X_t_bar);

    // Make and update estimates.
    // @todo
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

    x_t_1 += u_t;
    x_t_1.h = NBMath::subPIAngle(x_t_1.h);

    return x_t_1;
}

float AugmentedMCL::measurementUpdate(std::vector<PointObservation> &z1_t,
				      std::vector<CornerObservation> &z2_t,
				      PoseEst x_t)
{
    float pointWeight = 0.0f;
    float cornerWeight = 0.0f;

    if(z1_t.size() != 0)
	pointWeight = measurementUpdate<PointObservation, PointLandmark>(z1_t, x_t);

    if(z2_t.size() != 0)
	cornerWeight = measurementUpdate<CornerObservation, CornerLandmark>(z2_t, x_t);

    if(pointWeight > cornerWeight)
	return pointWeight;
    else 
	return cornerWeight;
}

std::vector<Particle<PoseEst> > AugmentedMCL::resample(std::vector<Particle<PoseEst> > X_t_bar)
{
    X_t.clear();

    // Normalize the weights.
    for(int i = 0; i < M; ++i)
	X_t_bar[i].setWeight(X_t_bar[i].getWeight()/totalWeight);
    
    averageWeight /= M;

    srand(time(0));
    float random = 0.0f;

    // Set the probability to be max{0.0, 1.0-w_fast/w_slow}.
    float injectionProbability = 1.0 - (w_fast/w_slow);
    if(injectionProbability < 0.0)
	injectionProbability = 0.0f;

    for(int i = 0; i < M; ++i)
    {
	// Check if necessary to inject random particle.
	random = (rand() % 101)/100.0f;
	if(random < injectionProbability)
	{
	    PoseEst randomPose;
	    randomPose.x = (rand() % fieldWidth)*1.0f;
	    randomPose.y = (rand() % fieldHeight)*1.0f;
	    randomPose.h = ((rand() % 361)*1.0f)*TO_RAD;
	    
	    randomPose.h = NBMath::subPIAngle(randomPose.h);
	    
	    Particle<PoseEst> randomParticle(randomPose, 0.0f);

	    X_t.push_back(randomParticle);
	}
	// Otherwise, continue normal resampling process.
	else
	{
	    random = (rand() % 101)/100.0f;
	    for(int i = 0; i < M; ++i)
	    {
		// Select a random particle based on the random number and the weights of each
		// particle.
		if(random < X_t_bar[i].getWeight())
		{
		    X_t.push_back(X_t_bar[i]);
		    break;
		}
		random -= X_t_bar[i].getWeight();
	    }
	}
    }
    
    return X_t;
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

void AugmentedMCL::updateEstimates()
{

}
