# 📖 PID Control Theory

## What is PID Control?

PID stands for **Proportional-Integral-Derivative**. It's a feedback control algorithm that adjusts an output based on an error signal.

**General PID Equation:**

u(t) = Kp·e(t) + Ki·∫e(t)dt + Kd·de(t)/dt


Where:
- `u(t)` = Control output (acceleration command)
- `e(t)` = Error (difference from target)
- `Kp, Ki, Kd` = Tuning gains

---

## The Three Terms

### 1. Proportional (P) Term

**Purpose:** Immediate response to error.

u_p = Kp · e(t)


**Effect:**
- ✅ Reduces error quickly
- ❌ Often causes overshoot
- ❌ May have steady-state error

**Example:**
- If target speed = 27 m/s and actual = 20 m/s
- Error = 7 m/s
- Output = Kp × 7 = responds immediately

---

### 2. Integral (I) Term

**Purpose:** Eliminate steady-state error over time.

u_i = Ki · ∫e(t)dt


**Effect:**
- ✅ Removes persistent error
- ✅ Reaches target exactly
- ❌ Slow response
- ❌ Can cause overshoot if too large

**Example:**
- If error persists for 5 seconds
- Integral accumulates: `∫e dt` grows
- Output increases until error = 0

---

### 3. Derivative (D) Term

**Purpose:** Predict and dampen oscillations.

u_d = Kd · de(t)/dt


**Effect:**
- ✅ Smooths response (less jerky)
- ✅ Reduces overshoot
- ✅ Improves stability
- ❌ Amplifies measurement noise

**Example:**
- If error is decreasing fast: `de/dt < 0`
- Output is reduced (prevents overshoot)
- Smooth, controlled approach to target

---

## Cascade (Dual-Loop) Control

### Why Two Loops?

In ACC, we need:
1. **Speed tracking** (comfort)
2. **Distance maintenance** (safety)

These can conflict! Cascade control solves this:

---

## **Priority: Headway (safety) > Cruise (comfort)**


### Architecture

```bash
   ┌─────────────────┐
   │  Cruise Error   │  e_cruise = v_set - v_ego
   │  e_cruise       │
   └────────┬────────┘
            │
      ┌─────▼──────┐
      │ Cruise PID │──→ u_cruise
      └─────┬──────┘
            │
   ┌────────▼───────────┐
   │  Headway Error      │  e_headway = d_desired - d_gap
   │  e_headway          │
   └────────┬────────────┘
            │
      ┌─────▼──────┐
      │ Headway PID│──→ u_headway
      └─────┬──────┘
            │
   ┌────────▼──────────┐
   │  Mode Selector    │
   │  IF headway active│
   │    use u_headway  │
   │  ELSE use u_cruise│
   └───────────────────┘
```


---

## Tuning Methodology: Ziegler-Nichols

### Manual Tuning Steps

**Step 1: P-Only Tuning**
- Set Ki = 0, Kd = 0
- Increase Kp until system oscillates
- Reduce Kp by 20-30%
- Note: `Kp_critical`

**Step 2: Add Integral**
- Increase Ki slowly
- Goal: zero steady-state error
- Watch for overshoot

**Step 3: Add Derivative**
- Increase Kd to dampen oscillations
- Improves stability
- Makes response smoother

---

## Performance Metrics

### Rise Time
Time for output to reach 90% of target.

> ↑ Kp → ↓ Rise time (faster but overshoots)
> ↑ Kd → ↑ Rise time (smoother but slower)


### Overshoot

How much output overshoots the target.

> ↑ Kp → ↑ Overshoot
> ↑ Kd → ↓ Overshoot (damping)


### Steady-State Error

Remaining error at final time.

> ↑ Kp → ↓ Error
> ↑ Ki → ↓ Error (integral eliminates)


### Settling Time

Time to stay within ±5% of target.

> ↑ Kd → ↓ Settling time (oscillations damped)

---

## Stability Margins

### Gain Margin
How much you can increase Kp before instability.
- Higher = more robust
- Target: > 2.0

### Phase Margin
Frequency response stability indicator.
- Target: 45-60° for comfortable control

---

## Real-World Considerations

### Measurement Noise
- Sensors have noise
- High Kd amplifies noise
- Filter sensor data to reduce this

### Actuator Saturation
- Max acceleration/braking limits
- PID output must be clipped
- Integral windup: reset integrator when saturated

### Time Delays
- Real vehicles have lag (engine response)
- Larger delays need lower gains
- Can cause instability

---

## ACC-Specific Notes

### Cruise Loop Tuning
- Prioritize **smooth** response
- Acceptable rise time: 5-8 seconds
- Low overshoot: < 10%
- Passenger comfort matters

### Headway Loop Tuning
- Prioritize **quick** response
- Acceptable rise time: < 2 seconds
- Safety critical
- Must handle emergency braking

### Cascade Strategy

```cpp
IF d_gap < d_desired:
Use stronger Kp_h (faster response)
Use higher Kd_h (smooth braking)
ELSE:
Use gentler Kp_c (comfort)
Use lower Kd_c (smoother acceleration)
```

---

## Further Reading

- Classic Control Theory: Ogata, "Modern Control Engineering"
- PID Tuning: Astrom & Hagglund, "Advanced PID Control"
- Vehicle Dynamics: Gillespie, "Fundamentals of Vehicle Dynamics"

---

## Quick Reference Table

| Gain | Effect ↑ | Effect ↓ | Use For |
|------|----------|----------|---------|
| **Kp** | Fast response, overshoot | Slow, stable | Base responsiveness |
| **Ki** | Eliminates error, overshoot | Steady error | Final accuracy |
| **Kd** | Smooth, damping | Slow, sluggish | Stability |






