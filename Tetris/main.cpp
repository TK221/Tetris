#include <SFML/Graphics.hpp>
using namespace sf;

const unsigned int X = 14;
const unsigned int Y = 20;

int field[X][Y] = { 0 };

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
    
    Texture t1;
    if (!t1.loadFromFile("../Assets/Tiles.png"))
    {
        printf("Didnt find tile sprite!");
    }

    Sprite tiles(t1);
    tiles.setTextureRect(IntRect(0, 0, 23, 23));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        tiles.move(0, 10);
        window.draw(tiles);
        window.display();
    }

    return 0;
}

void drawField()
{

}