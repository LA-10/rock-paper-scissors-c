# 🤝 Contributing to Rock-Paper-Scissors-C

Thank you for considering contributing to this project! Whether you're here to report a bug, suggest a feature, improve the code, or help with documentation, you're very welcome.

---

## 📜 Guidelines

### 1. Be Respectful
We're all here to learn — keep feedback constructive and discussions friendly.

### 2. Use Clear Commits
Try to write clear and concise commit messages like:
```
feat: add input validation for username
fix: correct logic in winner() function
refactor: move player logic into separate file
```

### 3. Match the Code Style
- Follow C99 conventions
- Indent with 4 spaces
- Keep functions short and focused

---

## 📁 Project Structure
```
├── src/                # All source code (.c)
├── include/            # Header files (.h)
├── assets/             # ASCII splash screen / round banners
├── save/               # Game history storage (runtime only)
├── build/              # CMake build folder (ignored by Git)
├── CMakeLists.txt      # Build config
├── LICENSE             # Project license
├── README.md           # Project intro
├── ROADMAP.md          # Feature goals
```

---

## ✅ Submitting a Change

1. **Fork the repository**
2. **Clone your fork**
3. **Create a branch** for your change:
```bash
git checkout -b fix-bug-name
```
4. **Commit clearly** and push:
```bash
git commit -m "fix: correct player name logic"
git push origin fix-bug-name
```
5. **Open a pull request** on GitHub

---

## 💡 Good First Ideas
- Refactor functions to improve clarity
- Add a simple test file
- Improve README formatting or visuals
- Add feature flags for rounds, rage mode, etc.

Thanks again for contributing — enjoy the project! ✨
