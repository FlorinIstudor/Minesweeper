#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Minesweeper");
    float r = 40.f;
 
    // LOAD TEXTURES

    sf::Image image;
    image.loadFromFile("Cells.png");

    sf::Texture* TextureVect;

    TextureVect = new sf::Texture[12];

    for (int i = 0; i < 2; i++)
    {
        (TextureVect + i)->loadFromImage(image, sf::IntRect(sf::Vector2i(i * 30, 0), sf::Vector2i(30, 30)));
    }

    for (int i = 2; i < 12; i++)
    {
        (TextureVect + i)->loadFromImage(image, sf::IntRect(sf::Vector2i((i-2) * 30, 30), sf::Vector2i(30, 30)));
    }

    // !LOAD TEXTURES

    srand(time(NULL));

    Board TEST(sf::Vector2i(20,20),TextureVect,60);

    TEST.SetPosition(sf::Vector2f(100, 100));

    int k = 0;

    sf::Clock MainClock;
    sf::Time dt;

    //TEST.REVEALALL();

    //window.setFramerateLimit(60);

    while (window.isOpen())
    {
        dt = MainClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::M)
                    TEST.DB_MARKALL();

                if (event.key.code == sf::Keyboard::Key::R)
                    TEST.DB_REVEALALL();

                if (event.key.code == sf::Keyboard::Key::Escape)
                    window.close();

                if (event.key.code == sf::Keyboard::Key::T)
                {
                    if(k % 16 == 0)
                        TEST.DB_REVEALBYINDEX(k);
                    if ((k + 1) % 16 == 0)
                        TEST.DB_REVEALBYINDEX(k);
                    if(k < 16)
                        TEST.DB_REVEALBYINDEX(k);
                    if (k >= 16 * (30 - 1))
                        TEST.DB_REVEALBYINDEX(k);

                    if (k < 16 * 30)
                        k++;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.key.code == sf::Mouse::Button::Left)
                    std::cout << "Left" << '\n';

                if (event.key.code == sf::Mouse::Button::Right)
                    std::cout << "Right" << '\n';
            }

            TEST.Update(window, event);

        }

        window.clear();

        //std::cout << TEST.GetMouseIndex(window).x << " " << TEST.GetMouseIndex(window).y << " ";
        std::cout<< 1/dt.asSeconds() <<'\n';
        //std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << '\n';
    
        TEST.Draw(window); 

        window.display();

        //std::cout << 1 / dt.asSeconds()<<'\n';
    }

    delete[] TextureVect;

    return 0;
}