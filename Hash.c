#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Hash.h"
#include "Deque.h"
#include "loselose.c"

#define MAX_LAMBDA 8

// triple to store data for pos
struct value {
    char *pos, *from;
    int nSteps;
};

// implements hash table
struct table {
    Value **vals; // 2D array of value-pointers
    int *NRows, M, N; // # of values at key, M, & N
};

void insertT(Table tab, char *pos, char *from, int nSteps)
{
    // make value
    Value store, *newCol, newVal = malloc(sizeof(struct value));
    newVal->pos = pos;
    newVal->from = from;
    newVal->nSteps = nSteps;

    // get column and # of rows
    int key=hash(pos,tab->M),
        NRows=tab->NRows[key],
        cont;

    // insert
    if (NRows == 0) { // is first item at key
        newCol = calloc(1, sizeof(Value));
        newCol[0] = newVal;  
    } else { // collision
        newCol = realloc(tab->vals[key],
                        (NRows+1)*sizeof(Value));
        newCol[NRows] = newVal;
        // bubble sort
        do {
            cont = 0;
            for (int i = NRows; i > 0; i--) {
                if (strcmp(newCol[i]->pos,newCol[i-1]->pos) < 0) {
                    store = newCol[i];
                    newCol[i] = newCol[i-1];
                    newCol[i-1] = store;
                    cont = 1; 
                }
            }
        } while (cont);
    }

    // update metadata
    tab->vals[key] = newCol;
    tab->NRows[key]++;
    tab->N++;
}

/* creates new table with index M */
Table createT(int M)
{
    // init table pointer
    Table newTable;
    newTable = malloc(sizeof(struct table));

    // init members
    Value **vals = calloc(M, sizeof(Value*));
    int *NRows = calloc(M, sizeof(int));
    for (int i = 0; i < M; i++) // init vals to 0
        NRows[i] = 0;
    
    // store
    newTable->NRows = NRows;
    newTable->vals = vals;
    newTable->M = M;
    newTable->N = 0;

    return newTable;
}


Value searchT(Table tab, char *pos)
{
    Value target = NULL;
    int key = hash(pos, tab->M);
    Value *col = tab->vals[key]; // get column

    // get row in column
    for (int i = 0; i < tab->NRows[key]; i++) {
        if (strcmp(col[i]->pos, pos) == 0) {
            target = col[i];
        }
    }

    return target;
}

/* takes table and backtracks across table
to track path taken to end and print as stack */
void backtrace(Table tab, char *end)
{
    Deque path; // stack to store positions
    createD(&path);
    int pathLength = 0;
    char *curPos = end;
    Value curValue;

    // hop across positions until we get NULL
    do {
        // store position
        pushD(&path, curPos);
        pathLength++;
        // jump to next position
        curValue = searchT(tab, curPos);
        curPos = curValue->from;
    } while (curPos);

    // print
    while ( !isEmptyD(&path) ) {
        remD(&path, &curPos);
        puts(curPos);
    }

    destroyD(&path);
}

// returns steps
int getNSteps(Value val)
{
    return val->nSteps;
}

/* checks if table needs to be rehashed, and
stores rehashed table in pointer to original */
void rehashIfNec(Table *tab)
{
    if ((*tab)->N / (*tab)->M >= MAX_LAMBDA) {
        // malloc new table
        Table newTab = createT(MAX_LAMBDA * (*tab)->M);
        // copy values over from original
        Value *col;
        for (int i = 0; i < (*tab)->M; i++) { // iterate over cols
            col = (*tab)->vals[i];
            for (int j = 0; j < (*tab)->NRows[i]; j++) { // rows
                insertT(newTab, col[j]->pos, col[j]->from,
                        col[j]->nSteps);
            }
        }
        // update
        free(*tab);
        *tab = newTab;
    }
}
