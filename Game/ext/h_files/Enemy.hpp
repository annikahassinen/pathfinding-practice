#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "Payload.hpp"
//#include "Player.hpp"
using namespace sf;

//enum EnemyState {
//	PATROL, CHASE, RETREAT
//};

class Enemy {
public:
	Enemy() {
		enemyShape.setFillColor(Color::Magenta);
		enemyShape.setSize(Vector2f(size, size));
	}

	Enemy(int xPos, int yPos) {
		//RectangleShape enemy;
		enemyShape.setFillColor(Color::Magenta);
		enemyShape.setSize(Vector2f(size, size));
		enemyShape.setPosition(xPos, yPos);
		x = xPos;
		y = yPos;
	}

	void drawEnemy(sf::RenderWindow& window) {
		window.draw(enemyShape);
	}

	/*void enemyMove(float dirX, float dirY)
	{
		enemyShape.move(dirX, dirY);
	}*/

	void TakeDamage(int damage)
	{
		health -= damage;
		hit = true;
	}

	void Patrol(float dirX, float dirY, Clock clock)
	{
		sf::Time elapsed = clock.getElapsedTime();

		//for (int i = 0; i < 5; i++)
		//{
		//	enemyShape.move(dirX, dirY);
		//}

		//moveForward = false;

		if (moveTimer < 100 && waitTimer == 0)
		{
			moveTimer++;
		}
		else if (moveTimer == 100)
		{
			waitTimer++;
			moving = false;
		}
		if (waitTimer > 100)
		{
			moving = true;
			if (moveForward && moving)
			{
				moveTimer = 0;
				waitTimer = 0;
				moveForward = false;
			}
			else if (moveForward == false && moving)
			{
				moveTimer = 0;
				waitTimer = 0;
				moveForward = true;
			}
		}

		//else
		//{
		//	for (float i = 0; i < moveTimer; moveTimer--)
		//	{
		//		moveForward = false;
		//	}

		//}

		if (moveForward && moving)
		{
			enemyShape.move(dirX, dirY);
		} 
		else if (moveForward == false && moving)
		{
			enemyShape.move(-dirX, -dirY);
		}

	}

	void Chase(Clock clock, RectangleShape recShape) //Player playerTest,
	{
		moveForward = false;
		moveTimer = 100;
		waitTimer = 0;
		pauseTimer = 0;
		//Player *player;
		//Vector2f distance2 = wall.wallShape.getPosition() - enemyShape.getPosition();
		//Vector2f distance = playerTest.playerShape.getPosition() - enemyShape.getPosition();
		Vector2f distance = recShape.getPosition() - enemyShape.getPosition();
		Vector2f normalizedDistance = normalize(distance);
		//Vector2f distance = player.wallShape.getPosition() - enemyShape.getPosition();
		//enemyShape.move(distance3 * moveSpeed * (clock.getElapsedTime().asSeconds()));
		//enemyShape.move(normalizedDistance * moveSpeed * (clock.getElapsedTime().asSeconds()));
		enemyShape.move(normalizedDistance * moveSpeed * (clock.restart().asSeconds() * 60));

		//pausingTime(clock);
		stop = true;

	}

	void goToPosition(Clock clock, RectangleShape recShape)
	{
		sf::Vector2f otherHalfSize = recShape.getSize() / 2.0f;
		sf::Vector2f thisHalfSize = enemyShape.getSize() / 2.0f;

		float deltaX = recShape.getPosition().x - enemyShape.getPosition().x;
		float deltaY = recShape.getPosition().y - enemyShape.getPosition().y;

		float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		if (intersectX < 200.0f && intersectY < 200.0f)
		{
			stop = true;
		}
		if (stop == false)
		{
			Vector2f position = recShape.getPosition() - enemyShape.getPosition();
			Vector2f normalizedPosition = normalize(position);
			enemyShape.move(normalizedPosition * moveSpeed * (clock.restart().asSeconds() * 60));
		}

	}

