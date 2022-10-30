#include "MenuUI.h"
#include "iostream"



MenuUI::MenuUI(float width, float height)
{
	if (!font.loadFromFile("theboldfont.ttf"))
	{
		//handle error
	}
//CREARE MENIU + DEFINIRE FONT + CULOARE + POZITIONARE
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("LOGIN");
	menu[0].setPosition(sf::Vector2f(20, 250 / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("SIGN-IN");
	menu[1].setPosition(sf::Vector2f(20, 220 / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("EXIT");
	menu[2].setPosition(sf::Vector2f(20, 210 / (MAX_NUMBER_OF_ITEMS + 1) * 3));


	selectedItemIndex = 0;

}

MenuUI::~MenuUI()
{
}


//AFISARE MENIULUI
void MenuUI::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

//FUNCTIONAREA BUTONULUI UP
void MenuUI::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);

	}
}
//FUNCTIONAREA BUTONULUI DOWN
void MenuUI::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);

	}
}
