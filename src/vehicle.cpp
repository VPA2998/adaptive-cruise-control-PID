/**
 * @file vehicle.cpp
 * @brief Vehicle Dynamics Implementation
 */

#include "vehicle.hpp"
#include <algorithm>


namespace acc_sim {

Vehicle::Vehicle(double initial_velocity, double initial_position)
    : velocity_(initial_velocity),
      position_(initial_position),
      acceleration_(0.0),
      friction_coeff_(0.9) {}

void Vehicle::update(double acceleration, double friction_coeff, double dt) {
    // Update friction coefficient
    friction_coeff_ = friction_coeff;
    
    // Compute drag force: F_drag = c_drag * v²
    double drag = DRAG_COEFF * velocity_ * velocity_;
    
    // Compute friction force: F_friction = μ * g
    double friction = friction_coeff_ * GRAVITY;
    
    // Compute max deceleration (friction-limited)
    double max_decel = friction_coeff_ * GRAVITY;
    
    // Longitudinal dynamics: a = u_acc - drag - friction
    double a_raw = acceleration - drag - friction;
    
    // Saturate acceleration
    acceleration_ = saturate_acceleration(a_raw, max_decel);
    
    // Update velocity using Euler integration
    velocity_ += acceleration_ * dt;
    
    // Saturate velocity
    velocity_ = std::max(MIN_VELOCITY, std::min(MAX_VELOCITY, velocity_));
    
    // Update position using kinematic equation
    // x(t+dt) = x(t) + v(t)*dt + 0.5*a(t)*dt²
    position_ += velocity_ * dt + 0.5 * acceleration_ * dt * dt;
}

double Vehicle::saturate_acceleration(double a_desired, double max_decel) {
    // Limit acceleration to physical constraints
    double a_min = -max_decel;  // Maximum braking (friction-limited)
    double a_max = MAX_ACCEL;    // Maximum acceleration (comfort limit)
    
    return std::max(a_min, std::min(a_max, a_desired));
}

}  // namespace acc_sim
