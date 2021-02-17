#include <SFML/Graphics.hpp>
#include <stdlib.h> 
#include <Windows.h>
#include "blocks.h"

using namespace sf;
using namespace std;

//variables
const unsigned int XSCREEN = 610;
const unsigned int YSCREEN = 640;
const unsigned int X = 14;
const unsigned int Y = 20;
const unsigned int SquareSize = 32;

//functions
void loadTextures();
void displayText(sf::RenderWindow* window);
void gameOver();

void addScore(int value);
void printFieldToConsole();
void drawField(sf::RenderWindow* window);
bool newBlock();
void clearField();
int moveBlockOneDown();
int moveBlockOneLeft();
int moveBlockOneRight();
void clearFullRows();
bool rotateBlock();
void deleteBlock();

//variables
Texture t1;
Sprite blockTiles[9];
Font font;
Text text;

int score = 0;
bool isGameOver = false;

int field[X][Y] = { 0 };
int currentObjectPosition[4][2] = { 0 };    //[one of the 4 blocks of one "total block"][X and Y]
int currentBlockType = 0;
int currentBlockPosX;
int currentBlockPosY;
int currentBlockRotation = 0;
int holdBlock = -1;

int main()
{
    sf::RenderWindow window(sf::VideoMode(XSCREEN, YSCREEN), "Tetris");

    loadTextures();
    readBlocks();

    Sprite tiles(t1);
    tiles.setTextureRect(IntRect(0, 0, SquareSize, SquareSize));

    //newBlock();
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
                    rotateBlock();
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
                    rotateBlock();
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
        Sleep(200);
        if (!isGameOver)
        {
            if (!moveBlockOneDown()) {
                srand(time(NULL));
                currentBlockType = rand() % 7;
                if (!newBlock()) {
                    gameOver();
                }

                moveBlockOneRight();
                //moveBlockOneLeft();
                printFieldToConsole();
            }
            clearFullRows();
            printFieldToConsole();
        }
        

        drawField(&window);
        displayText(&window);

        window.display();
    }

    return 0;
}

void drawField(sf::RenderWindow* window)
{
    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++)
        {
            int blockType = field[x][y];
            if (blockType == -1) blockType = 8;

            blockTiles[blockType].setPosition(x * SquareSize, y * SquareSize);

            (*window).draw(blockTiles[blockType]);
        }
    }

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (blockTypes[(currentBlockType)][0][x][y] == 0) continue;
            
            blockTiles[(currentBlockType + 1)].setPosition((x * SquareSize) + 15 * SquareSize, (y * SquareSize) + 10 * SquareSize);

            (*window).draw(blockTiles[(currentBlockType + 1)]);
        }
    }
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

bool newBlock() {   //returns false if collision
    int tmpField[X][Y];
    std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);
    currentBlockRotation = 1;
    
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (blockTypes[currentBlockType][currentBlockRotation][i][j] != 0) {
                if (field[j + (X / 2)][i] == 0) {
                    field[j + (X / 2)][i] = blockTypes[currentBlockType][currentBlockRotation][i][j];
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

void changeHoldBlock()
{
    deleteBlock();
    
    if (holdBlock != -1)
    {
        int tempBlock = currentBlockType;
        currentBlockType = holdBlock;
        holdBlock = tempBlock;
    }
    else
    {
        srand(time(NULL));
        currentBlockType = rand() % 7;
    }

    newBlock();
}

// delete current block in the field
void deleteBlock()
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (blockTypes[currentBlockType][currentBlockRotation][x][y] == 0) continue;

            field[currentBlockPosX + x][currentBlockPosY + y] = 0;
        }
    }
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
    for (int i = 0; i < 9; i++)
    {
        blockTiles[i].setTexture(t1);
        blockTiles[i].setTextureRect(sf::IntRect((SquareSize * i), 0, SquareSize, SquareSize));
    }

    // set font
    text.setFont(font);
}

void displayText(sf::RenderWindow *window)
{
    // define score text
    char str[25];

    sprintf_s(str, "Score: %04d", score);
    text.setString(str);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(460, 0);
    (*window).draw(text);

    // game over text
    if (isGameOver)
    {
        sprintf_s(str, "Game Over\nScore: %04d", score);
        text.setString(str);
        text.setCharacterSize(60);
        text.setFillColor(Color::Red);
        text.setPosition(XSCREEN/4, YSCREEN/4);
        (*window).draw(text);
    }
}

void clearFullRows() {
    for (int y = 1; y < Y-1; y++) {
        for (int x = 1; x < X; x++) {
            if (field[x][y] == 0) break;
            else if (x == X - 1) {
                printf("delete row");
                addScore(100);
                //delete this row and move everything above one down
                for (int x2 = 1; x2 < X-1; x2++) {
                    field[x2][y] = 0;
                }
                for (int y2 = y; y2>0; y2--) {
                    for (int x2 = 1; x2 < X-1; x2++) {
                        field[x2][y2] = field[x2][y2-1];
                        field[x2][y2 - 1] = 0;
                    }
                }
                currentBlockPosY++;
                printFieldToConsole();
                newBlock();
            }
        }
    }
}

bool rotateBlock() {
    printf("rotate start\n");
    int tmpField[X][Y];
    std::copy(&field[0][0], &field[0][0] + X * Y, &tmpField[0][0]);
    printf("\ncurrent block %d\nrotate: %d\n", currentBlockType, currentBlockRotation);


    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            printf("%d,", blockTypes[currentBlockType][currentBlockRotation][x][y]);
            if (blockTypes[currentBlockType][currentBlockRotation][x][y] != 0) {
                field[currentBlockPosX + y][currentBlockPosY + x] = 0;
            }
        }
        printf("\n");
    }
    printf("\n");
    if (currentBlockRotation < 3) {
        currentBlockRotation++;
    }
    else currentBlockRotation = 0;
    printf("rotate middle:\n");
    printFieldToConsole();

    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            if (blockTypes[currentBlockType][currentBlockRotation][i][j] != 0) {
                if (field[currentBlockPosX + j][currentBlockPosY + i] == 0) {
                    field[currentBlockPosX + j][currentBlockPosY + i] = blockTypes[currentBlockType][currentBlockRotation][i][j];
                }
                else {
                    std::copy(&tmpField[0][0], &tmpField[0][0] + X * Y, &field[0][0]);
                    printf("error rotate\n");
                    if (currentBlockRotation > 0) {
                        currentBlockRotation--;
                    }
                    else currentBlockRotation = 3;
                    printf("rotate: %d", currentBlockRotation);
                    return false;
                }
            }
        }
    }
    
    printf("rotate end:\n");
    return true;
}

// add points to score
void addScore(int value)
{
    score += value;
}

void gameOver()
{
    isGameOver = true;
}