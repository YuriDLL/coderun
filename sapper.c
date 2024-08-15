#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern FILE *stdin;		/* Standard input stream.  */
extern FILE *stdout;		/* Standard output stream.  */

int test();

int main()
{
    stdin = fopen("data/test1_input.txt", "r");
    stdout = fopen("data/test1_out.txt", "w");
    if (stdin == NULL || stdout == NULL)
    {
        printf("file err");
    }
    test();
    fclose(stdin);
    fclose(stdout);
}

#define MINE_NUM 10

int field[100][100] = {};
int row_count, column_count, mine_count;

void increment(int row, int column)
{
    if ((0 <= row && row < row_count) &&
        (0 <= column && column < column_count) &&
        field[row][column] != MINE_NUM)
    {
        field[row][column]++;
    }
}

void increment_near(int row, int column)
{
    for (int near_row = -1; near_row < 2; near_row++)
    {
        for(int near_column = -1; near_column < 2; near_column++)
        {
            increment(row + near_row, column + near_column);
        }
    }
}

int test()
{
    scanf("%d %d %d", &row_count, &column_count, &mine_count);
    for (int i = 0; i < mine_count; i++)
    {
        int mine_row, mine_column;
        scanf("%d %d", &mine_row, &mine_column);
        mine_row--;
        mine_column--;
        field[mine_row][mine_column] = MINE_NUM;
        increment_near(mine_row, mine_column);
    }
    for (int row = 0; row < row_count; row++)
    {
        for (int column = 0; column < column_count; column++)
        {
            char print_sym = field[row][column] + '0';
            printf("%c ", print_sym != ('0' + MINE_NUM) ? print_sym : '*');
        }
        printf("\n");
    }
    return 0;
}