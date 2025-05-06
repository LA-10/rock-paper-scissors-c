#include <stdbool.h>

#ifndef GAME_H
#define GAME_H

#define MAX_NAME_SIZE 100

typedef int (*play_fn)(void);

// Global score and round tracking
extern int user_points;
extern int computer_points;
extern int round_number;

extern char name[MAX_NAME_SIZE];

// Displays the splash screen and prompts for the player's name.
play_fn intro(void);

// Generates a random move for the computer between 1 and 3 using /dev/urandom.
// Also prints the move to the console.
int computer(void);

// Prompts the user for a move input and returns a char corresponding to:
// '1' for Rock, '2' for Paper, '3' for Scissors, or '0' to exit.
char play(void);

// Converts an integer (1-3) to its corresponding move name and prints it.
void conversion(int num);

// Generates a random move in a more non-intelligent way
int easy_play(void);

// Generates a random move for the computer (1-3).
int medium_play(void);


// A more intelligence implementation of medium play that learns player behavior
// requires: round_number > 10
int difficult_play(void);

// Displays the round number using ASCII art and asks the player to continue or exit.
int round_msg(void);

// Determines the winner based on the player and computer choices.
// Returns:
//   0 -> Draw
//   1 -> Player wins
//   2 -> Computer wins
int winner(int user, int computer);

// Prints an ASCII banner from a file, with an optional subtitle.
void print_ascii_screen(const char *filepath, const char *subtitle);

// Displays who won the individual game and updates scores.
void display_winner(int result);

// Reads input from stdin and returns the first valid digit ('1', '2', '3', '0'), or 'e' if invalid.
char read_stdin(void);

// Displays the current scores of both player and computer.
void display_points(void);

// Saves a summary of the game to "save/game_history.txt" in append mode.
// Includes the player name, score, winner, and timestamp.
// Parameters:
//   player_name - the name of the user (must be a valid C string)
//   user_points - the number of points the player scored
//   computer_points - the number of points the computer scored
void save_game_summary(void);

// Displays final summary and winner, and saves game results to file.
void end_game_msg(void);

#endif // GAME_H
