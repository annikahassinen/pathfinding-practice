#pragma once
#include <SFML\Graphics.hpp>
#include <cstdlib>

using namespace sf;

class Menu
{
public:
	Menu(int width, int height)
	{
		if (!font.loadFromFile("../Arialn.ttf"))
		{
			std::cout << "Couldn't find the font" << std::endl;
		}

		menuText[0].setFont(font);
		menuText[0].setFillColor(Color::Red);
		menuText[0].setString("Play");
		menuText[0].setPosition(Vector2f(width / 2, height / 3 * 1));

		menuText[1].setFont(font);
		menuText[1].setFillColor(Color::White);
		menuText[1].setString("Quit");
		menuText[1].setPosition(Vector2f(width / 2, height / 3 * 2));

		selectedItemIndex = 0;
	}

	Menu(int width, int height, std::string string)
	{
		if (!font.loadFromFile("../Arialn.ttf"))
		{
			std::cout << "Couldn't find the font" << std::endl;
		}
		text.setFont(font);
		text.setFillColor(Color::Green);
		text.setString(string);
		text.setPosition(Vector2f(width / 3, height / 6));

		menuText[0].setFont(font);
		menuText[0].setFillColor(Color::Red);
		menuText[0].setString("Play again");
		menuText[0].setPosition(Vector2f(width / 3, height / 3 * 1));

		menuText[1].setFont(font);
		menuText[1].setFillColor(Color::White);
		menuText[1].setString("Quit");
		menuText[1].setPosition(Vector2f(width / 3, height / 3 * 1.5f));

		selectedItemIndex = 0;
	}

	void DrawMenu(sf::RenderWindow& window)
	{
		for (int i = 0; i < 2; i++)
		{
			window.draw(menuText[i]);
		}
	}

	void MoveUp()
	{
		if (selectedItemIndex - 1 >= 0)
		{
			menuText[selectedItemIndex].setFillColor(Color::White);
			selectedItemIndex--;
			menuText[selectedItemIndex].setFillColor(Color::Red);
		}
	}

	void MoveDown()
	{
		if (selectedItemIndex + 1 < 2)
		{
			menuText[selectedItemIndex].setFillColor(Color::White);
			selectedItemIndex++;
			menuText[selectedItemIndex].setFillColor(Color::Red);
		}
	}

	int GetPressedItem() { return selectedItemIndex; }

	Text text;

private:
	int selectedItemIndex;
	Font font;
	Text menuText[2];

};
