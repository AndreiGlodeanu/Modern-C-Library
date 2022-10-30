#pragma once
#include<iostream>
#include<WS2tcpip.h>
#include<vector>
#include"../sqlite/sqlite3.h"
#include"LogIn.h"
#include"Menu.h"

#pragma comment(lib, "WS2_32.lib")

class Server {
public:
	LogIn obj;
	ServerMenu serverObj;
	Server();
	void Function(std::string column, std::string table, SOCKET&);
	void PrintMoreLines(std::vector<std::string>);
	SOCKET ReturnSocket(SOCKET);
	void CloseSocket(SOCKET clientSocket);
};