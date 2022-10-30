#include "Menu.h"
#include<iostream>
#include<string>
#include<vector>

ServerMenu::ServerMenu()
{
}

void ServerMenu::BigMenu(SOCKET clientSocket, sqlite3* db)
{
	char buf1[4096];
	char aux3[4096] = "1";
	std::ostringstream s;
	std::string menuMessage1 = "This is the menu, choose an option: \r\n";
	std::string menuMessage2 = "1. Rent a book, search by title and rent it: \r\n";
	std::string menuMessage3 = "2.Search a book by its title.\r\n";
	std::string menuMessage4 = "3.Delete your account.\r\n";
	std::string menuMessage5 = "4.List of rented books.\r\n";
	std::string menuMessage6 = "5.Log out.\n\r";

	send(clientSocket, menuMessage1.c_str(), menuMessage1.size() + 1, 0);
	send(clientSocket, menuMessage2.c_str(), menuMessage2.size() + 1, 0);
	send(clientSocket, menuMessage3.c_str(), menuMessage3.size() + 1, 0);
	send(clientSocket, menuMessage4.c_str(), menuMessage4.size() + 1, 0);
	send(clientSocket, menuMessage5.c_str(), menuMessage5.size() + 1, 0);
	send(clientSocket, menuMessage6.c_str(), menuMessage6.size() + 1, 0);

	ZeroMemory(buf, 4096);
	int bytesIn = recv(clientSocket, buf1, 4096, 0);
	int bytesIn1 = recv(clientSocket, aux3, 4096, 0);

	//check if client still send data to server, if not, close it and accept a new one
	if (bytesIn1 <= 0)
	{
		std::cout << "\n clientul nu mai trimite informatii, s-a deconectat subit";	
		return;
	}
	else
	{
		s << aux3;
		if (s.str() == "1")
			RentBook(clientSocket, db);
		if (s.str() == "2")
			Search(clientSocket, db);
		if (s.str() == "3")
			DeleteAccount(clientSocket, db);
		if (s.str() == "4")
			RentedBooks(clientSocket, db);
		if (s.str() == "5")
		{
			LogOut(clientSocket, db);
			return;
		}
		else {
			send(clientSocket, "Optiune invalida\n", 18, 0);
			BigMenu(clientSocket, db);
		}
		return;
	}
}

