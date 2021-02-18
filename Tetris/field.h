#pragma once

const unsigned int X = 14;
const unsigned int Y = 20;

void clearField();
int moveBlockOneDown();
int moveBlockOneLeft();
int moveBlockOneRight();
void clearFullRows();
bool rotateBlock();

extern int field[X][Y];
extern int currentBlockType;
extern int currentBlockPosX;
extern int currentBlockPosY;
extern int currentBlockRotation;