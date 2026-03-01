/**
 * @file pid_controller.hpp
 * @brief PID Controller Header
 * 
 * Implements Proportional-Integral-Derivative control:
 * u(t) = Kp*e(t) + Ki*∫e(t)dt + Kd*de(t)/dt
 */

#pragma once

namespace acc_sim {

/**
 * @class PIDController
 * @brief Single PID control loop
 */
class PIDController {
public:
    /// Gain structure
    struct Gains {
        double Kp = 0.0;  ///< Proportional gain
        double Ki = 0.0;  ///< Integral gain
        double Kd = 0.0;  ///< Derivative gain
    };
    
    /**
     * Constructor
     * @param gains PID gain values
     */
    explicit PIDController(const Gains& gains = Gains());
    
    /**
     * Compute control output
     * @param error Current tracking error
     * @param dt Time step [seconds]
     * @return Control command (acceleration/braking)
     */
    double compute(double error, double dt);
    
    /**
     * Reset integrator (anti-windup)
     * Call when saturated or switching modes
     */
    void reset();
    
    /**
     * Update gains (online tuning)
     * @param gains New gain values
     */
    void set_gains(const Gains& gains);
    
private:
    Gains gains_;              ///< Current gains
    double integral_error_ = 0.0;  ///< Accumulated error
    double last_error_ = 0.0;      ///< Previous error (for derivative)
};

}  // namespace acc_sim
