#include "LogIn.h"
#include<string>
#include<sstream>
#include<iostream>


#pragma once

LogIn::LogIn()
{
}

void LogIn::Logger(SOCKET clientSocket, sqlite3* db)
{
	
	bool nameOk=0, passwordOk=0;
	std::ostringstream s1,s3;
	std::ostringstream anotherTryStream;
	sqlite3_stmt* stmt;
	char* err;
	const unsigned char* vef;
	const unsigned char* vef2;
	char buf[4096];
	char buf2[4096];
	ZeroMemory(buf, 4096);
	ZeroMemory(buf2, 4096);
	std::string name, nameMessage, passwordMessage, query = "select user,password from users";
	nameMessage = "Type your name:";
	passwordMessage = "Type your password:";

	//citire date de la client

	send(clientSocket, nameMessage.c_str(), nameMessage.size() + 1, 0);
	int bytesIn = recv(clientSocket, buf, 4096, 0);
	bytesIn = recv(clientSocket, buf, 4096, 0);
	send(clientSocket, passwordMessage.c_str(), passwordMessage.size() + 1, 0);
	bytesIn = recv(clientSocket, buf2, 4096, 0);
	bytesIn = recv(clientSocket, buf2, 4096, 0);

	//verificare in baza de date

	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	s1 << buf;
	s3 << buf2;
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		std::ostringstream s2, s4;
		vef = sqlite3_column_text(stmt, 0);
		vef2 = sqlite3_column_text(stmt, 1);
		s2 << vef;
		s4 << vef2;
		if (s1.str() == s2.str() && s3.str() == s4.str())
		{
			nameOk = 1;
			passwordOk = 1;
		}
	}
	ZeroMemory(buf, 4096);
	//std::cout << nameOk << " " << passwordOk;
	if (nameOk == 1 && passwordOk == 1)
	{
		objServerMenu.setUsername(s1.str());
		objServerMenu.setPassword(s3.str());
		name = "te ai conectat!\n\r";
		send(clientSocket, name.c_str(), name.size() + 1, 0);

		//server message
		std::cout << "\nclientul s-a conectat la contul sau\n";

		objServerMenu.BigMenu(clientSocket, db);
		return;
	}
	else
	{
		name = "date gresite\n";
		send(clientSocket, name.c_str(), name.size() + 1, 0);
		std::string messageForSignIn = "would you like to create a new count or try to log in again? 0 or 1";
		int anotherTry = recv(clientSocket, buf, 4096, 0);
		send(clientSocket, messageForSignIn.c_str(), messageForSignIn.size() + 1, 0);
		ZeroMemory(buf, 4096);
		int anotherTry1 = recv(clientSocket, buf, 4096, 0);
		anotherTryStream << buf;
		if (anotherTryStream.str() == "0")
		{
			Signing(clientSocket, db);
		}
		else
		{
			if (anotherTryStream.str() == "1")
			{
				Logger(clientSocket, db);
			}
		}

	}
	


}

void LogIn::Login(SOCKET clientSocket, sqlite3* db)
{
	char buf[4096];
	ZeroMemory(buf, 4096);
	std::string message1 = "Log In Page.  Choose an option(1 or 2):\r\n",
		message2 = "1.Log in\r\n",
		message3 = "2.Sign in\r\n";
	send(clientSocket, message1.c_str(), message1.size() + 1, 0);
	send(clientSocket, message2.c_str(), message2.size() + 1, 0);
	send(clientSocket, message3.c_str(), message3.size() + 1, 0);
	int bytesIn = recv(clientSocket, buf, 4096, 0);
	if (bytesIn<0)
		return;
	if (strcmp(buf, "1") == 0)
	{
		Logger(clientSocket, db);
	}
	else
	{
		if (strcmp(buf, "2") == 0)
		{
			Signing(clientSocket, db);
		}
		else
		{
			send(clientSocket, "optiune gresita", 16, 0);
			Login(clientSocket, db);
		}
	}
}

void LogIn::Signing(SOCKET clientSocket, sqlite3* db)
{
	//variables
	bool nameOk=1;
	char* err;
	sqlite3_stmt* stmt;
	sqlite3_stmt* stmt1;
	char buf[4096];
	std::ostringstream s1, s2;
	const unsigned char* vef;
	const unsigned char* vef3;
	const unsigned char* vef2;
	std::string name, nameMessage, passwordMessage, query = "select user from users ";
	nameMessage = "Type your name:";
	passwordMessage = "Type your password:";
	send(clientSocket, "Sign In Page\n\r", 14, 0);

	//getting data from user
	send(clientSocket, nameMessage.c_str(), nameMessage.size() + 1, 0);
	ZeroMemory(buf, 4096);
	int bytesIn = recv(clientSocket, buf, 4096, 0);
	bytesIn = recv(clientSocket, buf, 4096, 0);
	s1 << buf;
	send(clientSocket, passwordMessage.c_str(), passwordMessage.size() + 1, 0);
	bytesIn = recv(clientSocket, buf, 4096, 0);
	bytesIn = recv(clientSocket, buf, 4096, 0);
	s2 << buf;

	//verify in db
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		std::ostringstream s3;
		vef = sqlite3_column_text(stmt, 0);
		s3 << vef;
		if (s1.str() == s3.str() )
		{
			nameOk = 0;
		}
	}
	if (nameOk == 0)
	{
		send(clientSocket, "This username already exist\n\r", 29, 0);
		Signing(clientSocket, db);
	}
	ZeroMemory(buf, 4096);
	std::string query1 = "insert into users(user) values ('";
	query1 = query1 + s1.str();
	query1 = query1 + "');";

	//takes the higher index from users tabel
	std::string query3 = "select max(idUser) from users";
	std::ostringstream idStream;
	sqlite3_prepare_v2(db, query3.c_str(), -1, &stmt1, 0);
	while (sqlite3_step(stmt1) != SQLITE_DONE)
	{
		vef3 = sqlite3_column_text(stmt1, 0);
		idStream << vef3;
	}
	int idInt = std::stoi(idStream.str());
	idInt++;
	std::ostringstream idStream2;
	idStream2 << idInt;
	 

	 std::string query2 = "insert into users(idUser,user,password,books_number) values(' ";
	 query2 = query2 + idStream2.str();
	 query2 = query2 + "','";
	 query2 = query2 + s1.str();
	 query2 = query2 + "','";
	 query2 = query2 + s2.str();
	 query2 = query2 + "','";
	 query2 = query2 + "0";
	 query2 = query2 + "');";

	
	 objServerMenu.setUsername(s1.str());
	 objServerMenu.setPassword(s2.str());
	 
	 int rc = sqlite3_exec(db, query2.c_str(), NULL, NULL, &err);
	 if (rc != SQLITE_OK) {
		 std::cout << "error: " << err;
	 }
	 //server message
	 std::cout << "\nclientul si-a creat un nou cont\n";
	 objServerMenu.BigMenu(clientSocket, db);
	 return;
}
