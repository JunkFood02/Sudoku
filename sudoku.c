#include <time.h>
#include <stdlib.h>
#include "painter.h"
int getRandom();
int generateSudoku();
int fillSudoku(int, int);
int putValue(int, int, int);
int clearValue(int, int, int);
int Matrix[10][10];
int block[10][10], row[10][10], column[10][10];
int progress = 11;
int flag = 0;
int main()
{
    srand(time(NULL));
    generateSudoku();
    //draw(Matrix);
    draw(Matrix);
}
int generateSudoku()
{
    int num = 11;
    int i, j, newValue;
    while (num)
    {
        i = getRandom(), j = getRandom();
        if (!Matrix[i][j])
        {
            newValue = getRandom();
            if (putValue(i, j, newValue))
            {
                num--;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            fillSudoku(i, j);
    return 0;
}
int getRandom()
{
    return rand() % 9 + 1;
}
int putValue(int x, int y, int value)
{
    int res = 1;
    int blockNum = (y - 1) / 3 * 3 + (x - 1) / 3 + 1;
    if (block[blockNum][value])
    {
        //printf("Block %d has already a/an %d.\n", blockNum, value);
        res = 0;
    }
    if (row[y][value])
    {
        //printf("Row %d has already a/an %d.\n", y, value);
        res = 0;
    }
    if (column[x][value])
    {
        //printf("Column %d has already a/an %d.\n", x, value);
        res = 0;
    }
    if (res)
    {
        column[x][value] = 1;
        row[y][value] = 1;
        block[blockNum][value] = 1;
        Matrix[x][y] = value;
        //printf("put (%d,%d) value:%d\n", x, y, value);
    }
    return res;
}
int clearValue(int x, int y, int value)
{
    if (flag)
        return 0;
    int blockNum = (y - 1) / 3 * 3 + (x - 1) / 3 + 1;
    column[x][value] = 0;
    row[y][value] = 0;
    block[blockNum][value] = 0;
    Matrix[x][y] = 0;
    //printf("clear (%d,%d) value:%d\n", x, y, value);
    return 0;
}
int fillSudoku(int i, int j)
{
    if (i == 10)
        flag = 1;
    if (flag)
        return 0;
    if (Matrix[i][j])
    {
        if (j == 9)
            fillSudoku(i + 1, 1);
        else
            fillSudoku(i, j + 1);
    }
    else
    {
        for (int k = 1; k <= 9; k++)
        {
            if (putValue(i, j, k))
            {
                if (j == 9)
                    fillSudoku(i + 1, 1);
                else
                    fillSudoku(i, j + 1);
                clearValue(i, j, k);
            }
        }
    }
    return 0;
}
