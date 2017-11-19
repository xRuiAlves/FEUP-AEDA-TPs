/*
 * Table.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Table.h"

using namespace std;

Table::Table(unsigned int n) {
	for(unsigned int i=0; i<n; i++) {
		places.push_back(stack<Dish*>());
	}
}

/**
 * Gets the number of places in this table.
 */
unsigned int Table::size() const {
	return places.size();
}

/**
 * Checks if this table is empty: all places should be empty.
 */
bool Table::empty() const {
	for(vector< stack<Dish*> >::const_iterator it = places.begin(); it != places.end(); ++it) {
		if(!(*it).empty()) {
			return false;
		}
	}

	return true;
}

/**
 * Gets the collection of the dishes on this table, if any.
 */
string Table::getCollection() const {

	if(!places[0].empty()) {
		return places[0].top()->getCollection();
	} else {
		return "";
	}
}

/**
 * Gets the places in this table.
 */
const vector< stack<Dish*> >& Table::getPlaces() const {
	return places;
}

/**
 * Puts dishes on this table, one in each place.
 * Throws WrongNumberOfDishesException if the number of dishes differs from the number of places in this table.
 * Throws WrongCollectionException if there are dishes of a different collection on this table.
 */
void Table::putOn(vector<Dish*> dishes) {
	if(dishes.size() != size()) {
		throw WrongNumberOfDishesException();
	}

	string c = getCollection();
	if(c != "" && c != dishes[0]->getCollection()) {
		throw WrongCollectionException();
	}

	vector<Dish*>::size_type i = 0;
	for(vector< stack<Dish*> >::iterator it = places.begin();
			it != places.end(); ++it) {
		(*it).push(dishes[i++]);
	}
}

/**
 * Clears this table, by picking up all dishes on every place.
 * Returns the picked up dishes.
 */
vector<Dish*> Table::clear() {
	vector<Dish*> dishes;

	for (unsigned int i=0 ; i<places.size() ; i++){		// Clear all the dishes from all the places
		while (!places.at(i).empty()){
			dishes.push_back(places.at(i).top());
			places.at(i).pop();	// Remove it from that place in the table
		}
	}

	return dishes;
}

