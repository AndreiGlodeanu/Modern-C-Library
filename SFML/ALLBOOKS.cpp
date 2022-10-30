#include "ALLBOOKS.h"
#include "SEARCHBOOKS.h"
#include "LOGINPAGE.h"
#include "inputBox.h"
#include "Button.h"
#include "MAINWINDOW.h"
#include "USERPAGE.h"

ALLBOOKS::ALLBOOKS()
{
	//button vector
	std::vector< Button>buttonVector;




	sf::Text books;
	sf::RenderWindow window(sf::VideoMode(640, 480), "LOGIN!");
	inputBox search(20, sf::Color::Black, true, 50, false);
	sf::Font font;
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(1920, 1080));
	sf::Texture MainTexture;
	MainTexture.loadFromFile("img.png");
	background.setTexture(&MainTexture);
	sf::Vector2u size = MainTexture.getSize();
	if (!font.loadFromFile("bebas.ttf"))
	{
		//handle error
	}
	books.setFont(font);
	books.setPosition({ 200, 100 });


	Button btn7("BACK", { 50,50 }, 15, sf::Color::Black, sf::Color::White);
	btn7.setFont(font);
	btn7.setPosition({ 10,10 });

	Button btn8("BORROW", { 100,25 }, 25, sf::Color::White, sf::Color::Black);
	btn8.setFont(font);

	sf::Text text;
	text.setFont(font);
	text.setString("BOOKS");
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(60);
	text.setPosition({ 250,10 });


	books.setFont(font);
	books.setString("BOOK");
	books.setFillColor(sf::Color::Black);
	books.setCharacterSize(25);
	// books.setPosition({ 100,100 });

	std::string auxBook = "book1";
	std::vector<std::string>bookName;
	bookName.push_back(auxBook);
	bookName.push_back("book2");
	bookName.push_back("book3");
	bookName.push_back("book4");
	bookName.push_back("book5");
	bookName.push_back("book6");


	float xbook = 100, ybook = 100;

	for (int i = 0; i < bookName.size(); i++)
	{
		// window.draw(bookName[i]);


		Button btn8(bookName[i], { 400,25 }, 18, sf::Color::Red, sf::Color::Green);
		std::cout << bookName[i] << "\n";
		ybook += 40;
		btn8.setPosition({ xbook, ybook });
		btn8.setBackColor(sf::Color::Green);
		btn8.setTextColor(sf::Color::Red);
		btn8.setFont(font);


		buttonVector.push_back(btn8);
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					for (int index = 0; index < buttonVector.size(); index++)
					{
						if (buttonVector[index].isMouseOver(window))
						{
							std::string bookNameToBorrow = bookName[index];
							//apelam functia de borrowbook cu numele cartii care a fost selectata
							std::cout << bookNameToBorrow;
						}
					}


					if (btn7.isMouseOver(window))
					{
						window.close();
						USERPAGE();

					}
				}

			}

		}
		window.clear();
		window.draw(background);
		search.drawTo(window);
		window.draw(text);
		for (int indexButton = 0; indexButton < buttonVector.size(); indexButton++)
		{
			buttonVector[indexButton].drawTo(window);
		}
		btn7.drawTo(window);
		window.display();
	}

	window.display();


}
