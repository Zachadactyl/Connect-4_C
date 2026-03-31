/*
 * File:        Connect_4.c
 * Authors:     Ashlee Santos, Zachary Tull, Angelo Valencia
 * Purpose:     A beginner-friendly implementation of Connect 4.
 * Date:        3 March 2026
 */

#include <stdio.h>

#define ROWS 6
#define COLS 7

/* Function Prototypes */
void initBoard(char board[ROWS][COLS]);
void printBoard(char board[ROWS][COLS]);
int dropPiece(char board[ROWS][COLS], int col, char mark);

int main() {
    char board[ROWS][COLS];
    int choice;
    int turn = 0;
    int gameRunning = 1;
    char playerMark;
    int playerNum;

    initBoard(board);

    printf("Welcome to Connect 4!\n");

    while (gameRunning == 1) {
        printBoard(board);

        /* Logic to switch players based on turn number */
        /* If turn is 0, 2, 4... it is Player 1's turn */
        if (turn % 2 == 0) {
            playerMark = 'X';
            playerNum = 1;
        } else {
            playerMark = 'O';
            playerNum = 2;
        }

        printf("Player %d (%c), enter column (1-7) or 0 to quit: ", playerNum, playerMark);
        
        /* Read user input */
        if (scanf("%d", &choice) != 1) {
            printf("Error: Please enter a number.\n");
            while(getchar() != '\n'); /* Clears bad input like letters */
            continue;
        }

        /* User choice 0 means they want to stop the game */
        if (choice == 0) {
            gameRunning = 0;
        } else if (choice >= 1 && choice <= COLS) {
            /* Try to drop the piece in the selected column */
            if (dropPiece(board, choice, playerMark) == 1) {
                turn = turn + 1; /* Move successful, next turn */
            } else {
                printf("\n--- Column %d is full! Try a different one. ---\n", choice);
            }
        } else {
            printf("\n--- Invalid column! Please choose 1 through 7. ---\n");
        }
    }

    printf("Game Over. Thanks for playing!\n");
    return 0;
}

/* Function Definitions */

/* Loop through every row and column to fill the board with spaces */
void initBoard(char board[ROWS][COLS]) {
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            board[r][c] = ' ';
        }
    }
}

/* Print the current state of the 2D array to the screen */
void printBoard(char board[ROWS][COLS]) {
    int r, c;
    printf("\n");
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            printf("| %c ", board[r][c]);
        }
        printf("|\n");
    }

    /* Print a line at the bottom */
    for (c = 0; c < COLS; c++) {
        printf("----");
    }
    printf("-\n");

    /* Print column numbers under the board */
    for (c = 1; c <= COLS; c++) {
        printf("  %d ", c);
    }
    printf("\n\n");
}

/* * This function places a piece in the board.
 * It searches from the bottom (row 5) to the top (row 0).
 */
int dropPiece(char board[ROWS][COLS], int col, char mark) {
    int r;
    int c;
    
    c = col - 1; /* Convert 1-7 user input to 0-6 array index */

    /* The loop starts at the bottom row and looks for an empty space */
    for (r = ROWS - 1; r >= 0; r--) {
        if (board[r][c] == ' ') {
            board[r][c] = mark; /* Found a spot! Save the piece here */
            return 1; /* Success */
        }
    }
    
    return 0; /* Column was already full */
}
