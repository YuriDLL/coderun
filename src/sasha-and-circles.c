#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


extern FILE *stdin;		/* Standard input stream.  */
extern FILE *stdout;		/* Standard output stream.  */

int main1();

int entry1(int argc, char **argv)
{
    stdin = fopen("data/test1_input.txt", "r");
    stdout = fopen("data/test1_out.txt", "w");
    if (stdin == NULL || stdout == NULL)
    {
        printf("file err");
    }
    main1();
    fclose(stdin);
    fclose(stdout);
}

#define POINT_COUNT 4
#define NEAR(x, y, delta) (abs(x - y) < delta)

typedef struct {
    float x;
    float y;
} point_t;

point_t find_center(point_t points[3])
{
    float ma = (points[1].y - points[0].y) / (points[1].x - points[0].x);
    float mb = (points[2].y - points[1].y) / (points[2].x - points[1].x);
    float x_center = (ma * mb * (points[0].y - points[2].y) + mb * (points[0].x + points[1].x) - ma * (points[1].x + points[2].x)) /
                     (2 * (mb - ma));
    float y_center = (points[0].y + points[1].y) / 2 - (x_center  - (points[0].x + points[1].x) / 2) / ma;
    return (point_t){.x = x_center, .y = y_center};
}

int main1()
{
    point_t n[POINT_COUNT] = {0};

    for (int i=0; i < POINT_COUNT; i++)
    {
        scanf("%f %f", &n[i].x, &n[i].y);
    }
    point_t center1 = find_center(&n[0]);
    point_t center2 = find_center(&n[1]);

    if (!NEAR(center1.x, center2.x, 1e-9) || !NEAR(center1.x, center2.x, 1e-9))
    {
        printf("NO\n");
    }
    else
    {
        printf("YES\n");
        for (int i=0; i < POINT_COUNT; i++)
        {
            printf("%.12f %.12f\n", -(n[i].x - center1.x), -(n[i].y - center1.y));
        }
    }
    return 0;
}