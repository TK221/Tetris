#pragma once
using namespace std;

const int BLOCKNUMBER = 7;

void readBlocks();
void changeHoldBlock();
bool newRandomBlock();
bool newBlock();
void deleteBlock();

extern int blockTypes[BLOCKNUMBER][4][4][4];
extern bool blockholded;
extern int blockInARow;
extern int holdBlock;