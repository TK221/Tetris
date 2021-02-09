#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

void rotateBlock(int block[4][4]);

int blocks[7][4][4] =
{
	
};

int Blocks[1][1][4][4] =
{
	{
		{
			0,1,1,0,
			0,1,0,0,
			0,1,0,0,
			0,0,0,0
		}
	}
};

void readBlocks()
{
	for (int i = 0; i < 1; i++)
	{
		for (int v = 0; v < 1; v++)
		{
			int charc = 0;
			
			rotateBlock(Blocks[i][v]);
			rotateBlock(Blocks[i][v]);

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (Blocks[i][v][y][x] == 1) 
					{
						blocks[i][v][charc] = ((y * 4) + x);
						printf("%d,", blocks[i][v][charc]);

						charc++;
					}
				}
			}
			printf("\n");
		}
	}
}

void rotateBlock(int block[4][4])
{
	int tempBlock[4][4];

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			tempBlock[y][x] = block[y][x];
		}
	}

	int rX = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			block[x][rX] = tempBlock[rX][y];
			printf("%d,", block[x][y]);
			
			rX++;
		}
		rX = 0;
		printf("\n");
	}

	printf("\n");
}