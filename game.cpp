
#include <iostream>
#include <optional>
#include <algorithm>
#include "game.h"

Game::Game()
    :m_window(sf::VideoMode({static_cast<unsigned>(WIDTH), static_cast<unsigned>(HEIGHT)}), "Arkanoid"),
     m_paletka(WIDTH / 2.f, HEIGHT - 40.f, 100.f, 20.f, 8.f),
     m_pilka(WIDTH / 2.f, HEIGHT - 60.f, 4.f, 3.f, 8.f) {
    m_window.setFramerateLimit(60);

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 50.f;
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::run() {
    while (m_window.isOpen()) {
        proccesEvents();
        sf::Time dt = m_deltaClock.restart();
        update(dt);
        render();
    }
}

void Game::proccesEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            m_window.close();
    }
}

void Game::update(sf::Time dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { m_paletka.moveLeft(); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { m_paletka.moveRight(); }
    m_paletka.clampToBounds(WIDTH);

    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);
    if (m_pilka.collidePaddle(m_paletka)) { std::cout << "HIT PADDLE\n"; }
    for (auto& blok : m_bloki) {
        if (m_pilka.collideStone(blok)) 
        { 
            std::cout << "HIT STONE\n"; 
            break;
        }
    }

    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(), [](const Stone& s) {
        return s.isDestroyed();
    }), m_bloki.end());


    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
        std::cout << "MISS KONIEC GRY\n";
        sf::sleep(sf::seconds(2.f));
        m_window.close();
    }

    m_klatki++;
    if (m_klatki == 20) {
        std::cout << "x=" << m_pilka.getX() << " y=" << m_pilka.getY() << " vx=" << m_pilka.getVx() << " vy=" << m_pilka.getVy() << std::endl;
        m_klatki = 0;
    }
}

void Game::render() {
    m_window.clear(sf::Color(20, 20, 30));
    
    for (const auto& blok : m_bloki) {
        blok.draw(m_window);
    }

    m_paletka.draw(m_window);
    m_pilka.draw(m_window);
    m_window.display();
}