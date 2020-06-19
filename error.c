/*
 * Name: Mahdeen (Neo) Khan
 * NetID: msk74
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "error.h"

void errorCheck(int rows, int col, char* board)
{
    // if the number of rows or columns are not positive integers
    if (rows < 1 || col < 1)
    {
        fprintf(stderr, "The number of rows and columns must be positive integers\n");
        exit(EXIT_FAILURE);
    }

    // board must be the same length as the number of rows times the number of columns
    if (strlen(board) != rows * col)
    {
        fprintf(stderr, "Board length must be equal to nRows x nCols\n");
        exit(EXIT_FAILURE);
    }

    // iterate through board and make sure everything is a letter
    for (int i = 0; i < strlen(board); i++)
    {
        if (!isalpha(board[i]) && board[i] != '_')
        {
            fprintf(stderr, "Board must be a letter from A-Z or an empty space (_)\n");
            exit(EXIT_FAILURE);
        }
    }
}
