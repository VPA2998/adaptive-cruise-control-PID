/**
 * @file pid_controller.hpp
 * @brief PID Controller Interface
 * 
 * Implements dual-loop PID control for ACC system.
 */

#pragma once

namespace acc_sim {

/**
 * @class PIDController
 * @brief Proportional-Integral-Derivative control loop
 * 
 * Computes: u = Kp*e + Ki*∫e + Kd*de/dt
 */
class PIDController {
public:
    struct Gains {
        double Kp;  ///< Proportional gain
        double Ki;  ///< Integral gain
        double Kd;  ///< Derivative gain
    };
    
    /// Constructor
    explicit PIDController(const Gains& gains);
    
    /// Compute control output
    double compute(double error, double dt);
    
    /// Reset integrator (anti-windup)
    void reset();
    
    /// Update gains
    void set_gains(const Gains& gains);
    
private:
    Gains gains_;
    double integral_error_ = 0.0;
    double last_error_ = 0.0;
};

}  // namespace acc_sim
