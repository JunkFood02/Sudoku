#include "sudoku.h"

int Matrix[10][10];
int tempMatrix[10][10];
int block[10][10], row[10][10], column[10][10], mark[10][10];
int levelNum[5] = {10, 20, 30, 42, 64};
char difficulty[5][20] = {"Very Easy", "Easy", "Normal", "Hard", "Very Hard"};
int flag = 0;
int level, progress;
time_t tt1, tt2;

int main()
{
    clear();
    level = Start();
    generateSudoku();
    progress = levelNum[level];
    generatePuzzle(progress);
    draw(Matrix);
    while (progress)
    {
        progress += InputNumber();
    }
    tt2 = time(NULL);
    printf("\nYou solved this Sudoku in %ld seconds!\n", tt2 - tt1);
    return 0;
}
int generateSudoku()
{
    tt1 = time(NULL);
    srand(tt1);
    memset(Matrix, 0, sizeof(Matrix));
    memset(row, 0, sizeof(row));
    memset(block, 0, sizeof(block));
    memset(column, 0, sizeof(column));
    memset(mark, 0, sizeof(mark));
    flag = 0;
    int num = 10;
    int i, j, newValue;
    while (num)
    {
        i = getRandom(), j = getRandom();
        if (!Matrix[i][j])
        {
            newValue = getRandom();
            if (checkLegal(i, j, newValue))
            {
                fillNumber(i, j, newValue);
                num--;
            }
        }
    }
    solveSudoku(1, 1, 1);
    memcpy(tempMatrix, Matrix, sizeof(Matrix));
    return 1;
}
int getRandom()
{
    return rand() % 9 + 1;
}

void solveSudoku(int i, int j, int FillOut)
{
    if (i == 10)
        flag = 1;
    if (flag)
        return;
    if (Matrix[i][j])
    {
        if (j == 9)
            solveSudoku(i + 1, 1, FillOut);
        else
            solveSudoku(i, j + 1, FillOut);
    }
    else
    {
        for (int k = 1; k <= 9; k++)
        {
            if (checkLegal(i, j, k))
            {
                fillNumber(i, j, k);
                if (j == 9)
                    solveSudoku(i + 1, 1, FillOut);
                else
                    solveSudoku(i, j + 1, FillOut);
                if (flag && FillOut)
                    return;
                clearNumber(i, j);
            }
        }
    }
}

int generatePuzzle(int progress)
{
    int x, y, temp, cnt = 0;
    while (progress)
    {
        if (cnt == 81)
            return 1;
        x = getRandom(), y = getRandom();
        if (!Matrix[x][y] || mark[x][y])
            continue;
        temp = Matrix[x][y];
        clearNumber(x, y);
        for (int i = 1; i <= 9; i++)
        {
            flag = 0;
            if (i == temp)
                continue;
            if (checkLegal(x, y, i))
            {
                fillNumber(x, y, i);
                solveSudoku(1, 1, 0);
                if (flag)
                {
                    clearNumber(x, y);
                    fillNumber(x, y, temp);
                    break;
                }
                else
                    clearNumber(x, y);
            }
        }
        if (!flag)
        {
            progress--;
            cnt++;
        }
        else
        {
            mark[x][y] = 1;
            cnt++;
        }
    }
    return 1;
}
int Start()
{
    printf("" REVERSE "Soduku" NONE "\nInput the level of Puzzle:\n");
    printf("[0]Very Easy [1]Easy [2]Normal [3]Hard [4]Very Hard\n");
    int n;
    scanf("%d", &n);
    if (n >= 0 && n <= 4)
    {
        printf("Generate Sudoku Puzzle for Difficulty [" WHITE "%s" NONE "]\n", difficulty[n]);
        return n;
    }
    else
    {
        clear();
        printf("Invalid Input!\n");
        return Start();
    }
}
int InputNumber()
{
    printf("\nInput a Position with an Operation:\n");
    printf("Insert: " CYAN "A23" NONE " put 3 into Row A Column 2\n");
    printf("Delete: " BLUE "C4D" NONE " remove number from Row C Column 4\n");
    char c[100];
    scanf("%3s", c);
    if (!strcmp(c, "IDK"))
    {
        printf("Print The Answer\n");
        draw(tempMatrix);
        return InputNumber();
    }
    int n0, n1, n2;
    n0 = c[0] - 'A' + 1;
    n1 = c[1] - '0';
    n2 = c[2] - '0';
    if (n0 < 1 || n0 > 9 || n1 < 1 || n1 > 9)
    {
        clear();
        draw(Matrix);
        printf("Invalid Input!\n");
        return InputNumber();
    }
    if (c[2] == 'D')
    {
        if (!Matrix[n1][n0])
        {
            clear();
            draw(Matrix);
            printf("Position %c%d is empty.\n", c[0], n1);
            return InputNumber();
        }
        else if (Matrix[n1][n0] > 0)
        {
            clear();
            draw(Matrix);
            printf("Number of Position %c%d cannot be clear.\n", c[0], n1);
            return InputNumber();
        }
        clear();
        clearNumber(n1, n0);
        draw(Matrix);
        return 1;
    }
    else if (n2 >= 1 && n2 <= 9)
    {
        clear();
        if (Matrix[n1][n0])
        {
            draw(Matrix);
            printf("Position %c%d has already a number.\n", c[0], n1);
            return InputNumber();
        }
        else if (checkLegalWithMsg(n1, n0, n2))
        {
            fillNumber(n1, n0, -n2);
            draw(Matrix);
            return -1;
        }
        else
        {
            draw(Matrix);
            return InputNumber();
        }
    }
    else
    {
        clear();
        draw(Matrix);
        printf("Invalid Input!\n");
        return InputNumber();
    }
}

int checkLegal(int x, int y, int value)
{
    int blockNum = (x - 1) / 3 * 3 + (y - 1) / 3 + 1;
    return !(column[x][value] || row[y][value] || block[blockNum][value]);
}

void fillNumber(int x, int y, int value)
{
    int blockNum = (x - 1) / 3 * 3 + (y - 1) / 3 + 1;
    Matrix[x][y] = value;
    if (value < 0)
        value = -value;
    column[x][value] = 1;
    row[y][value] = 1;
    block[blockNum][value] = 1;
}

void clearNumber(int x, int y)
{
    int blockNum = (x - 1) / 3 * 3 + (y - 1) / 3 + 1;
    int value = Matrix[x][y];
    if (value < 0)
        value = -value;
    column[x][value] = 0;
    row[y][value] = 0;
    block[blockNum][value] = 0;
    Matrix[x][y] = 0;
}
int checkLegalWithMsg(int x, int y, int value)
{
    int res = 1;
    int blockNum = (x - 1) / 3 * 3 + (y - 1) / 3 + 1;
    if (block[blockNum][value])
    {
        printf("Block %d has already a/an %d.\n", blockNum, value);
        res = 0;
    }
    if (row[y][value])
    {
        printf("Row %c has already a/an %d.\n", y + 'A' - 1, value);
        res = 0;
    }
    if (column[x][value])
    {
        printf("Column %d has already a/an %d.\n", x, value);
        res = 0;
    }
    return res;
}
