/*
 * Book.h
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#ifndef SRC_BOOK_H_
#define SRC_BOOK_H_

#include "User.h"
#include <string>
using namespace std;

class Book {
	const string title;
	const string author;
	const unsigned year;
	User* reader;
public:
	Book(string title, string author, unsigned year);
	string getTitle() const;
	string getAuthor() const;
	unsigned getYear() const;
	User* getReader() const;
	void setReader(User* reader);

};

class BookCatalogItem {
	string title;
	string author;
	vector<Book*> items;
public:
	BookCatalogItem(string title, string author, unsigned year);
	string getTitle() const;
	string getAuthor() const;
	vector<Book*> getItems() const;
	void setItems(vector<Book*> books);
	void addItems(Book* book);
	//TODO:
    bool operator<(const BookCatalogItem &bci1) const;
    bool operator==(const BookCatalogItem &bci1) const;
};


#endif /* SRC_BOOK_H_ */
