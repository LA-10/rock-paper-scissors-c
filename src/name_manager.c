#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <file_io.h>
#include <name_manager.h>
// Assigns default user name "USER" to the global buffer
char *assign_user_name(void) {
    strcpy(name, "USER");
    return name;
}

// Handles invalid name cases by prompting retry or assigning default
static char *invalid_name(int rename_tries) {
    printf("This name is not allowed. Your name must include letters, digits, or symbols.\n");
    printf("Type 1 to go with the default name (USER), or type 2 to try again.\n");

    char input = read_stdin();
    if (input == '1') {
        return assign_user_name();
    } else if (input == '2') {
        if (rename_tries >= 3) {
            printf("Too many invalid attempts. Proceeding with default name (USER).\n");
            return assign_user_name();
        } else {
            printf("Write your name: ");
            return read_str();
        }
    } else {
        printf("Invalid input. Proceeding with default name (USER).\n");
        return assign_user_name();
    }
}

char *read_str(void) {
    while (1) {
        name[0] = '\0';
        int rename_tries = 0;
        int len = 0;
        char letter = '\0';

        while (1 == scanf("%c", &letter)) {
            if (letter == '\n') break;

            if (len >= MAX_NAME_SIZE - 1) {
                printf("Name cannot exceed %d characters. Please try again.\n", MAX_NAME_SIZE - 1);
                rename_tries++;
                // Flush rest of input
                while (letter != '\n' && scanf("%c", &letter) == 1);
                len = 0;
                break;  // Return to top of outer loop
            }

            if (letter >= '!' && letter <= '~') {
                name[len++] = letter;
            }
        }

        name[len] = '\0';

        if (len == 0) {
            return invalid_name(rename_tries);
        }

        return name;
    }
}


// Loads the saved username into the global `name` buffer.
// Returns true on success, false otherwise.
bool load_saved_username(void) {
    FILE *username_file = fopen("save/username.txt", "r");
    if (!username_file) {
        perror("fopen");
        return false;
    }

    char buffer[MAX_NAME_SIZE];
    if (!fgets(buffer, sizeof(buffer), username_file)) {
        fprintf(stderr, "Could not read username.\n");
        fclose(username_file);
        return false;
    }

    buffer[strcspn(buffer, "\n")] = '\0';  // remove newline

    if (strlen(buffer) + 1 > MAX_NAME_SIZE) {
        fprintf(stderr, "Username is too long.\n");
        fclose(username_file);
        return false;
    }

    strcpy(name, buffer);  // safe copy into pre-allocated buffer
    fclose(username_file);
    return true;
}