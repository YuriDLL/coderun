#include <stdio.h>
#include <assert.h>

FILE *in, *out;
extern int testmain();

int main()
{
    in = fopen("../data/in.txt", "r");
    out = fopen("../data/out.txt", "w");
    if (stdin == NULL || stdout == NULL)
    {
        assert(0);
    }
    testmain();
    fclose(in);
    fclose(out);
}
