#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *Node;
typedef struct deque *Deque;
bool createD(Deque *);
bool isEmptyD(Deque *d);
bool addD(Deque *d, char *s);
bool remD(Deque *d, char **s);
bool headD(Deque *d, char **s);
bool pushD(Deque *d, char *s);
bool destroyD(Deque *d);
