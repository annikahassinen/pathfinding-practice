#pragma once
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include "Node.hpp"
using namespace sf;

class Payload
{
public:
    RectangleShape payloadShape;

    Payload(int x, int y)
    {
        payloadShape.setFillColor(Color::Red);
        payloadShape.setSize(Vector2f(25.f, 25.f));
        payloadShape.setPosition(x, y);
    };

    bool lategame = false;
    int hp = 50;

};
