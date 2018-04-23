
    #define SIZE 8

    enum colour{
        WHITE,
        BLACK,
        NONE,
        AVAILABLE
    };

    typedef struct position{
        int row;
        int col;
    } position;

    typedef struct disk{
        enum colour type;
        position pos;
    } disk;

    typedef struct player{
        char name[20];
        enum colour type;
        int points;
    } player;

    typedef struct pMove{
        int Axis;
        struct pMove * vAxis;
    } PMove;

    typedef PMove *pMovePtr;

    void initializePlayers(player *player1, player *player2);

    void initializeBoard(disk board[SIZE][SIZE]);

    void printBoard(disk board[SIZE][SIZE]);

    void computePositions(disk board[SIZE][SIZE], player currentPlayer, bool *cont);

    void printEndScreen(player player1, player player2);

    void refreshBoard(disk board[SIZE][SIZE]);

    void playerMove(disk board[SIZE][SIZE], player currentPlayer);

    void scores(disk board[SIZE][SIZE], player *player1, player *player2);
