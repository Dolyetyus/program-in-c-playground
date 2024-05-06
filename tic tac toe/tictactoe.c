#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

char* grid = " %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n";

char elements[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void display_grid() {
    printf("\033[2J\033[1;1H");
    printf("Grid numeration:\n 1 | 2 | 3 \n-----------\n 4 | 5 | 6 \n-----------\n 7 | 8 | 9 \n\n");
    printf(grid, elements[0], elements[1], elements[2], elements[3], elements[4], elements[5], elements[6], elements[7], elements[8]);
}


bool check_win(char player) {
    for (int i = 0; i < 3; i++) {
        if (elements[i * 3] == player && elements[i * 3 + 1] == player && elements[i * 3 + 2] == player)
            return true;
    }
    for (int i = 0; i < 3; i++) {
        if (elements[i] == player && elements[i + 3] == player && elements[i + 6] == player)
            return true;
    }
    if ((elements[0] == player && elements[4] == player && elements[8] == player) ||
        (elements[2] == player && elements[4] == player && elements[6] == player))
        return true;

    return false;
}

bool check_draw() {
    for (int i = 0; i < 9; i++) {
        if (elements[i] == ' ')
            return false;
    }
    return true;
}

void clear_board() {
    for (int i = 0; i < 9; i++) {
        elements[i] = ' ';
    }
}

void multiplayer() {
    char current_player = 'X';
    int cell;
    bool game_over = false;

    while (!game_over) {
        display_grid();
        printf("Player %c's turn. Enter cell number (1-9): ", current_player);
        scanf("%d", &cell);
        cell--;

        if (cell < 0 || cell >= 9 || elements[cell] != ' ') {
            continue;
        }

        elements[cell] = current_player;

        if (check_win(current_player)) {
            display_grid();
            printf("Player %c won!\n", current_player);
            game_over = true;
        }
        else if (check_draw()) {
            display_grid();
            printf("It's a draw!\n");
            game_over = true;
        }

        current_player = (current_player == 'X') ? 'O' : 'X';
    }
}

void singleplayer() {
    char human_player = 'X', bot_player = 'O';

    int cell;
    bool game_over = false;

    while (!game_over) {
        display_grid();
        
        printf("Your turn. Enter cell number (1-9): ");
        scanf("%d", &cell);
        cell--;

        if (cell < 0 || cell >= 9 || elements[cell] != ' ') {
            continue;
        }

        elements[cell] = human_player;

        if (check_win(human_player)) {
            display_grid();
            printf("Congratulations! You won!\n");
            game_over = true;
        } 
        else if (check_draw()) {
            display_grid();
            printf("It's a draw!\n");
            game_over = true;
        }

        if (game_over) break;
        
        display_grid();
        printf("Bot's turn.\n");
        
        for (int i = 0; i < 9; i++) {
            if (elements[i] == ' ') {
                elements[i] = bot_player;
                if (check_win(bot_player)) {
                    cell = i;
                    game_over = true;
                    break;
                }
                elements[i] = ' ';
            }
        }

        if (elements[4] == ' '){
            cell = 4;
        }
        else{
            do {
                srand(time(NULL));
                cell = rand() % 9;
            } while (elements[cell] != ' ');
        }

        elements[cell] = bot_player;

        if (check_win(bot_player)) {
            display_grid();
            printf("You lost. Loser lol!\n");
            game_over = true;
        } 
        else if (check_draw()) {
            display_grid();
            printf("It's a draw!\n");
            game_over = true;
        }
    }
}

int main() {
    int user_choice;
    bool replay = true;
    
    printf("WELCOME TO TIC TAC TOE");
    
    while (replay) {
        printf("\n1- Play turn based multiplayer\n2- Play against bot\n0- Exit the game\n");
        scanf("%d", &user_choice);

        if (user_choice == 1) {
            clear_board();
            multiplayer();
        }
        else if (user_choice == 2) {
            clear_board();
            singleplayer();
        } 
        else if (user_choice == 0) {
            printf("Exiting the game.\n");
            replay = false;
        } 
        else {
            printf("Invalid choice. Please enter 1 or 2 to start the game or 0 to exit.\n");
        }
    }

    return 0;
}
