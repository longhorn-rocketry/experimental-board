#ifndef FLIGHTSIM_H
#define FLIGHTSIM_H

#include "noise.h"
#include <vector>

namespace flightsim {
  const int X_AXIS = 0;
  const int Y_AXIS = 1;
  const int Z_AXIS = 2;
  const int AXES_COUNT = 3;
}

/**
  Physical properties of a simulant rocket.
*/
struct RocketData {
  float initial_altitude;
  float drag_coeff;
  float radius;
  float airbrake_area;
  float burnout_mass;
  float burnout_velocity;
  float burnout_altitude;
};

/**
  Simulates the cruise portion of the flight immediately following engine
  burnout.
*/
class FlightSimulator {
protected:
  const struct RocketData rocket_data;

  float t_0, t_c, t_f;
  float airbrake_extension;
  float rocket_altitude, rocket_velocity, rocket_acceleration;
  bool sim_running;

  void assert_valid_axis(int axis);

public:
  /**
    Configure simulation.

    @param RocketData rocket properties
  */
  FlightSimulator(const struct RocketData &rocket_data);

  ~FlightSimulator();

  /**
    Starts the simulation. This should be called once, followed by repeated
    calls to advance().

    @param time_initial instant of simulation start
    @param duration duration of simulation
  */
  void begin(float time_initial, float duration);

  /**
    @brief Gets whether or not the simulation is running.
  */
  bool is_running();

  /**
    Runs a single step of the simulation.

    @param delta_t size of timestemp
  */
  void advance(float delta_t);

  /**
    Gets the current timestep of the simulation.

    @return time
  */
  float get_time();

  /**
    Sets the rocket's airbrake position.

    @param x position on [0.0, 1.0]
  */
  void set_airbrake_extension(float x);

  /**
    @brief Gets the rocket's actual velocity magnitude
  */
  float get_rocket_velocity();

  /**
    @brief Gets the rocket's actual altitude
  */
  float get_rocket_altitude();

  /**
    @brief Gets the rocket's actual acceleration vector
  */
  std::vector<float> get_rocket_acceleration() const;

  /**
    @brief Gets the rocket's actual gyroscopic vector
  */
  std::vector<float> get_rocket_gyro() const;
};

#endif