void ServerMenu::Search(SOCKET clientSocket, sqlite3* db)
{
	//server message
	std::cout << "\nclientul a accesat functia de cautare a unei cartii.#"<<clientSocket<<"\n";
	char* err;
	sqlite3_stmt* stmt;
	sqlite3_stmt* stmt1;
	sqlite3_stmt* stmt2;
	char buf1[4096] = "1";
	std::ostringstream s, idStream;
	std::string message1 = "type the title of the book: ";
	std::string searchQuery = "select id from books where title = '";
	send(clientSocket, message1.c_str(), message1.size() + 1, 0);
	ZeroMemory(buf, 4096);
	int bytesIn = recv(clientSocket, buf, 4096, 0);
	int aux = recv(clientSocket, buf1, 4096, 0);
	s << buf1;
	searchQuery = searchQuery + s.str() + "'";
	int rc;
	sqlite3_prepare_v2(db, searchQuery.c_str(), -1, &stmt, 0);
	const unsigned char* myname;
	sqlite3_step(stmt);
	myname = sqlite3_column_text(stmt, 0);
	if (myname == NULL)
	{
		//print error message in server console
		std::cout << "nu s-au gasit rezultate in baza de date la cautarea facuta";
		send(clientSocket, "\nnu am gasit rezultate\n", 24, 0);
		return;
	}
	else
	{
		std::cout << myname;
		idStream << myname;
		std::string contentBook = "Continutul cartii este: ";
		contentBook = contentBook + idStream.str() + "\n\r";
		send(clientSocket, contentBook.c_str(), contentBook.size() + 1, 0);
		std::string numberOfAvailableBooks = "Numarul de carti disponibile este: ";
		std::string queryForNumberOfBooks = "select books_count from books where id = '";
		queryForNumberOfBooks = queryForNumberOfBooks + idStream.str() + "'";
		sqlite3_prepare_v2(db, queryForNumberOfBooks.c_str(), -1, &stmt1, 0);
		const unsigned char* aux1;
		sqlite3_step(stmt1);
		aux1 = sqlite3_column_text(stmt1, 0);
		std::ostringstream numberOfBooks;
		numberOfBooks << aux1;
		numberOfAvailableBooks = numberOfAvailableBooks + numberOfBooks.str() + "\n\r";

		send(clientSocket, numberOfAvailableBooks.c_str(), numberOfAvailableBooks.size(), 0);
		std::string rentbook = "Doresti sa imprumuti cartea aceasta ? (y or n)  \n\r";
		send(clientSocket, rentbook.c_str(), rentbook.size(), 0);
		ZeroMemory(buf, 4096);

		if (CheckBookAppearances(clientSocket, db, s.str()) == 1)
		{
			std::ostringstream yesorno, aux2, aux4;
			int bytes = recv(clientSocket, buf, 4096, 0);
			ZeroMemory(buf, 4096);
			bytes = recv(clientSocket, buf, 4096, 0);
			yesorno << buf;
			int numberOfBooksInt;
			std::string query_updateBooksNumber = "Update books set books_count = '";
			if (yesorno.str() == "y")
			{
				std::cout << username << "#";
				std::string query2 = "select books_number from users where user = '";
				query2 = query2 + username + "'";
				sqlite3_prepare_v2(db, query2.c_str(), -1, &stmt2, 0);
				const unsigned char* aux3;
				sqlite3_step(stmt2);
				aux3 = sqlite3_column_text(stmt2, 0);
				aux4 << aux3;
				int element = std::stoi(aux4.str());

				if (element < 5)
				{
					element++;
					numberOfBooksInt = std::stoi(numberOfBooks.str());
					numberOfBooksInt--;

					aux2 << numberOfBooksInt;
					query_updateBooksNumber = query_updateBooksNumber + aux2.str() + "'" + "where id = '" + idStream.str() + "'";

					rc = sqlite3_exec(db, query_updateBooksNumber.c_str(), NULL, NULL, &err);
					if (rc != SQLITE_OK) {
						std::cout << "error: " << err;
					}

					//10924890124
					std::string query3 = "select max(id) from rent_books";
					std::ostringstream id1Stream;
					sqlite3_prepare_v2(db, query3.c_str(), -1, &stmt1, 0);
					const unsigned char* vef3;
					while (sqlite3_step(stmt1) != SQLITE_DONE)
					{
						vef3 = sqlite3_column_text(stmt1, 0);
						id1Stream << vef3;
					}
					int idInt = std::stoi(id1Stream.str());
					idInt++;
					std::ostringstream idStream2;
					idStream2 << idInt;

					//insert into user table and borrowed books table what book the client want
					std::string query1 = "insert into rent_books(id,id_book, return_date, user_name) values( '";
					query1 = query1 + idStream2.str() + "','" + idStream.str() + "', 14 , '" + username + "')";
					char* err1;
					rc = sqlite3_exec(db, query1.c_str(), NULL, NULL, &err1);
					if (rc != SQLITE_OK) {
						std::cout << "error: " << err1;
					}
					std::ostringstream aux5;
					aux5 << element;
					query_updateBooksNumber = "update users set books_number = '";
					query_updateBooksNumber = query_updateBooksNumber + aux5.str() + "' where user = '" + username + "'";
					rc = sqlite3_exec(db, query_updateBooksNumber.c_str(), NULL, NULL, &err);
					if (rc != SQLITE_OK) {
						std::cout << "error: " << err;
					}
				}
				else
				{
					send(clientSocket, "A fost atins numarul maxim de carti ce pot fi imprumutate\n\r", 60, 0);
				}
			}

		}
		else {
			send(clientSocket, "Aceasta carte este imprumatata de dvs.\n\r", 41, 0);
		}
		BigMenu(clientSocket, db);
	}
}

void ServerMenu::DeleteAccount(SOCKET clientSocket, sqlite3* db)
{
	//server message
	std::cout << "\nclientul a accesat optiune de stergere a contului #" << clientSocket << "\n";
	char* err;
	char buf1[4096];
	std::ostringstream s;
	std::string message = "Are you sure? (y/n)";
	send(clientSocket, message.c_str(), message.size() + 1, 0);
	ZeroMemory(buf1, 4096);
	int bytesIn = recv(clientSocket, buf, 4096, 0);
	bytesIn = recv(clientSocket, buf1, 4096, 0);
	s << buf1;
	std::cout << "  " << s.str();
	if (s.str() == "y" || s.str()==" y")
	{
		std::cout << "#" << username << "#";
		send(clientSocket, "deleted\n\r", 9, 0);
		std::string queryForDeleteAccount = "Delete from users where user = '";
		queryForDeleteAccount = queryForDeleteAccount + username + "'";
		int rc = sqlite3_exec(db, queryForDeleteAccount.c_str(), NULL, NULL, &err);
		if (rc != SQLITE_OK) {
			std::cout << "error: " << err;
		}

		//server message
		std::cout << "\nclientul si-a sters contul#" << clientSocket << "\n";
	}
	else
	{
		send(clientSocket, "not deleted\n\r", 13, 0);

		//server message
		std::cout << "\nclientul NU si-a sters contul#" << clientSocket << "\n";
	}
	LogOut(clientSocket, db);
}

