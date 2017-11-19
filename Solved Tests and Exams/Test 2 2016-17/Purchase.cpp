/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	// Create the article
	Article* article = new Article(client,barCode);

	// Set the required Attributes
	article->setPresent(present);
	article->setDeliverHome(deliverHome);

	// Return it
	return article;
}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
	// If the bag isn't full, add it to the last bag!
	if (bags.back().size() < BAG_SIZE)
		bags.back().push(article);

	// If it's full, add a new bag!
	else{
		stack<Article*> newBag;
		newBag.push(article);
		bags.push_back(newBag);
	}
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;
	list< stack<Article*> >::iterator it;
	stack<Article*> tempBag;

	// Iterate though the bags
	for (it=bags.begin() ; it!=bags.end() ; it++){
		stack<Article*> & bag = (*it);

		// Iterate though the bag to find presents
		while (!bag.empty()){
			if (bag.top()->getPresent() == true)	// Present found!
				presents.push_back(bag.top());
			else
				tempBag.push(bag.top());	// Not a present ; goes to the temporary bag
			bag.pop();	// remove it from the bag
		}

		// Reset the bag with the non-presents
		while (!tempBag.empty()){
			bag.push(tempBag.top());
			tempBag.pop();
		}
	}


	return presents;
}

