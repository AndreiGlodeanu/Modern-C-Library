#include "SEARCHBOOKS.h"
#include "LOGINPAGE.h"
#include "inputBox.h"
#include "Button.h"
#include "MAINWINDOW.h"
#include "USERPAGE.h"

SEARCHBOOKS::SEARCHBOOKS()
{

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
    search.setFont(font);
    search.setPosition({ 200, 100 });

    Button btn6("SEARCH", { 100,25 }, 20, sf::Color::White, sf::Color::Black);
    btn6.setFont(font);
    btn6.setPosition({ 450,100 });

    Button btn7("BACK", { 50,50 }, 15, sf::Color::Black, sf::Color::White);
    btn7.setFont(font);
    btn7.setPosition({ 10,10 });

    sf::Text text;
    text.setFont(font);
    text.setString("SEARCH");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);
    text.setPosition({ 250,10 });

    sf::Text searchtext;
    searchtext.setFont(font);
    searchtext.setString("BOOK");
    searchtext.setFillColor(sf::Color::Black);
    searchtext.setCharacterSize(25);
    searchtext.setPosition({ 100,100 });


    std::vector<std::string> resultSearch;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                search.typedOn(event);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (btn6.isMouseOver(window))
                {
                    std::string searchtext;
                    searchtext = search.getText();;
                    std::cout << searchtext << std::endl;
                    //Link with server and DB with searchtext.
                    //Apel catre server si va returna cartile printr-un vector de string.
                    //restultSearch= Server Search.
                }
                if (btn7.isMouseOver(window))
                {
                    window.close();
                    USERPAGE();

                }
                if (search.isMouseover(window))
                {
                    search.setSelected(true);
                }


            }
        }

        window.clear();
        window.draw(background);
        search.drawTo(window);
        window.draw(text);
        window.draw(searchtext);
        btn6.drawTo(window);
        btn7.drawTo(window);
        window.display();
    }

}
