#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;

//functions
void printFieldToConsole();
void drawField();
bool newBlock();
void clearField();

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

    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,

    0,1,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0,

    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0,

    1,0,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0,

    1,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,0,0,0,

    0,1,0,0,
    0,1,0,0,
    1,1,0,0,
    0,0,0,0,
};

int field[X][Y] = { 0 };
int currentObjectPosition[4][2] = { 0 };    //[one of the 4 blocks of one "total block"][X and Y]

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
       
        clearField();
        if (!newBlock()) {
            printf("error\n");
        }
        printFieldToConsole();
        tiles.move(0, SquareSize);
        window.draw(tiles);
        window.display();
    }

    return 0;
}

void clearField() {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            field[i][j] = 0;
        }
    }
}

bool newBlock() {   //returns false if collision
    int type = rand() % 7;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[type][i][j] == 1) {
                if (field[i][j + (X / 2)] == 0) {
                    field[i][j + (X / 2)] = 1;
                }
                else return false;
            }
        }
    }
    return true;
}

void printFieldToConsole() {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            printf("%i", field[i][j]);
        }
        printf("\n");
    }
    printf("============\n");
}

void drawField()
{

}