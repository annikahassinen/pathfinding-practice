#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "Wall.hpp"
#include "WallMap.hpp"
#include "Collision.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Payload.hpp"

class Player {
public:


	Player(float x = 100.f, float y = 100.f) {
		playerShape.setFillColor(Color::Green);
		playerShape.setSize(Vector2f(size, size));
		playerShape.setPosition(x, y);
	}

	//Player(std::string imgDirectory, float x = 100.f, float y = 100.f) {
	//	if (!pTexture.loadFromFile(imgDirectory)) {
	//		std::cerr << "Error!\n";
	//	}
	//	pSprite.setTexture(pTexture);
	//	pSprite.setScale(0.05f, 0.05f);
	//	//pSprite.setPosition(100.0f, 100.0f);
	//	pSprite.setPosition(x, y);

	//	leftSide = pSprite.getPosition().x;
	//	rightSide = pSprite.getPosition().x + pSprite.getLocalBounds().width;
	//	topSide = pSprite.getPosition().y;
	//	bottomSide = pSprite.getPosition().y + pSprite.getLocalBounds().height;

	//	isCollide = false;
	//}

	/*void drawPlayer(sf::RenderWindow &window) {
		window.draw(pSprite);
	}*/

	void drawPlayer(sf::RenderWindow& window) {
		window.draw(playerShape);
	}

	//void movePlayer(char direction) {
	//	if (direction == 'u') {
	//		pSprite.move(0, -moveSpeed);
	//	} else if (direction == 'd') {
	//		pSprite.move(0, moveSpeed);
	//	} else if (direction == 'l') {
	//		pSprite.move(-moveSpeed, 0);
	//	} if (direction == 'r') {
	//		pSprite.move(moveSpeed, 0);
	//	}
	//}

	//void moveTest()
	//{
	//	float deltaPos = moveSpeed * (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	//	float delta = moveSpeed * (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A));

	//	pSprite.setPosition(pSprite.getPosition().x + delta, pSprite.getPosition().y + deltaPos);
	//	//Vector2f movement(0.f, 0.f);


	//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//		{
	//			isMovingUp = false;
	//			isMovingDown = false;
	//			isMovingRight = true;
	//			isMovingLeft = false;
	//		}


	//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//		{
	//			isMovingUp = false;
	//			isMovingDown = false;
	//			isMovingLeft = true;
	//			isMovingRight = false;
	//		}


	//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//		{
	//			isMovingUp = true;
	//			isMovingDown = false;
	//			isMovingLeft = false;
	//			isMovingRight = false;
	//		}
	//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//		{
	//			isMovingUp = false;
	//			isMovingDown = true;
	//			isMovingLeft = false;
	//			isMovingRight = false;
	//		}

	//	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	//{
	//	//	yMove = false;
	//	//	xMove = true;

	//	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//	//	{
	//	//		isMovingUp = false;
	//	//		isMovingDown = false;
	//	//		isMovingRight = true;
	//	//		isMovingLeft = false;
	//	//	}
	//	//	
	//	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	//	{
	//	//		isMovingUp = false;
	//	//		isMovingDown = false;
	//	//		isMovingLeft = true;
	//	//		isMovingRight = false;
	//	//	}
	//	//}

	//		
	//}

	/*Vector2f GetPlayerPosition()
	{
		return Vector2f(pSprite.getPosition());
	}*/

	//void TakeDamage(int damage)
	//{
	//	health -= damage;

	//}

	void Heal(Payload payload)
	{
		float deltaX = payload.payloadShape.getPosition().x - playerShape.getPosition().x;
		float deltaY = payload.payloadShape.getPosition().y - playerShape.getPosition().y;

		float intersectX = abs(deltaX) - (0.5f);
		float intersectY = abs(deltaY) - (0.5f);

		if (intersectX < 100.0f && intersectY < 100.0f)
		{
			if (healTimer < maxHealTimer)
			{
				healTimer++;

			}
			else
			{
				if (health < maxHealth)
				{
					//std::cout << health << std::endl;
					health++;
					healTimer = 0;
				}
			}

		}

	}

	//void Collide(Wall wall)
	//{
	//	if (rightSide > wall.leftSide) // && leftSide < wall.rightSide &&
	//		//bottomSide > wall.topSide && topSide < wall.bottomSide)
	//	{
	//		isCollide = true;
	//		pSprite.setPosition(Vector2f(wall.leftSide - pSprite.getGlobalBounds().width, pSprite.getPosition().y));
	//	}
	//	if (leftSide < wall.rightSide)
	//	{

	//	}
	//	else {
	//		isCollide = false;
	//	}

