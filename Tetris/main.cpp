#include <SFML/Graphics.hpp>
#include <windows.h>
#include <time.h>
#include "blocks.h"
#include "visualizer.h"
using namespace sf;


const unsigned int X = 14;
const unsigned int Y = 20;

int field[X][Y] = { 0 };

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
    
    Texture t1;
    Sprite blockTiles[8];

    if (!(t1).loadFromFile("../Assets/Tiles.png"))
    {
        printf("Didnt find tile texture!");
    }

    for (int i = 0; i < 8; i++)
    {
        blockTiles[i].setTexture(t1);
        blockTiles[i].setTextureRect(sf::IntRect((32 * i), 0, 32, 32));
    }

    float timer = 0, delay = 0.1;
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (time > delay)
        {
            blockTiles[0].move(0, 10);
            blockTiles[0].move(0, 12);
            time = 0;
        }
        window.clear();
        window.draw(blockTiles[0]);
        window.display();
    }

    return 0;
}

void drawField()
{

}