#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define MAX_PLAYERS 100

typedef struct Player {
    char name[50];
    int wins;
    int losses;
    int gamesPlayed;
} Player;

/* Array to hold player data for leaderboard */
Player leaderboard[MAX_PLAYERS];
    int player_count = 0;

/* --- Board Logic --- */

/* Function : void initBoard(char board[ROWS][COLS])
 * Purpose  : Loop through every row and column to fill the board with spaces
 * Arguments: char board[ROWS][COLS]
 * Returns  : void
*/
void initBoard(char board[ROWS][COLS]) {
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            board[r][c] = ' ';
        }
    }
}

/* Function : void printBoard(char board[ROWS][COLS])
 * Purpose  : Print the current state of the 2D array to the screen
 * Arguments: char board[ROWS][COLS]
 * Returns  : void
*/
void printBoard(char board[ROWS][COLS]) {
    int r, c;
    printf("\n");
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            if(board[r][c] == 'X') {
                printf("|\033[31m X \033[0m");
            }
            else if(board[r][c] == 'O') {
                printf("|\033[33m O \033[0m");
            }
            else {
                printf("| %c ", board[r][c]);
            }
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

/* Function : int dropPiece(char board[ROWS][COLS], int col, char mark)
 * Purpose  : This function places a piece in the board from bottom up
 * Arguments: char board[ROWS][COLS], int col, char mark
 * Returns  : 1 for success, 0 for full column
*/
int dropPiece(char board[ROWS][COLS], int col, char mark) {
    int r;
    int c = col - 1; 

    for (r = ROWS - 1; r >= 0; r--) {
        if (board[r][c] == ' ') {
            board[r][c] = mark;
            return 1;
        }
    }
    return 0;
}

/* Function : int checkWin(char board[ROWS][COLS], char mark)
 * Purpose  : Scans board for 4 connected pieces (horiz, vert, diag)
 * Returns  : 1 for win, 0 for none
*/
int checkWin(char board[ROWS][COLS], char mark) {
    int r, c;

    /* Horizontal check */
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == mark && board[r][c+1] == mark && 
                board[r][c+2] == mark && board[r][c+3] == mark) return 1;
        }
    }

    /* Vertical check */
    for (r = 0; r <= ROWS - 4; r++) {
        for (c = 0; c < COLS; c++) {
            if (board[r][c] == mark && board[r+1][c] == mark && 
                board[r+2][c] == mark && board[r+3][c] == mark) return 1;
        }
    }

    /* Diagonal (down-right) */
    for (r = 0; r <= ROWS - 4; r++) {
        for (c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == mark && board[r+1][c+1] == mark && 
                board[r+2][c+2] == mark && board[r+3][c+3] == mark) return 1;
        }
    }

    /* Diagonal (up-right) */
    for (r = 3; r < ROWS; r++) {
        for (c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == mark && board[r-1][c+1] == mark && 
                board[r-2][c+2] == mark && board[r-3][c+3] == mark) return 1;
        }
    }

    return 0;
}

/* --- Leaderboard Logic --- */

/* Function : void loadLeaderboard(void)
 * Purpose  : This function loads the leaderboard from the .dat file, or creates it
 * Arguments: void
 * Returns  : void
*/
void loadLeaderboard(void) {
    FILE* file = fopen("leaderboard.dat", "rb");
    if (file == NULL) return;
    player_count = fread(leaderboard, sizeof(Player), MAX_PLAYERS, file);
    fclose(file);
}

/* Function : void saveLeaderboard(void)
 * Purpose  : This function saves the leaderboard (winner name + win count) to the .dat file
 * Arguments: void
 * Returns  : void
*/
void saveLeaderboard(void) {
    FILE* file = fopen("leaderboard.dat", "wb");
    if (file == NULL) return;
    fwrite(leaderboard, sizeof(Player), player_count, file);
    fclose(file);
}

/* Function : void sortLeaderboard(void)
 * Purpose  : This function sorts the leaderboard by most wins up top, cascading down
 * Arguments: void
 * Returns  : void
*/
void sortLeaderboard(void) {
    Player temp;
    int i, j;
    for (i = 0; i < player_count - 1; i++) {
        for (j = 0; j < player_count - 1 - i; j++) {
            if (leaderboard[j].wins < leaderboard[j + 1].wins) {
                temp = leaderboard[j];
                leaderboard[j] = leaderboard[j+1];
                leaderboard[j+1] = temp;
            }
        }
    }
}

/* Function : void displayLeaderboard(void)
 * Purpose  : This function displays the leaderboard formatted for the viewer to stdout
 * Arguments: void
 * Returns  : void
*/
void displayLeaderboard(void) {
    int i;
    sortLeaderboard();
    printf("\n ---------------- LEADERBOARD -----------------\n");
    printf(" | %-15s | %-5s | %-7s | %-5s |\n", "Player Name", "Wins", "Losses", "Total");
    printf(" ----------------------------------------------\n");

    if (player_count == 0) {
        printf("| No games have been played yet, be the first! |\n");
    } else {
        for (i = 0; i < player_count; i++) {
            printf(" | %-15s | %-5d | %-7d | %-5d |\n", 
                    leaderboard[i].name, leaderboard[i].wins,  
                    leaderboard[i].losses, leaderboard[i].gamesPlayed);
        }
    }
    printf(" ----------------------------------------------\n\n");
}

