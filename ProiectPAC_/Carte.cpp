#include "Carte.h"
#include <string>
#include<WS2tcpip.h>
#include <iostream>

#include"../Server/Server.h"
#pragma comment(lib, "WS2_32.lib")

Carte::Carte() {

}


std::string Carte::getISBN()
{
	return ISBN;
}

void Carte::showInfo()
{
	SOCKET clientSocket;
	sqlite3* db;
	sqlite3_open("myDb.db", &db);
	objServer.Function("title", "books", clientSocket);
}

void Carte::changeBook()
{
	std::string content;
	std::cout << "Input content: ";
	std::cin >> content;
	this->content = content;
}
