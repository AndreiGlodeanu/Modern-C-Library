#include "LOGINPAGE.h"
#include "inputBox.h"
#include "Button.h"
#include "SIGNINPAGE.h"
#include "MAINWINDOW.h"

SIGNINPAGE::SIGNINPAGE()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SIGN-IN");
    inputBox username(20, sf::Color::Black, true, 10, false);
    inputBox password(20, sf::Color::Black, true, 10, false);
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
    username.setFont(font);
    username.setPosition({ 200, 100 });
    password.setFont(font);
    password.setPosition({ 200, 200 });
    password.SetPass(true);

    Button btn1("SIGN-IN", { 100,50 }, 20, sf::Color::White, sf::Color::Black);
    btn1.setFont(font);
    btn1.setPosition({ 250,300 });

    Button btn2("BACK", { 50,50 }, 15, sf::Color::Black, sf::Color::White);
    btn2.setFont(font);
    btn2.setPosition({ 10,10 });

    sf::Text text;
    text.setFont(font);
    text.setString("SIGN-IN");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);
    text.setPosition({ 250,10 });

    sf::Text usertext;
    usertext.setFont(font);
    usertext.setString("USERNAME");
    usertext.setFillColor(sf::Color::Black);
    usertext.setCharacterSize(25);
    usertext.setPosition({ 100,100 });

    sf::Text passtext;
    passtext.setFont(font);
    passtext.setString("PASSWORD");
    passtext.setFillColor(sf::Color::Black);
    passtext.setCharacterSize(25);
    passtext.setPosition({ 100,200 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                username.typedOn(event);
                password.typedOn(event);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (btn1.isMouseOver(window))
                {
                    std::string usernametext;
                    std::string passwordtext;
                    usernametext = username.getText();
                    passwordtext = password.getPassword();
                    //JUST FOR TEXT TEST, LINK WITH SERVER BY usernametext and passwordtext.
                    std::cout << usernametext << std::endl;
                    std::cout << passwordtext << std::endl;

                }

                if (btn2.isMouseOver(window))
                {
                    window.close();
                    MAINWINDOW();
                    
                }

                if (username.isMouseover(window))
                {
                    username.setSelected(true);
                    password.setSelected(false);
                }
                if (password.isMouseover(window))
                {
                    username.setSelected(false);
                    password.setSelected(true);
                }
            }
        }

        window.clear();
        window.draw(background);
        username.drawTo(window);
        password.drawTo(window);
        window.draw(text);
        window.draw(usertext);
        window.draw(passtext);
        btn1.drawTo(window);
        btn2.drawTo(window);
        window.display();
    }
}
