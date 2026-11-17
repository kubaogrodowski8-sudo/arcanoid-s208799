#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float x0, float y0, float szer, float wys, float pred) {
        x = x0;
        y = y0;
        szerokosc = szer;
        wysokosc = wys;
        predkosc = pred;

        shape.setSize({szerokosc, wysokosc});
        shape.setOrigin({szerokosc / 2, wysokosc / 2});
        shape.setPosition({x, y});
        shape.setFillColor(sf::Color::Blue);
    }

    void moveLeft() {
        x = x - predkosc;
        shape.setPosition({x, y});
    }

    void moveRight() {
        x = x + predkosc;
        shape.setPosition({x, y});
    }

    void clampToBounds(float width) {
        float polowa = szerokosc / 2.f;
        if (x - polowa < 0)
            x = polowa;
        else if (x + polowa > width)
            x = width - polowa;

        shape.setPosition({x, y});
    }

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};
