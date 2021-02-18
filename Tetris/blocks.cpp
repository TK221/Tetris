#include <SFML/Graphics.hpp>
#include <string>
#include "blocks.h"
#include "main.h"
#include "field.h"

//#define DEBUG_MODE

using namespace std;

void saveBlockTypes(int block[4][4], int type);

// indexes where the real blocks of every type of block is
int blockTypes[BLOCKNUMBER][4][4][4];	//blockTypes[BLOCKTYPE][BLOCKROTATION][X][Y]

bool blockholded = false;		// is block currently holded
int blockInARow = 0;			// new same created block in a row
int holdBlock = -1;				// blocktype which is currently holded

// definition of normal blocks
int blockDef[BLOCKNUMBER][4][4] =
{
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,

	0,1,0,0,
	0,1,1,0,
	0,0,1,0,
	0,0,0,0,

	0,0,1,0,
	0,1,1,0,
	0,1,0,0,
	0,0,0,0,

	0,0,1,0,
	0,0,1,0,
	0,1,1,0,
	0,0,0,0,

	0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0,
	
	0,1,0,0,
	0,1,1,0,
	0,1,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	0,1,1,0,
	0,0,0,0,
};

// read the block-definitions and call the save function
void readBlocks()
{
	for (int i = 0; i < BLOCKNUMBER; i++)
	{
		saveBlockTypes(blockDef[i], i);
	}
}

// save all rotated blocktypes
void saveBlockTypes(int block[4][4], int type)
{
	for (int i = 0; i < 4; i++)
	{
		// save array of the current blocktype
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (block[y][x] == 1)
				{
					blockTypes[type][i][x][y] = (type+1);
					
				}
				else
				{
					blockTypes[type][i][x][y] = 0;
				}
#ifdef DEBUG_MODE
	printf("%d,", blockTypes[type][i][x][y]);
#endif // DEBUG_MODE
			}
#ifdef DEBUG_MODE
	printf("\n");
#endif // DEBUG_MODE
		}
#ifdef DEBUG_MODE
	printf("\n");
#endif // DEBUG_MODE
		
		// copy array to temporary
		int tempBlock[4][4];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				tempBlock[y][x] = block[y][x];
			}
		}

		// rotate array and save it
		int rY = 3;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				block[y][x] = tempBlock[x][rY];
			}
			rY--;
		}
	}
#ifdef DEBUG_MODE
	printf("\n");
#endif // DEBUG_MODE
}

// initialize new random block and create it (In Progress)
bool newRandomBlock()
{
	srand(time(NULL));
	int newBlockType = rand() % 7;

	if (newBlockType == currentBlockType)
	{
		if (blockInARow > 0)
		{
			while (newBlockType != currentBlockType)
			{
				newBlockType = rand() % 7;
				blockInARow = 0;
			}
		}
		else
		{
			currentBlockType = newBlockType;
			blockInARow++;
		}
	}
	else
	{
		currentBlockType = newBlockType;
		blockInARow = 0;
	}

	blockholded = false;

	return newBlock();
}

// create new block at the top of the field
bool newBlock() {   //returns false if collision
	int tmpField[X][Y];
	std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);
	currentBlockRotation = 1;
	currentBlockPosX = (X / 2)-2;
	currentBlockPosY = 0;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (blockTypes[currentBlockType][currentBlockRotation][i][j] != 0) {
				if (field[j + currentBlockPosX][i] == 0) {
					field[j + currentBlockPosX][i] = blockTypes[currentBlockType][currentBlockRotation][i][j];
				}
				else {
					std::copy(&tmpField[0][0], &tmpField[0][0] + X * Y, &field[0][0]);
					return false;
				}
			}
		}
	}

	return true;
}

// delete current block in the field
void deleteBlock()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockTypes[currentBlockType][currentBlockRotation][x][y] == 0) continue;

			field[currentBlockPosX + y][currentBlockPosY + x] = 0;
		}
	}
}

// change current block with the hold block
void changeHoldBlock()
{
	if (blockholded) return;
	deleteBlock();

	if (holdBlock != -1)
	{
		// if a block is holded change current with holded
		int tempBlock = currentBlockType;
		currentBlockType = holdBlock;
		holdBlock = tempBlock;
		blockholded = true;
		newBlock();
	}
	else
	{
		// if no block is holded create a new random block and set holdblock
		holdBlock = currentBlockType;
		newRandomBlock();
	}
}