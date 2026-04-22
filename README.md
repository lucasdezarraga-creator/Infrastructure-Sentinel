# Infrastructure Sentinel v1.0 🛰️

A real-time, terminal-based power grid monitoring dashboard built in C. 

## 🚀 Overview
Infrastructure Sentinel simulates a high-stakes Human-Machine Interface (HMI) for managing electrical grid loads. It features stochastic telemetry drift, random power surges, and hardware-inspired command rate limiting.

## 📸 Preview
The dashboard:
<img width="645" height="326" alt="InfrastructureSentielDashboard" src="https://github.com/user-attachments/assets/bc0a47a7-f56c-40bb-ba4d-40e9c81c3d1b" />
*Custom cyan/blue interface designed for high-fidelity industrial monitoring.*

## 🛠️ Key Technical Features
- **Real-Time Telemetry:** Biased random-walk algorithm simulating 0.5s refresh intervals.
- **Hardware Cooldowns:** Implemented `time_t` logic to simulate physical grid stabilization latency.
- **Robust UI:** Dynamic terminal scaling and signal handling via PDCurses/ncurses.
- **Zero-Dependency Build:** Configured for static linking to ensure portability.

## 📄 Documentation
For a full deep-dive into the technical hurdles (WinMain entry point conflicts, linker flags, and spatial alignment logic), check out the [Full Project Documentation (PDF)](documentation.pdf).

## ⌨️ Controls
- `1-2`: Balance specific nodes (3s cooldown)
- `R`: Full system reboot (10s cooldown)
- `Q`: Safe shutdown (ncurses cleanup)
