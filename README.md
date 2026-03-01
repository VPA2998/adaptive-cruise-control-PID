# 🚗 Adaptive Cruise Control (ACC) with PID Control

A professional C++/Python implementation of an Adaptive Cruise Control system with dual PID loops, 
built for autonomous vehicle simulation and control education.

## 🎯 Project Goal

Demonstrate a production-grade ACC controller that:
- ✅ Maintains target speed (cruise control)
- ✅ Maintains safe distance from lead vehicle (headway control)
- ✅ Handles emergency braking scenarios
- ✅ Works across varying road conditions (friction coefficient adjustable)

## ⚡ Key Features

- **Dual PID Architecture** – Independent cruise & headway control loops
- **Physics-Based Simulation** – Realistic vehicle dynamics with drag and friction
- **Interactive Visualization** – Animated ego/lead vehicle with matplotlib
- **Web Interface** – Gradio app for parameter tuning
- **Comprehensive Tuning Guide** – PID gains explained and documented
- **Performance Metrics** – Stability, response time, overshoot analysis
- **Well-Documented Code** – Clean C++ with detailed comments

## 🚀 Quick Start

### Prerequisites
- CMake 3.10+
- C++17 compiler (g++, clang, or MSVC)
- Python 3.8+

### Build & Run

```bash
# Create build directory
mkdir -p build
cd build

# Configure and build
cmake ..
make

# Run simulation with example parameters
./acc_simulator 27 1.2 0.9 20 30 0 15 20 0.4 0.05 0.01 0.6 0.08 0.02
```

### Visualize Results
```bash
cd ../scripts
python3 visualization.py
```
### Interactive Web App
```bash
cd ../app
python3 app.py
# Open http://127.0.0.1:7860
```
### 📊 System Architecture
Inputs: ego_speed, lead_speed, distance
         ↓
    [PID Controller]
         ↓
    Cruise Loop ──┐
    Headway Loop ─┤─→ [Acceleration/Braking Command]
                  │
    Override Logic┘
         ↓
    [Vehicle Dynamics Model]
         ↓
Outputs: ego acceleration, position, velocity

### 🧪 PID Parameter Guide

| Parameter | Description               | Typical Range |
| --------- | ------------------------- | ------------- |
| Kp_c      | Cruise proportional gain  | 0.3 - 0.5     |
| Ki_c      | Cruise integral gain      | 0.04 - 0.08   |
| Kd_c      | Cruise derivative gain    | 0.01 - 0.03   |
| Kp_h      | Headway proportional gain | 0.5 - 0.8     |
| Ki_h      | Headway integral gain     | 0.06 - 0.10   |
| Kd_h      | Headway derivative gain   | 0.02 - 0.04   |
> See docs/tuning_guide.md for detailed tuning methodology.

### 📁 Project Structure
adaptive-cruise-control-PID/
├── src/                    # C++ source files
├── include/                # C++ header files
├── scripts/                # Python visualization & analysis
├── app/                    # Gradio web interface
├── docs/                   # Documentation & guides
├── tests/                  # Unit tests
├── build/                  # Build artifacts (git ignored)
├── CMakeLists.txt          # C++ build configuration
├── requirements.txt        # Python dependencies
├── README.md               # This file
├── LICENSE                 # MIT License
└── .gitignore

### 📚 Documentation
- ARCHITECTURE.md – System design & control theory

- docs/tuning_guide.md – Step-by-step PID tuning

- docs/pid_theory.md – PID control fundamentals

- docs/physics_model.md – Vehicle dynamics equations

#### 🧠 How It Works
Dual PID Control Strategy
The ACC system uses two independent PID controllers:

1. Cruise Control Loop

    - Tracks target speed (v_set)

    - Error: e = v_set - v_ego

    - Adjusts acceleration to maintain desired speed

2. Headway Control Loop

    - Maintains safe distance to lead vehicle

    - Error: e = d_desired - d_gap

    - Activates when distance drops below threshold

    - Prevents collisions with smooth braking

#### Mode Selection
```bash
IF distance < safe_threshold:
    Use Headway Control (priority)
ELSE:
    Use Cruise Control
``` 

### 🎬 Example Simulation
Run with example parameters:
```bash
./acc_simulator v_set=27 headway=1.2 friction=0.9 sim_time=20 init_gap=30 \
                lead_accel=-0.5 v_ego0=15 v_lead0=20 \
                Kp_c=0.4 Ki_c=0.05 Kd_c=0.01 \
                Kp_h=0.6 Ki_h=0.08 Kd_h=0.02
```
> Output CSV: build/acc_sim.csv
>
> Visualization: build/acc_animation.mp4

### 🔧 Tuning Tips
- Start conservative: Begin with low gains, increase gradually

- Test step responses: Observe rise time, overshoot, settling time

- Use visualization: Monitor real-time vehicle behavior

- Account for friction: Adjust gains for different road conditions

- Avoid oscillations: High gains → instability

> See docs/tuning_guide.md for detailed methodology.

### 📈 Performance Metrics
The simulation logs:

    - Time step

    - Ego velocity & acceleration

    - Lead velocity & acceleration

    - Gap distance

    - Control mode (cruise/headway/override)

    - PID control outputs

> Analyze with: python3 scripts/analyze_metrics.py
