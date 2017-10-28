/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>


PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){
	vector<Mail*> mail;

	for (unsigned int i=0 ; i<postmen.size() ; i++){
		if ( postmen.at(i).getName() == name ){		// Found him/her !
			mail = postmen.at(i).getMail();
			postmen.erase(postmen.begin() + i);
		}
	}

	return mail;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance){
	unsigned int balanceCounter = 0;

	// Count the balance
	for (unsigned int i=0 ; i<mailToSend.size() ; i++){
		balanceCounter += mailToSend.at(i)->getPrice();
	}

	// Get the balance value into balance variable
	balance = balanceCounter;

	// Deal with mail to send
	string zip;
	vector<Mail*> mail;

	while (mailToSend.size() != 0){
		zip = mailToSend.at(0)->getZipCode();

		// Check if it's within the limits
		if ((zip >= firstZipCode) && (zip <= lastZipCode))
			addMailToDeliver(mailToSend.at(0));
		else	// not within limits
			mail.push_back(mailToSend.at(0));

		// Remove it from mailToSend
		mailToSend.erase(mailToSend.begin());
	}

	return mail;
}

Postman PostOffice::addMailToPostman(Mail *m, string name){
	for (unsigned int i=0 ; i<postmen.size() ; i++){
		if (postmen.at(i).getName() == name){	// Found him/her !
			postmen.at(i).addMail(m);			// Add the mail
			return postmen.at(i);				// Return the postman
		}
	}

	// searched in all the vector and postman wasn't found, throw exception
	throw (NoPostmanException(name));
}
