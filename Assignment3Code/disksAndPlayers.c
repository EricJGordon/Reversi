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
    bool gap;

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
                        gap = false;
                              //by default it believes there is no gap between the anchor piece and the other piece of current player's colour until provwn otherwise
                        if(board[i+m][j+n].type==NONE&&(m!=0||n!=0)&&(i+m)>=0 && (i+m)<SIZE && (j+n)>=0 && (j+n)<SIZE)      //searching for any empty spaces where a new disk can be placed
                        {                                                                                        //also makes sure it's not trying to check a space past the edges of the board

                            for(x=1;(i-(m*x))>=0 && (i-(m*x))<SIZE && (j-(n*x))>=0 && (j-(n*x))<SIZE;x++)  //considers the piece directly opposite the empty space relative to the anchor piece, then checks the piece after that in the same direction,
                            {                                                                             //and keeps going until it reaches an edge

                                if(board[i-(m*x)][j-(n*x)].type==currentPlayer.type)    //if any of those pieces we just considered are the same colour as the current player,
                                {                                                //then current player is allowed to place a new piece in that empty space we found earlier on

                                    for(y=x-1;y>0;y--)
                                    {
                                        if(board[i-(m*y)][j-(n*y)].type==NONE||board[i-(m*y)][j-(n*y)].type==AVAILABLE)
                                        {                                       //catches scenarios where there is another piece of current players colour on the other side of the anchor piece
                                            gap = true;
                                            break;                              //therefore it breaks out, fails the final if condition because of the bool, and moves on to the next piece
                                        }
                                    }
                                    if(gap==false)
                                    {
                                        board[i+m][j+n].type=AVAILABLE;
                                        counter++;

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
    char yAxis;
    int xAxis, axisConvert, n, x, y, m;

    puts("*****************************************");
    printf("\t%s's turn\n", currentPlayer.name);
    puts("*****************************************");

    // Loop that checks if the input for the X Axis is valid (both uppercase and lowercase accepted)
    do{
        puts("Please enter the coordinates for your desired square (i.e. D3):");
        scanf(" %c", &yAxis);

        if (!((yAxis >= 'a' && yAxis <= 'h') || (yAxis >= 'A' && yAxis <= 'H'))){
            puts("Invalid character.");
        }

    }while(!((yAxis >= 'a' && yAxis <= 'h') || (yAxis >= 'A' && yAxis <= 'H')));

    // Converts the letters into a number to be used in the board position array (uppercase)
    if (yAxis >= 'A' && yAxis <= 'H'){

        axisConvert = yAxis - 'H' + 8;
    }

    // Converts the letters into a number to be used in the board position array (lowercase)
    if (yAxis >= 'a' && yAxis <= 'h'){
        axisConvert = yAxis - 'h' + 8;
    }

    // Loop that checks if the input for the Y Axis is valid
    do{
        scanf("%d", &xAxis);
        if (xAxis < 1 || xAxis > 8){
            puts("Invalid character.");
        }

    }while(xAxis < 1 || xAxis > 8);

    pMovePtr hAxis = NULL;
    hAxis = malloc(sizeof(PMove));
    hAxis->Axis=xAxis-1;
    hAxis->vAxis=malloc(sizeof(PMove));
    hAxis->vAxis->Axis= axisConvert-1;
    hAxis->vAxis->vAxis = NULL;
    printf("ARRAY X Axis Selection : %d\n", hAxis->Axis);
    printf("ARRAY Y Axis Selection : %d\n", hAxis->vAxis->Axis);

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
        for(m=-1;m<2;m++)
        {                       //searching in a 3-by-3 area centred on the your newly placed disk
            for(n=-1;n<2;n++)
            {

                if((board[hAxis->Axis+m][hAxis->vAxis->Axis+n].type!=currentPlayer.type)&&(board[hAxis->Axis+m][hAxis->vAxis->Axis+n].type!=NONE)&&(board[hAxis->Axis+m][hAxis->vAxis->Axis+n].type!=AVAILABLE)) //finds adjacent disks of opponent's colour
                {

                //yes in theory these should/could be combined into one if statement, but for whatevet reason this seems to work better, it was letting through all types when combined

                    if((hAxis->Axis+m)>=0 && (hAxis->Axis+m)<SIZE && (hAxis->vAxis->Axis+n)>=0 && (hAxis->vAxis->Axis+n)<SIZE);   //without considering positions off of the board
                    {
                        for(x=1;(hAxis->Axis+(m*x))>=0 && (hAxis->Axis+(m*x))<SIZE && (hAxis->vAxis->Axis+(n*x))>=0 && (hAxis->vAxis->Axis+(n*x))<SIZE;x++)  //and keeps going in that direction until it reaches an edge
                        {


                            if(board[hAxis->Axis+(m*x)][hAxis->vAxis->Axis+(n*x)].type==currentPlayer.type)    //if any of those pieces we just considered are the same colour as the newly placed disk
                            {
                                for(y=x-1;y>0;y--)          //then change the colour of every disk inbetween the newly placed disk and the other same-coloured disk just found to currentplayer's colour
                                {
                                    board[hAxis->Axis+(m*y)][hAxis->vAxis->Axis+(n*y)].type=currentPlayer.type;
                                    //implement score updates here
                                }
                            }
                        }
                    }
                }
            }
        }// Needs an algorithm here to convert the opponent's disks into the current player's colour
    }

}


void scores(disk board[SIZE][SIZE], player *player1, player *player2)
{
    int i, j;

    player1->points=0;
    player2->points=0;

    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            if(board[i][j].type==player1->type)
            {
                player1->points++;
            }

            if(board[i][j].type==player2->type)
            {
                player2->points++;
            }
        }
    }

    printf("\n%s has %d points, %s has %d\n", player1->name, player1->points, player2->name, player2->points);
}
