#pragma once
#include<string>
#include<vector>
#include"Carte.h"
class Client {
private:
	std::string m_Username, m_Password;
	std::vector<Carte>m_BorrowedBooks;
	std::vector<std::string>m_DeadLineborrowedBooks;
public:
	Client();
	Client(std::string username, std::string parola, std::vector<Carte>cartiImprutate, std::vector<std::string>DeadImprumutCarte);
	std::string GetUsername() const;
	std::vector<Carte>GetBorrowedBooks() const;
	std::vector<std::string>GetDeadLineborrowedBooks() const;
	std::string GetPassword() const;

	void setUsername(std::string username);
	void setPassword(std::string password);
	void setBorrowedBooks(std::vector<Carte>BorrowedBooks);
	void setDeadLineborrowedBooks(std::vector<std::string>DeadLineborrowedBooks);
};

