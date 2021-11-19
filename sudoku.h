#include <time.h>
#include <stdlib.h>
#include "painter.h"
#include <string.h>
int getRandom();
int getRandomMod(int);
int generateSudoku();
void fillSudoku(int, int);
int generatePuzzle(int);
int Start();
int InputNumber();
int invalidInput(int());
void checkSolution(int i, int j);
int checkLegal(int, int, int);
int checkLegalWithMsg(int, int, int);
void fillNumber(int, int, int);
void clearNumber(int, int);
void markNumber(int, int, int);
void clearMark(int, int, int);