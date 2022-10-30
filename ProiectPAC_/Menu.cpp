#include "../Server/Menu.h"
#include"Menu.h"

#include<iostream>


void Menu::Search()
{
	std::cout << "Search bar for books";
	std::cout << "Type the name of the book: ";
	
}

void Menu::BorrowedBooksList()
{
}

void Menu::BorrowABook()
{
	std::cout << "What book do you like to borrow?" << "\n" << "Type the name of the book: ";
	std::cin >> borrowBookName;
}

void Menu::ReturnBook()
{
	std::cout << "Which book would you like to return?";
}

void Menu::ReadABook()
{
	std::cout << "Which book would you like to read? ";
}
