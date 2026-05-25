🧠 Quiz Game (C++ Console Application)
📌 About the Project

Quiz Game is a console-based application developed in C++ that simulates an interactive quiz experience. The project is designed to practice and demonstrate core programming concepts such as functions, file handling, arrays, and structured problem-solving.

The game allows players to test their knowledge across multiple categories and difficulty levels while tracking scores and maintaining a persistent leaderboard.

🎮 Features
📚 Multiple Quiz Categories

Players can select from different knowledge domains:

Computer Science
Science
Sports
History

Each category contains a separate question bank stored in external files.

🎯 Difficulty-Based Gameplay

The game supports three difficulty levels:

Easy
Medium
Hard

Each level affects scoring rules and question difficulty.

🧠 Interactive Quiz System
Each session contains a fixed number of questions (10)
Questions are randomly selected from files
Timer-based answering system increases challenge
Input validation ensures smooth gameplay
🧩 Lifeline System

To assist players during gameplay, four lifelines are available:

50:50 → Removes two incorrect options
Skip → Skips current question without penalty
Swap → Replaces question with another
Time Boost → Adds extra time for answering

Each lifeline can be used only once per game.

🏆 Scoring System

The scoring system is based on difficulty level:

Easy: +10 correct, -2 incorrect
Medium: +15 correct, -3 incorrect
Hard: +20 correct, -5 incorrect
🔥 Bonus System
3 correct answers in a row → bonus points
5 correct answers in a row → higher bonus reward

This encourages consistent performance.

🥇 Leaderboard System
Stores top 5 high scores
Saves player name, score, difficulty, and date/time
Data is stored using file handling for persistence
Automatically updates when a new high score is achieved
📊 Review Mode

After completing a quiz, players can:

View incorrectly answered questions
Compare their answers with correct ones
Learn from mistakes to improve performance
📁 Data Persistence

The game uses external files to store and manage data:

computer.txt → Computer Science questions
science.txt → Science questions
sports.txt → Sports questions
history.txt → History questions
high_scores.txt → Leaderboard data
quiz_logs.txt → Game history logs
🧠 Concepts Used

This project demonstrates practical implementation of:

Functions and modular programming
Arrays and structured data handling
File input/output (read & write operations)
Random number generation
Conditional logic and loops
Game loop design
Input validation techniques
Basic system design for a console game
🕹️ How the Game Works
User enters their name
Selects a category
Chooses difficulty level
Answers a series of timed questions
Uses lifelines strategically if needed
Final score is calculated
Results are saved in leaderboard
Review mode displays mistakes
🚀 Future Improvements

This project can be expanded with:

Graphical user interface (GUI version)
Online multiplayer quiz mode
Advanced question editor system
Category expansion system
Sound effects and animations
Global online leaderboard
👨‍💻 Purpose of the Project

This project was built to strengthen understanding of:

Core C++ programming concepts
File handling and data persistence
Logical thinking and problem decomposition
Building structured console-based applications
📌 Note

This project is designed as a learning-based application and can be extended into a full-featured quiz platform with additional enhancements.

Enjoy testing your knowledge and competing for the top spot on the leaderboard!