void ServerMenu::setUsername(std::string m_username)
{
	username = m_username;
}

void ServerMenu::setPassword(std::string m_password)
{
	password = m_password;
}

void ServerMenu::LogOut(SOCKET clientSocket, sqlite3* db)
{
	//server message
	std::cout<<"\n clientul a accesat optiunea de deconectare #" << clientSocket << "\n";
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	fd_set master;
	FD_ZERO(&master);

	closesocket(clientSocket);
	FD_CLR(clientSocket, &master);
}

void ServerMenu::RentBook(SOCKET clientSocket, sqlite3* db)
{
	//server message
	std::cout<<"\nclientul doreste sa imprumute o carte#" << clientSocket << "\n"; 

	Search(clientSocket, db);
}

void ServerMenu::RentedBooks(SOCKET clientSocket, sqlite3* db)
{
	//server message
	std::cout << "\n clientul doreste sa si vada lista de carti imprumutate #" << clientSocket << "\n";

	char* err;
	sqlite3_stmt* stmt;
	std::vector<std::string>booksIdList;

	//number of borrowed books by a client
	std::ostringstream stream1;
	std::string queryNumberOfBooks = "select books_number from users where user = '";
	queryNumberOfBooks = queryNumberOfBooks + username + "'";

	sqlite3_prepare_v2(db, queryNumberOfBooks.c_str(), -1, &stmt, 0);
	const unsigned char* data1;
	sqlite3_step(stmt);
	data1 = sqlite3_column_text(stmt, 0);
	stream1 << data1;

	//find the borrowe books by the client

	std::string queryRentBooks = "select id_book from rent_books where user_name= '";
	queryRentBooks = queryRentBooks + username + "'";

	//search in table of borrowed books
	int index = 0, numberOfRentedBooks = std::stoi(stream1.str());
	int indexWhile = 0;
	while (indexWhile < numberOfRentedBooks)
	{
		if (index > 5)
		{
			//server message
			std::cout << "\n ERROR - functia nu se mai opreste, a aparut o problema, se revine la meniu";
			send(clientSocket, "A aparut o problema, se revine la meniu, daca aceasta persista, incearca restart ul aplicatiei\n\r", 97, 0);
			return;
		}
		std::string stringAux;
		std::ostringstream stream4, streamTest, stream5, stream6, stream7, stream8, stream9;
		streamTest << "NULL";
		index++;
		stream4 << index;

		//luam din tabelul de carti inchiriate toate inregistrarile(pe rand) ce contin numele utilizatorului
		std::string querySearchBooks = "select user_name from rent_books where id = '";
		querySearchBooks = querySearchBooks + stream4.str() + "'";
		sqlite3_prepare_v2(db, querySearchBooks.c_str(), -1, &stmt, 0);
		const unsigned char* data3;
		sqlite3_step(stmt);
		data3 = sqlite3_column_text(stmt, 0);
		if (data3 != NULL)
		{
			stream5 << data3;
			if (stream5.str() == username)
			{
				//luam id ul cartii  din tabelul de carti imprumutate, pentru a cauta in tabelul cu toate cartile bibliotecii
				std::string queryAux = "select id_book from rent_books where id = '";
				queryAux = queryAux + stream4.str() + "'";
				sqlite3_prepare_v2(db, queryAux.c_str(), -1, &stmt, 0);
				const unsigned char* data4;
				sqlite3_step(stmt);
				data4 = sqlite3_column_text(stmt, 0);
				stream6 << data4;
				booksIdList.push_back(stream6.str());

				//luam titlul cartii din tabelul mare de carti
				std::string queryBookName = "select title from  books where id = '";
				queryBookName = queryBookName + stream6.str() + "'";
				sqlite3_prepare_v2(db, queryBookName.c_str(), -1, &stmt, 0);
				const unsigned char* data5;
				sqlite3_step(stmt);
				data5 = sqlite3_column_text(stmt, 0);
				stream7 << data5;
				stringAux = std::to_string(indexWhile + 1) + ". " + stream7.str();
				//termenul de returnare al cartii
				std::string queryReturnABook = "select number_of_extensios from rent_books where id = ";
				queryReturnABook = queryRentBooks + stream4.str() + "'";
				sqlite3_prepare_v2(db, queryAux.c_str(), -1, &stmt, 0);
				const unsigned char* data6;
				sqlite3_step(stmt);
				data6 = sqlite3_column_text(stmt, 0);
				stream8 << data6;

				//afisam clientului cartile ce le are imprumutate
				send(clientSocket, stringAux.c_str(), stringAux.size(), 0);
				send(clientSocket, "\n\r", 3, 0);
				std::string ReturnDateMessage = "Mai sunt ";
				ReturnDateMessage = ReturnDateMessage + stream8.str() + " zile pana cartea trebuie returnata. ";
				send(clientSocket, ReturnDateMessage.c_str(), ReturnDateMessage.size(), 0);
				send(clientSocket, "\n\r", 3, 0);
				send(clientSocket, "\n\r", 3, 0);
				indexWhile++;

			}
		}
	}

	//server menu
	std::cout << "\nclientul a accesat meniul de optiuni pentru o carte\n";
	if (numberOfRentedBooks >= 1)
	{
		BookMenu(clientSocket, db, booksIdList);
	}
	else
	{
		send(clientSocket, "Dvs nu aveti carti imprumutate inca \n\r", 40, 0);
		BigMenu(clientSocket, db);
	}
}

