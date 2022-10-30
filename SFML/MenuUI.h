#pragma once
#include "Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3

class MenuUI
{
public:
	MenuUI(float width, float height);
	~MenuUI();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() {
		return selectedItemIndex;
	}

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

