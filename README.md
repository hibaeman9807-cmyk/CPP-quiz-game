# 🧠 Quiz Game (C++ Console Application)

A robust, interactive console-based quiz application built in C++ that simulates a dynamic gaming experience. This project demonstrates core programming principles, structured problem-solving, and file-based data persistence. 

Players can test their knowledge across multiple categories and difficulty levels, utilize strategic lifelines, earn streak bonuses, and compete for a spot on the persistent leaderboard.

---

## 🎮 Key Features

### 📚 Multiple Quiz Categories
Players can choose from four distinct knowledge domains. Each category pulls from a dedicated external question bank:
* Computer Science
* Science
* Sports
* History

### 🎯 Difficulty-Based Gameplay
The game features three difficulty tiers, each with tailored scoring mechanics to match the challenge level:
* **Easy:** +10 for correct, -2 for incorrect
* **Medium:** +15 for correct, -3 for incorrect
* **Hard:** +20 for correct, -5 for incorrect

### 🧠 Interactive Quiz System & Lifelines
* **Dynamic Sessions:** Each game consists of 10 questions randomly selected from the files.
* **Timer-Based:** Adds an extra layer of challenge to answering.
* **Input Validation:** Ensures robust, crash-free execution during gameplay.
* **Strategic Lifelines (Single-Use):**
    * `50:50` — Eliminates two incorrect options.
    * `Skip` — Skips the current question with zero penalty.
    * `Swap` — Replaces the current question with a fresh one.
    * `Time Boost` — Grants extra time to solve the question.

### 🔥 Performance Bonuses & Leaderboard
* **Streak Rewards:** Achieve 3 correct answers in a row for a standard bonus, or 5 in a row for a higher reward.
* **Persistent Leaderboard:** Automatically tracks and displays the top 5 high scores (storing player name, score, chosen difficulty, and timestamps) using local file updates.

### 📊 Review Mode
Post-game analysis allows players to inspect any questions they missed, compare their inputs with the correct answers, and learn from their mistakes.

---

## 📁 File Structure & Data Persistence

The application relies on file input/output (I/O) streams to manage data dynamically without a traditional database:

| File Name | Purpose |
| :--- | :--- |
| `computer.txt` | Holds the Computer Science question bank. |
| `science.txt` | Holds the General Science question bank. |
| `sports.txt` | Holds the Sports question bank. |
| `history.txt` | Holds the History question bank. |
| `high_scores.txt`| Maintains the top 5 leaderboard data. |
| `quiz_logs.txt` | Records historical game execution logs. |

---

## 🧠 Core Concepts Demonstrated

This project serves as a practical implementation of fundamental computer science and software development practices:
* **Modular Programming:** Clean code architecture using functions to separate game logic, file handling, and UI rendering.
* **File I/O Operations:** Reading structured text files for questions and writing/updating data for high scores and logs.
* **Data Structures:** Using arrays to manipulate session questions, choices, and user stats efficiently.
* **Game Loop Design:** Managing state transitions seamlessly from user login to gameplay, scoring, and review.
* **Algorithmic Logic:** Implementing random number generation for question selection and handling conditional streaks.

---

## 🕹️ How It Works

1. **Setup:** The player inputs their name, then selects a category and difficulty level.
2. **Gameplay:** The engine serves 10 timed, randomized questions. The player can activate lifelines strategically.
3. **Evaluation:** The system tracks correct/incorrect responses and active streaks to calculate the final score.
4. **Persistence:** The engine checks if the score qualifies for the top 5 leaderboard and updates `high_scores.txt`.
5. **Review:** The player can review mistakes before safely exiting back to the terminal.

---

## 🚀 Future Improvements

To expand this application beyond the console environment, future updates may include:
* **Graphical User Interface (GUI):** Transitioning the project from the terminal to a sleek desktop application using a C++ GUI framework (e.g., Qt or SFX).
* **Online Components:** Implementing global online leaderboards and a multiplayer quiz mode using socket programming.
* **Advanced Editor:** Creating a built-in admin panel to add, edit, or delete questions directly through the app interface.
* **Audio/Visuals:** Integrating background music, countdown sound effects, and animations.

---

## 👨‍💻 Purpose of the Project

This application was developed as a learning-focused project to bridge academic theory with practical application. It highlights the power of structured problem decomposition, building robust error-resistant console architectures, and establishing reliable file-handling mechanisms in native C++.

Enjoy testing your knowledge and competing for the top spot on the leaderboard!
