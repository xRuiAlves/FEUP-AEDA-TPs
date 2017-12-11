/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) const{
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
	BookCatalogItem notFound("", "", 0);

	for (unsigned int i=0 ; i<books.size() ; i++){
		BookCatalogItem newItem(books.at(i)->getTitle() , books.at(i)->getAuthor() , books.at(i)->getYear());
		BookCatalogItem findAttempt = catalogItems.find(newItem);

		if(findAttempt == notFound){
			newItem.addItems(books.at(i));
			catalogItems.insert(newItem);
		}
		else{
			 catalogItems.remove(findAttempt);
			 findAttempt.addItems(books.at(i));
			 catalogItems.insert(findAttempt);
		}
	}
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	vector<Book*> aux;

	BookCatalogItem notFound("", "", 0);
	BookCatalogItem toFind(book->getTitle() , book->getAuthor() , 0);
	BookCatalogItem findAttempt = catalogItems.find(toFind);


	if (!(findAttempt == notFound)){
		aux = findAttempt.getItems();

		for(unsigned int i=0 ; i<aux.size() ; i++){
			if (aux.at(i)->getReader() == NULL){
				temp.push_back(aux.at(i));
			}
		}
	}


	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	if(book->getReader() != NULL)
		return false;

	BookCatalogItem notFound("", "", 0);
	BookCatalogItem toFind(book->getTitle() , book->getAuthor() , book->getYear());
	BookCatalogItem findAttempt = catalogItems.find(toFind);

	if (findAttempt == notFound)
		return false;


	vector<Book*> temp = findAttempt.getItems();

	for(unsigned int i=0 ; i<books.size() ; i++){
		if(books.at(i)->getReader() == NULL && books.at(i)->getYear() == book->getYear()){
			reader->addReading(books.at(i)->getTitle() , books.at(i)->getAuthor());
			books.at(i)->setReader(reader);
			book->setReader(reader);
			return true;
		}
	}

	// Didn't find one!
	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(UserRecord(user));
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	// See if the user is in the table
	auto it = userRecords.find(UserRecord(user));

	if( it == userRecords.end())	// He isn't
		return;

	// He is : Remove it ...
	userRecords.erase(it);

	// ... change it ...
	user->setEMail(newEMail);

	// ... and re-add it!
	userRecords.insert(UserRecord(user));
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	// Add them to the heap!
	for (unsigned int i=0 ; i<candidates.size() ; i++){
		if(candidates.at(i).numReadings() >= min){
			readerCandidates.push(candidates.at(i));
		}
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
	if(readerCandidates.empty())
		return 0;

	champion = readerCandidates.top();
	readerCandidates.pop();


	// Check if he is the absolute champion or not
	if(readerCandidates.top().numReadings() >= champion.numReadings()){
		champion = User("","");
		return 0;
	}
	else{
		return (readerCandidates.size() + 1);
	}
}
























