#include <SFML/Graphics.hpp>
#include <stdlib.h> 
#include <Windows.h>
#include "blocks.h"
#include "main.h"
#include "field.h"

//#define DEBUG_MODE

using namespace sf;
using namespace std;


int field[X][Y] = { 0 };
int currentObjectPosition[4][2] = { 0 };    //[one of the 4 blocks of one "total block"][X and Y]
int currentBlockType = 0;
int currentBlockPosX;
int currentBlockPosY;
int currentBlockRotation = 0;

void clearField() {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (i == Y - 1 || j == 0 || j == X - 1) {
                field[j][i] = -1;
            }
            else {
                field[j][i] = 0;
            }
        }
    }
}

int moveBlockOneDown() {
    int tmpField[X][Y];
    std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            if (blockTypes[currentBlockType][currentBlockRotation][i][j] != 0) {
                if (field[currentBlockPosX + j][currentBlockPosY + i + 1] == 0) {
                    field[currentBlockPosX + j][currentBlockPosY + i + 1] = blockTypes[currentBlockType][currentBlockRotation][i][j];
                    field[currentBlockPosX + j][currentBlockPosY + i] = 0;
                }
                else {
                    std::copy(&tmpField[0][0], &tmpField[0][0] + X * Y, &field[0][0]);
                    return false;
                }
            }
        }
    }
    currentBlockPosY++;
    return true;
}

int moveBlockOneLeft() {
    int tmpField[X][Y];
    std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockTypes[currentBlockType][currentBlockRotation][i][j] != 0) {
                if (field[currentBlockPosX + j - 1][currentBlockPosY + i] == 0) {
                    field[currentBlockPosX + j - 1][currentBlockPosY + i] = blockTypes[currentBlockType][currentBlockRotation][i][j];
                    field[currentBlockPosX + j][currentBlockPosY + i] = 0;
                }
                else {
                    std::copy(&tmpField[0][0], &tmpField[0][0] + X * Y, &field[0][0]);
                    return false;
                }
            }
        }
    }
    currentBlockPosX--;
    return true;
}

int moveBlockOneRight() {
    int tmpField[X][Y];
    std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            if (blockTypes[currentBlockType][currentBlockRotation][i][j] != 0) {
                if (field[currentBlockPosX + j + 1][currentBlockPosY + i] == 0) {
                    field[currentBlockPosX + j + 1][currentBlockPosY + i] = blockTypes[currentBlockType][currentBlockRotation][i][j];
                    field[currentBlockPosX + j][currentBlockPosY + i] = 0;
                }
                else {
                    std::copy(&tmpField[0][0], &tmpField[0][0] + X * Y, &field[0][0]);
                    return false;
                }
            }
        }
    }
    currentBlockPosX++;
    return true;
}

void clearFullRows() {
    for (int y = 1; y < Y - 1; y++) {
        for (int x = 1; x < X; x++) {
            if (field[x][y] == 0) break;
            else if (x == X - 1) {
                addScore(100);
                //delete this row and move everything above one down
                for (int x2 = 1; x2 < X - 1; x2++) {
                    field[x2][y] = 0;
                }
                for (int y2 = y; y2 > 0; y2--) {
                    for (int x2 = 1; x2 < X - 1; x2++) {
                        field[x2][y2] = field[x2][y2 - 1];
                        field[x2][y2 - 1] = 0;
                    }
                }
                currentBlockPosY++;
#ifdef DEBUG_MODE
    printf("delete row");
    printFieldToConsole();
#endif // DEBUG_MODE
            }
        }
    }
}

bool rotateBlock() {
#ifdef DEBUG_MODE
    printf("rotate start\n");
    printf("\ncurrent block %d\nrotate: %d\n", currentBlockType, currentBlockRotation);
#endif // DEBUG_MODE
    int tmpField[X][Y];
    std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);


    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (blockTypes[currentBlockType][currentBlockRotation][x][y] != 0) {
                field[currentBlockPosX + y][currentBlockPosY + x] = 0;
            }
        }
    }
    if (currentBlockRotation < 3) {
        currentBlockRotation++;
    }
    else currentBlockRotation = 0;

#ifdef DEBUG_MODE
    printf("rotate middle:\n");
    printFieldToConsole();
#endif // DEBUG_MODE

    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            if (blockTypes[currentBlockType][currentBlockRotation][i][j] != 0) {
                if (field[currentBlockPosX + j][currentBlockPosY + i] == 0) {
                    field[currentBlockPosX + j][currentBlockPosY + i] = blockTypes[currentBlockType][currentBlockRotation][i][j];
                }
                else {
                    std::copy(&tmpField[0][0], &tmpField[0][0] + X * Y, &field[0][0]);
#ifdef DEBUG_MODE
    printf("error rotate\n");
#endif // DEBUG_MODE
                    if (currentBlockRotation > 0) {
                        currentBlockRotation--;
                    }
                    else currentBlockRotation = 3;
                    return false;
                }
            }
        }
    }
#ifdef DEBUG_MODE
    printf("rotate end:\n");
#endif // DEBUG_MODE
    return true;
}