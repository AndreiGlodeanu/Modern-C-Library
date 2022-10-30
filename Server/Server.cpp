#include<iostream>
#include<WS2tcpip.h>
#include<sstream>

#include "Server.h"
#include"LogIn.h"
#include"Menu.h"


#pragma comment(lib, "WS2_32.lib")

Server::Server()
{
}

void Server::Function(std::string column, std::string table, SOCKET& clientSocket)
{
	char* err;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	int rc = sqlite3_exec(db, "Create table if not exists algolancer(x1 int, x2 int, name varchar(100));", NULL, NULL, &err);
	rc = sqlite3_exec(db, "Create table if not exists users(user string, password string);", NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		std::cout << "error: " << err;
		
	}

	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0)
	{
		std::cerr << "Can't initialize winsock ! Quitting" << std::endl;
		return;
	}

	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create a socket! Quitting" << "\n";
		return;
	}

	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;//Could also use inet_pton.....

	bind(listening, (sockaddr*)&hint, sizeof(hint));


	//Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	fd_set master;
	FD_ZERO(&master);

	FD_SET(listening, &master);

	//server message
	std::cout << "\nserverul a fost pornit\n";
	while (true)
	{
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == listening)
			{
				SOCKET client = accept(listening, nullptr, nullptr);
				std::cout << "\nclientul s-a conectat la server #" << clientSocket << "\n";
				obj.Login(client, db);
				std::cout << "\n clientul s-a deconectat de la server#" << clientSocket << "\n";
			}
			else
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				//accept a new message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					//drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{

					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock)
						{
							std::ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							std::string strOut = ss.str();
							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}

	//Cleanup winsock
	WSACleanup();
}

void Server::PrintMoreLines(std::vector<std::string>)
{
}

SOCKET Server::ReturnSocket(SOCKET clientSocket)
{
	return clientSocket;
}

void Server::CloseSocket(SOCKET clientSocket)
{
	closesocket(clientSocket);
}
