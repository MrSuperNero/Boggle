# Boggle
A C program that can be used to list every word in the standard input that is a "Boggle word". This program implements a trie ADT to store a dictionary of words inputted by the user upon running the program. 

## The Game
Boggle is a word game where players are tasked with finding words in sequences of adjacent letters. The game was designed by Allan Turoff.

## Making the Program
Run `make` to get the executable `Boggle`.

## Usage of Program
./Boggle nRows nCols board

1. `Boggle`
This is the executable

2. `nRows nCols`
These are the dimensions of the "Boggle Board" aka the standard input

3. `board`
A string that acts as a one-dimensional Boggle board. 

4. `Standard Input`
After running the executable, the user inputs words line by line (i.e. hit "Enter" when you finish writing a word). When finished, prompt terminal to reach EOF (do this by using ^D). The standard input should contain one word per line, each containing only alphabetic characters.  These words serve as the "Boggle dictionary" which are inputted into the trie ADT so they can be searched for in the "board" string.
