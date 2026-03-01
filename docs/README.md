# 📚 Documentation

Welcome to the ACC (Adaptive Cruise Control) documentation folder.

## Quick Navigation

### 🧠 Theory & Concepts
- **[pid_theory.md](pid_theory.md)** – Learn PID control fundamentals
  - What is PID? (P, I, D terms explained)
  - Cascade control architecture
  - Tuning methodology
  - Performance metrics

### 🔬 Physics & Models
- **[physics_model.md](physics_model.md)** – Vehicle dynamics equations
  - Longitudinal dynamics
  - Kinematic integration
  - Acceleration & velocity constraints
  - Friction model

### 🧪 Practical Tuning
- **[tuning_guide.md](../tuning_guide.md)** – Step-by-step PID tuning
  - Test procedures (speed step, lead braking)
  - Adjustment table
  - Validation checklist
  - Common issues & fixes

---

## Getting Started

### For Beginners
1. Start with **pid_theory.md** (30 min read)
2. Understand **physics_model.md** (15 min read)
3. Follow **tuning_guide.md** to tune your own gains (1-2 hours)

### For Implementers
1. Review **ARCHITECTURE.md** in project root
2. Check **physics_model.md** for equations
3. Use **tuning_guide.md** for validation

---

## Key Concepts at a Glance

### PID Control

u = Kp·e + Ki·∫e·dt + Kd·de/dt

- **P (Proportional):** Immediate response
- **I (Integral):** Eliminates steady-state error
- **D (Derivative):** Damping, smoothness

### ACC Dual Loop

Priority: Headway (Safety) > Cruise (Comfort)

- **Cruise Loop:** Tracks target speed (Kp_c, Ki_c, Kd_c)
- **Headway Loop:** Maintains safe distance (Kp_h, Ki_h, Kd_h)

### Vehicle Dynamics

a = u_acc - c_drag·v² - μ·g

- u_acc = Control output
- c_drag = Aerodynamic drag
- μ = Road friction coefficient

---

## Typical Gain Values

| Loop | Kp | Ki | Kd |
|------|----|----|-----|
| **Cruise** | 0.4 | 0.05 | 0.01 |
| **Headway** | 0.6 | 0.08 | 0.02 |

*These are starting points. Tune based on your test results.*

---

## File Structure

```
docs/
├── README.md ← You are here
├── pid_theory.md ← PID fundamentals
├── physics_model.md ← Vehicle dynamics
├── tuning_guide.md ← Step-by-step tuning
└── images/ ← (Optional) Diagrams & plots
├── pid_response.png
├── system_architecture.png
└── demo.gif
```

---

## Quick Links

- **Main README:** [../README.md](../README.md)
- **Architecture:** [../ARCHITECTURE.md](../ARCHITECTURE.md)
- **Source Code:** [../src/](../src/)
- **Build Instructions:** [../README.md#quick-start](../README.md#quick-start)

---

## Common Questions

### Q: Where do I start?
**A:** Read pid_theory.md first, then follow tuning_guide.md

### Q: What are the typical gains?
**A:** See "Typical Gain Values" table above. Adjust based on your tests.

### Q: How do I validate my tuning?
**A:** Follow the test procedures in tuning_guide.md (speed step, lead braking, friction changes)

### Q: Can I tune both loops independently?
**A:** Yes! Tune cruise first (Kp_c, Ki_c, Kd_c), then headway (Kp_h, Ki_h, Kd_h)

---

## Further Resources

- **PID Control Book:** Åström & Hägglund, "Advanced PID Control"
- **Control Theory:** Ogata, "Modern Control Engineering"
- **Vehicle Dynamics:** Gillespie, "Fundamentals of Vehicle Dynamics"

---