	//}

	void Update(sf::RenderWindow& window, std::vector<Enemy> &enemies, Clock clock, std::vector<Wall> &walls, Payload payload) //WallMap wallMap)
	{
		Movement();
		Shoot(window, enemies, clock, walls);
		Heal(payload);
		takeDamage(enemies);
		//Collide(wallMap.walls);

		//float deltaPos = moveSpeed * (sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W));
		//float delta = moveSpeed * (sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A));

		//playerShape.setPosition(playerShape.getPosition().x + delta, playerShape.getPosition().y + deltaPos);
	}

	void Movement()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerShape.move(-moveSpeed, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playerShape.move(moveSpeed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playerShape.move(0.f, -moveSpeed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playerShape.move(0.f, moveSpeed);
		}
	}

	void takeDamage(std::vector<Enemy> &enemies)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			sf::Vector2f otherHalfSize = playerShape.getSize() / 2.0f;
			sf::Vector2f thisHalfSize = enemies[i].enemyShape.getSize() / 2.0f;

			float deltaX = playerShape.getPosition().x - enemies[i].enemyShape.getPosition().x;
			float deltaY = playerShape.getPosition().y - enemies[i].enemyShape.getPosition().y;

			float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
			float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

			if (damageTimer < maxDamageTimer)
			{
				damageTimer++;
			}
			else
			{
				if (intersectX < 0.0f && intersectY < 0.0f)
				{
					//TakeDamage(1);
					health -= 1;
					damageTimer = 0;
				}
			}

		}

	}

	void Shoot(sf::RenderWindow& window, std::vector<Enemy> &enemies, Clock clock, std::vector<Wall> &walls)
	{
		Bullet b1;
		/*std::vector<Bullet> bullets;*/
		Vector2f playerCenter, mousePosWindow, aimDir, aimDirNorm;

		playerCenter = Vector2f(playerShape.getPosition().x, playerShape.getPosition().y);
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2.f) + pow(aimDir.y, 2.f));

		if (shootTimer < shootLimit)
		{
			shootTimer++;
		}

		if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= shootLimit)
        {
            b1.bullet.setPosition(playerCenter);
            b1.currVelocity = aimDirNorm * b1.speed;
            bullets.push_back(Bullet(b1));
            shootTimer = 0;
        }

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].bullet.move(bullets[i].currVelocity);

			if (bullets[i].bullet.getPosition().x < 0 || bullets[i].bullet.getPosition().x > window.getSize().x
				|| bullets[i].bullet.getPosition().y < 0 || bullets[i].bullet.getPosition().y > window.getSize().y)
			{
				bullets.erase(bullets.begin() + i);
			}

			else
			{

				for (int k = 0; k < enemies.size(); k++)
				{
					if (bullets[i].bullet.getGlobalBounds().intersects(enemies[k].enemyShape.getGlobalBounds()))
					{
						bullets.erase(bullets.begin() + i);
						enemies[k].TakeDamage(1);
						if (enemies[k].health == 0)
						{
							enemies.erase(enemies.begin() + k);
							points += pointsPerEnemy;
						}

						break;
					}


				}

				//for (int j = 0; j < walls.size(); j++)
				//{
				//	if (bullets[i].bullet.getGlobalBounds().intersects(walls[j].wallShape.getGlobalBounds()))
				//	{
				//		bullets.erase(bullets.begin() + i);
				//		break;
				//	}
				//}
			}
			
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			for (int j = 0; j < walls.size(); j++)
			{
				if (bullets[i].bullet.getGlobalBounds().intersects(walls[j].wallShape.getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
					break;
				}
			}
		}
	}

	Collision GetCollider() { return Collision(playerShape); }

	sf::Sprite pSprite;
	RectangleShape playerShape;
	//bool isAlive = true;
	int health = 50;

	
	//float difference = 0.0f;
	//bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown = false;
	//bool xMove, yMove = false;

	//float topSide, bottomSide, rightSide, leftSide;
	//bool isCollide;
	

	std::vector<Bullet> bullets;

	//bool lateGame = false;
	int maxHealth = 50;
	int points = 0;
	int pointsPerEnemy = 100;

private:
	sf::Texture pTexture;
	//sf::Sprite pSprite;
	//float moveSpeed = 5;
	//int health = 10;
	//Vector2f playerCenter;
	
	float size = 25.f;
	int shootLimit = 30;
	int healTimer = 0;
	int maxHealTimer = 50;
	int damageTimer = 0;
	int maxDamageTimer = 100;
	float moveSpeed = 5.f;
	int shootTimer = 0;
};
