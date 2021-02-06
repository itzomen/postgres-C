#include <iostream>
#include <fstream>

#include<ios> //used to get stream size
#include<limits> //used to get numeric limits

#include"db.h"

using namespace std;

int bookOptions() {
	cout << "1. Add Book"<< endl;
	cout << "2. Update Book"<< endl;
	cout << "3. Delete Book"<< endl;
	cout << "4. Show All Books"<< endl;
	cout << "0. Exit"<< endl;
	cout << "--- Choose any one option ---" << endl;
	cout << "Enter one option: ";

	int selectedOption = 0;
	cin >> selectedOption;
	cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 

	return selectedOption;
}


void addBook() {
	string bookTitle, bookAuthor, bookDetail, count;
	cout << "Enter Book ID: ";
	cin >> count;

	cout << endl << "--- Provide Book Details ---" << endl;
	cout << "Title: ";
	cin >> bookTitle;
	cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 
	cout << "Author: ";
	cin >> bookAuthor;
	cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 

	// open file for writing
	ofstream writeToLibrary;

    writeToLibrary.open("library.dat", ios::app);

	bookDetail = count + ", " + bookTitle + ", " + bookAuthor;
	// Save to Database
	SaveToDb(count, bookTitle, bookAuthor);

	// write
	writeToLibrary << bookDetail << endl;

	// close the opened file.
    writeToLibrary.close();
	
   	cout << "Book added: " << bookDetail << endl; 
}


void UpdateBook() {
	cout << endl << "--- Update Book ---" << endl;
	string id;
	string title, author;
	cout << "Enter Book ID: ";
	cin >> id;
	cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 

	bool bookExist = false;
	cout << endl << "--- Provide Book Details ---" << endl;
	cout << "New Title: ";
	getline(cin, title);
	cout << "New  Author: ";
	getline(cin, author);
	updateDb(to_string(id), title, author);

	cout << "Book Details Updated" << endl; 
}


void DeleteBook() {
	cout << endl << "--- Delete Book ---" << endl;
	string id;
	cout << "Enter Book ID: ";
	cin >> id;
	cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 
	Delete(to_string(id));
	
	cout << "Book Deleted" << endl; 
}


void showBooks() {
	cout << "--- List of books ---" << endl;
	showBook();
}


void bookActions(int option) {
	switch(option) {
		case 1: 
			addBook();
			break;
		case 2: 
			UpdateBook();
			break;
		case 3: 
			DeleteBook();
			break;
		case 4: 
			showBooks();
			break;
	}
}


void home () {
	int option = bookOptions();
	if (option != 0 && option <= 4) {
		bookActions(option);
	} else if (option > 4) {
		cout << endl << "!!! Enter Valid Option !!!" << endl;
		option = bookOptions();
	} else {
	 	exit(0);
	}
}


int main () {
	CreateTable ();
	cout << "*** WELCOME ***";
	string yn;
	while(true) {
		cout << endl << "--- Postgres Library Management System ---" << endl;
		home();
		cout << endl << "continue? (y/n) :";
		cin >> yn;
		if(yn != "y") break;
	}
	return 0;
}