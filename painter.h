//
// Created by Always Not on 2021/11/17.
//

#ifndef DATASTRUCTURE_PAINTER_H
#define DATASTRUCTURE_PAINTER_H

#include <stdio.h>

#define GREEN "\e[1;32m"
#define BLANK "\e[1;30m"
#define NONE "\e[0m"
#define CLEAR "e[1;1He[2J"
#define UNDERLINE "\e[4m"
#define CYAN "\e[1;36m"
#define BLUE "\e[1;34m"

void draw(int Matrix[10][10]);

void clear();
#endif //DATASTRUCTURE_PAINTER_H
