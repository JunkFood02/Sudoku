#include <time.h>
#include <stdlib.h>
#include "painter.h"
#include "interaction.h"
int getRandom();
int getRandomMod(int);
int generateSudoku();
int solveSudoku(int, int, int);
int putValue(int, int, int, int);
int clearValue(int, int, int);
int generatePuzzle(int);