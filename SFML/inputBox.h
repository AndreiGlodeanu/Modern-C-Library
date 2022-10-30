#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <sstream>
#define DELETE_KEY 8 
#define ENTER_KEY 12
#define ESCAPE_KEY 27 
class inputBox
{
public:
	inputBox() = default;
	inputBox(int size, sf::Color, bool hasL, int limit, bool selected);
	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	void typedOn(sf::Event input);
	void setSelected(bool sel);
	void SetPass(bool sel);
	std::string getText();
	bool isMouseover(sf::RenderWindow& window);
	std::string getPassword();
	void emptyString();
private:
	sf::Text textbox;
	std::ostringstream password;
	std::ostringstream text;
	sf::RectangleShape bkg;
	bool isSelected = false;
	bool hasLimit = false;
	bool isPassword = false;
	int limit;
	void inputLogic(int charTyped);
	void deleteLastChar();

};

