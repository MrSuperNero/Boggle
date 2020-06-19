/*
 * Name: Mahdeen (Neo) Khan
 * NetID: msk74
 */

#define ALPHABET_SIZE 26  

// trie will be based on letters in alphabet
struct trie
{
    char key;
    char* dict_word;    // string to contain word if reached end of word
    int word_count;     // keeps track of how many times word appears in Boggle board
    struct trie* children[ALPHABET_SIZE];  // fixed-length array of pointers to tries 
};

// Define struct for trie pointer
typedef struct trie* Trie;

Trie make_node(void);

void insert_trie(Trie t, char* key);

Trie child_search(Trie t, char key);

void trie_destroy(Trie t);

void print_trie(Trie t);

void print_boggle(Trie t);

void print_c(Trie t);