void ServerMenu::BookMenu(SOCKET clientSocket, sqlite3* db, std::vector<std::string>booksList)
{
	char buf[4096];
	char buf1[4096];
	std::ostringstream stream1, stream0;
	std::string bookId;
	//afisam optiunile
	std::string option0 = "Alegeti una dintre carti pentru a efectua o actiune: ",
		option1 = "1. Doriti prelungirea termenului acestei carti ? ",
		option2 = "2. Doriti sa returnati aceasta carte? ",
		option3 = "3. Doriti sa cititi aceasta carte? ";
	send(clientSocket, option0.c_str(), option0.size(), 0);
	ZeroMemory(buf, 4096);
	int bytesIn2 = recv(clientSocket, buf, 4096, 0);
	int bytesIn3 = recv(clientSocket, buf1, 4096, 0);
	std::cout << "#\n" << bytesIn3;
	if (bytesIn3 <= 0)
	{
		std::cout << "Clientul a parasit conexiunea";
	}
	else
	{
		stream0 << buf1;
		std::stringstream aux(stream0.str());
		int auxInt;
		aux >> auxInt;

		bookId = booksList[auxInt - 1];
		std::cout << "@" << bookId << "@";

		send(clientSocket, "\n\r", 3, 0);
		send(clientSocket, option1.c_str(), option1.size(), 0);
		send(clientSocket, "\n\r", 3, 0);
		send(clientSocket, option2.c_str(), option1.size(), 0);
		send(clientSocket, "\n\r", 3, 0);
		send(clientSocket, option3.c_str(), option1.size(), 0);
		send(clientSocket, "\n\r", 3, 0);



		//luam optiunea aleasa de client
		ZeroMemory(buf1, 4096);
		ZeroMemory(buf, 4096);
		int bytesIn = recv(clientSocket, buf, 4096, 0);
		int bytesIn1 = recv(clientSocket, buf1, 4096, 0);
		stream1 << buf1;


		if (stream1.str() == "1")
			DeadlineExtension(clientSocket, db, bookId);
		if (stream1.str() == "2")
			ReturnABook(clientSocket, db, bookId);
		if (stream1.str() == "3")
			//apelam functie de afisat continut carte
			1 + 1;
	}
}