	void EnemyLogic(int dirX, int dirY, Clock clock, RectangleShape recShape, int xPos, int yPos, Payload payload)
	{
		sf::Vector2f otherHalfSize = recShape.getSize() / 2.0f;
		sf::Vector2f thisHalfSize = enemyShape.getSize() / 2.0f;

		float deltaX = recShape.getPosition().x - enemyShape.getPosition().x;
		float deltaY = recShape.getPosition().y - enemyShape.getPosition().y;

		float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		if (payload.lategame == false)
		{
			if (hit)
			{
				if (hitTimer < 100)
				{
					Chase(clock, recShape);
					hitTimer++;
				}

				if (hitTimer == 100)
				{
					hitTimer = 0;
					hit = false;
				}

			}
			else
			{
				if (inSight == false)
				{
					if (stop == true)
					{
						moveBack(clock, xPos, yPos, recShape);
					}
					else 
					{
						pauseTimer = 0;
						Patrol(dirX, dirY, clock);
					}


				}

				if (intersectX < 100.0f && intersectY < 100.0f)
				{
					inSight = true;

					Chase(clock, recShape);

				}
				else
				{
					inSight = false;
				}
			}
		}

		else
		{
			Chase(clock, recShape);
		}

	}

	void moveBack(Clock clock, float xPos, float yPos, RectangleShape recShape)
	{

		
		if (pauseTimer < 100)
		{
			pauseTimer++;
		}
		else
		{
			float deltaZ = enemyShape.getPosition().x - xPos;
			float deltaW = enemyShape.getPosition().y - yPos;

			float intersectZ = abs(deltaZ) - 0.5f;
			float intersectW = abs(deltaW) - 0.5f;

			Vector2f distance = Vector2f(xPos, yPos) - enemyShape.getPosition();
			Vector2f normalizedDistance = normalize(distance);
			enemyShape.move(normalizedDistance * moveSpeed * (clock.restart().asSeconds() * 60));
			//pauseTimer = 0;

			if (intersectZ < 0.01f && intersectW < 0.01f)//(enemyShape.getPosition() == Vector2f(xPos, yPos))
			{
				//pausingTime(clock);
				stop = false;
			}
		}

		
	}


	//void testing(float dirX, float dirY, Clock clock, RectangleShape recShape, float xPos, float yPos)
	//{
	//	//EnemyState currentState = PATROL;

	//	sf::Vector2f otherHalfSize = recShape.getSize() / 2.0f;
	//	sf::Vector2f thisHalfSize = enemyShape.getSize() / 2.0f;

	//	float deltaX = recShape.getPosition().x - enemyShape.getPosition().x;
	//	float deltaY = recShape.getPosition().y - enemyShape.getPosition().y;

	//	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	//	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	//	switch (currentState)
	//	{
	//	case PATROL:
	//		Patrol(dirX, dirY, clock);
	//		if (intersectX < 200.0f && intersectY < 200.0f)
	//		{
	//			currentState = CHASE;
	//		}
	//		break;
	//	case CHASE:
	//		Chase(clock, recShape);
	//		if (intersectX < 300.0f && intersectY < 300.0f)
	//		{
	//			currentState = RETREAT;
	//		}
	//		break;
	//	case RETREAT:
	//		moveBack(clock, xPos, yPos, recShape);
	//		if (enemyShape.getPosition() == Vector2f(xPos, yPos))
	//		{
	//			currentState = PATROL;
	//		}
	//		break;
	//	default:
	//		std::cout << "Error: invalid state" << std::endl;
	//		break;
	//	}
	//}

	Vector2f normalize(Vector2f vec)
	{
		float magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y);
		if (magnitude != 0)
		{
			vec.x /= magnitude;
			vec.y /= magnitude;
		}

		return vec;
	}

	float Calc(RectangleShape recShape)
	{
		sf::Vector2f otherHalfSize = recShape.getSize() / 2.0f;
		sf::Vector2f thisHalfSize = enemyShape.getSize() / 2.0f;

		float deltaX = recShape.getPosition().x - enemyShape.getPosition().x;
		float deltaY = recShape.getPosition().y - enemyShape.getPosition().y;

		float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		return intersectX, intersectY;
	}

	Collision GetCollider() { return Collision(enemyShape); }

	RectangleShape enemyShape;
	int health = 5;
	//bool isAlive = true;
	//EnemyState currentState;
	bool hit = false;
	//bool lateGame = false;

	int x = 0;
	int y = 0;


private:
	//RectangleShape enemy;
	float moveSpeed = 200;
	float moveTimer = 0;
	float waitTimer = 0;
	float pauseTimer = 0;
	bool moveForward, moving;
	//float testSpeed = 1;
	bool stop = false;
	bool inSight = false;
	float hitTimer = 0;
	float size = 25.f;

	//float intersectX = 0;
	//float intersectY = 0;
};
