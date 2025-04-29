# Rock-Paper-Scissors C Project

![Version](https://img.shields.io/badge/version-v1.5-blue.svg)
![Status](https://img.shields.io/badge/status-released-brightgreen)

> A simple terminal-based Rock-Paper-Scissors game evolving step-by-step.

---

## 🌟 About the Project

This project implements a simple yet expandable Rock-Paper-Scissors game in C, focusing on clean modular design, user input validation, and gradual feature expansions.

Originally built as a simple rage-game mechanic, the project is now evolving into a more polished, session-based experience.

---

## 🛠️ How to Compile and Run

### Option 1: Recommended (Using the provided script)

```bash
./run.sh
```

This script will:
- Clean previous builds (`make clean`)
- Compile the project
- Automatically run the executable (`./game`)

---

### Option 2: Manual Compilation

```bash
make clean
make
./game
```

(Ensure you have `clang` or `gcc` and `make` installed.)

---

## ✨ Features (v1.5)

- Best-of-3 rounds system.
- User-defined player names.
- Game summary saved automatically (`save/game_history.txt`).
- Splash screen and round banners (ASCII art).
- Rage mechanic (lose a point on invalid input).
- Clear, structured output formatting.
- Modular, clean C99 codebase (`src/`, `include/`, `save/`, `assets/` folders).

---

## 🚀 Upcoming in v1.7

- Persistent username system.
- Option to continue or reset user profile at startup.
- Improved session management across games.

See full details in the [ROADMAP.md](./ROADMAP.md).

---

## 📜 Project Structure

```text
rock-paper-scissors-c/
├── assets/             # ASCII art (splash screen, round banners)
├── save/               # Game history, last user save
├── src/                # Source code files (.c)
├── include/            # Header files (.h)
├── run.sh              # Build and run automation script
├── Makefile            # Makefile for compilation
├── README.md           # This file
├── ROADMAP.md          # Project planning and future goals
```

---

## 📋 Requirements

- C compiler supporting C99 (tested with `clang`)
- Unix-like environment (Linux, macOS, or WSL)

---

## 🗓️ Last Updated

April 28, 2025
