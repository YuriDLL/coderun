#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINE_NUM 10

int test(FILE *input, FILE *output);

int main()
{
    FILE *test_input, *test_output;
    test_input = fopen("data/test1_input.txt", "r");
    test_output = fopen("data/test1_out.txt", "w");
    if (test_input == NULL || test_output == NULL)
    {
        printf("file err");
    }
    test(test_input, test_output);
    fclose(test_input);
    fclose(test_output);
}

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

int test(FILE *input, FILE *output)
{
    fscanf(input, "%d %d %d", &row_count, &column_count, &mine_count);
    for (int i = 0; i < mine_count; i++)
    {
        int mine_row, mine_column;
        fscanf(input, "%d %d", &mine_row, &mine_column);
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
            fprintf(output, "%c ", print_sym != ('0' + MINE_NUM) ? print_sym : '*');
        }
        fprintf(output, "\n");
    }
    return 0;
}