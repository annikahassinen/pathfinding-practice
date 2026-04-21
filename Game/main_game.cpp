#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <vector>
#include <cstdlib>
#include <math.h>
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <sstream>
#include "Tilemap.hpp"
#include "Wall.hpp"
#include "WallMap.hpp"
#include "Menu.hpp"

using namespace sf;

int main()
{
    
    float dt = 0.f;
    Clock dtClock;

    srand(time(NULL));

    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window"); //1000 800
    window.setFramerateLimit(60);
    View view;
    view.setSize(1000.f,800.f); //1000 800
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
    float viewSpeed = 100.f;

    //sf::Texture texture;
    //std::string fileName = "../kamklogo.png";
    //if (!texture.loadFromFile(fileName))
    //{
    //    printf("Texture %s could not be loaded!\n", fileName.c_str());
    //    return -1;
    //}

    //sf::Sprite sprite(texture);

    //sprite.setScale(0.1f, 0.1f);
    //sprite.setPosition(100.0f, 100.0f);

    sf::Clock clock, Cooldown;

    Menu menu(window.getSize().x, window.getSize().y);
    Menu endMenu(window.getSize().x, window.getSize().y, "Placeholder text");
/*    Player myPlayer("../kamklogo.png");*///, 100, 100);
    Player myPlayer(50.f, 50.f);

    //enemy
    int enemy1x = 700;
    int enemy1y = 700;
    int enemy2x = 450;
    int enemy2y = 400;
    int enemy3x = 800;
    int enemy3y = 300;
    int enemy4x = 200;
    int enemy4y = 500;
    int enemy5x = 400;
    int enemy5y = 100;

    Enemy enemy1(enemy1x, enemy1y);
    Enemy enemy2(enemy2x, enemy2y);
    Enemy enemy3(enemy3x, enemy3y);
    Enemy enemy4(enemy4x, enemy4y);
    Enemy enemy5(enemy5x, enemy5y);

    std::vector<Enemy> enemyVector;
    enemyVector.push_back(Enemy(enemy1));
    enemyVector.push_back(Enemy(enemy2));
    enemyVector.push_back(Enemy(enemy3));
    enemyVector.push_back(Enemy(enemy4));
    enemyVector.push_back(Enemy(enemy5));

    //timers
    int shootTimer = 0;
    int damageTimer = 0;
    int enemySpawnTimer = 0;
    int spawnTimerMax = 250;
    int payloadTimer = 0;
    int payloadTimerMax = 50;
    int payloadDamageTimer = 0;
    int payloadDamageTimerMax = 20;

    Payload payload(900, 50);
    WallMap myWallmap;
    Tilemap myTilemap(myWallmap.walls);

    //gamestate
    bool gameIsOn = false;
    bool mainMenuOn = true;
    bool endMenuOn = false;

    //UI text
    Font font;
    Text hpText;
    Text pointsText;
    Text payloadHp;

    if (!font.loadFromFile("../Arialn.ttf"))
    {
        std::cout << "Couldn't find the font" << std::endl;
    }

    hpText.setFont(font);
    hpText.setFillColor(Color::Red);
    hpText.setPosition(Vector2f(window.getSize().x - 950.f, window.getSize().y - 50.f));

    pointsText.setFont(font);
    pointsText.setFillColor(Color::Red);
    pointsText.setPosition(Vector2f(window.getSize().x - 150.f, window.getSize().y - 50.f));

    payloadHp.setFont(font);
    payloadHp.setFillColor(Color::Red);
    payloadHp.setPosition(Vector2f(window.getSize().x - 950.f, window.getSize().y - 775.f));
  

    while (window.isOpen()) {
        sf::Event Event;
        sf::Time elapsed = clock.restart();
        sf::Time cooldown = Cooldown.getElapsedTime();
        dt = dtClock.restart().asSeconds();


        while (window.pollEvent(Event)) {
            switch (Event.type) {


            case sf::Event::KeyReleased:
                if (mainMenuOn)
                {
                    switch (Event.key.code)
                    {
                    case sf::Keyboard::W://Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::S://Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            //std::cout << "Play button" << std::endl;
                            mainMenuOn = false;
                            gameIsOn = true;
                            break;
                        case 1:
                            //std::cout << "Quit button" << std::endl;
                            window.close();
                            break;
                        }

                    }
                    break;
                }

                if (endMenuOn)
                {
                    switch (Event.key.code)
                    {
                    case sf::Keyboard::W://Up:
                        endMenu.MoveUp();
                        break;
                    case sf::Keyboard::S://Down:
                        endMenu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (endMenu.GetPressedItem())
                        {
                        case 0:
                        {
                            //reset game 
                            endMenuOn = false;

                            Enemy enemy1(enemy1x, enemy1y);
                            Enemy enemy2(enemy2x, enemy2y);
                            Enemy enemy3(enemy3x, enemy3y);
                            Enemy enemy4(enemy4x, enemy4y);
                            Enemy enemy5(enemy5x, enemy5y);

                            enemyVector.push_back(Enemy(enemy1));
                            enemyVector.push_back(Enemy(enemy2));
                            enemyVector.push_back(Enemy(enemy3));
                            enemyVector.push_back(Enemy(enemy4));
                            enemyVector.push_back(Enemy(enemy5));

                            myPlayer.points = 0;

                            gameIsOn = true;

                            myPlayer.playerShape.setPosition(50.f, 50.f);
                            payload.payloadShape.setPosition(900.f, 50.f);

                            payload.lategame = false;
                            myPlayer.health = myPlayer.maxHealth;
                            payload.hp = 50;

                            myTilemap.Astar();
                            myTilemap.DrawWayBack();
                            std::reverse(myTilemap.sNodeWay.begin(), myTilemap.sNodeWay.end());
                        }
                            break;
                        case 1:
                            //std::cout << "Quit button" << std::endl;
                            window.close();
                            break;
                        }

                    }
                    break;
                }
            

            break;

            case sf::Event::Closed:
                    window.close();
            }
                  
        }

        //UPDATE

        if (gameIsOn)
        {
            //myTilemap.Update(window);

            //UI text
            std::ostringstream oss;
            oss << myPlayer.health;
            hpText.setString("Player hp: " + oss.str());

            std::ostringstream oss2;
            oss2 << myPlayer.points;
            pointsText.setString(oss2.str() + " points");

            std::ostringstream oss3;
            oss3 << payload.hp;
            payloadHp.setString("Payload hp: " + oss3.str());

            //player
            myPlayer.Update(window, enemyVector, dtClock, myWallmap.walls, payload);

            //colliders
            for (int i = 0; i < myWallmap.walls.size(); i++)
            {
                myWallmap.walls[i].GetCollider().CheckCollision(myPlayer.GetCollider(), 1.f);

                for (int j = 0; j < enemyVector.size(); j++)
                {
                    myWallmap.walls[i].GetCollider().CheckCollision(enemyVector[j].GetCollider(), 1.f);
                }
            }

            for (int i = 0; i < enemyVector.size(); i++)
            {
                enemyVector[i].GetCollider().CheckCollision(myPlayer.GetCollider(), 0.3f);

                for (int j = 0; j < enemyVector.size(); j++)
                {
                    enemyVector[i].GetCollider().CheckCollision(enemyVector[j].GetCollider(), 0.5f);
                }

                if (enemyVector[i].enemyShape.getGlobalBounds().intersects(payload.payloadShape.getGlobalBounds()))
                {
                    if (payloadDamageTimer < payloadDamageTimerMax)
                    {
                        payloadDamageTimer++;
                    }
                    else
                    {
                        payload.hp--;
                        std::cout << "Payload hp: " << payload.hp << std::endl;
                        payloadDamageTimer = 0;
                    }

                }
            }

            if (myPlayer.playerShape.getGlobalBounds().intersects(payload.payloadShape.getGlobalBounds()))
            {
                payload.lategame = true;

            }


            //losing
            if (myPlayer.health == 0 || payload.hp == 0)
            {
                gameIsOn = false;
                endMenuOn = true;

                //reset enemies and A*
                while (!enemyVector.empty())
                {
                    enemyVector.erase(enemyVector.begin());
                }

                while (!myTilemap.sNodeWay.empty())
                {
                    myTilemap.sNodeWay.erase(myTilemap.sNodeWay.begin());
                }

                endMenu.text.setString("You lost! You got " + oss2.str() + " points!");
            }

            

            //enemy logic
            for (int i = 0; i < enemyVector.size(); i++)
            {

                if (enemyVector[i].x == enemy1x && enemyVector[i].y == enemy1y)
                {
                    enemyVector[i].EnemyLogic(0, -1, dtClock, myPlayer.playerShape, enemy1x, enemy1y, payload);
                }
                else if (enemyVector[i].x == enemy2x && enemyVector[i].y == enemy2y)
                {
                    enemyVector[i].EnemyLogic(1, 0, dtClock, myPlayer.playerShape, enemy2x, enemy2y, payload);
                }
                else if (enemyVector[i].x == enemy3x && enemyVector[i].y == enemy3y)
                {
                    enemyVector[i].EnemyLogic(-1, 0, dtClock, myPlayer.playerShape, enemy3x, enemy3y, payload);
                }
                else if (enemyVector[i].x == enemy4x && enemyVector[i].y == enemy4y)
                {
                    enemyVector[i].EnemyLogic(0, 1, dtClock, myPlayer.playerShape, enemy4x, enemy4y, payload);
                }
                else if (enemyVector[i].x == enemy5x && enemyVector[i].y == enemy5y)
                {
                    enemyVector[i].EnemyLogic(0, 1, dtClock, myPlayer.playerShape, enemy5x, enemy5y, payload);
                }
                else
                {
                    enemyVector[i].EnemyLogic(0, -1, dtClock, myPlayer.playerShape, 800, 300, payload);
                }

            }


            //this lets you move the screen
            /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
                view.move(viewSpeed * dt, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                view.move(-viewSpeed * dt, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                view.move(0.f, viewSpeed * dt);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
                view.move(0.f, -viewSpeed * dt);*/



            //spawn new enemies late
            if (payload.lategame)
            {
                if (enemySpawnTimer < spawnTimerMax)
                {
                    enemySpawnTimer++;
                }

                if (enemySpawnTimer >= spawnTimerMax)
                {
                    Enemy e1;
                    //random position
                    e1.enemyShape.setPosition((rand() % int(window.getSize().x - e1.enemyShape.getSize().x)), (rand() % int(window.getSize().y - e1.enemyShape.getSize().y)));
                    enemyVector.push_back(e1);
                    enemySpawnTimer = 0;
                }

                //move the payload along the way
                if (payloadTimer < payloadTimerMax)
                {
                    payloadTimer++;
                }
                if (payloadTimer >= payloadTimerMax)
                {
                    if (payload.payloadShape.getPosition() == myTilemap.goalNode.nodeShape.getPosition())
                    {
                        //get rid of all enemies so the game can be reset
                        gameIsOn = false;
                        endMenuOn = true;

                        while (!enemyVector.empty())
                        {
                            enemyVector.erase(enemyVector.begin());
                        }

                        //just in case
                        while (!myTilemap.sNodeWay.empty())
                        {
                            myTilemap.sNodeWay.erase(myTilemap.sNodeWay.begin());
                        }

                        endMenu.text.setString("You won! You got " + oss2.str() + " points!");
                    }
                    else
                    {
   
                        payload.payloadShape.setPosition(myTilemap.sNodeWay.front().getPosition());
                        payloadTimer = 0;
                        myTilemap.sNodeWay.erase(myTilemap.sNodeWay.begin());
                    }
                }


            }
        }
      

        //DRAW
        window.clear();

        window.setView(view);

        window.setView(window.getDefaultView());

        //render game elements

        if (mainMenuOn)
        {
            menu.DrawMenu(window);
        }

        if (endMenuOn)
        {
            window.draw(endMenu.text);
            endMenu.DrawMenu(window);
        }

        if (gameIsOn)
        {
            myTilemap.DrawTilemap(window);

            myWallmap.DrawWalls(window);

            for (int i = 0; i < myTilemap.sNodeWay.size(); i++)
            {
                if (payload.lategame)
                {
                    window.draw(myTilemap.sNodeWay[i]);
                }

            }

            window.draw(hpText);
            window.draw(pointsText);

            if (payload.lategame)
            {
                window.draw(payloadHp);
            }

            myPlayer.drawPlayer(window);


            for (size_t i = 0; i < myPlayer.bullets.size(); i++)
            {
                window.draw(myPlayer.bullets[i].bullet);
            }


            for (size_t i = 0; i < enemyVector.size(); i++)
            {
                window.draw(enemyVector[i].enemyShape);
            }

            window.draw(payload.payloadShape);

        }

        window.display();
    }

    return 0;
}
