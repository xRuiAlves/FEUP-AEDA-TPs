/*
 * User.h
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#ifndef SRC_USER_H_
#define SRC_USER_H_

#include <string>
#include <vector>
#include <utility>

using namespace std;

class UserRecord;

class User {
	string name;
	string eMail;
	pair<string, string> titleReading;
	vector<pair<string, string> > titlesRead;
public:
	friend class UserRecord;
	User(string name, string eMail);
	string getName() const;
	string getEMail() const;
	void setEMail(string eMail);
	void addReading(string title, string author);
	void endReading();
	pair<string, string> getReading() const;
	vector<pair<string, string> > getReadings() const;
	int numReadings() const;
	//TODO:
	bool operator<(const User& u1) const;
};

class UserRecord {
	User* userPtr;
public:
	UserRecord(User* user);
	string getName() const;
	string getEMail() const;
	void setEMail(string eMail);
};

#endif /* SRC_USER_H_ */
