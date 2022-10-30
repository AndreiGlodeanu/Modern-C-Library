#pragma once
#include <string>
#include"../Server/Server.h"
#include"../Server/Menu.h"
class Carte {
private:
	std::string title, author, ISBN, content;
	unsigned numarCartiDisponibile;
	Server objServer;
	ServerMenu objServerMenu;

public:
	Carte();
	std::string getISBN();
	void showInfo();
	void changeBook();

};
