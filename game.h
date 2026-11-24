#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "stone.h"
#include "pilka.h"
#include "paletka.h"

class Game {
    private:
        const float WIDTH = 640.f;
        const float HEIGHT = 480.f;
        Pilka m_pilka;
        Paletka m_paletka;
        sf::Clock m_deltaClock;
        sf::RenderWindow m_window;
        std::vector<Stone> m_bloki;
        int m_klatki = 0;
        
        void proccesEvents();
        void update(sf::Time dt);
        void render();
    public:
        Game();
        void run();
};





