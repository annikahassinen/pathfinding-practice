#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.hpp"
using namespace sf;

class Wall
{
public:
    sf::RectangleShape wallShape;

    Wall(float xPos, float yPos)
    {
        wallShape.setFillColor(Color::Blue);
        wallShape.setSize(Vector2f(size, size));
        //wallShape.setOrigin(Vector2f(50.f, 50.f) / 2.0f);
        wallShape.setPosition(xPos, yPos);

        /*leftSide = wallShape.getPosition().x;
        rightSide = wallShape.getPosition().x + wallShape.getLocalBounds().width;
        topSide = wallShape.getPosition().y;
        bottomSide = wallShape.getPosition().y + wallShape.getLocalBounds().height;*/
    }

    Collision GetCollider() { return Collision(wallShape); }

    //float topSide, bottomSide, rightSide, leftSide;

private:
    float size = 25.f;
};
