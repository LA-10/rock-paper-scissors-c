#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <game.h>

// Assigns default user name "USER" to the provided buffer
char *assign_user_name(char *name) {
    name = realloc(name, (strlen("USER") + 1) * sizeof(char));
    if (!name) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(name, "USER");
    name[4] = '\0';
    return name;
}

// Generates and returns a random computer move between 1 and 3
int computer(void) {
    int min = 1;
    int max = 3;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int rd_num;
    int bytes_read = read(fd, &rd_num, sizeof(rd_num));
    if (bytes_read != sizeof(rd_num)) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    rd_num = rd_num % (max - min + 1) + min;
    printf("Computer played ");
    conversion(rd_num);
    return rd_num;
}

// Forward declaration for recursive use
char *read_str(int rename_tries, char *name, int max_len);

// Handles invalid name cases by prompting retry or assigning default
static char *invalid_name(char *name, int max_len, int rename_tries) {
    printf("This name is not allowed, your name has to include integer, symbols, or letter combinations.\n");
    printf("Type 1 to go with the default name (USER), or type 2 to try again.\n");

    char input = read_stdin();
    if (input == '1') {
        return assign_user_name(name);
    } else if (input == '2') {
        max_len = 1;
        name = realloc(name, sizeof(char) * max_len);
        if (!name) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        if (rename_tries >= 3) {
            printf("Repeated invalid name combinations, proceeding with default name (USER)\n");
            return assign_user_name(name);
        } else {
            printf("Write your name: ");
            return read_str(rename_tries + 1, name, max_len);
        }
    } else {
        printf("Invalid input, proceeding with the name \"USER\"\n");
        return assign_user_name(name);
    }
}

// Reads a name string from stdin and validates it
char *read_str(int rename_tries, char *name, int max_len) {
    name[0] = '\0';
    int len = 0;
    char letter = '\0';

    while (1 == scanf("%c", &letter)) {
        if (letter == '\n') break;

        if (len == max_len) {
            max_len *= 2;
            name = realloc(name, max_len * sizeof(char));
            if (!name) {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
        }

        if (letter >= '!' && letter <= '~') {
            name[len++] = letter;
        }
    }

    if (!name[0]) {
        return invalid_name(name, max_len, rename_tries);
    }

    name = realloc(name, (len + 1) * sizeof(char));
    if (!name) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    name[len] = '\0';
    return name;
}

// Prompts user to play and returns the move choice
char play(void) {
    printf("Type the following number:\n* Rock (1)\n* Paper (2)\n* Scissors (3)\n* Exit (0) ");
    char user = read_stdin();
    return user;
}
