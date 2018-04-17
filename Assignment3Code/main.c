#include <stdio.h>
#include <stdlib.h>
#include "disksAndPlayers.h"


int main()
{
    // Variables declaration
    int i;
    player player1= {"player1", NONE,0};
    player player2= {"player2", NONE,0};
    disk board[SIZE][SIZE];

    initializePlayers(&player1, &player2);

    initializeBoard(board);

    printBoard(board);

    //printf("\n\n%d, %d\n", player1.type, player2.type); troubleshooting player types

    computePositions(board, player1);

    /*for(i=0;i<32;i++)
        {
            computePositions(board, player1);


            computePositions(board, player2);
        }*/

    //invoke a method that implements the game logic

        //invoke a method that prints the final result

        printEndScreen(player1, player2);

}
