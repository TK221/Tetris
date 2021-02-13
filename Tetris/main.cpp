#include <SFML/Graphics.hpp>
#include <windows.h>
#include "blocks.h"
using namespace sf;


const unsigned int X = 14;
const unsigned int Y = 20;

int field[X][Y] = { 0 };

int main()
{
    sf::RenderWindow window(sf::VideoMode(610, 640), "Tetris");
    
    Texture t1;
    Sprite blockTiles[8];

    Font font;
    Text text;

    if (!(t1).loadFromFile("../Assets/Tiles.png"))
    {
        printf("Didnt find tile texture!");
    }
    if (!font.loadFromFile("../Assets/Righteous.ttf"))
    {
        printf("Couldn't load the font!");
    }

    text.setFont(font);
    text.setString("Score: 0000");
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(460, 0);

    for (int i = 0; i < 8; i++)
    {
        blockTiles[i].setTexture(t1);
        blockTiles[i].setTextureRect(sf::IntRect((32 * i), 0, 32, 32));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        
        for (int y = 0; y < Y; y++)
        {
            for (int x = 0; x < X; x++)
            {
                int blockType = ((x+1)*(y+1))%8;
                if (blockType == -1) continue;

                blockTiles[blockType].setPosition(x*32,y*32);
                
                window.draw(blockTiles[blockType]);
            }
        }
        window.draw(text);
        window.display();
    }

    return 0;
}