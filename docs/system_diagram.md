# 📊 System Architecture Diagrams

## Signal Flow Diagram

```
SENSOR LAYER
┌─────────────────────────┐
│ Simulated Sensors │
│ - v_ego (ego speed) │
│ - v_lead (lead speed) │
│ - d_gap (distance) │
└────────────┬────────────┘
│
CONTROLLER LAYER
│
┌────▼────────────┐
│ Error Calc │
│ e_c = v_set-v_e │
│ e_h = d_des-d_g │
└────┬────────────┘
│
┌──────┴──────┐
│ │
┌───▼──┐ ┌──▼───┐
│Cruise│ │Headwa│
│ PID │ │ PID │
└───┬──┘ └──┬───┘
│ │
└──────┬─────┘
│
┌────▼─────────┐
│ Mode Select │
│ Priority: │
│ H > C │
└────┬─────────┘
│
ACTUATION LAYER
┌────▼──────────────┐
│ Vehicle Dynamics │
│ a = u - drag - μg │
└────┬───────────────┘
│
┌────▼──────┐
│ Integrate │
│ v, x │
└────┬──────┘
│
┌────▼──────┐
│ Log │
│ CSV file │
└───────────┘
```

---

## Control Mode State Machine

```
       ┌──────────────┐
┌─────→│   CRUISE     │◄─────┐
│      │ (Kp_c, etc)  │      │
│      └──────┬───────┘      │
│             │              │
│    d_gap < d_desired       │
│             │              │
│             ▼              │
│      ┌──────────────┐      │
└──────│  HEADWAY     │      │
d_gap>d│ (Kp_h, etc)  │──────┘
_des   └──────┬───────┘
              │
      d_gap < d_critical
              │
              ▼
      ┌──────────────┐
      │  OVERRIDE    │
      │ (Max brake)  │
      └──────────────┘
```

---

## Data Flow

### Simulation Step Loop:
1. Read v_ego, v_lead, d_gap from previous step
2. Calculate errors:
    - e_cruise = v_set - v_ego
    - e_headway = d_desired - d_gap
3. Compute PID outputs:
    - u_cruise = Kp_ce_c + Ki_c∫e_c + Kd_c*de_c/dt
    - u_headway = Kp_he_h + Ki_h∫e_h + Kd_h*de_h/dt
4. Select control mode → u_final
5. Update vehicle:
    - a = u_final - drag - friction
    - v = v + a*dt
    - x = x + v*dt
6. Log to CSV
7. Repeat at next timestep

---











