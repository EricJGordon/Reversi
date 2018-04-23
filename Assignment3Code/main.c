
// Written by Eric Gordon 17341111 and Rokas Stasiskis 17716065

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "disksAndPlayers.h"


int main()
{
    FILE *ScoreSheet;
    // Variables declaration

    player player1= {"player1", NONE,0};
    player player2= {"player2", NONE,0};
    disk board[SIZE][SIZE];
    bool cont = true;
    initializePlayers(&player1, &player2);
    printf("%s's disks are represented by \"B\" \n%s's disks are represented by \"W\" \nAvailable moves are represented by \"o\".\n", player1.name, player2.name); //Info for players

    initializeBoard(board);
    ScoreSheet = fopen("./Assignment3/Assignment3Code/Score.txt","w+");
    fprintf(ScoreSheet, "Player1 %s, points: %d \nPlayer2 %s, points: %d \nThe winner is ", player1.name, player1.points, player2.name, player2.points);
    while (cont ==true){

        computePositions(board, player1, &cont);
        printBoard(board);
        scores(board, &player1, &player2);


        if (cont == false)
            break;

        playerMove(board, player1);
        refreshBoard(board);

        computePositions(board, player2, &cont);
        printBoard(board);
        scores(board, &player1, &player2);


        if (cont == false)
            break;

        playerMove(board, player2);
        refreshBoard(board);
        }

    printEndScreen(player1, player2);

    return 0;
}
