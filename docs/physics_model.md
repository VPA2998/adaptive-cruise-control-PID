# 🔬 Vehicle Physics Model

## Longitudinal Dynamics

The vehicle motion is governed by Newton's second law:

- F_net = m * a_ego
- a_ego = (u_acc - F_drag - F_friction) / m


**Simplified (assuming m=1):**

> a_ego = u_acc - c_drag * v_ego² - μ * g


Where:
- `u_acc` = Control output (PID) [m/s²]
- `c_drag` = Drag coefficient (~0.01)
- `v_ego` = Ego velocity [m/s]
- `μ` = Road friction coefficient
- `g` = 9.81 m/s²

---

## Position & Velocity Updates

**Kinematic Integration (Euler method):**

v(t+dt) = v(t) + a(t) * dt

x(t+dt) = x(t) + v(t) * dt + 0.5 * a(t) * dt²


---

## Constraints

### Velocity Limits
- `v_min = 0 m/s` (no reverse)
- `v_max = 50 m/s` (180 km/h)

### Acceleration Limits
- `a_max = +2.0 m/s²` (comfort max)
- `a_min = -μ * g` (friction limited braking)

**Output Saturation:**
```cpp
a_final = clip(a_ego, a_min, a_max)
```
---

### Friction Model
**Road friction affects maximum braking:**
| Road Type   | μ    | Max Decel |
| ----------- | ---- | --------- |
| Dry asphalt | 0.95 | 9.31 m/s² |
| Wet road    | 0.7  | 6.87 m/s² |
| Icy road    | 0.5  | 4.91 m/s² |
| Snow        | 0.3  | 2.94 m/s² |
---

## Model Accuracy

**Assumptions:**
- 1D longitudinal motion only
- No suspension dynamics
- Constant mass
- Linear friction model

**Valid for:**
- Control algorithm testing
- Scenario evaluation
- Educational purposes

**Limitations:**
- Real vehicles have lag
- Tire slip not modeled
- No load transfer effects
- Simplified aerodynamics

---












