"""
Interactive Gradio Web Interface for ACC Simulator.

Allows users to:
- Adjust PID gains
- Set scenario parameters
- Run simulation
- View results live
"""

import gradio as gr
import numpy as np
from pathlib import Path

def run_acc_simulation(ego_speed, rel_speed, distance, 
                       Kp_c, Ki_c, Kd_c, 
                       Kp_h, Ki_h, Kd_h):
    """
    Run ACC simulation with given parameters.
    
    Returns:
    - Status message
    - Results plot
    """
    
    # TODO: Call C++ simulator with these parameters
    # For now, just return placeholder
    
    result_msg = f"""
    Simulation Parameters:
    - Ego Speed: {ego_speed} m/s
    - Rel Speed: {rel_speed} m/s
    - Distance: {distance} m
    - Cruise Gains: Kp={Kp_c}, Ki={Ki_c}, Kd={Kd_c}
    - Headway Gains: Kp={Kp_h}, Ki={Ki_h}, Kd={Kd_h}
    """
    
    return result_msg

# Gradio Interface
demo = gr.Interface(
    fn=run_acc_simulation,
    inputs=[
        gr.Slider(0, 50, value=20, label="Ego Speed [m/s]"),
        gr.Slider(-30, 30, value=-5, label="Relative Speed [m/s]"),
        gr.Slider(1, 100, value=25, label="Distance [m]"),
        gr.Slider(0.1, 1.0, value=0.4, label="Kp_cruise"),
        gr.Slider(0.01, 0.2, value=0.05, label="Ki_cruise"),
        gr.Slider(0.001, 0.1, value=0.01, label="Kd_cruise"),
        gr.Slider(0.2, 1.0, value=0.6, label="Kp_headway"),
        gr.Slider(0.01, 0.2, value=0.08, label="Ki_headway"),
        gr.Slider(0.001, 0.1, value=0.02, label="Kd_headway"),
    ],
    outputs="text",
    title="ACC PID Tuning Interface",
    description="Adjust parameters and run simulations"
)

if __name__ == "__main__":
    demo.launch()
