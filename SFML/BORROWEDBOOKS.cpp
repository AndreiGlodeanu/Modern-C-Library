#include "BORROWEDBOOKS.h"
#include "SEARCHBOOKS.h"
#include "LOGINPAGE.h"
#include "inputBox.h"
#include "Button.h"
#include "MAINWINDOW.h"
#include "USERPAGE.h"
#include "ALLBOOKS.h"

BORROWEDBOOKS::BORROWEDBOOKS()
{
    std::vector< Button>buttonVectorDELETE;
    std::vector< Button>buttonVectorREAD;
    std::vector< Button>buttonVectorEXTEND;



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

    Button btn9("DELETE", { 0,0 }, 0, sf::Color::White, sf::Color::Black);
    Button btn10("EXTEND ", { 0,0 }, 0, sf::Color::White, sf::Color::Black);
    Button btn11("READ", { 0,0 }, 0, sf::Color::White, sf::Color::Black);


    Button btn7("BACK", { 50,50 }, 15, sf::Color::Black, sf::Color::White);
    btn7.setFont(font);
    btn7.setPosition({ 10,10 });

    sf::Text text;
    text.setFont(font);
    text.setString("BORROWED BOOKS");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(60);
    text.setPosition({ 150,10 });

    //CREATING VECTOR FOR BOOKS.

    std::vector<std::string> bookName;
    std::string auxBook = "book1";
    bookName.push_back(auxBook);
    bookName.push_back("book2");
    bookName.push_back("book3");
    bookName.push_back("book4");
    bookName.push_back("book5");
    bookName.push_back("book6");
    sf::Text myBook[150];
    float ybook4 = 135;
    for (int i = 0; i < bookName.size(); i++)
    {
        myBook[i].setPosition({ 50, ybook4 });
        myBook[i].setFillColor(sf::Color::Black);
        myBook[i].setCharacterSize(25);
        myBook[i].setFont(font);
        myBook[i].setString(bookName[i]);
        ybook4 += 40;
    }

   



    float  ybook = 100, y2book = 100, y3book = 100;

    //EVERY BUTTON POSITION FONT AND COLOR.
    for (int i = 0; i < bookName.size(); i++)
    {


        Button btn9("DELETE", { 50,25 }, 10, sf::Color::Black, sf::Color::White);
        ybook += 40;
        btn9.setPosition({ 350, ybook });
        btn9.setBackColor(sf::Color::White);
        btn9.setTextColor(sf::Color::Black);
        btn9.setFont(font);

        buttonVectorDELETE.push_back(btn9);

       
    }

    for (int i = 0; i < bookName.size(); i++)
    {


        Button btn10("EXTEND", { 50,25 }, 10, sf::Color::Black, sf::Color::White);
        y2book += 40;
        btn10.setPosition({ 450, y2book });
        btn10.setBackColor(sf::Color::White);
        btn10.setTextColor(sf::Color::Black);
        btn10.setFont(font);

        buttonVectorEXTEND.push_back(btn10);


    }

    for (int i = 0; i < bookName.size(); i++)
    {


        Button btn11("READ", { 50,25 }, 10, sf::Color::Black, sf::Color::White);
        y3book += 40;
        btn11.setPosition({ 550, y3book });
        btn11.setBackColor(sf::Color::White);
        btn11.setTextColor(sf::Color::Black);
        btn11.setFont(font);

        buttonVectorREAD.push_back(btn11);


    }


    std::vector<std::string> resultSearch;

//WINDOW COMMANDS.
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
                for (int index = 0; index < buttonVectorDELETE.size(); index++)
                {

                    if (buttonVectorDELETE[index].isMouseOver(window))
                    {
                        std::cout << "DELETE TEST";
                        //MATCHING WITH SERVER TO DELETE FROM DB.
                    }
                }

                for (int index = 0; index < buttonVectorEXTEND.size(); index++) {
                    if (buttonVectorEXTEND[index].isMouseOver(window))
                    {
                        std::cout << "EXTEND TIME TEST";
                        //MATCHING WITH SERVER TO EXTEND TIME.
                    }
                }
                for (int index = 0; index < buttonVectorREAD.size(); index++) {
                    if (buttonVectorREAD[index].isMouseOver(window))
                    {
                        std::cout << "READ BOOK TEST.";
                        //MATCHING WITH SERVER TO READ BOOK.
                    }

                }
                if (btn7.isMouseOver(window))
                {
                    window.close();
                    USERPAGE();

                }
                


            }
        }

        window.clear();
        window.draw(background);
        window.draw(text);
        for (int indexButton = 0; indexButton < buttonVectorREAD.size(); indexButton++)
        {
            buttonVectorREAD[indexButton].drawTo(window);
        }
        for (int indexButton = 0; indexButton < buttonVectorEXTEND.size(); indexButton++)
        {
            buttonVectorEXTEND[indexButton].drawTo(window);
        }
        for (int indexButton = 0; indexButton < buttonVectorDELETE.size(); indexButton++)
        {
            buttonVectorDELETE[indexButton].drawTo(window);
        }
        for (int indexButton = 0; indexButton < bookName.size(); indexButton++)
        {   
            window.draw(myBook[indexButton]);
        }

        //btn9.drawTo(window);
        btn7.drawTo(window);
        window.display();
    }
}
