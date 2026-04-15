/* File: fileio.c
 * Author: Ashlee Santos
 * Purpose: For Tic-Tac-Toe project | fileio for leaderboard and storing player data, starter/opening screen
 * Acknoledgments: Canvas, Stack Exchange
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYERS 100

/* Stuct definition for storing player data */
typedef struct Player {
    char name[50];
    int wins;
    int losses;
} Player;

/* Array to hold player data for leaderboard */
Player leaderboard[MAX_PLAYERS];
    int player_count = 0;

/* Function prototypes */
void loadLeaderboard(void);
void sortLeaderboard(void);
void displayLeaderboard(void);
int getPlayerInfo(char* name);
void saveLeaderBoard(void);

/* main */
int main() {

    loadLeaderboard();
    sortLeaderboard();
    displayLeaderboard(); 

    return EXIT_SUCCESS;
}

/* Function definitions */

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