/* Function : int getPlayerInfo(void)
 * Purpose  : This function gets player info (name, new/old) and stores it to the .dat file
 * Arguments: void
 * Returns  : i for success, -1 errors
*/
int getPlayerInfo(void) {
    char name[50];
    int i;
    printf("Enter player name (no spaces): ");
    scanf("%s", name);

    for (i = 0; i < player_count; i++) {
        if (strcmp(leaderboard[i].name, name) == 0) {
            printf("Welcome back, %s!\n", name);
            return i;
        }
    }

    if (player_count < MAX_PLAYERS) {
        strcpy(leaderboard[player_count].name, name);
        leaderboard[player_count].wins = 0;
        leaderboard[player_count].losses = 0;
        leaderboard[player_count].gamesPlayed = 0;
        printf("New user created for %s!\n", name);
        return player_count++;
    }
    return -1;
}

/* Function : void updateMatchStats(int winner, int loser, int isDraw)
 * Purpose  : This function updates players wins/losses to display in the leaderboard and .dat file
 * Arguments: int winner, int loser, int isDraw
 * Returns  : void
*/
void updateMatchStats(int winner, int loser, int isDraw) {
    if (winner == -1 || loser == -1) return;
    if (isDraw) {
        leaderboard[winner].gamesPlayed++;
        leaderboard[loser].gamesPlayed++;
    } else {
        leaderboard[winner].wins++;
        leaderboard[winner].gamesPlayed++;
        leaderboard[loser].losses++;
        leaderboard[loser].gamesPlayed++;
    }
    saveLeaderboard();
}

/* --- High-Level Game Execution --- */

/* Function : void playGame()
 * Purpose  : This function contains all the function calls, main game logic, and everything in between
 * Arguments: void
 * Returns  : void
*/
void playGame(void) {
    char board[ROWS][COLS];
    int choice, turn = 0, gameRunning = 1;
    int p1, p2;

    printf("--- Player 1 (X) ---\n");
    p1 = getPlayerInfo();
    printf("--- Player 2 (O) ---\n");
    p2 = getPlayerInfo();

    if (p1 != -1 && p1 == p2) {
        printf("Error: You cannot play against yourself!\n");
        return;
    }

    initBoard(board);

    while (gameRunning == 1) {
        /*system("clear");*/
        printBoard(board);
        char mark = (turn % 2 == 0) ? 'X' : 'O';
        Player playerNum;
        strcpy(playerNum.name, leaderboard[(turn % 2 == 0) ? p1 : p2].name);
        int currentIdx = (turn % 2 == 0) ? p1 : p2;
        int otherIdx = (turn % 2 == 0) ? p2 : p1;

        printf("%s (%c), enter column (1-7) or 0 to quit: ", playerNum.name, mark);
        
        if (scanf("%d", &choice) != 1) {
            printf("Error: Please enter a number.\n");
            while(getchar() != '\n'); 
            continue;
        }

        if (choice == 0) {
            gameRunning = 0;
        } else if (choice >= 1 && choice <= COLS) {
            if (dropPiece(board, choice, mark) == 1) {
                if (checkWin(board, mark)) {
                    /*system("clear");*/
                    printBoard(board);
                    printf("\n*** %s (%c) WINS! ***\n", playerNum.name, mark);
                    updateMatchStats(currentIdx, otherIdx, 0);
                    gameRunning = 0;
                } else if (turn >= (ROWS * COLS) - 1) {
                    /*system("clear");*/
                    printBoard(board);
                    printf("\n--- It's a draw! ---\n");
                    updateMatchStats(p1, p2, 1);
                    gameRunning = 0;
                }
                turn++;
            } else {
                printf("\n--- Column %d is full! ---\n", choice);
            }
        }
    }
    printf("Game Over. Returning to menu.\n\n");
}


/* Function : void startMenu()
 * Purpose  : This function contains all cases/breaks for the initial menu printed upon game start
 * Arguments: void
 * Returns  : void
*/
void startMenu(void) {
    int caseNum = 0;
    loadLeaderboard();
    
    while (caseNum != 4) {
        printf("\n\033[33mWELCOME\033[0m \033[31mTO\033[0m \033[33mCONNECT\033[0m \033[31m4!\033[0m\n\n");
        printf("1. Play the game!\n");
        printf("2. View Leaderboard!\n");
        printf("3. Get Help!\n");
        printf("4. Exit Game :(\n\n");
        
        printf("Choose an option: ");
        if (scanf("%d", &caseNum) != 1) {
            printf("\n--- Error: Please enter a valid number ---\n");
            while(getchar() != '\n'); 
            caseNum = 0;
            continue;
        }
        
        switch (caseNum){
            case 1: playGame(); break;
            case 2: displayLeaderboard(); break;
            case 3: printf("\n--- Instructions ---\nGet four in a row horizontally, vertically, or diagonally.\n"); break;
            case 4: printf("Thanks for playing!!\n\n"); break;
            default: printf("\n--- Invalid choice! Please pick 1, 2, 3, or 4 ---\n"); break;
        }
    }
}

#endif
