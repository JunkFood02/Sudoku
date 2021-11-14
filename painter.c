
void clear()
{
    printf("\e[1;1H\e[2J");
}
void draw(int Matrix[10][10])
{
    printf("   ");
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
            printf("\e[1;32m%2d\e[0m", Matrix[i][j]);
            if (j % 3 == 0)
                printf(" |");
        }
        printf("\n");
        if (i % 3 == 0)
            printf("    ——————————————————————\n");
    }
}