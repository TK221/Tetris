#include <SFML/Graphics.hpp>
#include <windows.h>
#include "blocks.h"
using namespace sf;


const unsigned int X = 14;
const unsigned int Y = 20;

Sprite bT, rT, yT, gT, cT, pT, oT, bT;

int field[X][Y] = { 0 };

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
    
    Texture t1;
    if (!t1.loadFromFile("../Assets/Tiles.png"))
    {
        printf("Didnt find tile texture!");
    }

    Sprite tile1(t1), tile2(t1);
    tile1.setTextureRect(IntRect(0, 0, 32, 32));
    tile2.setTextureRect(IntRect(32, 0, 32, 32));

    readBlocks();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(tile1);
        tile1.move(0, 10);
        window.draw(tile2);
        tile2.move(0, 12);
        Sleep(1000);
        window.display();
    }

    return 0;
}

void drawField()
{

}