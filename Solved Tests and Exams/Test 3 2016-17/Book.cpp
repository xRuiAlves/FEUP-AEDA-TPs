/*
 * Book.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "Book.h"

Book::Book(string title, string author, unsigned year):
	title(title), author(author), year(year) {
	reader = NULL;
}

string Book::getTitle() const {
	return this->title;
}

string Book::getAuthor() const {
	return this->author;
}

unsigned Book::getYear() const {
	return this->year;
}

User* Book::getReader() const {
	return this->reader;
}

void Book::setReader(User* reader) {
	this->reader = reader;
}


BookCatalogItem::BookCatalogItem(string title, string author, unsigned year) {
	this->title = title;
	this->author = author;
}

string BookCatalogItem::getTitle() const {
	return this->title;
}

string BookCatalogItem::getAuthor() const {
	return this->author;
}

vector<Book*> BookCatalogItem::getItems() const {
	return this->items;
}

void BookCatalogItem::setItems(vector<Book*> books) {
	items = books;
}

void BookCatalogItem::addItems(Book* book) {
	this->items.push_back(book);
}

//
// TODO:
//

bool BookCatalogItem::operator<(const BookCatalogItem &bci1) const {
	if(title == bci1.title){
		return (author < bci1.author);
	}
	else
		return (title < bci1.title);
}

bool BookCatalogItem::operator==(const BookCatalogItem &bci1) const {
	return ((author == bci1.author) && (title == bci1.title));
}
