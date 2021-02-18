#include <SFML/Graphics.hpp>
#include <stdlib.h> 
#include <Windows.h>
#include "blocks.h"
#include "main.h"
#include "field.h"

//#define DEBUG_MODE

using namespace sf;
using namespace std;

//functions
void loadTextures();
void displayText(sf::RenderWindow* window);
void gameOver();
void drawField(sf::RenderWindow* window);

//variables
Texture t1;
Sprite blockTiles[9];
Font font;
Text text;

int score = 0;
bool isGameOver = false;


int main()
{
    sf::RenderWindow window(sf::VideoMode(XSCREEN, YSCREEN), "Tetris");
    printf("####### ####### ####### ######  ###  #####  \n    #    #          #    #     #  #  #     # \n    #    #          #    #     #  #  #       \n    #    #####      #    ######   #   #####  \n    #    #          #    #   #    #        # \n    #    #          #    #    #   #  #     # \n    #    #######    #    #     # ###  #####\n");

    loadTextures();
    readBlocks();
    clearField();
    newBlock();

    Clock clock;
    float timer = 0, delay = 0.4f;

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
                if (!isGameOver){
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
                    case sf::Keyboard::Space:
                    {
                        changeHoldBlock();
                        break;
                    }
                    default:
                        break;
                    } 
                }
                else {
                    if (event.key.code == sf::Keyboard::R) {
                        clearField();
                        newBlock();
                        score = 0;
                        isGameOver = false;
                    }
                }
                break;

            default:
                break;
            }
        }
        
        window.clear();

        float Ftime = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += Ftime;

        if (!isGameOver && timer > delay)
        {
            if (!moveBlockOneDown()) {
                if (!newRandomBlock()) {
                    gameOver();
                }

            }
            clearFullRows();

#ifdef DEBUG_MODE
    printFieldToConsole();
#endif // DEBUG_MODE
    
            timer = 0;
        }
        

        drawField(&window);
        displayText(&window);

        window.display();
    }

    return 0;
}

// draw the enitre field
void drawField(sf::RenderWindow* window)
{
    // draw gamefield with current blocks
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

    // draw current holded block
    if (holdBlock != -1)
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (blockTypes[(holdBlock)][1][x][y] == 0) continue;

                blockTiles[(holdBlock + 1)].setPosition((y * SquareSize) + 15 * SquareSize, (x * SquareSize) + 10 * SquareSize);

                (*window).draw(blockTiles[(holdBlock + 1)]);
            }
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
    return;
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
    // define text
    char str[25];

    // print Score
    sprintf_s(str, "Score: %04d", score);
    text.setString(str);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(460, 0);
    (*window).draw(text);

    // print GameOver text with current score
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

// add points to score
void addScore(int value)
{
    score += value;
}

// gameover function
void gameOver()
{
    isGameOver = true;
}