/* File: fileio.c
 * Author: Ashlee Santos
 * Purpose: For Tic-Tac-Toe project | fileio for leaderboard and storing player data, starter/opening screen, updating player stats
 * Acknoledgments: Canvas, Stack Exchange
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 100

/* Stuct definition for storing player data */
typedef struct Player {
    char name[50];
    int wins;
    int losses;
    int gamesPlayed;
} Player;

/* Global array to hold player data for leaderboard */
Player leaderboard[MAX_PLAYERS];
    int player_count = 0;

/* Function prototypes */
void loadLeaderboard(void);
void sortLeaderboard(void);
void displayLeaderboard(void);
int getPlayerInfo(void);
void saveLeaderboard(void);
void updateMatchStats(int winner, int loser, int isDraw);

/* main */
int main() {

    loadLeaderboard();
    sortLeaderboard();
    displayLeaderboard();
    getPlayerInfo();
    saveLeaderboard();

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
    printf(" | %-15s | %-5s | %-7s | %-5s |\n", "Player Name", "Wins", "Losses", "Total");
    printf(" ----------------------------------------------\n");

    if (player_count == 0) {
        printf("| No games have been played yet, be the first! |\n");
    } else {
        for ( i = 0; i < player_count; i++) {
            printf(" | %-15s | %-5d | %-7d | %-5d |\n", 
                    leaderboard[i].name, 
                    leaderboard[i].wins,  
                    leaderboard[i].losses,
                    leaderboard[i].gamesPlayed);
        }
    }
    
    printf(" ----------------------------------------------\n\n");
}

/* Function : getPlayerInfo();
 * Purpose  : To search and load  exsisting players and their info on the leaderboard
              if the player doesn't exsist, new user is created.
 * Arguments: none
 * Returns  : int i = Exsisting player index found
              int player_count = New player created and added to index
              int -1 = Error/Player Array full; game is at max cap.
*/

/* implementation into main() instructions :
    call this function/logic to assign an ID to both player 1 and player 2:

    int p1, p2;

    printf("--- Player 1 (X) --- \n");
        p1 = getPlayerInfo();
    printf("--- Player 2 (O) --- \n");
        p2 = getPlayerInfro();

    /* prevents someone from playing against themselves
    if (p1 != -1 && p1 == p2) {  
        printf("Error: You cannot play against your self! Please restart.\n");
    return;
    } */

int getPlayerInfo(void) {

    int i;
    char name[50];

    printf("Enter player name (no spaces): ");
        scanf("%s", name);

    /* search for exsisting player */
    for (i = 0; i < player_count; i++) {
        if (strcmp(leaderboard[i].name, name) == 0) {
            printf("Welcome back, %s!\n", name);
            return i;
        }
    }

    /* if player not found, create new player */
    if (player_count < MAX_PLAYERS) {
        strcpy(leaderboard[player_count].name, name);
        leaderboard[player_count].wins = 0;
        leaderboard[player_count].losses = 0;
        leaderboard[player_count].gamesPlayed = 0;

        printf("New user created for %s!\n", name);
        return player_count++; /* return current index, then increase total count */
    }

    printf("Leaderboard full! Playing as guest.\n");
    return -1;

}


/* Function : saveLeaderboard()
 * Purpose  : to save the leaderboard after the current session has taken place
 * Arguments: none
 * Returns  : none
*/

void saveLeaderboard(void){

    FILE* file = fopen("leaderboard.dat", "wb");
    

    if (file == NULL ) {
        perror("ERROR: Could not open file for saving leaderboard!\n");
    return;
    }

    /* takes: source array, size of 1 struct, number of structs, file ptr */
    fwrite(leaderboard, sizeof(Player), player_count, file);

    fclose(file);
    printf("Leaderboard saved successfully. \n");
}

/* Function : updateMatchStats()
 * Purpose  : to update the stats of each player after a round
 * Arguments: winner = winner of the match
              loser = loser of the match
              isDraw = if the match was a tie
 * Returns  : none
*/

void updateMatchStats(int winner, int loser, int isDraw) {

    if (isDraw ) {
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
