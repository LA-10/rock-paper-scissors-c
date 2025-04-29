#ifndef PLAYERS_H
#define PLAYERS_H

// Assigns the default name "USER" to the given buffer and returns it.
// Requires: 'name' must be a valid pointer to a malloc'd or realloc'd buffer.
char *assign_user_name(char *name);

// Prompts the user for a move input and returns a char corresponding to:
// '1' for Rock, '2' for Paper, '3' for Scissors, or '0' to exit.
char play(void);

// Generates a random move for the computer between 1 and 3 using /dev/urandom.
// Also prints the move to the console.
int computer(void);

// Reads a string from stdin into a dynamically resizable buffer.
// Performs basic validation and retry logic.
// rename_tries - tracks how many invalid attempts have been made.
// name - pointer to an allocated char buffer.
// max_len - current capacity of the buffer.
// Returns the pointer to the finalized name string.
char *read_str(int rename_tries, char *name, int max_len);

#endif // PLAYERS_H
