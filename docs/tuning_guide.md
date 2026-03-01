# 🧪 PID Tuning Guide for ACC System

## Overview

This guide walks you through tuning the PID gains for both the cruise control and headway control loops.

---

## Step 1: Understand Your System

**Key Parameters:**
- `Kp` = Proportional gain (immediate response)
- `Ki` = Integral gain (eliminates steady-state error)
- `Kd` = Derivative gain (damping, smoothness)

**Starting Points:**

Cruise Control: Kp=0.4, Ki=0.05, Kd=0.01

Headway Control: Kp=0.6, Ki=0.08, Kd=0.02


---

## Step 2: Tune Cruise Control Loop

### Test: Speed Step Response

Run a simulation with a **speed step** (e.g., from 20 m/s to 27 m/s):

```bash
cd build
./acc_simulator v_set=27 headway=2.0 friction=0.9 sim_time=15 \
                init_gap=50 lead_accel=0 v_ego0=20 v_lead0=20 \
                Kp_c=0.4 Ki_c=0.05 Kd_c=0.01 \
                Kp_h=0.6 Ki_h=0.08 Kd_h=0.02 
```

**Observe and Adjust**

| Symptom               | Adjustment                   |
| --------------------- | ---------------------------- |
| Too slow to respond   | Increase Kp_c                |
| Oscillating (ringing) | Decrease Kp_c, increase Kd_c |
| Overshoot > 10%       | Increase Kd_c                |
| Steady-state error    | Increase Ki_c                |
| Jerky acceleration    | Increase Kd_c                |
---
## Step 3: Tune Headway Control Loop

Test: Lead Vehicle Braking

Simulate lead vehicle slowing down:
```
./acc_simulator v_set=27 headway=1.5 friction=0.9 sim_time=20 \
                init_gap=30 lead_accel=-0.8 v_ego0=25 v_lead0=25 \
                Kp_c=0.4 Ki_c=0.05 Kd_c=0.01 \
                Kp_h=0.6 Ki_h=0.08 Kd_h=0.02
```
**Goals**

✅ Quick response (< 2 seconds)

✅ Smooth braking (no jerk)

✅ No gap oscillations

✅ Final distance = headway_time * v_ego

---

## Step 4: Validate on Different Road Conditions
Test with different friction coefficients (wet, dry, icy):
```bash
# Dry road (mu=0.95)
./acc_simulator ... friction=0.95 ...

# Wet road (mu=0.7)
./acc_simulator ... friction=0.7 ...

# Icy road (mu=0.5)
./acc_simulator ... friction=0.5 ...

```
Gains should work reasonably across all conditions.

---

### **Quick Tuning Checklist:**
- [ ] Cruise control responds smoothly (rise time < 5 sec)
- [ ] No oscillations or overshoot
- [ ] Headway control reacts quickly to lead braking
- [ ] Final gap equals target (headway_time * v_ego)
- [ ] Works on multiple friction values
- [ ] No jerky accelerations

### **Common Issues & Fixes**

| Issue                   | Cause     | Fix                        |
| ----------------------- | --------- | -------------------------- |
| Slow speed tracking     | Low Kp_c  | Increase Kp_c by 0.05      |
| Ringing/oscillation     | High Kp_c | Reduce by 0.1, add Kd_c    |
| Late collision response | Low Kp_h  | Increase Kp_h to 0.7-0.8   |
| Jerky braking           | Low Kd_h  | Increase Kd_h to 0.03-0.04 |
| Overshoot on speed step | High Ki_c | Reduce Ki_c slightly       |

---

**Tips for Success**

✅ Tune one loop at a time

✅ Small increments (±0.01-0.05)

✅ Run visualization after each test

✅ Check CSV logs for detailed metrics

✅ Document your results (working gains)
```bash
# Example Working Gains (Dry Road)
Cruise:  Kp_c=0.42, Ki_c=0.055, Kd_c=0.012
Headway: Kp_h=0.65, Ki_h=0.085, Kd_h=0.022
```
---



 

 

 

 