/*
 * Dish.h
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#ifndef DISH_H_
#define DISH_H_

#include <string>

enum TypeOfDish {Plate, Dessert, Bowl};

class Dish {
	const std::string collection;
	const TypeOfDish type;
public:
	Dish(std::string c, TypeOfDish t);
	std::string getCollection() const;
	TypeOfDish getType() const;
	bool operator ==(const Dish& d) const;
};

#endif /* DISH_H_ */
