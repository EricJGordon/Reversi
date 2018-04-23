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


    //board[1][1].type=board[0][2].type=board[1][2].type=board[2][2].type=board[2][3].type=board[2][1].type=board[3][2].type=board[4][2].type=board[4][3].type=board[4][4].type=WHITE;
    //board[1][5].type=board[2][4].type=board[3][3].type=board[3][4].type=board[3][5].type=BLACK;

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
                        gap = false;        //by default it believes there is no gap between the anchor piece and the other piece of current player's colour until provwn otherwise

                        if(board[i+m][j+n].type==NONE&&(m!=0||n!=0/*is this bit still needed?*/)&&(i+m)>=0 && (i+m)<SIZE && (j+n)>=0 && (j+n)<SIZE)      //searching for any empty spaces where a new disk can be placed
                        {                                                                                        //also makes sure it's not trying to check a space past the edges of the board

                                 for(x=1;(i-(m*x))>=0 && (i-(m*x))<SIZE && (j-(n*x))>=0 && (j-(n*x))<SIZE;x++)  //considers the piece directly opposite the empty space relative to the anchor piece, then checks the piece after that in the same direction,
                                 {                                                                             //and keeps going until it reaches an edge

                                        if(board[i-(m*x)][j-(n*x)].type==currentPlayer.type)    //if any of those pieces we just considered are the same colour as the current player,
                                            {                                                //then current player is allowed to place a new piece in that empty space we found earlier on

                                                for(y=x-1;y>0;y--)
                                                {
                                                    if(board[i-(m*y)][j-(n*y)].type==NONE||board[i-(m*y)][j-(n*y)].type==AVAILABLE)
                                                    {                                                   //catches scenarios where there is another piece of current players colour on the other side of the anchor piece
                                                       // printf("\nI broke at %d, %d \n", i+m+1, j+n+1);      //but separated by a gap, which is not allowed
                                                        gap = true;
                                                        break;                              //therefore it breaks out, fails the final if condition because of the bool, and moves on to the next piece
                                                    }
                                                }

                                                if(gap==false)
                                                {

                                                        printf("\nCurrent Player type = %d (0=WHITE, 1=BLACK, 2=NONE), Able to put a piece at i=%d, j=%d, Anchor piece is i=%d, j=%d", currentPlayer.type, i+m+1, j+n+1, i+1, j+1);   //+1 so it match the printed grid numbers
                                                        board[i+m][j+n].type=AVAILABLE;

                                                        counter++; // Looks if there are any available moves
                                                }       //could this just be changed to cont = true?
                                                    //(and then also moving the original bool cont = false declaration to the top of this function instead of main)

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


    //from here downwards is for testing what will ultimately be the playerMove logic, can be copied, changed, deleted, etc later

    /*printBoard(board);
    refreshBoard(board);

    int row, col;
    printf("\nInput row (1-8)\n");
    scanf(" %d", &row);
    row--;
    printf("\nInput column (1-8)\n");
    scanf(" %d", &col);
    col--;

    board[row][col].type=currentPlayer.type;

    for(m=-1;m<2;m++)
        {                       //searching in a 3-by-3 area centred on the your newly placed disk
        for(n=-1;n<2;n++)
            {

                //printf("type = %d. This should only be printed as an opponent's disk co-ordinates if it's a type 1 (in this example) \n", board[row+m][col+n].type);

            if((board[row+m][col+n].type!=currentPlayer.type)&&(board[row+m][col+n].type!=NONE)&&(board[row+m][col+n].type!=AVAILABLE)) //finds adjacent disks of opponent's colour
            {

            //yes in theory these should/could be combined into one if statement, but for whatevet reason this seems to work better, it was letting through all types when combined

            if((row+m)>=0 && (row+m)<SIZE && (col+n)>=0 && (col+n)<SIZE);   //without considering positions off of the board
                {
                for(x=1;(row+(m*x))>=0 && (row+(m*x))<SIZE && (col+(n*x))>=0 && (col+(n*x))<SIZE;x++)  //and keeps going in that direction until it reaches an edge
                    {
                         //printf("opponents disk at %d, %d\n", row+m+1, col+n+1); //+1 just to match printed grid numbers

                    if(board[row+(m*x)][col+(n*x)].type==currentPlayer.type)    //if any of those pieces we just considered are the same colour as the newly placed disk
                        {
                        for(y=x-1;y>0;y--)          //then change the colour of every disk inbetween the newly placed disk and the other same-coloured disk just found to currentplayer's colour
                            {
                            board[row+(m*y)][col+(n*y)].type=currentPlayer.type;
                            //implement score updates here
                            }
                        }
                    }
                }
              }
            }
        }

            printBoard(board);


*/
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
    int yAxis, axisConvert, n, x, y, m;
    // Loop that checks if the input for the X Axis is valid (both uppercase and lowercase accepted)
    do{
        puts("\nPlease enter a letter (horizontal axis) for your desired square:");
        scanf ("%c", &xAxis);
        printf("\nEntered character:%d \n", xAxis);
        if (!((xAxis >= 'a' && xAxis <= 'h') || (xAxis >= 'A' && xAxis <= 'H'))){
            puts("Invalid character.");
        }
    }while(!((xAxis >= 'a' && xAxis <= 'h') || (xAxis >= 'A' && xAxis <= 'H')));
    // Converts the letters into a number to be used in the board position array (uppercase)
    if (xAxis >= 'A' && xAxis <= 'H'){

        axisConvert = xAxis - 'H' + 8;
        printf("Converted x Axis : %d ", axisConvert);
    }
    // Converts the letters into a number to be used in the board position array (lowercase)
    if (xAxis >= 'a' && xAxis <= 'h'){
        axisConvert = xAxis - 'h' + 8;
        printf("Converted x Axis : %d ", axisConvert);
    }

    // Loop that checks if the input for the Y Axis is valid
    do{
        puts("\nPlease enter a number (vertical axis) for your desired square:");
        scanf("%d", &yAxis);

        if (yAxis < 1 || yAxis > 8){
            puts("Invalid character.");
        }
    }while(yAxis < 1 || yAxis > 8);
    // Linked list initialisation protoype, does not work as of now for some reason, too late in the night to dig at it

    pMovePtr hAxis = NULL;
    hAxis = malloc(sizeof(PMove));
    hAxis->Axis=axisConvert;
    hAxis->vAxis=malloc(sizeof(PMove));
    hAxis->vAxis->Axis= yAxis;
    hAxis->vAxis->vAxis = NULL;
    printf("X Axis Selection : %d\n", hAxis->Axis-1);
    printf("Y Axis Selection : %d\n", hAxis->vAxis->Axis-1);

    // Checks if the user selected an available square and calls the function all over again if the square is invalid
    if (board[hAxis->vAxis->Axis-1][hAxis->Axis-1].type != AVAILABLE){
        puts("Invalid square selected.");
        free(hAxis->vAxis);
        free(hAxis);
        playerMove(board, currentPlayer);
    }
    // Makes the move
    else{
        board[hAxis->vAxis->Axis-1][hAxis->Axis-1].type = currentPlayer.type;
        for(m=-1;m<2;m++)
        {                       //searching in a 3-by-3 area centred on the your newly placed disk
        for(n=-1;n<2;n++)
            {

                //printf("type = %d. This should only be printed as an opponent's disk co-ordinates if it's a type 1 (in this example) \n", board[axisConvert+m][yAxis+n].type);

            if((board[axisConvert+m][yAxis+n].type!=currentPlayer.type)&&(board[axisConvert+m][yAxis+n].type!=NONE)&&(board[axisConvert+m][yAxis+n].type!=AVAILABLE)) //finds adjacent disks of opponent's colour
            {

            //yes in theory these should/could be combined into one if statement, but for whatevet reason this seems to work better, it was letting through all types when combined

            if((axisConvert+m)>=0 && (axisConvert+m)<SIZE && (yAxis+n)>=0 && (yAxis+n)<SIZE);   //without considering positions off of the board
                {
                for(x=1;(axisConvert+(m*x))>=0 && (axisConvert+(m*x))<SIZE && (yAxis+(n*x))>=0 && (yAxis+(n*x))<SIZE;x++)  //and keeps going in that direction until it reaches an edge
                    {
                         //printf("opponents disk at %d, %d\n", axisConvert+m+1, yAxis+n+1); //+1 just to match printed grid numbers

                    if(board[axisConvert+(m*x)][yAxis+(n*x)].type==currentPlayer.type)    //if any of those pieces we just considered are the same colour as the newly placed disk
                        {
                        for(y=x-1;y>0;y--)          //then change the colour of every disk inbetween the newly placed disk and the other same-coloured disk just found to currentplayer's colour
                            {
                            board[axisConvert+(m*y)][yAxis+(n*y)].type=currentPlayer.type;
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
