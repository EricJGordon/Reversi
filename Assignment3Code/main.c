
// Written by Eric Gordon 17341111 and Rokas Stasiskis 17716065

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "disksAndPlayers.h"


int main()
{
    // Variables declaration

    player player1= {"player1", NONE,0};
    player player2= {"player2", NONE,0};
    disk board[SIZE][SIZE];
    cont = true;
    initializePlayers(&player1, &player2);
    printf("%s's disks are represented by \"B\" \n%s's disks are represented by \"W\" \nAvailable moves are represented by \"x\".\n", player1.name, player2.name); //Info for players

    initializeBoard(board);

    while (cont == true){   //while there are positions available to put the next piece

        computePositions(board, player1);
        printBoard(board);
        if (cont == false)
            break;

        scores(board, &player1, &player2);

        playerMove(board, player1);
        refreshBoard(board);

        computePositions(board, player2);

        printBoard(board);
        if (cont == false)
            break;
        scores(board, &player1, &player2);

        playerMove(board, player2);
        refreshBoard(board);
        }

    printEndScreen(player1, player2);

    return 0;
}
