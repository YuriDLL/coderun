#include <stdio.h>

#define main testmain

extern FILE *in, *out;

#define printf(...) fprintf(out, __VA_ARGS__)
#define scanf(...) fscanf(in, __VA_ARGS__)