void ServerMenu::DeadlineExtension(SOCKET clientSocket, sqlite3* db, std::string book)
{
	//server message
	std::cout<<"\n clientul doreste sa extinda termenul unei carti#" << clientSocket << "\n";
	char* err;
	sqlite3_stmt* stmt;
	char buf[4096];
	char buf1[4096];
	std::ostringstream stream1, stream0;
	std::string newDeadline;
	//mesaje de afisat
	std::string message1 = "Cu cate zile doriti prelungirea termenului de returnare(maxim 10 zile per prelungire, maxim 2 prelungiri): ",
		spaceMessage = "\n\r",
		confirmMessage = "Termenul a fost prelungit.",
		rejectionMessage = "A fost atinsul numarul maxim de prelungiri, ne pare rau";
	//luam din baza de date termenul de returnare ramas pt ca ulterior sa facem suma
	std::string queryUpdate1 = "select return_date from rent_books where id_book= '";
	queryUpdate1 = queryUpdate1 + book + "'";
	sqlite3_prepare_v2(db, queryUpdate1.c_str(), -1, &stmt, 0);
	const unsigned char* vef1;
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		vef1 = sqlite3_column_text(stmt, 0);
		stream0 << vef1;
	}

	//luam informatii de la client;
	send(clientSocket, message1.c_str(), message1.size(), 0);
	int bytesIn = recv(clientSocket, buf, 4096, 0);
	int bytesIn1 = recv(clientSocket, buf1, 4096, 0);
	stream1 << buf1;
	std::cout << "in" << stream1.str();

	int aux1, aux2;
	std::stringstream stringToInt1(stream0.str());
	std::stringstream stringToInt2(stream1.str());
	stringToInt1 >> aux1;
	stringToInt2 >> aux2;
	std::cout << aux1 << "@" << aux2;

	aux1 = aux1 + aux2;
	std::string finalNumber = std::to_string(aux1);
	std::cout << finalNumber;
	std::string queryUpdate2 = "update rent_books set return_date= '";
	queryUpdate2 = queryUpdate2 + finalNumber + "'";
	std::string add = "where id_book = '";
	add = add + book + "';";
	queryUpdate2 = queryUpdate2 + add;

	int rc = sqlite3_exec(db, queryUpdate2.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		std::cout << "error: " << err;
	}
	BigMenu(clientSocket, db);

}

void ServerMenu::ReturnABook(SOCKET clientSocket, sqlite3* db, std::string book)
{
	//server message
	std::cout<<"\n clientul doreste sa returneze o carte#" << clientSocket << "\n";
	char* err;
	sqlite3_stmt* stmt;
	std::ostringstream stream1, stream0;
	//query pentru a sterge inregistrare din tabelul de carti imprumutate
	std::string queryDeleteFromRentBooks = "delete from rent_books where id_book = '";
	queryDeleteFromRentBooks = queryDeleteFromRentBooks + book + "'";

	//stergem inregistrarea
	int rc = sqlite3_exec(db, queryDeleteFromRentBooks.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		std::cout << "error: " << err;
	}

	//query pentru a lua numarul de carti ramase de un anumit tip din tabelul de carti al bibliotecii
	std::string queryNumberOfBooks = "select books_count from books where id= '";
	queryNumberOfBooks = queryNumberOfBooks + book + "'";
	sqlite3_prepare_v2(db, queryNumberOfBooks.c_str(), -1, &stmt, 0);
	const unsigned char* vef1;
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		vef1 = sqlite3_column_text(stmt, 0);
		stream0 << vef1;
	}
	int oldNumber;
	std::stringstream stringStream1(stream0.str());
	stringStream1 >> oldNumber;
	oldNumber++;
	std::string finalString = std::to_string(oldNumber);

	//query pentru a modifica numarul de carti din biblioteca
	std::string queryUpdateBook = "update books set books_count = '";
	queryUpdateBook = queryUpdateBook + finalString + "'";

	int rc1 = sqlite3_exec(db, queryUpdateBook.c_str(), NULL, NULL, &err);
	if (rc1 != SQLITE_OK) {
		std::cout << "error: " << err;
	}
	BigMenu(clientSocket, db);
}

bool ServerMenu::CheckBookAppearances(SOCKET clientSocket, sqlite3* db, std::string book)
{
	//return 0-doesnt exist, return 1 - exist
	std::string auxString = "exist";
	sqlite3_stmt* stmt;
	std::ostringstream stream0;
	std::string query1 = "if exists(select * from rent_books where id_book = '";
	query1 = query1 + book + "' and user_name = '" + username + "') select id_book  from rent_books where user_name = '" + username + " ' "
		+ " else  select id_book from rent_books where user_name = '0'";
	std::cout << "\n" << query1 << "\n";
	sqlite3_prepare_v2(db, query1.c_str(), -1, &stmt, 0);
	const unsigned char* vef1;
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		if (sqlite3_column_text(stmt, 0) != NULL)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}