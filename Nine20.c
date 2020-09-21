#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "Hash.h"
#include "Deque.h"

#define quit(mess) fprintf(stderr, mess); exit(1)
#define M_INIT 1024

char **getChdn(char *board, int height, int width);
char *swap(char *board, int space, int toSwap);
char *isValid(char *board, int height, int width);
int equivalent(char *initial, char *goal);

int main(int argc, char **argv)
{
    // parse ipt args
    int HEIGHT = 3, WIDTH = 3;

    // check for number of args
    if (argc == 6) { // HEIGHT & WIDTH specified
        if (isdigit(argv[1][0]) && isdigit(argv[2][0])
                && strlen(argv[1]) == 1 && strlen(argv[2]) == 1) {
            HEIGHT = atoi(argv[1]);
            WIDTH = atoi(argv[2]);
        } else {
            quit("HEIGHT & WIDTH MUST BE INTS ON [2,5]\n");
        }

        if (HEIGHT > 5 || HEIGHT < 2 || WIDTH > 5 || WIDTH < 2) {
            quit("HEIGHT & WIDTH MUST BE INTS ON [2,5]\n");
        }
    } else if (argc != 4) {
        quit("Nine20 [HEIGHT WIDTH] MAXSTEPS INITIAL GOAL\n");
    }

    // get MAXSTEPS
    char *ptr;
    int MAXSTEPS = strtol(argv[argc-3], &ptr, 10);
    if (MAXSTEPS < 0 || strcmp(ptr, "")) {
        quit("MAXSTEPS MUST BE INT >= 0\n");
    }

    // get strings and check for validity
    char *INITIAL = isValid(argv[argc-2], HEIGHT, WIDTH),
        *GOAL = isValid(argv[argc-1], HEIGHT, WIDTH);

    // make sure INITIAL and GOAL contain same characters
    if ( !equivalent(INITIAL, GOAL) ) {
        quit("INITIAL AND GOAL MUST CONTAIN SAME CHARS\n");
    }    


    // BFS algorithm
    Table TAB = createT(M_INIT); 
    insertT(TAB, INITIAL, NULL, 0);
    Deque queue;
    createD(&queue);
    addD(&queue, INITIAL);

    Value parVal;
    int NSteps;
    char **chdn, *parPos, *chdPos;
    
    while ( !isEmptyD(&queue) ) {
        // rehash if necessary, storing new table in pointer
        rehashIfNec(&TAB);

        // get next item in queue
        remD(&queue, &parPos);
        parVal = searchT(TAB, parPos);
        NSteps = getNSteps(parVal);
        
        if (NSteps < MAXSTEPS) {
            chdn = getChdn(parPos, HEIGHT, WIDTH); 
            // iterate over children
            for (int i = 0; i < 4; i++) {
                chdPos = chdn[i];
                if (!chdPos) { // move isn't possible
                    ;
                } else if ( !strcmp(chdPos, GOAL) ) { // hit target
                    insertT(TAB, chdPos, parPos, NSteps+1);
                    backtrace(TAB, chdPos); // print path
                    exit(0);
                } else if ( !searchT(TAB, chdPos) ) { 
                    addD(&queue, chdPos);
                    insertT(TAB, chdPos, parPos, NSteps+1);
                } else {
                    free(chdPos);
                }
            }
            free(chdn);
        }
    }
}



/* returns new board with swaps tiles swapped
at indicated indices */
char *swap(char *board, int space, int toSwap)
{
    char *newBoard = strdup(board);
    newBoard[space] = newBoard[toSwap];
    newBoard[toSwap] = '-';
    return newBoard;
}

/* returns a quadruple of strings, each indicating
the next possible arrangement of tiles in the board
passed in. Some elements of quadruple may be NULL */
char **getChdn(char *board, int height, int width)
{
    char **nextPos = calloc(4, sizeof(char*));
    int space, column;

    // find index of space
    for (space = 0; board[space] != '-'; space++)
        ;
    
    // column in which index is located
    column = space % width;

    // assign next pos if move is possible
    nextPos[0] = (!column) ?
        NULL : swap(board, space, space-1);
    nextPos[1] = (column == width-1) ?
        NULL : swap(board, space, space+1);
    nextPos[2] = (space <= width-1) ?
        NULL : swap(board, space, space-width);
    nextPos[3] = (width*(height-1) <= space &&
        space <= height*width-1) ?
        NULL : swap(board, space, space+width);

    return nextPos;
}

// checks input string is valid
char *isValid(char *board, int height, int width)
{
    int foundSpace = 0, length = strlen(board);

    // check for valid length
    if (length != height*width) {
        quit("INPUT IS TOO LONG/SHORT\n");
    }

    // check for at most one dash and printable chars
    for (int i = 0; i < length; i++) {
        if (board[i] == '-') {
            if (foundSpace) {
                quit("INPUT CAN ONLY HAVE ONE SPACE\n");
            } else {
                foundSpace = 1;
            }
        } else if ( !isprint(board[i]) ) {
            quit("INPUT MUST CONTAIN PRINTABLE CHARACTERS\n");
        }
    }

    // check for exactly one space
    if (!foundSpace) {
        quit("INPUT MUST CONTAIN ONE SPACE\n");
    }

    return board;
}


/* determines whether INITIAL and GOAL contain
exclusively the same characters */
int equivalent(char *initial, char *goal)
{
    char *loc, *buffer = strdup(goal),
        *store = malloc(strlen(initial)+1);
    int length = strlen(initial), ans;

    // check that every char in INITIAL is in GOAL
    for (int i = 0; i < length; i++) {
        loc = strchr(buffer, initial[i]);
        if (loc) {
            strncpy(store, buffer, loc-buffer);
            store[loc-buffer] = '\0';
            strcat(store, loc+1);
            strcpy(buffer, store);
        } else {
            return 0;
        }
    }

    // check that no remaining chars in GOAL
    ans = strcmp(buffer, "");
    
    free(buffer);
    free(store);

    return ans == 0;
}
