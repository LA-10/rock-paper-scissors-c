# 🪨 Rock Paper Scissors - C Version ![version](https://img.shields.io/badge/version-1.7-blue) ![release](https://img.shields.io/github/v/release/LA-10/rock-paper-scissors-c?label=release)

A terminal-based Rock-Paper-Scissors game written in clean, modular C99. Designed for simplicity, learning, and extensibility.

---

## 🎮 Features

- Classic Rock-Paper-Scissors terminal game
- Rage mechanic: user loses a point on invalid input
- Round system: game is structured into best-of-3 rounds
- ASCII splash and round headers
- Personalized player names
- Continue / Restart / Quit prompt at startup
- Game history logging (persistent across sessions)
- Username persistence (saved and reloaded from file)
- Rewritten with **CMake** instead of Makefiles for building
- Modular codebase split into `main`, `game`, and `players` logic

---

## 🧑‍💻 How to Compile

```bash
# Clone the repository
git clone https://github.com/LA-10/rock-paper-scissors-c.git
cd rock-paper-scissors-c

# Build with CMake
cmake -S . -B build
cmake --build build

# Run the game
./build/rock-paper-scissors-c
```

---

## 📂 Directory Structure

```
rock-paper-scissors-c/
├── .vscode/              # Editor-specific settings (optional)
├── assets/               # ASCII splash art
├── build/                # CMake build output (ignored by git)
├── include/              # Header files (game.h, players.h)
├── src/                  # Source files (main.c, game.c, players.c)
├── .gitignore            # Git ignored files config
├── CMakeLists.txt        # Build configuration for CMake
├── CONTRIBUTING.md       # Contribution guidelines
├── LICENSE               # MIT license
├── README.md             # Project overview and instructions
├── ROADMAP.md            # Feature roadmap and version plans
└── run.sh                # (Deprecated) Old build/run script
```

---

## 📖 How to Play

```text
Type the following number:
* Rock     (1)
* Paper    (2)
* Scissors (3)
* Exit     (0)
```

- You will be asked to enter your name the first time you play
- You can resume your progress by selecting **Continue**
- Every 3 matches, the round ends and the scoreboard is updated
- At the end of each round, you can Continue, Restart, or Quit

---

## 🚣️ Project Roadmap
See [ROADMAP.md](./ROADMAP.md) for version history and future plans.

---

## 🧾 License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.

---

## 🧕‍♂️ Contributing

See [CONTRIBUTING.md](./CONTRIBUTING.md) if you'd like to suggest changes, improvements, or report bugs. Beginners welcome!
