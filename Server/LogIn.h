#pragma once
#include<WS2tcpip.h>
#include"../sqlite/sqlite3.h"
#include <sstream>
#include "Menu.h"


class LogIn {
public:
	LogIn();
	ServerMenu objServerMenu;
	void Logger(SOCKET, sqlite3*);
	void Login(SOCKET,sqlite3*);
	void Signing(SOCKET,sqlite3 *);

};
