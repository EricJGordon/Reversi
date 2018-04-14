#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disksAndPlayers.h"


void initializePlayers(player *player1, player *player2){
    int nameSize;
    // Insert player 1
    printf("Player 1 please insert your name:   \n");
    fgets(player1->name, 20, stdin);
    nameSize = strlen(player1->name);
    player1->name[nameSize -1] = '\0';

    // Assign colours and points to player 1
    player1->type = BLACK;
    player1->points = 2;

    // Insert player 2
    printf("Player 2 please insert your name:   \n");
    fgets(player2->name, 20, stdin);
    nameSize = strlen(player2->name);
    player2->name[nameSize -1] = '\0';

    // Assign colours and points to player 2
    player2->type = WHITE;
    player2->points = 2;

    //printf("\n%d, %d\n", player1->type, player2->type); troubleshooting player types


}

void initializeBoard(disk board [SIZE][SIZE]){
 int i, j;
 //board initialization
    for(i=0; i< SIZE; i++){
        for(j=0;j<SIZE; j++){
            if(i==3){
                if(j==3)
                    board[i][j].type = WHITE;
                else{
                    if(j==4)
                        board[i][j].type = BLACK;
                    else
                        board[i][j].type = NONE;
                    }
                }
            else {
                if(i==4){
                    if(j == 3)
                        board[i][j].type = BLACK;
                    else {
                        if(j == 4)
                        board[i][j].type = WHITE;
                        else
                            board[i][j].type = NONE;
                        }
                    }
                else
                    board[i][j].type = NONE;
            }
            board[i][j].pos.row = i;
            board[i][j].pos.col = j;

            }
        }

    //board[4][0].type=board[4][1].type=board[2][2].type=board[2][3].type=board[2][4].type=board[3][4].type=board[4][4].type=board[5][4].type=WHITE;
    //board[3][2].type=board[4][2].type=board[5][2].type=board[3][3].type=board[4][3].type=board[5][3].type=BLACK;

    //example board state used to test computePositions function
    }


void printBoard(disk board[SIZE][SIZE]){
    int i,j;
    j = 0;

    printf("\n    ");
    for(i=0; i< SIZE; i++){
        printf("%d   ",i+1);
    }
    for(i=0; i< SIZE; i++){
        printf("\n%d | ", i+1);
        for(j=0;j<SIZE; j++){
            switch(board[i][j].type){
                case BLACK:
                    printf("1 | ");
                    break;
                case WHITE:
                    printf("0 | ");
                    break;
                case NONE:
                    printf("x | ");
                    break;
                default:
                    break;
            }
        }
    }
}
void computePositions(disk board [SIZE][SIZE], player currentPlayer)
{
    int i, j, m, n;


    for(i=0;i<8;i++)
    {
        for(j=0; j<8;j++)
        {
            if((board[i][j].type!=currentPlayer.type)&&(board[i][j].type!=NONE))
            {
                for(m=-1;m<2;m++)   //searching in a 3-by-3 area centred on the opponent's disk
                {
                    for(n=-1;n<2;n++)
                    {
                        if(board[i+m][j+n].type==NONE && board[i-m][j-n].type==currentPlayer.type)    //for any empty spaces where a new disk can be placed
                        {
                            printf("\ntype = %d (0=WHITE, 1=BLACK, 2=NONE), i=%d, j=%d", currentPlayer.type, i+1+m, j+1+n);   //+1 so it match the printed grid numbers
                        }

                    }
                }
            }
        }

    }



}
