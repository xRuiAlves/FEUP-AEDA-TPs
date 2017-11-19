/*
 * Table.h
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include <stack>
#include "Dish.h"

/**
 * A Table has a number of places, and each place has a stack of dishes.
 */
class Table {
	std::vector< std::stack<Dish*> > places;
public:
	Table(unsigned int n);
	unsigned int size() const;
	bool empty() const;
	std::string getCollection() const;
	const std::vector< std::stack<Dish*> >& getPlaces() const;
	void putOn(std::vector<Dish*> dishes);

	//--- TO IMPLEMENT
	// c)
	std::vector<Dish*> clear();
	//---

	class WrongNumberOfDishesException {
	public:
		WrongNumberOfDishesException() {}
	};

	class WrongCollectionException {
	public:
		WrongCollectionException() {}
	};

};

#endif /* TABLE_H_ */
