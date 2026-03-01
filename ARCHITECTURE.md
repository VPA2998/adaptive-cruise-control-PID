# 🏗️ System Architecture

## System Overview

```
Sensor Inputs (v_ego, v_lead, d_gap)
↓
[PID Controller]
↓
Cruise Loop ──┐
Headway Loop ─┤─→ Control Output (acceleration/braking)
Override Logic┘
↓
[Vehicle Dynamics]
↓
Output (position, velocity, CSV log)

```
---

## Control Architecture

### Dual PID Loops

**Loop 1: Cruise Control**
- Error: `e_cruise = v_set - v_ego`
- Maintains target speed when safe
- Typical gains: `Kp_c=0.4, Ki_c=0.05, Kd_c=0.01`

**Loop 2: Headway Control**
- Error: `e_headway = d_desired - d_gap`
- Maintains safe distance from lead vehicle
- Typical gains: `Kp_h=0.6, Ki_h=0.08, Kd_h=0.02`

### Mode Selection

```cpp
if (d_gap < d_desired) {
    use_headway_control();  // Safety priority
} else {
    use_cruise_control();   // Speed tracking
}
```
## Vehicle Dynamics
### Longitudinal Motion:

> a_ego = u_acc - 0.01 * v_ego² - μ * g

Where:

- u_acc = PID control output [m/s²]

- 0.01 * v_ego² = Aerodynamic drag

- μ * g = Friction (depends on road condition)

Constraints:

* Max acceleration: +2.0 m/s²

* Max braking: -μ * g (friction-limited)
---

# **Project Structure**

```
adaptive-cruise-control-PID/
├── include/              # C++ headers (vehicle, sensor, PID, etc.)
├── src/                  # C++ source files (main, simulator, pid_controller)
├── scripts/              # Python (visualization.py, analyze_metrics.py)
├── app/                  # Gradio web interface (app.py)
├── docs/                 # Documentation & guides
├── tests/                # Unit tests
├── CMakeLists.txt        # C++ build config
├── requirements.txt      # Python dependencies
├── README.md             # Main documentation
├── LICENSE               # MIT License
└── .gitignore
```
---

## **Simulation Loop**

> ### for each time step:
>    1. Read sensors (v_ego, v_lead, d_gap)
>    2. Compute PID errors (e_cruise, e_headway)
>    3. Calculate control outputs (u_cruise, u_headway)
>    4. Select active control mode
>    5. Update vehicle dynamics
>    6. Log data to CSV

```
Key Design Choices
✅ Dual PID: Separate loops for speed and distance → independent tuning
✅ Mode Priority: Headway (safety) > Cruise (comfort)
✅ Simplified Physics: Kinematic model sufficient for control validation
✅ CSV Logging: Easy visualization and analysis in Python
```

## **PID Parameter Tuning**

| Parameter | Description               | Range       |
| --------- | ------------------------- | ----------- |
| Kp_c      | Cruise proportional gain  | 0.3 - 0.5   |
| Ki_c      | Cruise integral gain      | 0.04 - 0.08 |
| Kd_c      | Cruise derivative gain    | 0.01 - 0.03 |
| Kp_h      | Headway proportional gain | 0.5 - 0.8   |
| Ki_h      | Headway integral gain     | 0.06 - 0.10 |
| Kd_h      | Headway derivative gain   | 0.02 - 0.04 |


See [tuning_guide.md](../tuning_guide.md) for detailed tuning steps.


### Output Data (CSV)
```
time, v_ego, v_lead, a_ego, d_gap, u_control, mode
0.0,  15.0,  20.0,   0.0,   30.0,  0.0,      CRUISE
0.1,  15.05, 20.0,   0.5,   29.95, 0.45,     CRUISE
```

### **Validation**

- Cruise control: Smooth speed tracking, no oscillation
- Headway control: Quick response, smooth braking
- Emergency: Handles lead vehicle braking gracefully
- Stability: Works across different friction coefficients

See [pid_theory.md](pid_theory.md) for control theory details.




