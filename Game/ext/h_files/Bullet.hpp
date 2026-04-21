#pragma once
#include <SFML\Graphics.hpp>
#include <cstdlib>
using namespace sf;

class Bullet
{
public:
    CircleShape bullet;
    Vector2f currVelocity;
    float speed;

    Bullet(float radius = 5.f)
        : currVelocity(0.f, 0.f), speed(15.f)
    {
        this->bullet.setRadius(radius);
        this->bullet.setFillColor(Color::Green);
    };
};
