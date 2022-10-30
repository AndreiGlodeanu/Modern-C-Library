#pragma once
#include<vector>
#include<string>
class Menu {
private:
	
	std::string borrowBookName;
	std::vector<std::string> borrowedBookList;
	std::string bookName;
	//Metods for what the app has to do

	//Search
	void Search();

	//List of borrowed books

	void BorrowedBooksList();

	//Borrow a book metod

	void BorrowABook();

	//Return a book metod

	void ReturnBook();

	//Read a book

	void ReadABook();


};