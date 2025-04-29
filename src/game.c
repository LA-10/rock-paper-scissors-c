#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h> 
#include <time.h>
#include "players.h"

/*
    How to play the game:
    1 - Rock
    2 - Paper
    3 - Scissors
*/

// Global game state
int user_points = 0;
int computer_points = 0;
int round_number = 1;

// Input Utilities
char read_stdin(void) {
    char buff[10];
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Input error!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++) {
        if (buff[i] == '1' || buff[i] == '2' || buff[i] == '3' || buff[i] == '0') {
            return buff[i];
        }
    }
    return 'e';
}

// Display ASCII art splash or round banner
void print_ascii_screen(const char *filepath, const char *subtitle) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror(filepath);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    if (subtitle != NULL) {
        printf("\n%s\n", subtitle);
        printf("=========================================\n\n");
    }
}

// Startup name prompt
char *intro(void) {
    print_ascii_screen("assets/splash.txt", "Welcome to the simple Rock-Paper-Scissors Game!\n");
    int max_len = 1;
    char *name = malloc(sizeof(char) * max_len);
    if (!name) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    int rename_tries = 0;
    printf("Write your name: ");
    read_str(rename_tries, name, max_len);
    printf("Welcome %s to the game! Let's begin!\n", name);
    return name;
}

// Translate int to R/P/S string
void conversion(int num) {
    if (num == 1) {
        printf("ROCK\n");
    } else if (num == 2) {
        printf("PAPER\n");
    } else {
        printf("SCISSORS\n");
    }
}

// Game logic: decide winner
int winner(int user, int computer) {
    if (user > 3 || user <= 0) {
        printf("INVALID INPUT: losing one point\n");
        return -1;
    }
    if (user == computer) return 0;
    if ((user == 1 && computer == 3) ||
        (user == 2 && computer == 1) ||
        (user == 3 && computer == 2)) {
        return 1;
    }
    return 2;
}

// Update and show point winner
void display_winner(int result, char *name) {
    if (result == 0) {
        printf("This round is a draw!\n");
    } else if (result == 1) {
        printf("%s scored a point!!\n", name);
        user_points++;
    } else if (result == 2) {
        printf("The computer scored a point!!\n");
        computer_points++;
    } else {
        user_points--;
    }
}

// Display current points
void display_points(char *name) {
    assert(name);
    printf(" %s: %d Point%s\n", name, user_points, user_points == 1 ? "" : "s");
    printf(" Computer: %d Point%s\n", computer_points, computer_points == 1 ? "" : "s");
}

// Round menu
int round_msg() {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "ROUND %d", round_number);
    print_ascii_screen("assets/round.txt", buffer);
    round_number++;
    printf("Please choose one of the following options:\n");
    printf("* Continue (1)\n* Exit without saving (2)\n* Exit and save (3) ");
    char input = read_stdin();
    if (input == '2') return 2;
    if (input == '3') return 3;
    return 1;
}

// Save summary to file
void save_game_summary(const char *player_name, int user_points, int computer_points) {
    FILE *f = fopen("save/game_history.txt", "a");
    if (!f) {
        perror("fopen");
        return;
    }
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strcspn(time_str, "\n")] = '\0';

    fprintf(f, "Date: %s\n", time_str);
    fprintf(f, "Player: %s\n", player_name);
    fprintf(f, "User Score: %d | Computer Score: %d\n", user_points, computer_points);
    if (user_points > computer_points) {
        fprintf(f, "Winner: %s\n", player_name);
    } else if (user_points < computer_points) {
        fprintf(f, "Winner: Computer\n");
    } else {
        fprintf(f, "Result: Draw\n");
    }
    fprintf(f, "-------------------------\n");
    fclose(f);
}

// End-of-game message
void end_game_msg(char *name) {
    assert(name);
    printf("GAME SUMMARY:\n");
    display_points(name);
    printf("**********************  WINNER  **********************\n");
    printf("                        ");
    if (user_points == computer_points) {
        printf("NONE, the game is a draw\n");
    } else if (user_points > computer_points) {
        printf("%s\n", name);
    } else {
        printf("COMPUTER\n");
    }
}
