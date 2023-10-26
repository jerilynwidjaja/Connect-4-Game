#include <stdio.h>

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2


/* Initialize the game board by setting all squares to EMPTY */
void initGameBoard(int gameBoard[6][7]) {
    
    int i, j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            gameBoard[i][j] = EMPTY;
        }
    }
}


/* Display the game board on the screen. */
void printGameBoard(int gameBoard[6][7]) {
    
    int i, j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (gameBoard[i][j] == EMPTY) {
                printf("| ");
            }
            else if (gameBoard[i][j] == CIRCLE) {
                printf("|O");
            }
            else if (gameBoard[i][j] == CROSS) {
                printf("|X");
            }
        }
        printf("|\n");
    }
    printf(" 1 2 3 4 5 6 7\n");
}



/* Ask the human player to place the mark.*/
void placeMarkByHumanPlayer(int gameBoard[6][7], int mark) {
    
    int count = 0;
    int column;
    scanf("%d", &column);
    while (column < 1 || column > 7) {
        printf("Input out of range. Please input again:\n");
        scanf("%d", &column);
    }
    for (int i = 5; i >= 0; i--) {
        if (gameBoard[i][column-1] == EMPTY) {
            gameBoard[i][column-1] = mark;
            return;
        }
        else if (gameBoard[i][column-1] != EMPTY){
            count++;
            while (count == 6){
                printf("Column is full. Please input again:\n");
                scanf("%d", &column);
                while (column < 1 || column > 7) {
                    printf("Input out of range. Please input again:\n");
                    scanf("%d", &column);
                }
                for (int i = 5; i >= 0; i--) {
                    if (gameBoard[i][column-1] == EMPTY) {
                        gameBoard[i][column-1] = mark;
                        return;
                    }
                }
            }
        }
    }
}



/* Return 1 if there is a winner in the game, otherwise return 0.
   Note: the winner is the current player indicated in main(). */
int hasWinner(int gameBoard[6][7]){
    
    int i, j;
    //check for horizontal row
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            if (gameBoard[i][j] != EMPTY) {
                if (gameBoard[i][j] == gameBoard[i][j+1] && gameBoard[i][j] == gameBoard[i][j+2] && gameBoard[i][j] == gameBoard[i][j+3]){
                    return 1;
                }
            }
        }
    }
    //check for vertical row
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 3; i++) {
            if (gameBoard[i][j] != EMPTY) {
                if (gameBoard[i][j] == gameBoard[i+1][j] && gameBoard[i][j] == gameBoard[i+2][j] && gameBoard[i][j] == gameBoard[i+3][j]){
                    return 1;
                }
            }
        }
    }
    //check for diagonal row
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 3; i++) {
            if (gameBoard[i][j] != EMPTY) {
                if (gameBoard[i][j] == gameBoard[i+1][j+1] && gameBoard[i][j] == gameBoard[i+2][j+2] && gameBoard[i][j] == gameBoard[i+3][j+3]){
                    return 1;
                }
            }
        }
        for (i = 5; i >= 3; i--) {
            if (gameBoard[i][j] != EMPTY) {
                if (gameBoard[i][j] == gameBoard[i-1][j+1] && gameBoard[i][j] == gameBoard[i-2][j+2] && gameBoard[i][j] == gameBoard[i-3][j+3]){
                    return 1;
                }
            }
        }
    }
    for (j = 6; j >= 4; j--) {
        for (i = 0; i < 3; i++) {
            if (gameBoard[i][j] != EMPTY) {
                if (gameBoard[i][j] == gameBoard[i+1][j-1] && gameBoard[i][j] == gameBoard[i+2][j-2] && gameBoard[i][j] == gameBoard[i+3][j-3]){
                    return 1;
                }
            }
        }
        for (i = 5; i >= 3; i--) {
            if (gameBoard[i][j] != EMPTY) {
                if (gameBoard[i][j] == gameBoard[i-1][j-1] && gameBoard[i][j] == gameBoard[i-2][j-2] && gameBoard[i][j] == gameBoard[i-3][j-3]){
                    return 1;
                }
            }
        }
    }
    return 0;
}



/* Return 1 if the game board is full, otherwise return 0. */
int isFull(int gameBoard[6][7]) {

    int i, j;
    int count = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if (gameBoard[i][j] != EMPTY) {
                count++;
            }
        }
    }
    if (count == 42) {
        return 1;
    }
    return 0;
}



