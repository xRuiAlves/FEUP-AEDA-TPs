/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include <cmath>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

bool compareArticles(Article* a1, Article* a2){
	/* Get the 'Deliver Home' to the end */
	if (a1->getDeliverHome() && !a2->getDeliverHome())
		return false;
	else if(!a1->getDeliverHome() && a2->getDeliverHome())
		return true;
	/* -------------------------------- */
	else if(!a1->getDeliverHome() && !a2->getDeliverHome()){	// Both are to deliver now
		if (abs(a1->getPresentNumber() - a2->getPresentNumber()) > 2){	// They differ more than 2!
			return (a1->getPresentNumber() < a2->getPresentNumber());
		}
	}

	return false;
}

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {

	vector<Article*> clientPresents;

	// Iterate though the presents table
	for (unsigned int i=0 ; i<presentsTable.size() ; i++){
		if(presentsTable.at(i)->getClient() == client){	// Found one! Remove it from the table!
			clientPresents.push_back(presentsTable.at(i));
			presentsTable.erase(presentsTable.begin()+i);
			i--;	// Assert i
		}
	}

	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
void AfterSalesService::sortArticles() {

	sort(presentsTable.begin() , presentsTable.begin()+10 , compareArticles);

}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {

	// Get as many elements as possible to the 'to wrap' queue
	while ((toWrap.size() < toWrapQueueSize) && (!presentsTable.empty())) {
		toWrap.push(presentsTable.at(0));			// Push the first element in the table
		presentsTable.erase(presentsTable.begin());	// Erase the first element, which was added to the 'to wrap' queue
	}

}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {

	// Check if 'to Wrap' queue isn't empty
	if (toWrap.empty())
		return NULL;

	// Remove the wrapped article from the queue
	Article* wrappedArticle = toWrap.front();
	toWrap.pop();

	// Verify if it is to be delivered at home
	if (wrappedArticle->getDeliverHome()){
		toDeliver.push(wrappedArticle);
		return NULL;
	}
	else{
		return wrappedArticle;
	}
}

