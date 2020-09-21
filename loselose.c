// http://www.cse.yorku.ca/~oz/hash.html

unsigned long
hash(char *str, int M)
{
    int hash = 0,
        c;

    while (c = *str++)
        hash += c;

    return hash % M;
}
