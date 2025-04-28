#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>


/* How to play the game
    1 - Rock
    2 - Paper
    3 - Scissors
*/


int user_points = 0;
int computer_points = 0;

// conversion(num) displays 1 for rock, 2 for paper, and 3 for scissors.
void conversion(int num) {
    assert(num >= 1 && num <= 3);

    if (num == 1) {
        printf("ROCK\n");
    } else if (num == 2) {
        printf("PAPER\n");
    } else {
        printf("SCISSORS\n");
    }

}

// computer(): GeeksForGeeks: https://www.geeksforgeeks.org/generating-random-number-range-c/
int computer(void) {
    int min = 1;
    int max = 3;

  
    // Open the file urandom
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
    

    // Scale the random value to the range [min, max]
    rd_num = rd_num % (max - min + 1) + min;
    printf("Computer played ");

    conversion(rd_num);

    // close the file
    close(fd);

    return rd_num;
}



// winner(user, computer) determines the winner of the game by returning 
//                      0 -> draw
//                      1 -> user wins
//                      2 -> computer wins
int winner(int user, int computer) {

    if (user > 3 || user <= 0) {
        printf("INVALID INPUT: losing one point\n");
        return -1;
    }

    if (user == computer) {
        return 0;
    } else if ((user == 1 && computer == 3) || 
               (user == 2 && computer == 1) || 
               (user == 3 && computer == 2)) {
        return 1;  // user wins
    } else {
        return 2;  // computer wins
    }

}

// display_winner(result): displays the appropriate message given the results of the winner function
void display_winner(int result) {
    if (result == 0) {
        printf("DRAW\n");
    } else if (result == 1) {
        printf("USER WON!!\n");
        user_points++;
    } else if (result == 2){
        printf("COMPUTER WON!!\n");
        computer_points++;
    } else {
        user_points--;
    }
}

// end_game_msg(): displays the total points of each player and who won the game.
void end_game_msg(void) {
    printf("GAME SUMMARY:\n User: %d points\n Computer: %d points\n", user_points, computer_points);
    printf("**********************  WINNER  **********************\n");
    printf("                        ");
    if (user_points == computer_points) {
        printf("NONE, the game is a draw\n");
    } else if (user_points > computer_points) {
        printf("USER\n");
    } else {
        printf("COMPUTER\n");
    }
}


char read_stdin(void) {
    char buff[10];

    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Input error!\n");
        exit(EXIT_FAILURE);
    }
    

    for(int i = 0; i < 10; i++) {
        if (buff[i] == '1' || buff[i] == '2' || buff[i] == '3' || buff[i] == '0') {
            return buff[i];
        }
    }


    return 'e';
}



int main(){


    printf("Welcome to the simple Rock-Paper-Scissors Game!\n");
    printf("Type the following number:\n* Rock (1)\n* Paper (2)\n* Scissors (3)\n*Exit (0) ");

    char user = read_stdin();


    while(user && user != '0') {

        if (user == '1' || user == '2' || user == '3') {
            int comp = computer();

            int user_num = user - '0';
            
            int result = winner(user_num, comp);
    
            printf("User played ");

            conversion(user_num);


            display_winner(result);


        } else {
            printf("INVALID INPUT: losing one point\n");
            user_points--;
        }
           
    
        printf("Type the following number:\n* Rock (1)\n* Paper (2)\n* Scissors (3)\n*Exit (0) ");
        user = read_stdin();
    }

    end_game_msg();
}