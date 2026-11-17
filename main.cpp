#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "paletka.h"
#include "pilka.h"
#include "stone.h"

int main() {
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;
    sf::RenderWindow window(sf::VideoMode({(unsigned)WIDTH, (unsigned)HEIGHT}), "Arkanoid");
    window.setFramerateLimit(60);

    Paletka pal(320.f, 440.f, 100.f, 20.f, 8.f);
    Pilka pilka(320.f, 420.f, 4.f, 3.f, 8.f);


    std::vector<Stone> bloki;
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 50.f;
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }

    int klatki = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { pal.moveLeft(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { pal.moveRight(); }
        pal.clampToBounds(WIDTH);

        pilka.move();
        pilka.collideWalls(WIDTH, HEIGHT);
        if (pilka.collidePaddle(pal)) { std::cout << "HIT PADDLE\n"; }
        for (auto& blok : bloki) {
            if (pilka.collideStone(blok)) 
            { 
                std::cout << "HIT STONE\n"; 
                break;
            }
        }


        if (pilka.getY() - pilka.getRadius() > HEIGHT) {
            std::cout << "MISS! KONIEC GRY\n";
            sf::sleep(sf::seconds(2.f));
            window.close();
        }


        klatki++;
        if (klatki == 20) {
            std::cout << "x=" << pilka.getX() << " y=" << pilka.getY() << " vx=" << pilka.getVx() << " vy=" << pilka.getVy() << std::endl;
            klatki = 0;
        }

        window.clear(sf::Color(20, 20, 30));
        
        for (const auto& blok : bloki) {
            blok.draw(window);
        }

        pal.draw(window);
        pilka.draw(window);
        window.display();
    }

    return 0;
}