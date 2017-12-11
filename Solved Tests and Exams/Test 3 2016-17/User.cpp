/*
 * User.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "User.h"

User::User(string name, string eMail) {
	this->name = name;
	this->eMail = eMail;
}

string User::getName() const {
	return this->name;
}

string User::getEMail() const {
	return this->eMail;
}

void User::setEMail(string eMail) {
	this->eMail = eMail;
}

void User::addReading(string title, string author) {
	if(this->titleReading.first == "" && this->titleReading.second == "") {
		this->titleReading = make_pair(title, author);
	}
	else {
		this->titlesRead.push_back(this->titleReading);
		this->titleReading = make_pair(title, author);
	}
}

void User::endReading() {
	if(titleReading.first != "" && titleReading.second != "") {
		titlesRead.push_back(make_pair(titleReading.first, titleReading.second));
	}
}

pair<string, string>  User::getReading() const {
	return this->titleReading;
}

vector<pair<string, string> > User::getReadings() const {
	return this->titlesRead;
}

int User::numReadings() const {
	int num = 0;
	if(this->titleReading.first != "" && this->titleReading.second != "") num++;
	return this->titlesRead.size() + num;
}

//
// TODO:
//
bool User::operator<(const User& u1) const {
	return (this->numReadings() < u1.numReadings());
}

UserRecord::UserRecord(User* user) {
	this->userPtr = user;
}

string UserRecord::getName() const {
	return this->userPtr->name;
}

string UserRecord::getEMail() const {
	return this->userPtr->eMail;
}

void UserRecord::setEMail(string eMail) {
	this->userPtr->eMail = eMail;
}



