#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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


    board[1][1].type=board[0][2].type=board[1][2].type=board[2][2].type=board[2][3].type=board[2][1].type=board[3][2].type=board[4][2].type=board[4][3].type=board[4][4].type=WHITE;
    board[1][5].type=board[2][4].type=board[3][3].type=board[3][4].type=board[3][5].type=BLACK;

    //another sample board state

    }


void printBoard(disk board[SIZE][SIZE]){
    int i,j,k;
    j = 0;

    printf("\n    ");
    for(i=0; i< SIZE; i++){
        printf("%c   ",'A'+i);
    }
    for(i=0; i< SIZE; i++){
        printf("\n%d | ", i+1);

        for(j=0;j<SIZE; j++){
            switch(board[i][j].type){
                case BLACK:
                    printf("B | ");
                    break;
                case WHITE:
                    printf("W | ");
                    break;
                case NONE:
                    printf("  | ");
                    break;
                case AVAILABLE:
                    printf("o | ");
                default:
                    break;
            }
        }
        printf("\n   ");
        for (k=0; k<SIZE; k++){
            printf("----");
        }
    }
}
void computePositions(disk board[SIZE][SIZE], player currentPlayer, bool *cont)
{
    int i, j, m, n, x, y, counter=0;


    for(i=0;i<SIZE;i++)
    {
        for(j=0; j<SIZE;j++)        //loops through both dimensions of the array
        {
            if((board[i][j].type!=currentPlayer.type)&&(board[i][j].type!=NONE)&&(board[i][j].type!=AVAILABLE)) //i.e. if board[i][j].type is the opponent's colour
            {
                for(m=-1;m<2;m++)
                {                       //searching in a 3-by-3 area centred on the opponent's disk
                    for(n=-1;n<2;n++)
                    {
                        if(board[i+m][j+n].type==NONE&&(m!=0||n!=0/*is this bit still needed?*/)&&(i+m)>=0 && (i+m)<SIZE && (j+n)>=0 && (j+n)<SIZE)      //searching for any empty spaces where a new disk can be placed
                        {                                                                                        //also makes sure it's not trying to check a space past the edges of the board

                                 for(x=1;(i-(m*x))>=0 && (i-(m*x))<SIZE && (j-(n*x))>=0 && (j-(n*x))<SIZE;x++)  //considers the piece directly opposite the empty space relative to the anchor piece, then checks the piece after that in the same direction,
                                 {                                                                             //and keeps going until it reaches an edge

                                        if(board[i-(m*x)][j-(n*x)].type==currentPlayer.type)    //if any of those pieces we just considered are the same colour as the current player,
                                            {                                                //then current player is allowed to place a new piece in that empty space we found earlier on

                                                for(y=x-1;y>0;y--)
                                                {


                                                    if(board[i-(m*y)][j-(n*y)].type==NONE||board[i-(m*y)][j-(n*y)].type==AVAILABLE)
                                                    {
                                                        printf("\nI broke at %d, %d \n", i+m+1, j+n+1);
                                                        break;
                                                    }



                                                //still need to add check here to make sure there are no gaps between [i+m][j+n] and [i-(m*x)][j-(n*x)]
                                                //otherwise, like with the second example board state, you get it thinking that black is allowed to place a piece
                                                //at spots like (2,7) or (5,7) when they shouldn't be.

                                //To reiterate, system does currently correctly include all allowable positions, but also includes a few it shouldn't, so these need to be weeded out

                                                        printf("\nCurrent Player type = %d (0=WHITE, 1=BLACK, 2=NONE), Able to put a piece at i=%d, j=%d, Anchor piece is i=%d, j=%d", currentPlayer.type, i+m+1, j+n+1, i+1, j+1);   //+1 so it match the printed grid numbers
                                                        board[i+m][j+n].type=AVAILABLE;
                                                        counter++; // Looks if there are any available moves
                                                        //if we do end up using graphical representation on board for available spaces, make sure to clear those before next cycle,
                                                        //something like "if board[i][j]==AVAILABLE, set to NONE     Done?

                                                }

                                            }
                                 }
                        }
                    }
                }
            }
        }
    }
    if (counter == 0) // if there are no available moves, changes the bool variable to break the main game loop
        cont = false;
    puts("");
}

void printEndScreen(player player1, player player2)
{
    printf("\nPlayer1 %s, points: %d", player1.name, player1.points);
    printf("\nPlayer2 %s, points: %d", player2.name, player2.points);

    puts("");

    if(player1.points>player2.points)
    {
        printf("\nThe winner is %s", player1.name);
    }
     else if(player2.points>player1.points)
    {
        printf("\nThe winner is %s", player2.name);
    }
     else
    {
        printf("\nAre ties possible? If so, this is one.");
    }
    puts("");


}
// Function which prepares the board for the opponent's turn
void refreshBoard(disk board[SIZE][SIZE]){
    for (int x=0; x<SIZE; x++){
        for (int y=0; y<SIZE; y++){
            if (board[x][y].type == AVAILABLE){
                board[x][y].type = NONE;
            }
        }
    }
}
 // Player move function which takes the user's square selection
void playerMove(disk board[SIZE][SIZE], player currentPlayer){
    char xAxis;
    int yAxis, axisConvert;
    // Loop that checks if the input for the X Axis is valid (both uppercase and lowercase accepted)
    do{
        puts("Please enter a letter (horizontal axis) for your desired square:");
        xAxis = getchar();

        if (!(xAxis < 65 || xAxis > 72) || !(xAxis < 97 || xAxis > 104)){
            puts("Invalid character.");
        }
    }while(!(xAxis < 65 || xAxis > 72) || !(xAxis < 97 || xAxis > 104));
    // Converts the letters into a number to be used in the board position array (uppercase)
    if (xAxis > 64 && xAxis < 73){

        axisConvert = xAxis - 72 + 8;
    }
    // Converts the letters into a number to be used in the board position array (lowercase)
    if (xAxis > 96 && xAxis < 105){
        axisConvert = xAxis - 105 + 8;
    }

    // Loop that checks if the input for the Y Axis is valid
    do{
        puts("Please enter a number (vertical axis) for your desired square:");
        scanf("%d ", &yAxis);

        if (yAxis < 1 || yAxis > 8){
            puts("Invalid character.");
        }
    }while(yAxis < 1 || yAxis > 8);
    // Linked list initialisation protoype, does not work as of now for some reason, too late in the night to dig at it
    pMovePtr hAxis = NULL;
    hAxis = malloc(sizeof(PMove));
    hAxis->Axis=xAxis;
    hAxis->vAxis=malloc(sizeof(PMove));
    hAxis->vAxis->Axis=axisConvert;
    hAxis->vAxis->vAxis = NULL;
    // Checks if the user selected an available square and calls the function all over again if the square is invalid
    if (board[hAxis->Axis][hAxis->vAxis->Axis].type != AVAILABLE){
        puts("Invalid square selected.");
        free(hAxis->vAxis);
        free(hAxis);
        playerMove(board, currentPlayer);
    }
    // Makes the move
    else{
        board[hAxis->Axis][hAxis->vAxis->Axis].type = currentPlayer.type;
        // Needs an algorithm here to convert the opponent's disks into the current player's colour
    }
}
