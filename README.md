# Rock-Paper-Scissors (C Terminal Version)

![C99 Badge](https://img.shields.io/badge/C-Standard%20C99-blue)

---

## 📜 Description

A simple **Rock-Paper-Scissors** game implemented in **pure C99**.

- Play against the computer in a terminal.
- User inputs are loosely parsed: you can type random text, and the game extracts the first valid number (`1`, `2`, `3`, or `0`).
- Invalid inputs cause you to **lose one point**, adding a "rage" factor to the gameplay.
- The computer uses **/dev/urandom** for generating random moves.

This project focuses on **simplicity**, **minimalism**, and a **rage-inducing penalty system** when mistakes are made.

---

## 🎮 How to Play

1. Run the compiled program.
2. Follow the instructions:
    - **1** for Rock
    - **2** for Paper
    - **3** for Scissors
    - **0** to Exit the Game
3. Winning earns a point.
4. Invalid inputs **lose you a point**.
5. At the end, the winner is displayed.

---

## ⚙️ How to Compile

Make sure you have a C compiler installed (`clang` recommended).

```bash
clang -std=c99 game.c -o game
