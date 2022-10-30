#include "client.h"
#include <fstream>
#include <iostream>
#include <string>

Client::Client()
{

}


std::string Client::GetUsername() const
{
	return m_Username;
}

std::vector<Carte> Client::GetBorrowedBooks() const
{
	return m_BorrowedBooks;
}

std::vector<std::string> Client::GetDeadLineborrowedBooks() const
{
	return m_DeadLineborrowedBooks;
}

std::string Client::GetPassword() const
{
	return m_Password;
}

void Client::setUsername(std::string username)
{
	this->m_Username = username;
}

void Client::setPassword(std::string password)
{
	this->m_Password = password;
}

void Client::setBorrowedBooks(std::vector<Carte> BorrowedBooks)
{
	m_BorrowedBooks = BorrowedBooks;
}

void Client::setDeadLineborrowedBooks(std::vector<std::string> DeadLineborrowedBooks)
{
	m_DeadLineborrowedBooks = DeadLineborrowedBooks;
}
