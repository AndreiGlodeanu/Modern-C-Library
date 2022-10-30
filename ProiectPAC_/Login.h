#pragma once
#include <string>

#include<WS2tcpip.h>

class Login {
private:
	std::string username, password, lastname, firstname, email;
public:
	//Sinq account with DB
	void login();
	void signin();
	void logout();
	void deleteaccount();

};