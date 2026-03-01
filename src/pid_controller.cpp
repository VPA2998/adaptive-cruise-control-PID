/**
 * @file pid_controller.cpp
 * @brief PID Controller Implementation
 * 
 * Implements Proportional-Integral-Derivative control:
 * u(t) = Kp*e(t) + Ki*∫e(t)dt + Kd*de(t)/dt
 */

#include "pid_controller.hpp"

namespace acc_sim {

/**
 * Constructor: Initialize PID with gains
 */
PIDController::PIDController(const Gains& gains)
    : gains_(gains), 
      integral_error_(0.0), 
      last_error_(0.0) {}

/**
 * Compute PID output for given error and time step
 * 
 * Formula: u = Kp*e + Ki*∫e + Kd*de/dt
 * 
 * @param error Current tracking error
 * @param dt Time step [seconds]
 * @return Control output (acceleration command)
 */
double PIDController::compute(double error, double dt) {
    
    // === PROPORTIONAL TERM ===
    // Immediate response to error
    double p_term = gains_.Kp * error;
    
    // === INTEGRAL TERM ===
    // Accumulate error over time to eliminate steady-state error
    integral_error_ += error * dt;
    double i_term = gains_.Ki * integral_error_;
    
    // === DERIVATIVE TERM ===
    // Predict and dampen oscillations
    // de/dt ≈ (e(t) - e(t-dt)) / dt
    double derivative = (dt > 0.0) ? (error - last_error_) / dt : 0.0;
    double d_term = gains_.Kd * derivative;
    
    // Store current error for next iteration
    last_error_ = error;
    
    // === TOTAL OUTPUT ===
    double output = p_term + i_term + d_term;
    
    return output;
}

/**
 * Reset integrator (anti-windup)
 * 
 * Call this when:
 * - Switching control modes
 * - Output is saturated
 * - You want to clear accumulated error
 */
void PIDController::reset() {
    integral_error_ = 0.0;
    last_error_ = 0.0;
}

/**
 * Update PID gains (for online tuning)
 * 
 * @param gains New Kp, Ki, Kd values
 */
void PIDController::set_gains(const Gains& gains) {
    gains_ = gains;
}

}  // namespace acc_sim
