"""
Visualization script for ACC simulation results.

Generates time-series plots of velocity, distance, and control output.
"""

import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

def load_simulation(csv_path):
    """Load simulation CSV file."""
    df = pd.read_csv(csv_path)
    return df

def plot_results(df):
    """Generate time-series plots."""
    fig, axes = plt.subplots(3, 1, figsize=(12, 10))
    
    # Plot 1: Velocities
    axes[0].plot(df['time'], df['v_ego'], label='Ego Vehicle', linewidth=2, color='blue')
    axes[0].plot(df['time'], df['v_lead'], label='Lead Vehicle', linewidth=2, color='red')
    axes[0].set_ylabel('Velocity [m/s]', fontsize=12)
    axes[0].set_title('Vehicle Velocities', fontsize=14, fontweight='bold')
    axes[0].legend(fontsize=10)
    axes[0].grid(True, alpha=0.3)
    
    # Plot 2: Distance (Gap)
    axes[1].plot(df['time'], df['d_gap'], label='Gap Distance', linewidth=2, color='green')
    axes[1].axhline(y=0, color='red', linestyle='--', label='Collision', linewidth=1)
    axes[1].set_ylabel('Distance [m]', fontsize=12)
    axes[1].set_title('Gap to Lead Vehicle', fontsize=14, fontweight='bold')
    axes[1].legend(fontsize=10)
    axes[1].grid(True, alpha=0.3)
    
    # Plot 3: Control Output
    axes[2].plot(df['time'], df['u_control'], label='Control Output', linewidth=2, color='purple')
    axes[2].axhline(y=0, color='black', linestyle='-', linewidth=0.5)
    axes[2].set_ylabel('Acceleration [m/s²]', fontsize=12)
    axes[2].set_xlabel('Time [s]', fontsize=12)
    axes[2].set_title('Control Command', fontsize=14, fontweight='bold')
    axes[2].legend(fontsize=10)
    axes[2].grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('build/acc_results.png', dpi=150, bbox_inches='tight')
    print("✅ Saved: build/acc_results.png")
    plt.show()

def print_statistics(df):
    """Print simulation statistics."""
    print("\n" + "="*50)
    print("SIMULATION STATISTICS")
    print("="*50)
    print(f"\nEgo Vehicle:")
    print(f"  Min velocity: {df['v_ego'].min():.2f} m/s")
    print(f"  Max velocity: {df['v_ego'].max():.2f} m/s")
    print(f"  Avg velocity: {df['v_ego'].mean():.2f} m/s")
    
    print(f"\nLead Vehicle:")
    print(f"  Min velocity: {df['v_lead'].min():.2f} m/s")
    print(f"  Max velocity: {df['v_lead'].max():.2f} m/s")
    
    print(f"\nGap Distance:")
    print(f"  Min gap: {df['d_gap'].min():.2f} m")
    print(f"  Max gap: {df['d_gap'].max():.2f} m")
    print(f"  Avg gap: {df['d_gap'].mean():.2f} m")
    
    print(f"\nControl Output:")
    print(f"  Min accel: {df['u_control'].min():.2f} m/s²")
    print(f"  Max accel: {df['u_control'].max():.2f} m/s²")
    
    # Mode distribution
    mode_counts = df['mode'].value_counts()
    print(f"\nControl Modes:")
    for mode, count in mode_counts.items():
        percentage = (count / len(df)) * 100
        print(f"  {mode}: {count} steps ({percentage:.1f}%)")
    print("="*50 + "\n")

def main():
    csv_path = Path('build/acc_sim.csv')
    
    if not csv_path.exists():
        print(f"❌ Error: {csv_path} not found!")
        print("Run simulator first: ./acc_simulator 27 1.2 0.9 20 30 -0.5 15 20 0.4 0.05 0.01 0.6 0.08 0.02")
        return
    
    print("Loading simulation data...")
    df = load_simulation(csv_path)
    
    print_statistics(df)
    
    print("Generating plots...")
    plot_results(df)

if __name__ == '__main__':
    main()
