#include "MAINWINDOW.h"
#include "SFML/Graphics.hpp"
#include "MenuUI.h"
#define SFML_NO_DEPRECATED_WARNING
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "LOGINPAGE.h"
#include "SIGNINPAGE.h"
#include "USERPAGE.h"

MAINWINDOW::MAINWINDOW()
{


    /* sf::TcpSocket socket;
     sf::Socket::Status status = socket.connect("192.168.1.1", 54000);
     if (status != sf::Socket::Done)
     {
         // error...
     }*/


    sf::RenderWindow window(sf::VideoMode(640, 480), "BIBLIOTECA");



    MenuUI menu(window.getSize().x, window.getSize().y);



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
    text.setString("BIBLIOTECA");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);


    //DEFINIRE TEXT LOGIN
    sf::Font Bebas;
    Bebas.loadFromFile("bebas.ttf");
    // LOGINSFML textbox1(15, sf::Color::White, true);
     //textbox1.setFont(Bebas);
    // textbox1.setPosition({ 100, 100 });




    //FOLOSIREA FERESTREI


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type)
            {
                //FOLOSIREA BUTOANELOR + COMENZI
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {

                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;


                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        std::cout << "LOGIN" << std::endl;
                        window.close();
                        LOGINPAGE();
                        break;

                    case 1:
                        std::cout << "SIGN-IN" << std::endl;
                        window.close();
                        SIGNINPAGE();
                        break;

                    case 2:
                        window.close();
                       
                        break;

                    }
                    break;
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;
            }

        }


        window.draw(background);
        window.draw(text);
        //textbox1.drawTo(window);

        menu.draw(window);
        text.setPosition(175, 0);
        window.display();


    }






}
