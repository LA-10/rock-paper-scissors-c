#ifndef PLAYERS_H
#define PLAYERS_H

// Assigns the default name "USER" to the given buffer and returns it.
// Requires: 'name' must be a valid pointer to a malloc'd or realloc'd buffer.
char *assign_user_name(void);



// Reads a string from stdin
// Performs basic validation and retry logic.
// Returns the pointer to the finalized name string.
char *read_str(void);

bool load_saved_username(void);

#endif // PLAYERS_H
