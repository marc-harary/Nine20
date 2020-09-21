#include "Deque.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    char *line;
};
// typedef struct node *Node;

struct deque {
    Node head;
    Node tail;
};

// Implementation of createD()
bool createD(Deque *d)
{
    Deque newD = malloc(sizeof(struct deque));
    if (!newD) return false;

    *d = newD;
    (*d)->head = (*d)->tail = NULL;
    return true;
}

// Implementation of isEmptyD()
bool isEmptyD(Deque *d)
{
    if (!d) return NULL;
    return ((*d)->head==NULL && (*d)->tail==NULL);
}


// Implementation of addD()
bool addD(Deque *d, char *s)
{
    Node newNode = malloc(sizeof(struct node));
    if (!newNode) return false;
    
    // initialize
    newNode->line = s;
    newNode->next = NULL;

    // 
    if ((*d)->tail == NULL) // if tail was empty, newNode becomes tail
        (*d)->tail = newNode;
    else { // otherwise just append
        newNode->next = (*d)->tail;
        (*d)->tail = newNode;
    }

    return true;
}


// Implementation of remD()
bool remD(Deque *d, char **s)
{
    // if both head and tail are empty
    if (isEmptyD(d)) return false;

    // just head's empty--transfer to head
    if ((*d)->head == NULL) {
        Node cur;
        while ((cur=(*d)->tail) != NULL) {
            pushD(d, cur->line); // push line onto head
            (*d)->tail = (*d)->tail->next; // pop tail
            free(cur); // destroy tail
        }
    }

    // pop head
    Node oldHead = (*d)->head;
    *s = (*d)->head->line;
    (*d)->head = (*d)->head->next;
    free(oldHead);

    return true;
}


// Implementation of headD()
bool headD(Deque *d, char **s)
{   
    // if both head and tail are empty
    if (isEmptyD(d)) return false;

    // just head's empty--transfer to head
    if ((*d)->head == NULL) {
        Node cur;
        while ((cur=(*d)->tail) != NULL) {
            pushD(d, cur->line); // push line onto head
            (*d)->tail = (*d)->tail->next; // pop tail
            free(cur); // destroy tail
        }
    }
    
    *s = (*d)->head->line;
    return true;
}


// Implementation of pushD()
bool pushD(Deque *d, char *s)
{
    // malloc and test for success
    Node newNode = malloc(sizeof(struct node));
    if (!newNode) return false;

    newNode->line = s;
    newNode->next = NULL;
    // if head was empty, newNode becomes head
    if ((*d)->head == NULL)
        (*d)->head = newNode;
    else { // otherwise just append
        newNode->next = (*d)->head;
        (*d)->head = newNode;
    }

    return true;
}


// Implementation of destroyD()
bool destroyD(Deque *d)
{
    if (*d == NULL) return false;

    // keep removing while full
    char *buffer = NULL;
    while (remD(d, &buffer))
        ;
        
    free(*d);
    *d = NULL;
    return true;
}
