#pragma once
#include<WS2tcpip.h>
#include"../sqlite/sqlite3.h"
#include <sstream>
#include<vector>

class ServerMenu {
public:
	ServerMenu();
	void BigMenu(SOCKET, sqlite3*);
	void Search(SOCKET, sqlite3*);
	void DeleteAccount(SOCKET, sqlite3*);
	void setUsername(std::string);
	void setPassword(std::string );
	void LogOut(SOCKET, sqlite3*);
	void RentBook(SOCKET, sqlite3*);
	void RentedBooks(SOCKET, sqlite3*);
	void BookMenu(SOCKET, sqlite3*, std::vector<std::string>);
	void DeadlineExtension(SOCKET ,sqlite3*,std::string);
	void ReturnABook(SOCKET, sqlite3*, std::string);
	void ReadABook(SOCKET, sqlite3*, std::string);
	bool CheckBookAppearances(SOCKET, sqlite3*, std::string);
private:
	char buf[4096];
	std::string username, password;
};