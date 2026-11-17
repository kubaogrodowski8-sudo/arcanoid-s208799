#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "paletka.h"
#include "stone.h"


class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float x0, float y0, float vx0, float vy0, float r) {
        x = x0;
        y = y0;
        vx = vx0;
        vy = vy0;
        radius = r;

        shape.setRadius(radius);
        shape.setOrigin({radius, radius});
        shape.setPosition({x, y});
        shape.setFillColor(sf::Color::White);
    }

    void move() {
        x += vx;
        y += vy;
        shape.setPosition({x, y});
    }

    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    void collideWalls(float width, float height) {
        if (x - radius <= 0) {
            x = radius;
            bounceX();
        }
        if (x + radius >= width) {
            x = width - radius;
            bounceX();
        }
        if (y - radius <= 0) {
            y = radius;
            bounceY();
        }
        shape.setPosition({x, y});
    }

    bool collidePaddle(const Paletka& p) {
        float gora = p.getY() - p.getWysokosc() / 2;
        float lewo = p.getX() - p.getSzerokosc() / 2;
        float prawo = p.getX() + p.getSzerokosc() / 2;

        if (x >= lewo && x <= prawo && (y + radius) >= gora && (y - radius) < gora) {
            vy = -std::abs(vy);
            y = gora - radius;
            shape.setPosition({x, y});
            return true;
        }
        return false;
    }
    bool collideStone(Stone& s) {
        if (s.isDestroyed()) {
            return false;
        }

        float lewo = s.getPosition().x;
        float prawo = s.getPosition().x + s.getSize().x;
        float gora = s.getPosition().y;
        float dol = s.getPosition().y + s.getSize().y;

        if (x + radius >= lewo && x - radius <= prawo &&
            y + radius >= gora && y - radius <= dol) {

            float overlapLeft = (x + radius) - lewo;
            float overlapRight = prawo - (x - radius);
            float overlapTop = (y + radius) - gora;
            float overlapBottom = dol - (y - radius);

            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            if (minOverlapX < minOverlapY) {
                bounceX();
                if (overlapLeft < overlapRight) x = lewo - radius;
                else x = prawo + radius;
            } else {
                bounceY();
                if (overlapTop < overlapBottom) y = gora - radius;
                else y = dol + radius;
            }

            shape.setPosition({x, y});
            s.trafienie();
            return true;
        }
        return false;
    }

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};
