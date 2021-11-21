#include "painter.h"

void clear()
{
    printf("\e[1;1H\e[2J");
}

void draw(int Matrix[10][10])
{
    int cnt = 0;
    printf("\n   ");
    for (int i = 1; i <= 9; i++)
    {
        printf("%2c", 'A' + i - 1);
        if (i % 3 == 0)
            printf("  ");
    }
    printf("\n    ——————————————————————\n");
    for (int i = 1; i <= 9; i++)
    {
        printf("%2d|", i);
        for (int j = 1; j <= 9; j++)
        {
            if (Matrix[i][j] > 0)
                printf("" GREEN "%2d" NONE "", Matrix[i][j]);
            else if (Matrix[i][j] < 0)
                printf("" CYAN "%2d" NONE "", -Matrix[i][j]);
            else
            {
                printf(" " UNDERLINE " " NONE "");
                cnt++;
            }

            if (j % 3 == 0)
                printf(" |");
        }
        printf("\n");
        if (i % 3 == 0)
            printf("    ——————————————————————\n");
    }
    //printf("total :%d \n", 81 - cnt);
}