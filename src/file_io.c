#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h> 
#include <time.h>
#include <stdbool.h>
#include "name_manager.h"
#include "file_io.h"
#include <fcntl.h>
#include <unistd.h>
#include <Python.h>


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

char name[MAX_NAME_SIZE];

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


// Prompts the user for a new username, saves it, and resets game history.
// Returns true on success.
static bool reset_game(void) {
    remove("save/username.txt");
    remove("save/game_history.txt");
    remove("save/game_moves.txt");
    remove("save/round_number.txt");

    round_number = 1;


    int rename_tries = 0;
    printf("Write your name: ");
    read_str();

    printf("Welcome %s to the game! Let's begin!\n", name);

    FILE *f = fopen("save/username.txt", "w");
    if (!f) {
        perror("fopen");
        return false;
    }

    fprintf(f, "%s\n", name);
    fclose(f);

    return true;
}

static int get_round_number() {
    FILE *f_rnd = fopen("save/round_number.txt", "r");
    if (!f_rnd) {
        // If file cannot be opened, reset the game
        reset_game();
        return -1;
    }

    // Try reading the round number as an integer
    if (fscanf(f_rnd, "%d", &round_number) != 1) {
        // If the round number cannot be read, reset the game
        fclose(f_rnd);
        reset_game();
        return -1;
    }

    fclose(f_rnd);
    
    return 0;  // Successfully read the round number
}


// Startup entry point for name logic.
// Displays splash, and asks if user wants to continue/reset.
// Returns true if a valid name is loaded or set.
play_fn intro(void) {
    get_round_number();
    print_ascii_screen("assets/splash.txt", "Welcome to the simple Rock-Paper-Scissors Game!\n");

    FILE *username_file = fopen("save/username.txt", "r");
    if (!username_file) {
        reset_game();
        return medium_play;  // Don't exit abruptly
    }

    char buffer[MAX_NAME_SIZE] = {0};
    if (!fgets(buffer, sizeof(buffer), username_file)) {
        fclose(username_file);
        reset_game();
        return medium_play;
    }

    buffer[strcspn(buffer, "\n")] = '\0';  // remove trailing newline
    fclose(username_file);

    // Ask user whether to continue or start over
    printf("Please choose one of the following options:\n");
    printf(" * Continue (1)\n * Start Again (2)\n * Quit (3) ");
    char choice = read_stdin();

    if (choice == '1') {
        load_saved_username();
    } else if (choice == '2') {
        reset_game();
    } else {
        return false;  // Quit
    }

    // Difficulty selection
    printf("Please choose one of the following options:\n");
    if (round_number > 10) {
        printf(" * Difficult (1)\n * Medium (2)\n * Easy (3) ");
        choice = read_stdin();
        if (choice == '1') return difficult_play;
        if (choice == '2') return medium_play;
        if (choice == '3') return easy_play;
    } else {
        printf(" * Difficult (Locked)\n * Medium (2)\n * Easy (3) ");
        choice = read_stdin();
        if (choice == '2') return medium_play;
        if (choice == '3') return easy_play;
    }

    printf("Invalid choice, proceeding with medium level\n");

    return medium_play;  // default fallback
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
    FILE *f = fopen("save/game_moves.txt", "a");

    if (!f) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%s: %d\n", name, user);
    fprintf(f, "Computer: %d\n", computer);


    fclose(f);

    if (user > 3 || user <= 0) {

        printf("INVALID INPUT: losing one point\n");
        return -1;
    }
    if (user == computer) {
        return 0; // draw
    } else if ((user - computer + 3) % 3 == 1) {
        return 1; // user won
    }


    return 2; // computer won
}

// Update and show point winner
void display_winner(int result) {
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

// Prompts user to play and returns the move choice
char play(void) {
    printf("Type the following number:\n* Rock (1)\n* Paper (2)\n* Scissors (3)\n* Exit (0) ");
    char user = read_stdin();
    return user;
}


int easy_play(void) {
    int num = rand() % 6 + 1;

    if (num % 3 == 0) {
        return 3;
    } else if (num % 2 == 0) {
        return 2;
    } else {
        return 1;
    }
}

// Generates and returns a random computer move between 1 and 3
int medium_play(void) {
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

    if (rd_num % 3 == 0) {
        return 3;
    } else if (rd_num % 2 == 0) {
        return 2;
    } else {
        return 1;
    }
}

int difficult_play(void) {
    Py_Initialize();
    // Set the Python path to the current directory (where ai_model.py is located)
    PyRun_SimpleString("import sys\n"
        "sys.path.append('/Users/leen/Desktop/programming/C/rock-paper-scessiors/rock-paper-scissors-c/src/');");

    // Now you can import your Python file
    PyObject *pModule = PyImport_ImportModule("ai_model");  // Import ai_model
    if (!pModule) {
        PyErr_Print();
        return -1;
    }

        
    // Get the predict_next_move function
    PyObject *pFunc = PyObject_GetAttrString(pModule, "q_learning_predict");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        fprintf(stderr, "Function predict_next_move not found or not callable\n");
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
        Py_Finalize();
        return 1;
    }
    
    // Call the function
    PyObject *pValue = PyObject_CallObject(pFunc, NULL);
    int result = 1;  // fallback move
    
    if (pValue != NULL) {
        result = (int)PyLong_AsLong(pValue);
        Py_DECREF(pValue);
    } else {
        PyErr_Print();
        fprintf(stderr, "Call to predict_next_move failed\n");
    }
    
    // Cleanup
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
    Py_Finalize();

    printf("result is %d\n", result);
    
    return result;    
}


// Display current points
void display_points() {
    assert(name);
    printf(" %s: %d Point%s\n", name, user_points, user_points == 1 ? "" : "s");
    printf(" Computer: %d Point%s\n", computer_points, computer_points == 1 ? "" : "s");
}


// Round menu
int round_msg(void) {
    FILE *f = fopen("save/game_moves.txt", "a");

    fprintf(f, "========================================\n");
    if (!f) {
        perror("fopen");
        return -1;
    }

    fprintf(f, "ROUND %d\n", round_number);
    fclose(f);
  
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
void save_game_summary(void) {
    FILE *f = fopen("save/game_history.txt", "a");
    if (!f) {
        perror("fopen");
        return;
    }
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strcspn(time_str, "\n")] = '\0';

    fprintf(f, "Date: %s\n", time_str);
    fprintf(f, "Player: %s\n", name);
    fprintf(f, "User Score: %d | Computer Score: %d\n", user_points, computer_points);
    if (user_points > computer_points) {
        fprintf(f, "Winner: %s\n", name);
    } else if (user_points < computer_points) {
        fprintf(f, "Winner: Computer\n");
    } else {
        fprintf(f, "Result: Draw\n");
    }
    fprintf(f, "-------------------------\n");
    fclose(f);
  
}

// End-of-game message
void end_game_msg(void) {

    remove("save/round_number.txt");

    FILE *f = fopen("save/round_number.txt", "a");

    if (!f) {
        perror("fopen");
        return;
    }

    fprintf(f, "%d", round_number);

    fclose(f);

    printf("GAME SUMMARY:\n");
    display_points();
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
