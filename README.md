# Wordle Solver

This project is a C++ program designed to help users solve the daily ‘Wordle’ game.  
The program minimizes the number of guesses needed to solve Wordle by using advanced string comparison algorithms to recommend the most helpful words.

## Features
- Jaccard Similarity: Computes the Jaccard similarity coefficient between two strings to measure their similarity.
- Sorting by Similarity: Sorts a list of words based on their average similarity to other words.
- Sorting by Common Letters: Sorts words based on the number of common letters they share with other words.
- Word Filtering: Filters possible words based on the feedback (green, yellow, gray) from previous guesses.

## Getting Started

Prerequisites
- A C++ compiler that supports C++11 or later (e.g., g++).
- A file named words.txt containing a list of valid Wordle words, each on a new line.

## Compilation

To compile the program, use the following command:  
```bash
g++ solver.cpp -o solver
```

To run the compiled program, use the following command:  
```bash
./solver
```

Usage
1. Run the program using the command above.
2. The program will prompt you to enter your guesses and the corresponding Wordle output.
3. Enter your guesses and feedback in the following format:
- Guess: A 5-letter word you want to guess.
- Wordle output: A string of 5 characters representing the feedback, where:
- g means the letter is in the correct position (green).
- y means the letter is in the word but in the wrong position (yellow).
- x means the letter is not in the word (gray).

Example:  
```
Enter guess 1: crane  
Enter Wordle output (g/y/x): gyxxy
```

4. The program will filter and sort the possible words based on your input and recommend the next best guesses.
5. Repeat the process until you solve the Wordle.