/* Determine the next move of the computer player.*/
void placeMarkByComputerPlayer(int gameBoard[6][7], int mark) {
    int checkWinner;
    //Search for computer's winning move
    for (int j = 0; j < 7; j++) {
        for (int i = 5; i >= 0; i--) {
            if (gameBoard[i][j] == EMPTY) {
                gameBoard[i][j] = mark;
                checkWinner = hasWinner(gameBoard);
                if (checkWinner != 1) {
                    gameBoard[i][j] = EMPTY;
                }
                else {
                    return 0;
                }
            }
        }
    }
    //Search for human player's winning move.
    for (int j = 0; j < 7; j++) {
        for (int i = 5; i >= 0; i--) {
            if (gameBoard[i][j] == EMPTY) {
                gameBoard[i][j] = CIRCLE;
                checkWinner = hasWinner(gameBoard);
                gameBoard[i][j] = EMPTY;
                int b = gameBoard[i+1][j];
                if (checkWinner == 1) {
                    if (i != 0 && b != EMPTY) {
                        gameBoard[i][j] = mark;
                        return 0;
                    }
                    else if (i == 0){
                        gameBoard[i][j] = mark;
                        return 0;
                    }
                }
            }
        }
    }
    //Search for column with fewest marks, and in case of tie, take the larger column
    int column[7] = { 0 };
    int tmp, position;
    for (int j = 0; j < 7; j++) {
        int numOfEmptySquares = 0;
        for (int i = 5; i >= 0; i--) {
            if (gameBoard[i][j] == EMPTY) {
                numOfEmptySquares++;
            }
        }
        column[j] = numOfEmptySquares;
    }
    // Find smallest value of column[n] and then look through the columns again to see which one has same number
    int columnWithFewestMarks = column[6];
    for (int n = 5; n >= 0; n--) {
        tmp = column[n];
        if (tmp > columnWithFewestMarks) {
            columnWithFewestMarks = tmp;
        }
    }
    for (int j = 6; j >= 0; j--) {
        tmp = column[j];
        if (tmp == columnWithFewestMarks) {
            position = j;
            break;
        }
    }
    for (int i = 5; i >= 0; i--) {
        if (gameBoard[i][position] == EMPTY) {
            gameBoard[i][position] = mark;
            return 0;
        }
    }
}

/* The main function */
int main()
{
    /* Local variables */
    int gameBoard[6][7];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1             2: Player 2
    int gameContinue;       // 1: The game continues   0: The game ends
    int numOfHumanPlayers;  // 1 or 2

    /* Initialize the local variables */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameContinue = 1;
    printf("Enter the number of human players [1-2]:\n");
    scanf("%d", &numOfHumanPlayers);    

    /* Game start
       If there are two human players, they are Player 1 and Player 2
       If there is only one human player, he/she is Player 1 and another player is the computer player
       For both cases, Player 1 moves first and places the CIRCLE mark; while Player 2 (or the computer player) places the CROSS mark */

    printGameBoard(gameBoard);
    int checkFull;
    int checkWinner;
    if (numOfHumanPlayers == 2) {
        while (gameContinue == 1) {
            currentPlayer = 1;
            printf("Player 1's turn:\n");
            placeMarkByHumanPlayer(gameBoard, CIRCLE);
            printGameBoard(gameBoard);
            checkFull = isFull(gameBoard);
            if (checkFull == 1){
                gameContinue = 0;
                checkWinner =  hasWinner(gameBoard);
                if (checkWinner == 0) {
                    printf("Draw game.\n");
                    return 0;
                }
            }
            checkWinner = hasWinner(gameBoard);
            if (checkWinner == 1) {
                gameContinue = 0;
                printf("Congratulations! Player %d wins!\n", currentPlayer);
                return 0;
            }
            currentPlayer = 2;
            printf("Player 2's turn:\n");
            placeMarkByHumanPlayer(gameBoard, CROSS);
            printGameBoard(gameBoard);
            checkFull = isFull(gameBoard);
            if (checkFull == 1){
                gameContinue = 0;
                checkWinner =  hasWinner(gameBoard);
                if (checkWinner == 0) {
                    printf("Draw game.\n");
                    return 0;
                }
            }
            checkWinner = hasWinner(gameBoard);
            if (checkWinner == 1) {
                gameContinue = 0;
                printf("Congratulations! Player %d wins!\n", currentPlayer);
                return 0;
            }
        }
    }
    else if (numOfHumanPlayers == 1) {
        while (gameContinue == 1) {
            currentPlayer = 1;
            printf("Player 1's turn:\n");
            placeMarkByHumanPlayer(gameBoard, CIRCLE);
            printGameBoard(gameBoard);
            checkFull = isFull(gameBoard);
            if (checkFull == 1){
                gameContinue = 0;
                checkWinner =  hasWinner(gameBoard);
                if (checkWinner == 0) {
                    printf("Draw game.\n");
                    return 0;
                }
            }
            checkWinner = hasWinner(gameBoard);
            if (checkWinner == 1) {
                gameContinue = 0;
                printf("Congratulations! Player 1 wins!\n");
                return 0;
            }
            printf("Computer's turn:\n");
            placeMarkByComputerPlayer(gameBoard, CROSS);
            printGameBoard(gameBoard);
            checkFull = isFull(gameBoard);
            if (checkFull == 1){
                gameContinue = 0;
                checkWinner =  hasWinner(gameBoard);
                if (checkWinner == 0) {
                    printf("Draw game.\n");
                    return 0;
                }
            }
            checkWinner = hasWinner(gameBoard);
            if (checkWinner == 1) {
                gameContinue = 0;
                printf("Computer wins!\n");
                return 0;
            }
        }
    }
    return 0;
}
