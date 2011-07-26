#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER_H

#include <vector>
#include <cstdlib>
#include <ctime>

enum PF
{
    PoseDimensions = 3,
    PointMeasurementDimensions = 2,
    CornerMeasurementDimensions = 3
};

template <class State>
class Particle
{
 public:
    /**
     * Class constructor.
     *
     * @param s The particle state vector.
     * @param w The particle importance factor (weight.)
     */
    Particle(State s, float w);

    /**
     * Class destructor.
     */
    ~Particle();

    State getState() const { return state; }
    void setState(State newState) { state = newState; }
    float getWeight() const { return weight; }
    void setWeight(float newWeight) { weight = newWeight; }

 private:
    State state;
    float weight;
};

template <class State>
Particle<State>::Particle(State s, float w)
: state(s), weight(w)
{ }

template <class State>
Particle<State>::~Particle()
{ }

template <class State, class Measurement, class Control, unsigned int stateVectorDimensions>
class ParticleFilter 
{
 public:
    typedef std::vector<Particle<State> > ParticleSet;

    /**
     * Class constructor.
     *
     * @param M The total number of particles.
     */
    ParticleFilter(int particles);

    /**
     * Class destructor.
     */
    virtual ~ParticleFilter();

    /**
     * Responsible for returning a new particle set of updated particles according to the
     * most recent control data and measurements.
     *
     * @param X_t_1 The set of particles from the previous time step.
     * @param u_t The most recent control data.
     * @param z_t The most recent measurement.
     *
     * @return The updated particle set (before resampling.)
     */
    ParticleSet updateRule(ParticleSet X_t_1, Control u_t, std::vector<Measurement> z_t);

    /**
     * Finds the current state by sampling the state transition distribution, based on the 
     * previous state and the most recent control data.
     *
     * @param u_t The most recent control data.
     * @param x_t_1 The last state.
     *
     * @return The current updated state.
     */
    virtual State prediction(Control u_t, State x_t_1) = 0;

    /**
     * Finds the weight (importance factor) of the given state according to the probability
     * of measurement under the given state.
     *
     * @param z_t The most recent measurement.
     * @param x_t The most recent state.
     *
     * @return The weight of the particle with state x_t.
     */
    virtual float measurementUpdate(std::vector<Measurement> z_t, State x_t) = 0;

    /**
     * Draws with replacement M particles from the temporary set into a new particle set 
     * according to each particle's importance factor (weight.)
     *
     * @param X_t_bar The set of particles to be resampled.
     *
     * @return The resampled set of particles from the set X_t_bar.
     */
    ParticleSet resample(ParticleSet X_t_bar);

 protected:
    ParticleSet X_t;
    int M;
    float totalWeight;
};

template <class State, class Measurement, class Control, unsigned int stateVectorDimensions>
ParticleFilter<State, Measurement, Control, stateVectorDimensions>::ParticleFilter(int particles)
    : M(particles), totalWeight(0.0f)
{ }

template <class State, class Measurement, class Control, unsigned int stateVectorDimensions>
ParticleFilter<State, Measurement, Control, stateVectorDimensions>::~ParticleFilter()
{ }

template <class State, class Measurement, class Control, unsigned int stateVectorDimensions>
std::vector<Particle<State> > ParticleFilter<State, Measurement, Control, stateVectorDimensions>::updateRule(ParticleSet X_t_1, 
										      Control u_t, 
										      std::vector<Measurement> z_t)
{
    ParticleSet X_t_bar;
    totalWeight = 0.0f;
    for(int m = 0; m < M; ++m)
    {
	// Sample from the state transition distribution, incorperating the control model.
	State x_t_m = prediction(u_t, X_t_1[m].getState());
	// Determine the importance factor by incorperating the measurement.
	float w_t_m = measurementUpdate(z_t, x_t_m);
	totalWeight += w_t_m;
	// Add the particle to the temporary set.
	Particle<State> p(x_t_m, w_t_m);
	X_t_bar.push_back(p);
    }
    // Return the updated set.
    return X_t_bar;
}

template <class State, class Measurement, class Control, unsigned int stateVectorDimensions>
std::vector<Particle<State> > ParticleFilter<State, Measurement, Control, stateVectorDimensions>::resample(ParticleSet X_t_bar)
{
    using namespace std;

    X_t.clear();

    // Normalize the weights.
    for(int i = 0; i < M; i++)
	X_t_bar[i].setWeight(X_t_bar[i].getWeight()/totalWeight);

    srand(time(0));
    float random = 0.0f;

    // Draw M particles randomly from X_t_bar (with likelihood of being chosen proportional to 
    // the particle's weight) by replacement and insert into set X_t.
    for(int i = 0; i < M; ++i)
    {
	random = (rand() % 101)/100.0f; // Between 0.0 and 1.0.
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

    // Return the resampled set.
    return X_t;
}

#endif // PARTICLE_FILTER_H
