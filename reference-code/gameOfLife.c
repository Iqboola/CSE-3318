#include <stdio.h>
#include <stdlib.h>
#define DELAY 0

int **alloc2DArray(int rows, int cols)
{
    int **board = malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; i++)
    {
        board[i] = malloc(cols * sizeof(int));
    }
    return board;
}

void free2DArray(int **array, int rows)
{
    for(int i = 0; i < rows; i++)
    {
        free(array[i]);
    }
    free(array);
}

// Fills 2D Array with zeros
void init2DArray(int **array, int rows, int cols)
{
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            array[r][c] = 0;
        }
    }
}

void printBoard(int **board, int rows, int cols)
{
    printf("\n");
    for(int i = 0; i < 2 * cols + 1; i++)
    {
        printf("-");
    }
    printf("\n");
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            if(board[r][c] == 0)
            {
                printf("| ");
            }
            else
            {
                printf("|\u2588");
            }
        }
        printf("|\n");
    }
    for(int i = 0; i < 2 * cols + 1; i++)
    {
        printf("-");
    }
    printf("\n\n");
}

int countAliveNeighbors(int **board, int r, int c, int rows, int cols)
{
    int count = 0;
    for(int i = r - 1; i <= r + 1; i++)
    {
        for(int j = c - 1; j <= c + 1; j++)
        {
            if((i != r || j != c) && i >= 0 && j >= 0 && i < rows && j < rows && board[i][j] == 1)
            {
                count++;
            }
        }
    }
    return count;
}

// Returns new 2D array representing new board state
int **nextGeneration(int **board, int rows, int cols)
{
    int **newBoard = alloc2DArray(rows, cols);

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            int neighbors = countAliveNeighbors(board, r, c, rows, cols);
            // Decide whether newBoard[r][c] should be 0 or 1
            if(board[r][c])
            {
                // Cell is alive
                if(neighbors < 2)
                {
                    // Loneliness
                    newBoard[r][c] = 0;
                }
                else if(neighbors < 4)
                {
                    // Survival
                    newBoard[r][c] = 1;
                }
                else
                {
                    // Overcrowding
                    newBoard[r][c] = 0;
                }
            }
            else
            {
                if(neighbors == 3)
                {
                    newBoard[r][c] = 1;
                }
                else
                {
                    newBoard[r][c] = 0;
                }
            }
        }
    }

    free2DArray(board, rows);
    return newBoard;
}

int main(void)
{
    printf("........................ GAME OF LIFE ........................\n\n");
    int rows;
    int cols;
    printf("Enter Number of Rows : ");
    scanf("%d", &rows);
    printf("Enter Number of Columns : ");
    scanf("%d", &cols);

    printf("\n");

    int **board = alloc2DArray(rows, cols);
    init2DArray(board, rows, cols);

    printf("How many alive cells? ");
    int aliveCells;
    scanf("%d", &aliveCells);

    for(int i = 0; i < aliveCells; i++)
    {
        printf("Enter coordinates for cell %d: ", i + 1);
        int r, c;
        scanf("%d %d", &r, &c);
        board[r][c] = 1;
    }

    printBoard(board, rows, cols);

    

    int numGenerations;
    printf("How many generations? ");
    scanf("%d", &numGenerations);

    for(int i = 0; i < numGenerations; i++)
    {
        board = nextGeneration(board, rows, cols);
        printBoard(board, rows, cols);
        printf("\n");
        if(DELAY)
            system("sleep 0.3");
    }

    free2DArray(board, rows);
    return 0;
}