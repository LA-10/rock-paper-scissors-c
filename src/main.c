#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"



/* How to play the game
    1 - Rock
    2 - Paper
    3 - Scissors
*/

void bar(void) {
    printf("------------------------------------------\n");
}

int main() {
    
    int num_of_plays = 0;

    play_fn res = intro();

    while(res) {
        if (num_of_plays % 3 == 0) {

            if (num_of_plays == 0) {

                char buffer[64];
                snprintf(buffer, sizeof(buffer), "ROUND %d", round_number);

                round_number++;
                print_ascii_screen("assets/round.txt", buffer);
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
            int comp = res();

            int user_num = user - '0';

            int result = winner(user_num, comp);
    
            printf("%s played ", name);

            
            conversion(user_num);

            printf("Computer played ");
            conversion(comp);

            display_winner(result);

        } else {
            printf("INVALID INPUT: losing one point\n");
            user_points--;
            
        }

        
        bar();
        num_of_plays++;
    }

    end_game_msg();
    exit(EXIT_SUCCESS);

}