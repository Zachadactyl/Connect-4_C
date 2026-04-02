#ifndef CONNECTION_H
#define CONNECTION_H

#define ROWS 6
#define COLS 7
#define MAX_PLAYERS 100

typedef struct Player {
    char name[50];
    int wins;
    int losses;
} Player;

/* Array to hold player data for leaderboard */
Player leaderboard[MAX_PLAYERS];
    int player_count = 0;

/* Function Definitions */

/* Function : void initBoard(char board[ROWS][COLS])
 * Purpose  : Loop through every row and column to fill the board with spaces
 * Arguments: char board[ROWS][COLS]
 * Returns  : none.
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
 * Returns  : none.
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

/* Function : void dropPiece(char board[ROWS][COLS], int col, char mark)
 * Purpose  : This function places a piece in the board.
 * It searches from the bottom (row 5) to the top (row 0)
 * Arguments: char board[ROWS][COLS], int col, char mark
 * Returns  : placement or full column
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


void playGame() {
char board[ROWS][COLS];
    int choice;
    int turn = 0;
    int gameRunning = 1;
    char playerMark;
    int playerNum;

/* getPlayerInfo(); */
    initBoard(board);

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

      /* saveLeaderBoard(); */
      printf("Game Over. Thanks for playing!\n\n");
}

/* Function : void loadLeaderboard(void)
 * Purpose  : load current leaderboard to local memory
 * Arguments: none.
 * Returns  : none.
*/

void loadLeaderboard(void) {
    FILE* file = fopen("leaderboard.dat", "rb");
     
    if (file == NULL) { /* line for if the file doesn't exsist yet, OK if it doesn't */
        return;
    } else {
        player_count = fread(leaderboard, sizeof(Player), MAX_PLAYERS, file);
    }
    
}

/* Function : void sortLeaderboard(void)
 * Purpose  : sort leaderboard of players based on wins
 * Arguments: none.
 * Returns  : none.
*/

void sortLeaderboard(void) {

    Player temp;
    int i;
    int j;

    /* using nested loops to iterate through and compare player data */
    for ( i = 0; i < player_count - 1; i++) {
        for ( j = 0; j < player_count - 1 - i; j++) {
            if (leaderboard[j].wins < leaderboard[j + 1].wins) {
                temp = leaderboard[j];
                leaderboard[j] = leaderboard[j+1];
                leaderboard[j+1] = temp;
            }
        }
    }
}

/* Function : void displayLeaderboard(void)
 * Purpose  : print current leaderboard to console
 * Arguments: none.
 * Returns  : none.
*/

void displayLeaderboard(void) {
    
    int i;

    sortLeaderboard();
    printf("\n ---------------- LEADERBOARD -----------------\n");
    printf("|        %-18s |       %-10s |\n", "Player Name", "Wins");
    printf(" ----------------------------------------------\n");

    if (player_count == 0) {
        printf("| No games have been played yet, be the first! |\n");
    } else {
        for ( i = 0; i < player_count; i++) {
            printf("%-20s | %-10d\n", leaderboard[i].name, leaderboard[i].wins);
        }
    }
    
    printf(" ----------------------------------------------\n\n");
}

/* Function :
 * Purpose  :
 * Arguments:
 * Returns  :
*/

/* Function :
 * Purpose  :
 * Arguments:
 * Returns  :
*/


#endif
