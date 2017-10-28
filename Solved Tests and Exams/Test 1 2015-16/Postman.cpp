/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int Postman::numId = 1;

template <class T>
unsigned int numberDifferent (const vector<T> & v1){
	unsigned int counter = 0;
	bool foundRepetition;

	for (unsigned int i=0 ; i< v1.size() ; i++){
		foundRepetition = false;	// Reset the found repetition flag

		for (unsigned int j=i+1 ; j<v1.size() ; j++){
			if(v1.at(i) == v1.at(j)){	// found a repetition! Set the flag and break the loop
				foundRepetition = true;
				break;
			}
		}

		if(!foundRepetition)	// If no repetition was found, increment the counter
			counter++;
	}

	return counter;
}

Postman::Postman(): id(0) {}

Postman::Postman(string name){
	this->name = name;
	this->id = (numId++);
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman & p2) const{
	vector<string> zips1;
	vector<string> zips2;

	// Get zips1
	for (unsigned int i=0 ; i<myMail.size() ; i++){
		zips1.push_back(myMail.at(i)->getZipCode());
	}

	vector<Mail*> otherPostmanMail = p2.getMail();

	// Get zips2
	for(unsigned int i=0 ; i<otherPostmanMail.size() ; i++){
		zips2.push_back(otherPostmanMail.at(i)->getZipCode());
	}

	// Compare them and return result
	return (numberDifferent(zips1) < numberDifferent(zips2));
}

