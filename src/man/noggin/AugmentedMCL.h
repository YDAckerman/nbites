#ifndef AUGMENTED_MCL_H
#define AUGMENTED_MCL_H

#include "ParticleFilter.h"
#include "Observation.h"
#include "EKFStructs.h"
#include "LocSystem.h"
#include "NBMath.h"

// Decay rates for exponential importance factor filters.
static const float ALPHA_FAST = 0.2f;
static const float ALPHA_SLOW = 0.05f;


class AugmentedMCL : public ParticleFilter<PoseEst, 
                                           MotionModel, 
                                           std::vector<VisualMeasurement>,
                                           PF::PoseDimensions, 
                                           PF::TwoMeasurement>, 
                     LocSystem
{
 public:
    /**
     * Class constructor, randomly distributes the particles over the 
     * entire pose space.
     *
     * @param particles Specifies the number of particles.
     * @param width The width (x-boundary) of the pose space.
     * @param height The height (y-boundary) of the pose space.
     */
    AugmentedMCL(int particles, int width, int height);

    /**
     * Class destructor.
     */
    virtual ~AugmentedMCL();

    void updateLocalization(const MotionModel& u_t,
			    const std::vector<PointObservation>& pt_z,
			    const std::vector<CornerObservation>& c_z);

    /**
     * Reset.
     */
    void reset();

    void blueGoalieReset();
    void redGoalieReset();

    /**
     * Resets the current pose estimate to the provided x, y, and angle 
     * (heading) with some initial uncertainty.
     *
     * @param x The x component of the pose.
     * @param y The y component of the pose.
     * @param h The angular component of the pose; the heading.
     */
    void resetLocTo(float x, float y, float h);

    PoseEst getCurrentEstimate() const { return currPoseEstimate; }
    PoseEst getCurrentUncertainty() const { return currPoseUncertainty; }
    float getXEst() const { return currPoseEstimate.x; }
    float getYEst() const { return currPoseEstimate.y; }
    float getHEst() const { return currPoseEstimate.h; }
    float getHEstDeg() const { return currPoseEstimate.h*TO_DEG; }
    float getXUncert() const { return currPoseUncertainty.x; }
    float getYUncert() const { return currPoseUncertainty.y; }
    float getHUncert() const { return currPoseUncertainty.h; }
    float getHUncertDeg() const { return currPoseUncertainty.h*TO_DEG; }
    MotionModel getLastOdo() const { return lastOdo; }

    std::vector<PointObservation> getLastPointObservations() const 
    { 
	return lastPointObservations; 
    }

    std::vector<CornerObservation> getLastCornerObservations() const 
    { 
	return lastCornerObservations; 
    }

    void setXEst(float xEst) { currPoseEstimate.x = xEst; }
    void setYEst(float yEst) { currPoseEstimate.y = yEst; }
    void setHEst(float hEst) { currPoseEstimate.h = hEst; }
    void setXUncert(float uncertX) { currPoseUncertainty.x = uncertX; }
    void setYUncert(float uncertY) { currPoseUncertainty.y = uncertY; }
    void setHUncert(float uncertH) { currPoseUncertainty.h = uncertH; }

    /**
     * Implements an algorithm for smapling from an approximate normal
     * distrubution with zero mean and specified variance. 
     *
     * @param standardDeviation The square root of the variance.
     *
     * @return A generated random sample from the zero-centered 
     * distribution with provided variance.
     */
    float sampleNormalDistribution(float standardDeviation);

    /**
     *
     */
    float probabilityNormalDistribution(float a, float standardDeviation);

    /**
     * Find's the weight (or correspondence) of a given observed 
     * landmark. The Observation object contains the standard 
     * deviation, and the Landmark object holds the field position
     * of it.
     *
     * @param z The observation object.
     * @param l The landmark object.
     * @param x_t The current pose estimate.
     *
     * @return The likelihood of measuring the landmark given a pose
     * estimate.
     */
    template <class ObservationType, class LandmarkType>
    float findCorrespondence(ObservationType& z, LandmarkType& l, PoseEst& x_t);

    /**
     * Updates the current pose estimates and uncertainties.
     */
    

 private:
    /**
     * Implements the prediction phase of Monte Carlo Localization. Finds
     * a new pose based on the previous pose state and the most current
     * odometry information.
     * 
     * @param u_t The most recent control (odometry) information.
     * @param x_t_1 The last pose state.
     *
     * @return A new predicted pose based on current and previous information.
     */
    PoseEst prediction(MotionModel u_t, PoseEst x_t_1);
    float measurementUpdate(std::vector<std::vector<VisualMeasurement> > z_t,
			    PoseEst x_t);

    /**
     *methods to determine new position estimates and variances
     */
    void updateEstimates();
    std::vector<Particle<PoseEst>> determineBestFitSubset(std::vector<Particle<PoseEst>> X_t_bar);
    Particle<PoseEst> determineHeaviestParticle(std::vector<Particle<PoseEst>> X_t_bar);
    PoseEst robustMeanEstimate( std::vector<Particle<PoseEst>> bestFit);
    PoseEst determineVariances( std::vector<Particle<PoseEst>> bestFit);
    float variance( std::vector<float> set );



    template <class ObservationType, class LandmarkType>
    float measurementUpdate(std::vector<ObservationType> z_t, PoseEst x_t);
    
    int fieldWidth;
    int fieldHeight;
    
    MotionModel lastOdo;
    std::vector<PointObservation> lastPointObservations;
    std::vector<CornerObservation> lastCornerObservations;
    
    PoseEst currPoseEstimate;
    PoseEst currPoseUncertainty;

    float w_slow;
    float w_fast;
};

template <class ObservationType, class LandmarkType>
float AugmentedMCL::findCorrespondence(ObservationType& z, 
				       LandmarkType& l,
				       PoseEst& x_t)
{
    float r_hat = hypotf(l.x - x_t.x, l.y - x_t.y);
    float psi_hat = std::atan2(l.y - x_t.y, l.x - x_t.x);
    float q = probabilityNormalDistribution(z.getVisDistance() - r_hat,
					    z.getDistanceSD())
	* probabilityNormalDistribution(z.getVisBearing() - psi_hat,
					z.getBearingSD());
    return q;
}

template <class ObservationType, class LandmarkType>
float AugmentedMCL::measurementUpdate(std::vector<ObservationType> z_t, PoseEst x_t)
{
    // Find the weight of all observations (including all possible landmarks if
    // the observation is ambiguous, then choose the observation with the
    // highest weight. @TODO: This might not be the best method, we may instead choose
    // to use some sort of average or a top n best average. For now this will be fine.
    float maxWeight = 0.0f;
    float w = 0.0f;
    for(int i = 0; i < z_t.size(); ++i)
    {
	    
	for(int j = 0; j < z_t[i].getNumPossibilities(); ++j)
	{
	    w = findCorrespondence<ObservationType, LandmarkType>
		(z_t[i],
		 z_t[i].getPossibilities()[j],
		 x_t);	

	    if(w > maxWeight)
		maxWeight = w;
	}
    }

    return maxWeight;
}
 

#endif // AUGMENTED_MCL_H