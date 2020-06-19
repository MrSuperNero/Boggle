/*
 * Name: Mahdeen (Neo) Khan
 * NetID: msk74
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "trie.h"
#include "error.h"

void trie_dfs(Trie t, char* board, char key, int board_index, bool* visited, bool t_flag, int rows, int cols);
int findRow(int index, int rows, int cols);


int main(int argc, char* argv[])
{
    char* board = NULL;
    int nRows, nCols;

    // inputs for dicionary
    char* line = NULL; 
    size_t n = 0;
    bool spec_char = false;
    
    if (argc < 4 || argc > 6)
    {
        fprintf(stderr, "./Boggle [-c] [-t] nRows nCols board\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 6 && strcmp(argv[1], "-c") != 0)
    {
        fprintf(stderr, "./Boggle [-c] [-t] nRows nCols board\n");
        exit(EXIT_FAILURE);
    }

    board = argv[argc - 1];

    // convert all chars in board to lowercase
    for (int i = 0; i < strlen(board); i++)
    {
        board[i] = tolower(board[i]);
    }

    nCols = atoi(argv[argc - 2]);
    nRows = atoi(argv[argc - 3]);

    errorCheck(nRows, nCols, board);

    Trie root = make_node();

    // read in lines from standard input into dictionary
    while (getline (&line, &n, stdin) != -1) 
    {
        // remove trailing newline
        if (line[strlen(line) - 1] == '\n')   
        {
            line[strlen(line) - 1] = '\0';
        }

        // check to make sure that there are no special characters in input
        for (int i = 0; i < strlen(line); i++)
        {
            // if there is a special character, break and update bool
            if (!isalpha(line[i]))
            {
                spec_char = true;
                break;
            }

            line[i] = tolower(line[i]);
        }

        // continue if special char detected
        if (spec_char)
        {
            spec_char = false;
            continue;
        }
        
        // insert line into the trie
        insert_trie(root, strdup(line)); 

        free(line);
        line = NULL;
        n = 0;
    }

    int board_length = strlen(board);  // calculate length of board
    bool* visited = malloc(sizeof(bool) * board_length);    // make array that keeps track of visited letters in board (indexes map to each other)
    bool t_flag = (strcmp("-t", argv[1]) == 0 || strcmp("-t", argv[2]) == 0);

    // depth first search of graph and board
    for (int i = 0; i < strlen(board); i++)
    {
        // initialize visited array for every new word
        // for some reason, words are recognized on their own but when inputted together, are already visited
        for (int i = 0; i < board_length; i++)
        {
            *(visited + i) = false;
        }

        trie_dfs(root, board, board[i], i, visited, t_flag, nRows, nCols);
    }

    if (strcmp(argv[1], "-c") == 0)
    {
        print_c(root);
    }

    if (strcmp(argv[1], "-c") != 0)
    {
        print_boggle(root);
    }

    trie_destroy(root);
    free(line);
    free(visited);

    exit(EXIT_SUCCESS);
}

void trie_dfs(Trie t, char* board, char key, int board_index, bool* visited, bool t_flag, int rows, int cols)
{   
    if (t == NULL)    {   return;   }   // check to make sure that there is a trie in the first place

    // wildcard
    if (key == '_')
    {
        // go through all children of current node
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            // recursive call with valid keys
            if (t->children[i] != NULL)
            {
                *(visited + board_index) = false; // make sure that the visited array is set to false so we can go through all possible letters
                trie_dfs(t, board, t->children[i]->key, board_index, visited, t_flag, rows, cols);
            }
        }
        return;
    }

    // check if key is child of node and go to that child
    t = child_search(t, key);

    // key is not a child, so return and reset visited values from key index onwards
    // need to find better way of updating visited field
    if (t == NULL)    
    {   
        return;   
    }

    // check if we reached a word
    if (t->dict_word != NULL)
    {
        t->word_count += 1;
    }

    *(visited + board_index) = true;  // mark letter as visited

    int letterRow = findRow(board_index, rows, cols);  // find the row of letter
    int letterCol = board_index % cols; // find the column of letter

    // iterate through rows
    for (int i = letterRow - 1; i < letterRow + 2; i++)
    {
        if (i < 0)  { continue; }
        if (i >= rows)  { break; }

        // iterate through columns
        for (int j = letterCol - 1; j < letterCol + 2; j++)
        {
            if (j < 0)  { continue; }
            if (j >= cols)  { break; }

            // if the next move is the same key 
            // or if the t flag was invoked and the next letter has been visited already, 
            // skip
            if ((i * cols + j) == board_index || (t_flag && *(visited + (i * cols + j))))
            {
                continue;
            }

            // else, do recursive call on moves
            trie_dfs(t, board, board[(i * cols + j)], (i * cols + j), visited, t_flag, rows, cols);

            *(visited + (i * cols + j)) = false;  // reset moves being false after reaching word
        }
    }
}

int findRow(int index, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        if (cols * (i + 1) > index)
        {
            return i;
        }
    }

    return index;
}
