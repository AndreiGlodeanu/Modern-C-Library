#include "MAINWINDOW.h"
#include "SFML/Graphics.hpp"
#include "MenuUI.h"
#define SFML_NO_DEPRECATED_WARNING
#include <iostream>
#include "LOGINPAGE.h"
#include "SIGNINPAGE.h"
#include "Button.h"
#include "USERPAGE.h"
#include "SEARCHBOOKS.h"
#include "ALLBOOKS.h"
#include "BORROWEDBOOKS.h"

USERPAGE::USERPAGE()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "BIBLIOTECA");





    sf::RectangleShape background;
    background.setSize(sf::Vector2f(1920, 1080));
    sf::Texture MainTexture;
    MainTexture.loadFromFile("img.png");
    background.setTexture(&MainTexture);
    sf::Vector2u size = MainTexture.getSize();
    background.setOrigin(size.x / 2, size.y / 2);

    sf::Font font;
    if (!font.loadFromFile("bebas.ttf"))
    {
        //handle error
    }
    //DEFINIRE TITLU + FONT + CULOARE + POZITIONARE
    sf::Text text;
    text.setFont(font);
    text.setString("USER");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);
    text.setPosition({ 250,5 });


  
    Button btn2("BACK", { 50,50 }, 15, sf::Color::Black, sf::Color::White);
    btn2.setFont(font);
    btn2.setPosition({ 10,10 });

    Button btn3("AVAILABLE BOOKS", { 200,30 }, 20, sf::Color::White, sf::Color::Black);
    btn3.setFont(font);
    btn3.setPosition({ 200,100 });

    Button btn4("SEARCH BOOKS", { 200,30 }, 20, sf::Color::White, sf::Color::Black);
    btn4.setFont(font);
    btn4.setPosition({ 200,200 });

    Button btn5("BORROWED BOOKS", { 200,30 }, 20, sf::Color::White, sf::Color::Black);
    btn5.setFont(font);
    btn5.setPosition({ 200,300 });

    //FOLOSIREA FERESTREI




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (btn2.isMouseOver(window))
                {
                    window.close();
                    MAINWINDOW();
                }

                if (btn3.isMouseOver(window))
                {
                    window.close();
                    ALLBOOKS();

                }
                if (btn4.isMouseOver(window))
                {
                    window.close();
                    SEARCHBOOKS();

                }
                if (btn5.isMouseOver(window))
                {
                    window.close();
                    BORROWEDBOOKS();
                }



            }
        }


        window.draw(background);
        window.draw(text);
        btn2.drawTo(window);
        btn3.drawTo(window);
        btn4.drawTo(window);
        btn5.drawTo(window);
        window.display();


    }





    //testare animatie
    //variabila playerTexture va trebui importata

}


