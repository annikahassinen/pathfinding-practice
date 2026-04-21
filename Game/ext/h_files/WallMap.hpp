#pragma once
#include <SFML\Graphics.hpp>
#include "Wall.hpp"
using namespace sf;

class WallMap
{
public:

    WallMap()
    {
        //std::vector<Wall> walls;
        //borders
        //left
        for (int i = 0; i < 32; i++) //16
        {
            Wall wall(0, i * wallSize);
            walls.push_back(wall);
        }
        //right
        for (int i = 0; i < 32; i++)
        {
            Wall wall(19.5f*50, i * wallSize); //19*50
            walls.push_back(wall);
        }
        //top
        for (int i = 0; i < 40; i++) //20
        {
            Wall wall(i * wallSize, 0);
            walls.push_back(wall);
        }
        //bottom
        for (int i = 0; i < 40; i++)
        {
            Wall wall(i * wallSize, 15.5f*50); //15*50
            walls.push_back(wall);
        }

        //others
        for (int i = 0; i < 6; i++)
        {
            Wall wall(i * wallSize, 5 * 50); 
            walls.push_back(wall);
        }

        for (int i = 0; i < 20; i++) //20 
        {
            Wall wall(i * wallSize + 175, 12 * 50); 
            walls.push_back(wall);
        }

        for (int i = 0; i < 24; i++) //24 
        {
            Wall wall(5.5f * 50, i * wallSize); 
            walls.push_back(wall);
        }

        for (int i = 0; i < 5; i++)
        {
            Wall wall(12.5f * 50, i * wallSize); 
            walls.push_back(wall);
        }

        for (int i = 0; i < 8; i++)
        {
            Wall wall(12.5f * 50, i * wallSize + 400); 
            walls.push_back(wall);
        }

        for (int i = 0; i < 20; i++)
        {
            Wall wall(i * wallSize + 500, 4.5f * 50); 
            walls.push_back(wall);
        }
    }

    void DrawWalls(sf::RenderWindow& window)
    {
        for (int i = 0; i < walls.size(); i++)
        {
            window.draw(walls[i].wallShape);
        }
        //window.draw(walls);
    }
    
    std::vector<Wall> walls;
private:
    int wallSize = 25;

};
