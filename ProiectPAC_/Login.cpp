#include"Login.h"

#include <iostream>
#include <string>

void Login::login()
{

		std::cout << "Username: ";
		std::cin >> username;
		std::cout << "Password: ";
		std::cin >> password;

}

void Login::signin()
{
	std::cout << "First Name: ";
	std::cin >> firstname;
	std::cout << "Last Name: ";
	std::cin >> lastname;
	std::cout << "Username: ";
	std::cin >> username;
	std::cout << "Password: ";
	std::cin >> password;
	std::cout << "Email: ";
	std::cin >> email;
}

void Login::logout()
{
	std::cout << "If you want to logout from accout, press button";
	std::cout << "LOGOUT";
}

void Login::deleteaccount()
{
	std::cout << "If you are sure, you want to delete accout, press button";
	std::cout << "DELETE ACCOUNT";
}

