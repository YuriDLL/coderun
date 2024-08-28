#include <stdio.h>
#include <assert.h>

extern FILE *stdin;
extern FILE *stdout;
extern int testmain();

int main()
{
    stdin = fopen("../data/in.txt", "r");
    stdout = fopen("../data/out.txt", "w");
    if (stdin == NULL || stdout == NULL)
    {
        assert(0);
    }
    testmain();
    fclose(stdin);
    fclose(stdout);
}