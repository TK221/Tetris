#pragma once
using namespace std;

const int BLOCKNUMBER = 7;

void readBlocks();
void changeHoldBlock();

extern int blockTypes[BLOCKNUMBER][4][4][4];
extern int holdBlock[4][4];
extern int currentBlock[4][4];