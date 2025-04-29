#ifndef GAME_H
#define GAME_H

// Global score and round tracking
extern int user_points;
extern int computer_points;
extern int round_number;

// Displays the splash screen and prompts for the player's name.
char *intro(void);

// Converts an integer (1-3) to its corresponding move name and prints it.
void conversion(int num);

// Prompts the player to make a move and returns their choice.
char play(void);

// Generates a random move for the computer (1-3).
int computer(void);

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
void display_winner(int result, char *name);

// Reads input from stdin and returns the first valid digit ('1', '2', '3', '0'), or 'e' if invalid.
char read_stdin(void);

// Displays the current scores of both player and computer.
void display_points(char *name);

// Saves a summary of the game to "save/game_history.txt" in append mode.
// Includes the player name, score, winner, and timestamp.
// Parameters:
//   player_name - the name of the user (must be a valid C string)
//   user_points - the number of points the player scored
//   computer_points - the number of points the computer scored
void save_game_summary(const char *player_name, int user_points, int computer_points);

// Displays final summary and winner, and saves game results to file.
void end_game_msg(char *name);

#endif // GAME_H
