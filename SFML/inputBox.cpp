#include "inputBox.h"

inputBox::inputBox(int size, sf::Color color, bool hasL, int limit, bool selected)
{
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	hasLimit = true;
	this->limit = limit;
	isSelected = selected;
	if (selected)
	{
		textbox.setString("_");
	}
	else
	{
		textbox.setString("");
	}
	bkg.setSize(sf::Vector2f(230, 24));
	bkg.setFillColor(sf::Color::White);

}

void inputBox::inputLogic(int charTyped)
{
	if (isSelected)
	{
		if (!isPassword)
		{
			if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
			{
				text << static_cast<char>(charTyped);
			}
			else if (charTyped == DELETE_KEY)
			{
				if (text.str().length() > 0) {
					deleteLastChar();
				}
			}
			textbox.setString(text.str() + "_");
		}
		else
		{

			if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
			{
				password << static_cast<char>(charTyped);
				text << static_cast<char>('*');
			}
			else if (charTyped == DELETE_KEY)
			{
				if (text.str().length() > 0) {
					deleteLastChar();
				}
			}
			textbox.setString(text.str() + "_");
		}

	}

}

void inputBox::deleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}
	text.str("");
	text << newT;
	textbox.setString(text.str());
	if (isPassword)
	{
		std::string p = password.str();

		std::string newP = "";
		for (int i = 0; i < p.length() - 1; i++)
		{
			newP += t[i];
		}
		password.str("");
		password << newT;
	}
}

void inputBox::setFont(sf::Font& font)
{
	textbox.setFont(font);
}

void inputBox::setPosition(sf::Vector2f pos)
{
	textbox.setPosition(pos);
	bkg.setPosition(pos);
}

void inputBox::drawTo(sf::RenderWindow& window)
{
	window.draw(bkg);
	window.draw(textbox);
}

void inputBox::typedOn(sf::Event input)
{
	int charTyped = input.text.unicode;
	if (charTyped < 128)
	{
		if (hasLimit)
		{
			if (text.str().length() < limit)
			{
				inputLogic(charTyped);
			}
			else if (text.str().length() == limit && charTyped == DELETE_KEY)
			{
				deleteLastChar();
			}
		}
		else
		{
			inputLogic(charTyped);
		}
	}

}

void inputBox::setSelected(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++)
		{
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

void inputBox::SetPass(bool sel)
{
	isPassword = sel;
}

std::string inputBox::getText()
{
	return text.str();
}

bool inputBox::isMouseover(sf::RenderWindow& window)
{
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = bkg.getPosition().x;
	float btnPosY = bkg.getPosition().y;

	float btnxPosWidth = bkg.getPosition().x + bkg.getLocalBounds().width;
	float btnyPosHeight = bkg.getPosition().y + bkg.getLocalBounds().height;

	if (mouseX<btnxPosWidth && mouseX>btnPosX && mouseY<btnyPosHeight && mouseY>btnPosY)
	{
		return true;
	}
	return false;
}

std::string inputBox::getPassword()
{
	return password.str();
}

void inputBox::emptyString()
{
	while (text.str().length() > 0)
	{
		deleteLastChar();
	}
	password << "";
	text << "";
}
