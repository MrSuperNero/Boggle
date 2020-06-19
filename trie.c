/*
 * Name: Mahdeen (Neo) Khan
 * NetID: msk74
 */

// used https://www.techiedelight.com/trie-implementation-insert-search-delete/ and 
// Aspnes's notes as a model for my trie implementation

// File that contains functions for the trie data structure
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

Trie make_node(void)
{
    // make the trie and initialize it
    Trie t = malloc(sizeof(struct trie));
    t->key = '\0';
    t->dict_word = NULL;
    t->word_count = 0;
    
    for (int i = 0; i < 26; i++)
    {
        t->children[i] = NULL;
    }

    return t;
}

void insert_trie(Trie t, char* key)
{
    int trie_index;

    for (int i = 0; i < strlen(key); i++)
    {
        trie_index = key[i] - 'a';

        // if no node prior, make one
        if (t->children[trie_index] == NULL)
        {
            t->children[trie_index] = make_node();
            t->children[trie_index]->key = key[i];
        }

        if (i == strlen(key) - 1)
        {
            t->children[trie_index]->dict_word = key;
        }

        t = t->children[trie_index];
    }
}

// recursive depth search
Trie child_search(Trie t, char key)
{
    int trie_index = key - 'a';
    
    if (t->children[trie_index] == NULL)
    {
        return NULL;
    }

    return t->children[trie_index];
}

void trie_destroy(Trie t)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (t->children[i] != NULL)
        {
            trie_destroy(t->children[i]);
        }
    }

    free(t->dict_word);
    free(t);
}

// printing using recursion
void print_trie(Trie t)
{
    if (t->dict_word != NULL)
    {
        printf("%s: %i\n", t->dict_word, t->word_count);
    }

    // go through all children to print words in trie
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (t->children[i] == NULL)
        {
            continue;
        }
        print_trie(t->children[i]);
    }
}

// print words from boggle board
void print_boggle(Trie t)
{
    if (t->dict_word != NULL && t->word_count > 0)
    {
        printf("%s: %i\n", t->dict_word, t->word_count);
    }

    // go through all children to print words in trie
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (t->children[i] != NULL)
        {
            print_boggle(t->children[i]);
        }
    }
}

void print_c(Trie t)
{
    if (t->dict_word != NULL && t->word_count == 0)
    {
        printf("%s\n", t->dict_word);
    }

    // go through all children to print words in trie
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (t->children[i] != NULL)
        {
            print_c(t->children[i]);
        }
    }
}
