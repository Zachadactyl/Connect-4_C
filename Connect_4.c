/*
 * File:        Connect_4.c
 * Authors:     Ashlee Santos, Zachary Tull, Angelo Valencia
 * Purpose:     A beginner-friendly implementation of Connect 4.
 * Date:        3 March 2026 
 * 
 * Sources of Help: Canvas, W3 Schools, Stack Exchange
 */

#include <stdio.h>
#include "connections.h"


/* Function Prototypes */
void initBoard(char board[ROWS][COLS]);
void printBoard(char board[ROWS][COLS]);
int dropPiece(char board[ROWS][COLS], int col, char mark);
void playGame();
void loadLeaderboard(void);
void sortLeaderboard(void);
void displayLeaderboard(void);
int getPlayerInfo(char* name);
void saveLeaderBoard(void);

int main() {
    int caseNum = 0;
    
    
    printf("\n\033[33mWELCOME\033[0m \033[31mTO\033[0m \033[33mCONNECT\033[0m \033[31m4!\033[0m\n\n"); /* WELCOME TO CONNECT 4! (in red and yellow caps) */
    printf("1. Play the game!\n");
    printf("2. View Leaderboard!\n");
    printf("3. Get Help!\n");
    printf("4. Exit Game :(\n\n");
    
    printf("Choose an option: ");
    scanf("%d", &caseNum);
    
    switch (caseNum){
        case 1: 
            playGame();
        break;
    case 2: 
        printf("Put leaderbord here or sum...\n");
        loadLeaderboard();
        sortLeaderboard();
        displayLeaderboard();
        break;
    case 3:
        printf("Working on instructions...\n");
        break;
    case 4:
        printf("Thanks for playing!!\n\n");
        break;
    }
  
    
    return 0;
}



