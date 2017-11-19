/*
 * Restaurant.h
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <stack>
#include <queue>
#include <list>
#include "Table.h"
#include "Dish.h"

/**
 * A Restaurant has:
 * - tables
 * - clean dish stacks for different collections/types of dishes, some of which may become empty
 * - a queue of dirty dishes
 * - a list of drying dishes
 */
class Restaurant {
	std::vector<Table> tables;
	std::vector< std::stack<Dish*> > clean;
	std::queue<Dish*> dirty;
	std::list<Dish*> drying;
public:
	Restaurant();
	Restaurant(std::vector< std::stack<Dish*> >* cl, std::queue<Dish*>* di, std::list<Dish*>* dr);
	void addTable(unsigned int n_places);
	void addTable(Table& t);
	const Table& getTable(std::vector<Table>::size_type idx) const;
	std::stack<Dish*>& getCleanDishStack(std::string collection, TypeOfDish type);
	const std::queue<Dish*>& getDirty() const;
	const std::list<Dish*>& getDrying() const;

	//--- TO IMPLEMENT
	// a)
	void addDishes(unsigned int n, std::string collection, TypeOfDish type);
	// b)
	Dish* washDish();
	// c)
	void clearTable(std::vector<Table>::size_type idx);
	// d)
	void storeDryDishes(std::string collection, TypeOfDish type);
	// e)
	void setupTable(std::vector<Table>::size_type idx, std::string collection);
	// f)
	std::list<Dish*> pickupAndGroupDryDishes();
	// g)
	int storeGroupedDishes(std::list<Dish*> grouped_dishes);
	//---

	class NotEnoughDishesException {
	public:
		NotEnoughDishesException() {}
	};

	class TableNotReadyException {
	public:
		TableNotReadyException() {}
	};
};

#endif /* RESTAURANT_H_ */
