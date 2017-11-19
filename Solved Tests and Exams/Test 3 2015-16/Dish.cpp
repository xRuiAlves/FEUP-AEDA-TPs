/*
 * Dish.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Dish.h"

using namespace std;

Dish::Dish(string c, TypeOfDish t): collection(c), type(t) { }

string Dish::getCollection() const {
	return collection;
}

TypeOfDish Dish::getType() const {
	return type;
}

bool Dish::operator ==(const Dish& d) const {
	return collection == d.collection && type == d.type;
}
