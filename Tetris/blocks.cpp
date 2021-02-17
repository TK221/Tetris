#include <SFML/Graphics.hpp>
#include <string>
#include "blocks.h"
using namespace std;

void saveBlockTypes(int block[4][4], int type);
void changeHoldBlock();

// indexes where the real blocks of every type of block is
int blockTypes[BLOCKNUMBER][4][4][4];
int holdBlock[4][4];
int currentBlock[4][4];


// definition of normal block
int blockDef[BLOCKNUMBER][4][4] =
{
	0,1,1,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,

	0,1,1,0,
	0,0,1,0,
	0,0,1,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,1,0,0,

	0,1,1,0,
	0,0,1,1,
	0,0,0,0,
	0,0,0,0,

	0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0,
	
	0,0,0,0,
	0,1,0,0,
	1,1,1,0,
	0,0,0,0,

	0,0,1,1,
	0,1,1,0,
	0,0,0,0,
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
				printf("%d,", blockTypes[type][i][x][y]);
			}
			printf("\n");
		}
		printf("\n");
		
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
	printf("\n");
}

// swap block between current and holded
void changeHoldBlock()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int temp = currentBlock[x][y];
			currentBlock[x][y] = holdBlock[x][y];
			holdBlock[x][y] = temp;
		}
	}
}