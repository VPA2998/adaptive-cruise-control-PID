/**
 * @file vehicle.hpp
 * @brief Vehicle Dynamics Model Header
 * 
 * Simulates longitudinal vehicle dynamics:
 * a = u_acc - c_drag*v² - μ*g
 */

#pragma once

namespace acc_sim {

/**
 * @class Vehicle
 * @brief Represents ego or lead vehicle with kinematic model
 */
class Vehicle {
public:
    /**
     * Constructor
     * @param initial_velocity Starting velocity [m/s]
     * @param initial_position Starting position [m]
     */
    Vehicle(double initial_velocity = 0.0, double initial_position = 0.0);
    
    /**
     * Update vehicle state
     * @param acceleration Command acceleration [m/s²]
     * @param friction_coeff Road friction coefficient μ
     * @param dt Time step [seconds]
     */
    void update(double acceleration, double friction_coeff, double dt);
    
    // Getters
    double get_velocity() const { return velocity_; }
    double get_position() const { return position_; }
    double get_acceleration() const { return acceleration_; }
    
    // Setters
    void set_velocity(double v) { velocity_ = v; }
    void set_position(double x) { position_ = x; }
    void set_friction(double mu) { friction_coeff_ = mu; }
    
private:
    double velocity_;           ///< Current velocity [m/s]
    double position_;           ///< Current position [m]
    double acceleration_;       ///< Current acceleration [m/s²]
    double friction_coeff_;     ///< Road friction coefficient
    
    // Constants
    static constexpr double DRAG_COEFF = 0.01;     ///< Aerodynamic drag
    static constexpr double GRAVITY = 9.81;         ///< Gravitational acceleration
    static constexpr double MAX_ACCEL = 2.0;        ///< Max acceleration [m/s²]
    static constexpr double MIN_VELOCITY = 0.0;     ///< Min velocity (no reverse)
    static constexpr double MAX_VELOCITY = 50.0;    ///< Max velocity [m/s]
    
    /**
     * Saturate acceleration to physical limits
     * @param a_desired Desired acceleration
     * @param max_decel Maximum deceleration (friction-limited)
     * @return Saturated acceleration
     */
    double saturate_acceleration(double a_desired, double max_decel);
};

}  // namespace acc_sim

