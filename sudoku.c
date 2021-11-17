#include "sudoku.h"

int Matrix[10][10];
int block[10][10], row[10][10], column[10][10];
int levelNum[4] = {10, 15, 20, 25};
int flag = 0;
int level, progress;
int main()
{
    srand(time(NULL));
    level = Start();
    generateSudoku();
    progress = levelNum[level];
    generatePuzzle(progress);
    while (progress)
    {
        }
    draw(Matrix);
}
int generateSudoku()
{
    int num = 10;
    int i, j, newValue;
    while (num)
    {
        i = getRandom(), j = getRandom();
        if (!Matrix[i][j])
        {
            newValue = getRandom();
            if (putValue(i, j, newValue, 1))
            {
                num--;
            }
        }
    }
    solveSudoku(1, 1, 1);
    return 0;
}
int getRandom()
{
    return rand() % 9 + 1;
}
int getRandomMod(int mod)
{
    return rand() % mod + 1;
}
int putValue(int x, int y, int value, int fill)
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
        if (fill)
            Matrix[x][y] = value;
        //printf("put (%d,%d) value:%d\n", x, y, value);
    }
    return res;
}
int clearValue(int x, int y, int clear)
{
    if (flag)
        return 0;
    int value = Matrix[x][y];
    int blockNum = (y - 1) / 3 * 3 + (x - 1) / 3 + 1;
    column[x][value] = 0;
    row[y][value] = 0;
    block[blockNum][value] = 0;
    if (clear)
        Matrix[x][y] = 0;
    //printf("clear (%d,%d) value:%d\n", x, y, value);
    return 0;
}
int solveSudoku(int i, int j, int fill)
{
    if (i == 10)
        flag = 1;
    if (flag)
        return 1;
    if (Matrix[i][j])
    {
        if (j == 9)
            solveSudoku(i + 1, 1, fill);
        else
            solveSudoku(i, j + 1, fill);
    }
    else
    {
        for (int k = 1; k <= 9; k++)
        {
            if (putValue(i, j, k, fill))
            {
                if (j == 9)
                    solveSudoku(i + 1, 1, fill);
                else
                    solveSudoku(i, j + 1, fill);
                clearValue(i, j, fill);
            }
        }
    }
    return 0;
}
int generatePuzzle(int level)
{
    int x, y, temp;
    while (level)
    {
        x = getRandom();
        y = getRandom();
        if (!Matrix[x][y])
            continue;
        temp = Matrix[x][y];
        for (int i = 1; i <= 9; i++)
        {
            if (i == temp)
                continue;
            flag = 0;
            clearValue(x, y, 1);
            if (putValue(x, y, i, 1))
            {
                if (solveSudoku(1, 1, 0))
                {
                    putValue(x, y, temp, 1);
                    break;
                }
            }
            else
            {
                level--;
                break;
            }
        }
    }
    return 1;
}
