#include <stdio.h>
#include <stdlib.h>
#include "game.h"



/* How to play the game
    1 - Rock
    2 - Paper
    3 - Scissors
*/

void bar(void) {
    printf("------------------------------------------\n");
}

int main() {

    name = malloc(sizeof(char) * MAX_NAME_SIZE); // example: 100
    if (!name) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    int num_of_plays = 0;

    bool res = intro();

    while(res) {
        if (num_of_plays % 3 == 0) {

            if (num_of_plays == 0) {
                print_ascii_screen("assets/round.txt", "ROUND 1");
                round_number++;
            } else {
                int result = round_msg();

                if (result == 3) {
                    save_game_summary();
                }

                if (result != 1) {
                    break;
                }
            }
        }

        char user = play();

        if (user_points < 0 || user == '0') {
            break;
        }

        if (user == '1' || user == '2' || user == '3') {
            int comp = computer();

            int user_num = user - '0';

            int result = winner(user_num, comp);
    
            printf("%s played ", name);

            
            conversion(user_num);

            display_winner(result);

        } else {
            printf("INVALID INPUT: losing one point\n");
            user_points--;
            
        }

        bar();
        num_of_plays++;
    }

    end_game_msg();
    free(name);
    exit(EXIT_SUCCESS);

}