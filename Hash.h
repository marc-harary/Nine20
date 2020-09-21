// Marc Harary (mah258)
typedef struct value *Value;
typedef struct table *Table;

void insertT(Table tab, char *pos, char *from, int nSteps);
void backtrace(Table tab, char *end);
void rehashIfNec(Table *tab);
char *getPos(Value val);
int getNSteps(Value val);
Value searchT(Table tab, char *pos);
Table createT(int M);
