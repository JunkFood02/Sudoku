#include <time.h>
#include <stdlib.h>
#include "painter.h"
#include <string.h>
int getRandom();
int generateSudoku();
void solveSudoku(int, int, int);
int generatePuzzle(int);
int Start();
int InputNumber();
int invalidInput(int());
int checkLegal(int, int, int);
int checkLegalWithMsg(int, int, int);
void fillNumber(int, int, int);
void clearNumber(int, int);