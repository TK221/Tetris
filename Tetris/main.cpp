#include <SFML/Graphics.hpp>
#include <stdlib.h> 
#include <Windows.h>
#include "blocks.h"

using namespace sf;
using namespace std;

//functions
void loadTextures();
void addScore(int value);
void printFieldToConsole();
void drawField();
bool newBlock();
void clearField();
int moveBlockOneDown();
int moveBlockOneLeft();
int moveBlockOneRight();

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


Texture t1;
Sprite blockTiles[8];
Font font;
Text text;

int score = 0;

int field[X][Y] = { 0 };
int currentObjectPosition[4][2] = { 0 };    //[one of the 4 blocks of one "total block"][X and Y]
int currentBlockType = 0;
int currentBlockPosX;
int currentBlockPosY;

int main()
{
    sf::RenderWindow window(sf::VideoMode(610, 640), "Tetris");

    loadTextures();
    readBlocks();

    Sprite tiles(t1);
    tiles.setTextureRect(IntRect(0, 0, SquareSize, SquareSize));

    newBlock();
    printFieldToConsole();
    clearField();
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            // key pressed
            case sf::Event::KeyPressed:
                printf("keypressed");
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                {
                    moveBlockOneLeft();
                    break;
                }
                case sf::Keyboard::Right:
                {
                    moveBlockOneRight();
                    break;
                }
                case sf::Keyboard::Down:
                {
                    while (moveBlockOneDown()) {}
                    break;
                }
                case sf::Keyboard::Up:
                {
                    //rotate
                    break;
                }
                case sf::Keyboard::A:
                {
                    moveBlockOneLeft();
                    break;
                }
                case sf::Keyboard::D:
                {
                    moveBlockOneRight();
                    break;
                }
                case sf::Keyboard::S:
                {
                    while (moveBlockOneDown()) {}
                    break;
                }
                case sf::Keyboard::W:
                {
                    //rotate
                    break;
                }
                default:
                    break;
                } 

                break;

            default:
                break;
            }
        }
        
        window.clear();
        Sleep(100);
                
        if (!moveBlockOneDown()) {
            if (!newBlock()) {
                printf("\ngame over!\n\n");
                return 0;
            }
        }
        printFieldToConsole();
        
        for (int y = 0; y < Y; y++)
        {
            for (int x = 0; x < X; x++)
            {
                int blockType = field[x][y];
                if (blockType == -1) blockType = 7;

                blockTiles[blockType].setPosition(x*32,y*32);
                
                window.draw(blockTiles[blockType]);
            }
        }

        window.draw(text);
        window.display();
    }

    return 0;
}

void clearField() {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (i == Y - 1 || j == 0 || j == X-1) {
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
            if (block[currentBlockType][i][j] != 0) {
                if (field[currentBlockPosX + j][currentBlockPosY + i + 1] == 0) {
                    field[currentBlockPosX + j][currentBlockPosY + i + 1] = block[currentBlockType][i][j];
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
            if (block[currentBlockType][i][j] != 0) {
                if (field[currentBlockPosX + j - 1][currentBlockPosY + i] == 0) {
                    field[currentBlockPosX + j - 1][currentBlockPosY + i] = block[currentBlockType][i][j];
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
            if (block[currentBlockType][i][j] != 0) {
                if (field[currentBlockPosX + j + 1][currentBlockPosY + i] == 0) {
                    field[currentBlockPosX + j + 1][currentBlockPosY + i] = block[currentBlockType][i][j];
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

bool newBlock() {   //returns false if collision
    srand(time(NULL));
    currentBlockType = rand() % 7;
    int tmpField[X][Y];
    std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);
    
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (block[currentBlockType][i][j] != 0) {
                if (field[j + (X / 2)][i] == 0) {
                    field[j + (X / 2)][i] = block[currentBlockType][i][j];
                }
                else {
                    std::copy(&tmpField[0][0], &tmpField[0][0] + X * Y, &field[0][0]);
                    return false;
                }
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

void loadTextures()
{
    // load textures
    if (!(t1).loadFromFile("../Assets/Tiles.png"))
    {
        printf("Didnt find tile texture!");
    }
    if (!font.loadFromFile("../Assets/Righteous.ttf"))
    {
        printf("Couldn't load the font!");
    }

    // set tile sprites
    for (int i = 0; i < 8; i++)
    {
        blockTiles[i].setTexture(t1);
        blockTiles[i].setTextureRect(sf::IntRect((32 * i), 0, 32, 32));
    }

    // define score text
    text.setFont(font);
    text.setString("Score: 0000");
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(460, 0);
}

// add points to score
void addScore(int value)
{
    score += value;
}