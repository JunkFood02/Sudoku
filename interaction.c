#include "interaction.h"

int Start()
{
    printf("Soduku\nInput the level of Puzzle:\n");
    printf("[0]Very Easy [1]Easy [2]Normal [3]Hard\n");
    int n;
    scanf("%d", &n);
    if (n >= 0 && n <= 3)
    {
        return n;
    }
    else
    {
        return invalidInput(Start);
    }
}
int invalidInput(int func())
{
    clear();
    printf("Invalid Input!\n");
    return func();
}
int putNumber(char Matrix[10][10])
{
    draw(Matrix);
    printf("Input the Position and the Value you want to put:\n");
    printf("Example: A 2 3 put 3 into Row A Column 2\n");
    char c1;
    int n0, n1, n2;
    scanf("%c%d%d", &c1, &n1, &n2);
    n0 = c1 - 'A' + 1;
    if (n0 < 1 || n0 > 9 || n1 < 1 || n1 > 9 || n2 < 1 || n2 > 9)
    {
        clear();
        printf("Invalid Input!\n");
        return putNumber(Matrix);
    }
}