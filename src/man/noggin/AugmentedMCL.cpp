#include "AugmentedMCL.h"

AugmentedMCL::AugmentedMCL(int particles, int width, int height)
    : ParticleFilter<PoseEst, MotionModel, std::vector<VisualMeasurement>, PF::PoseDimensions, PF::TwoMeasurement>(particles), fieldWidth(width), fieldHeight(height), lastOdo(0, 0, 0)
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
	X_t.push_back(randomPose);
    }
}

AugmentedMCL::~AugmentedMCL()
{ }

void AugmentedMCL::updateLocalization(const MotionModel& u_t,
				      const std::vector<PointObservation>& pt_z,
				      const std::vector<CornerObservation>& c_z)
{
    lastPointObservations = pt_z;
    lastCornerObservations = c_z;

    // If are no new observations, do not update localization.
    if(lastPointObservations.size() == 0 && lastCornerObservations.size() == 0)
	return;
   
    // Kind of a hack to ... @todo explain
    std::vector<std::vector<VisualMeasurement> > measurements;
    measurements.push_back(pt_z);
    measurements.push_back(c_z);

    std::vector<Particle<PoseEst> > X_t_1 = X_t;

    std::vector<Particle<PoseEst> > X_t_bar = updateRule(X_t_1, u_t, measurements);

    w_slow += ALPHA_SLOW*(averageWeight - w_slow);
    w_fast += ALPHA_FAST*(averageWeight - w_fast);

    X_t = resample(X_t_bar);

    // Make and update estimates.
    updateEstimates();
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

float AugmentedMCL::measurementUpdate(std::vector<std::vector<VisualMeasurement> > z_t,
				      PoseEst x_t)
{
    std::vector<PointObservation> pt_z = z_t[0];
    std::vector<CornerObservation> c_t = z_t[1];

    float pointWeight = 0.0f;
    float cornerWeight = 0.0f;

    if(z_t.size() != 0)
	pointWeight = measurementUpdate<PointObservation, PointLandmark>(pt_t, x_t);

    if(c_t.size() != 0)
	cornerWeight = measurementUpdate<CornerObservation, CornerLandmark>(c_t, x_t);

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
	    
	    X_t.push_back(randomPose);
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


Particle<PoseEst> AugmentedMCL::determineHeaviestParticle(std::vector<Particle<PoseEst> > X_t_bar)
{
  
  Particle<PoseEst> p;
  float maxWeight = 0;
  float weight;
  for(int i = 0; i < M; ++i)
    {
      weight = X_t_bar[i].getWeight
      
      if(weight > maxWeight){
	maxWeight = weight;
	p = X_t_bar[i];
      }
    }
  
  return p;

}


vector<Particle<PoseEst> determineBestFitSubset(std::vector<Particle<PoseEst> > X_t_bar)
{

  std::vector<Particle<PoseEst>> bestFitSubset;
  Particle<PoseEst> particle_i;
  PoseEst pose_i;


  // get the best particle and its weight from the 
  // particle set
  Particle<PoseEst> p = determineHeaviestParticle(X_t_bar);
  PoseEst heaviestState = p.getState();
  

  // loop through all particles, finding those within 
  // epsilon distance (euclidean metric @TODO: consider
  // mahalanobis distance) from the 'best' particle, then
  // add their poseEst to the poseEstimates vector and
  // their weights to the poseEstimatesWeights vector and
  // the total subset weight variable.
  for(int i = 0; i < M; ++i)
    {
      particle_i = X_t_bar[i];
      pose_i = curParticle.getState();
      if(heaviestState.distanceTo(pose_i) < epsilon)
	{
	  bestFitSubset.push_back(particle_i);
	}
    }

  return bestFitSubset;
}

PoseEst AugmentedMCL::robustMeanEstimate( std::vector<Particle<PoseEst> > bestFit)
{

  // this will house the total weight of the subset
  // and the temporary particle
  float total = 0.0f;
  Particle<PoseEst> p_i;

  for(int i = 0; i < bestFit.size(); ++i)
    {
      total += bestFit.size[i].getWeight();
    }

  // initialize a new poseEst to be 'empty'
  PoseEst bestEst(0,0,0);
 
  // loop through poseEstimates and add
  // a fraction of each pose based on the 
  // its weight relative to the total subset
  // weight. This is a slight modification from
  // the method described in Probabilistic 
  // Robotics. There they suggest simply multiplying
  // by the weight, so if our pose is (423,64,pi/2)
  // and our weight is .79, we'd add .79(423,64,pi/2)
  // to our best estimate. It makes more sense to me
  // to do it our way, but I could very easily be
  // mistaken. -Yoni Ackerman July, 2011.
  for(int i = 0; i < bestFit.size(); ++i)
    {
      p_i = bestFit[i]
      float weight = p_i.getWeight / total;
      bestEst += p_i.getState() * weight;
    }

  bestEst.h = NBMath::subPIAngle(bestEst.h);
  return bestEst;
}


PoseEst determineVariances(std::vector<Particle<PoseEst> > bestFit) 
{
  
  Particle<PoseEst> p_i;
  PoseEst pose_i;
  std::vector<float> X_subset;
  std::vector<float> Y_subset;
  std::vector<float> H_subset;
  
  for(int i = 0; i < bestFit.size(); ++i)
    {
      p_i = bestFit[i];
      pose_i = p_i.getState();

      X_subset.push_back(pose_i.x);
      Y_subset.push_back(pose_i.y);
      H_subset.push_back(pose_i.h);
    }
  
  PoseEst varEst(variance(X_subset),
		 variance(Y_subset),
		 variance(H_subset)
		 );
  return varEst;
}
 
float variance( std::vector<float> set)
{
  float mean = 0;
  float variance = 0;
  int count = set.size();
  for(int i = 0; i < count, ++i)
    {
      mean += set[i]; 
    }
  mean /= (float)count;
  
  for(int i = 0; i < count; ++i)
    {
      variance += (set[i] - mean)*(set[i] - mean);
    }
  
  return variance / (float) max

}

void AugmentedMCL::updateEstimates()
{
  std::vector<Particle<PoseEst>> bestFit = determineBestFitSubset(X_t)
  currentPoseEstimate = robustMeanEstimate(bestFit);
  currentPoseVariance = determineVariances(bestFit);
}						    }
