# 🗺️ Project Roadmap

This document outlines the planned development of the Rock-Paper-Scissors C terminal game.

---

## ✅ v1.0 (Released)

- Basic Rock-Paper-Scissors game logic.
- Random move generation via `/dev/urandom`.
- Rage mechanic (lose a point on invalid input).
- Clean C99 code structure.

---

## ✅ v1.5 (Released)

- Save game summaries to `save/game_history.txt`.
- Player name input and validation.
- Basic ASCII splash screen.
- Modular separation of gameplay and I/O logic.
- Optional round-based format introduced.

---

## ✅ v1.7 (Released)

- Round system formalized (best-of-3 per round).
- New ASCII art formatting for round headers.
- Persistent user identity (username stored between runs).
- Continue / Restart / Quit prompt at launch.
- Replaced Makefile + run.sh with CMake build system.
- Improved structure, fixed realloc edge cases, better error handling.

---

## ✅ v2.0 (Released)

- Fully track number of rounds won/lost.
- Prepare for difficulty selection and unlocks.
- UI improvements in text formatting.
- Streamline code with reusable components (e.g., `name_manager`, `file_io`).
- Improved structure, fixed memory leaks, better error handling.
- Difficulty levels (easy/medium/difficult).

## ✨ Future Minor Versions

- **v2.2**: AI learns from user choices after 10+ rounds.
- **v2.5**: Local multiplayer support.

---

## ✨ Future Major Version

- **v3.0**: GUI implementation using SDL2 or Nuklear.

---

## 📅 Last Updated

April 29, 2025
