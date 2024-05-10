#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

char board[9];
char player_symbol = 'X';
char computer_symbol = 'O';

void print_board() {
    printf("-------------\n");
    for (int i = 0; i < 9; i += 3) {
        printf("| %c | %c | %c |\n", board[i], board[i + 1], board[i + 2]);
        printf("-------------\n");
    }
}

void make_move(int position, char symbol) {
    board[position] = symbol;
}

bool is_valid_move(int position) {
    return position >= 0 && position < 9 && board[position] == ' ';
}

bool is_winner(char symbol) {
    int winning_combinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6} // diagonals
    };
    for (int i = 0; i < 8; i++) {
        int* combo = winning_combinations[i];
        if (board[combo[0]] == symbol && board[combo[1]] == symbol && board[combo[2]] == symbol) {
            return true;
        }
    }
    return false;
}

bool is_board_full() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

bool player_turn() {
    int position;
    printf("Enter your move (0-8): ");
    scanf("%d", &position);
    if (is_valid_move(position)) {
        make_move(position, player_symbol);
        print_board();
        if (is_winner(player_symbol)) {
            printf("Congratulations! You won!\n");
            return true;
        } else if (is_board_full()) {
            printf("It's a draw!\n");
            return true;
        }
    } else {
        printf("Invalid move. Try again.\n");
    }
    return false;
}

bool computer_turn() {
    int available_moves[9];
    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            available_moves[count++] = i;
        }
    }
    int position = available_moves[rand() % count];
    make_move(position, computer_symbol);
    printf("Computer chose position %d\n", position);
    print_board();
    if (is_winner(computer_symbol)) {
        printf("Computer wins!\n");
        return true;
    } else if (is_board_full()) {
        printf("It's a draw!\n");
        return true;
    }
    return false;
}

void play_game() {
    printf("Welcome to Tic-Tac-Toe!\n");
    print_board();
    while (true) {
        if (player_turn()) {
            break;
        }
        if (computer_turn()) {
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
    play_game();
    return 0;
}
