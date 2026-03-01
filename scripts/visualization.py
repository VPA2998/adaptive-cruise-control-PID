"""
Visualization script for ACC simulation results.

Generates:
- Time-series plots (velocity, distance, control)
- Animated GIF of ego/lead vehicle interaction
"""

import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from pathlib import Path
import numpy as np

def load_simulation(csv_path):
    """Load simulation CSV."""
    return pd.read_csv(csv_path)

def plot_results(df):
    """Generate time-series plots."""
    fig, axes = plt.subplots(3, 1, figsize=(12, 10))
    
    # Plot 1: Velocities
    axes[0].plot(df['time'], df['v_ego'], label='Ego', linewidth=2)
    axes[0].plot(df['time'], df['v_lead'], label='Lead', linewidth=2)
    axes[0].set_ylabel('Velocity [m/s]')
    axes[0].legend()
    axes[0].grid()
    
    # Plot 2: Distance
    axes[1].plot(df['time'], df['d_gap'], label='Gap', linewidth=2, color='green')
    axes[1].set_ylabel('Distance [m]')
    axes[1].legend()
    axes[1].grid()
    
    # Plot 3: Control Output
    axes[2].plot(df['time'], df['u_control'], label='Control', linewidth=2, color='red')
    axes[2].set_ylabel('Acceleration [m/s²]')
    axes[2].set_xlabel('Time [s]')
    axes[2].legend()
    axes[2].grid()
    
    plt.tight_layout()
    plt.savefig('build/acc_results.png', dpi=150)
    print("Saved: build/acc_results.png")

def main():
    csv_path = Path('build/acc_sim.csv')
    if not csv_path.exists():
        print(f"Error: {csv_path} not found. Run simulator first.")
        return
    
    df = load_simulation(csv_path)
    plot_results(df)
    plt.show()

if __name__ == '__main__':
    main()
