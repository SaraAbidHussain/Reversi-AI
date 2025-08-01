# Reversi Game (Console-based C++)

🎮 A simple console-based **Reversi (Othello)** game written in C++.  
Supports:
- **Human vs Human** mode
- **Human vs AI** mode

---

## 📂 Features

- 8x8 game board initialized from a file (`board.txt`)
- Color-coded terminal display for X and O
- Move validation and flipping mechanism according to Reversi rules
- Basic AI opponent logic
- Winner announcement and piece count
- Uses file handling to read and initialize the game board

---

## 🧠 Game Rules (Simplified)

- Players take turns placing pieces (X or O).
- A move is valid only if it flips at least one of the opponent’s pieces.
- Flipping occurs in all 8 directions (horizontal, vertical, diagonal).
- The game ends when the board is full.
- The player with more pieces on the board wins.

---

## 🛠️ How to Run

### 🖥️ Requirements
- C++ Compiler (e.g. g++, MSVC)
- Visual Studio or any IDE supporting C++

### 🧾 Build & Run (Using VS Code / Terminal)
```bash
g++ reversi.cpp -o reversi
./reversi
