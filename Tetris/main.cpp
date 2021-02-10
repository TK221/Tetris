#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;

//functions
void printFieldToConsole();
void drawField();
bool newBlock();
void clearField();
int moveBlockOneDown();

//variables
const unsigned int X = 14;
const unsigned int Y = 20;
const unsigned int SquareSize = 23;

int block[7][4][4] =
{
    1,0,0,0,    
    1,0,0,0,
    1,0,0,0,
    1,0,0,0,

    2,0,0,0,
    2,2,0,0,
    0,2,0,0,
    0,0,0,0,

    0,3,0,0,
    3,3,0,0,
    3,0,0,0,
    0,0,0,0,

    0,4,0,0,
    0,4,0,0,
    4,4,0,0,
    0,0,0,0,

    5,5,0,0,
    5,5,0,0,
    0,0,0,0,
    0,0,0,0,

    6,0,0,0,
    6,6,0,0,
    6,0,0,0,
    0,0,0,0,

    7,0,0,0,
    7,0,0,0,
    7,7,0,0,
    0,0,0,0,
};

int field[X][Y] = { 0 };
int currentObjectPosition[4][2] = { 0 };    //[one of the 4 blocks of one "total block"][X and Y]
int currentBlockType = 0;
int currentBlockPosX;
int currentBlockPosY;

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
    
    Texture t1;
    if (!t1.loadFromFile("../Assets/Tiles.png"))
    {
        printf("Didnt find tile sprite!");
    }

    Sprite tiles(t1);
    tiles.setTextureRect(IntRect(0, 0, SquareSize, SquareSize));

    newBlock();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        Sleep(1000);
        
        //clearField();
        //if (!newBlock()) {
        //    printf("error\n");
        //}
        printFieldToConsole();
        moveBlockOneDown();
        tiles.move(0, SquareSize);
        window.draw(tiles);
        window.display();
    }

    return 0;
}

void clearField() {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            field[j][i] = 0;
        }
    }
}

int moveBlockOneDown() {
    
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            if (block[currentBlockType][i][j] != 0) {
                if (field[currentBlockPosX + j][currentBlockPosY + i + 1] == 0) {
                    field[currentBlockPosX + j][currentBlockPosY + i + 1] = block[currentBlockType][i][j];
                    field[currentBlockPosX + j][currentBlockPosY + i] = 0;
                }
                //else return false;
            }
        }
    }
    currentBlockPosY++;
    return true;
}

bool newBlock() {   //returns false if collision
    currentBlockType = rand() % 7;
    
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (block[currentBlockType][i][j] != 0) {
                if (field[j + (X / 2)][i] == 0) {
                    field[j + (X / 2)][i] = block[currentBlockType][i][j];
                }
                else return false;
            }
        }
    }
    currentBlockPosX = X / 2;
    currentBlockPosY = 0;
    return true;
}

void printFieldToConsole() {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            printf("%i", field[j][i]);
        }
        printf("\n");
    }
    printf("============\n");
}

void drawField()
{

}