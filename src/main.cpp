/**
 * @file main.cpp
 * @brief ACC Simulator Entry Point
 * 
 * Simulates Adaptive Cruise Control with dual PID loops.
 * 
 * Usage:
 * ./acc_simulator v_set headway mu sim_time init_gap lead_accel \
 *                 v_ego0 v_lead0 \
 *                 Kp_c Ki_c Kd_c Kp_h Ki_h Kd_h
 * 
 * Example:
 * ./acc_simulator 27 1.2 0.9 20 30 -0.5 15 20 0.4 0.05 0.01 0.6 0.08 0.02
 */

#include "pid_controller.hpp"
#include "vehicle.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace acc_sim;

struct SimParams {
    double v_set;
    double headway_time;
    double friction_coeff;
    double sim_time;
    double init_gap;
    double lead_accel;
    double v_ego0;
    double v_lead0;
    double Kp_c, Ki_c, Kd_c;
    double Kp_h, Ki_h, Kd_h;
};

enum ControlMode {
    CRUISE,
    HEADWAY,
    OVERRIDE
};

int main(int argc, char* argv[]) {
    
    std::cout << "=== ACC Simulator ===" << std::endl;
    
    if (argc != 15) {
        std::cerr << "Error: Expected 14 arguments\n";
        return 1;
    }
    
    SimParams params;
    params.v_set = std::stod(argv[1]);
    params.headway_time = std::stod(argv[2]);
    params.friction_coeff = std::stod(argv[3]);
    params.sim_time = std::stod(argv[4]);
    params.init_gap = std::stod(argv[5]);
    params.lead_accel = std::stod(argv[6]);
    params.v_ego0 = std::stod(argv[7]);
    params.v_lead0 = std::stod(argv[8]);
    params.Kp_c = std::stod(argv[9]);
    params.Ki_c = std::stod(argv[10]);
    params.Kd_c = std::stod(argv[11]);
    params.Kp_h = std::stod(argv[12]);
    params.Ki_h = std::stod(argv[13]);
    params.Kd_h = std::stod(argv[14]);
    
    std::cout << "Parameters:\n";
    std::cout << "  v_set=" << params.v_set << " m/s\n";
    std::cout << "  headway=" << params.headway_time << " s\n";
    std::cout << "  friction=" << params.friction_coeff << "\n";
    std::cout << "  sim_time=" << params.sim_time << " s\n";
    std::cout << "  init_gap=" << params.init_gap << " m\n\n";
    
    PIDController pid_cruise({params.Kp_c, params.Ki_c, params.Kd_c});
    PIDController pid_headway({params.Kp_h, params.Ki_h, params.Kd_h});
    
    Vehicle ego(params.v_ego0, 0.0);
    Vehicle lead(params.v_lead0, params.init_gap);
    
    double dt = 0.1;
    int num_steps = (int)(params.sim_time / dt);
    
    std::ofstream csv_file("build/acc_sim.csv");
    if (!csv_file.is_open()) {
        std::cerr << "Error: Cannot open build/acc_sim.csv\n";
        return 1;
    }
    
    csv_file << "time,v_ego,v_lead,a_ego,d_gap,u_control,mode,e_cruise,e_headway\n";
    
    for (int step = 0; step < num_steps; ++step) {
        double time = step * dt;
        
        double v_ego = ego.get_velocity();
        double v_lead = lead.get_velocity();
        double x_ego = ego.get_position();
        double x_lead = lead.get_position();
        
        double d_gap = x_lead - x_ego;
        
        double e_cruise = params.v_set - v_ego;
        double d_desired = params.headway_time * v_ego;
        double e_headway = d_desired - d_gap;
        
        double u_cruise = pid_cruise.compute(e_cruise, dt);
        double u_headway = pid_headway.compute(e_headway, dt);
        
        double u_control = 0.0;
        ControlMode mode = CRUISE;
        
        if (d_gap < 5.0) {
            mode = OVERRIDE;
            u_control = -params.friction_coeff * 9.81;
        } else if (d_gap < d_desired) {
            mode = HEADWAY;
            u_control = u_headway;
        } else {
            mode = CRUISE;
            u_control = u_cruise;
        }
        
        ego.update(u_control, params.friction_coeff, dt);
        lead.update(params.lead_accel, params.friction_coeff, dt);
        
        std::string mode_str = (mode == CRUISE) ? "CRUISE" : 
                               (mode == HEADWAY) ? "HEADWAY" : "OVERRIDE";
        
        csv_file << std::fixed << std::setprecision(2)
                 << time << ","
                 << v_ego << ","
                 << v_lead << ","
                 << ego.get_acceleration() << ","
                 << d_gap << ","
                 << u_control << ","
                 << mode_str << ","
                 << e_cruise << ","
                 << e_headway << "\n";
        
        if (step % 50 == 0) {
            std::cout << "Step " << step << "/" << num_steps 
                      << " (t=" << time << "s)\n";
        }
    }
    
    csv_file.close();
    std::cout << "\nSimulation complete! Results in build/acc_sim.csv\n";
    
    return 0;
}

