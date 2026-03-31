/*
 * File:        Connect_4.c
 * Authors:     Ashlee Santos, Zachary Tull, Angelo Valencia
 * Purpose:     Demonstrate teamwork, problem solving, time management, and a moderate understanding of C coding in large-scale projects.
 * 
 * Date:        3 March 2026
 *
 * Sources of Help: N/A so far
 */

#include <stdio.h>
#include <time.h>
#define ROWS 6
#define COLS 7

/* Function Prototypes */
void initBoard();
void printBoard();
void dropPiece();


int main() {

    printf("Welcome to Connect 4! \nThis is a two-player game where you take turns placing tokens until one person achieves 4 tokens in a row.\nPlayer 1 (yellow) will start.\n\n");
    initBoard();

    printf("Place your first token by typing which row you would like the piece dropped in: ");

    /* Some sort of for loop to iterate through turns, maybe a while-do */
    
    return 0;
}

/* Function Definitions */

void initBoard() {
    printf(" | 1 | 2 | 3 | 4 | 5 | 6 | 7 | \n");
    printf(" |___|___|___|___|___|___|___| \n");
    printf(" |___|___|___|___|___|___|___| \n");
    printf(" |___|___|___|___|___|___|___| \n");
    printf(" |___|___|___|___|___|___|___| \n");
    printf(" |___|___|___|___|___|___|___| \n");
    printf(" |___|___|___|___|___|___|___| \n\n");
}
