#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "Restaurant.h"

using namespace std;

// Restaurant::addDishes()
void test_A_() {

	stack<Dish*> st1;
	st1.push(new Dish("Spring", Dessert));
	st1.push(new Dish("Spring", Dessert));
	st1.push(new Dish("Spring", Dessert));

	stack<Dish*> st2;
	st2.push(new Dish("Spring", Plate));
	st2.push(new Dish("Spring", Plate));

	stack<Dish*> st3;
	st3.push(new Dish("Asian", Plate));
	st3.push(new Dish("Asian", Plate));
	st3.push(new Dish("Asian", Plate));
	st3.push(new Dish("Asian", Plate));

	vector< stack<Dish*> > clean;
	clean.push_back(st1);
	clean.push_back(st2);
	clean.push_back(st3);

	Restaurant r(&clean, NULL, NULL);

	r.addDishes(10, "Spring", Plate);
	ASSERT_EQUAL(12, r.getCleanDishStack("Spring", Plate).size());

	r.addDishes(5, "Asian", Bowl);
	ASSERT_EQUAL(5, r.getCleanDishStack("Asian", Bowl).size());

	ASSERT_EQUAL(4, r.getCleanDishStack("Asian", Plate).size());

}

// Restaurant::washDish()
void test_B_() {

	Dish* d1 = new Dish("Asian", Plate);
	Dish* d2 = new Dish("White", Bowl);
	Dish* d3 = new Dish("Spring", Plate);
	Dish* d4 = new Dish("White", Dessert);

	queue<Dish*> dirty;
	dirty.push(d1);
	dirty.push(d2);
	dirty.push(d3);
	dirty.push(d4);

	Restaurant r(NULL, &dirty, NULL);

	ASSERT_EQUAL(true, r.washDish() == d1);
	ASSERT_EQUAL(true, r.getDirty().front() == d2);
	ASSERT_EQUAL(1, r.getDrying().size());
	list<Dish*> drying = r.getDrying();
	ASSERT_EQUAL(true, (find(drying.begin(), drying.end(), d1) != drying.end()));

	ASSERT_EQUAL(true, r.washDish() == d2);
	ASSERT_EQUAL(true, r.getDirty().front() == d3);
	ASSERT_EQUAL(2, r.getDrying().size());
	drying = r.getDrying();
	ASSERT_EQUAL(true, (find(drying.begin(), drying.end(), d2) != drying.end()));

	ASSERT_EQUAL(true, r.washDish() == d3);
	ASSERT_EQUAL(true, r.getDirty().front() == d4);
	ASSERT_EQUAL(3, r.getDrying().size());
	drying = r.getDrying();
	ASSERT_EQUAL(true, (find(drying.begin(), drying.end(), d3) != drying.end()));

}

// Restaurant::clearTable()
void test_C_() {
	Restaurant r;

	int table0_size = 5;
	r.addTable(table0_size);

	Table t1(4);
	vector<Dish*> dishes11;
	dishes11.push_back(new Dish("Spring", Plate));
	dishes11.push_back(new Dish("Spring", Plate));
	dishes11.push_back(new Dish("Spring", Plate));
	dishes11.push_back(new Dish("Spring", Plate));
	t1.putOn(dishes11);
	vector<Dish*> dishes12;
	dishes12.push_back(new Dish("Spring", Dessert));
	dishes12.push_back(new Dish("Spring", Dessert));
	dishes12.push_back(new Dish("Spring", Dessert));
	dishes12.push_back(new Dish("Spring", Dessert));
	t1.putOn(dishes12);
	r.addTable(t1);

	Table t2(3);
	vector<Dish*> dishes2;
	dishes2.push_back(new Dish("White", Dessert));
	dishes2.push_back(new Dish("White", Dessert));
	dishes2.push_back(new Dish("White", Dessert));
	t2.putOn(dishes2);
	r.addTable(t2);

	int n_dirty = r.getDirty().size();
	r.clearTable(0);
	Table t0_changed = r.getTable(0);
	ASSERT_EQUAL(true, t0_changed.empty());
	ASSERT_EQUAL(0, r.getDirty().size()-n_dirty);

	n_dirty = r.getDirty().size();
	r.clearTable(1);
	Table t1_changed = r.getTable(1);
	ASSERT_EQUAL(true, t1_changed.empty());
	ASSERT_EQUAL(8, r.getDirty().size()-n_dirty);

	n_dirty = r.getDirty().size();
	r.clearTable(2);
	Table t2_changed = r.getTable(2);
	ASSERT_EQUAL(true, t2_changed.empty());
	ASSERT_EQUAL(3, r.getDirty().size()-n_dirty);

	r.clearTable(3);

}

// Restaurant::storeDryDishes()
void test_D_() {

	stack<Dish*> st1;
	st1.push(new Dish("Spring", Dessert));
	st1.push(new Dish("Spring", Dessert));
	st1.push(new Dish("Spring", Dessert));

	stack<Dish*> st2;
	st2.push(new Dish("Spring", Plate));
	st2.push(new Dish("Spring", Plate));

	stack<Dish*> st3;
	st3.push(new Dish("Asian", Plate));
	st3.push(new Dish("Asian", Plate));
	st3.push(new Dish("Asian", Plate));

	vector< stack<Dish*> > clean;
	clean.push_back(st1);
	clean.push_back(st2);
	clean.push_back(st3);

	list<Dish*> drying;
	drying.push_back(new Dish("Asian", Plate));
	drying.push_back(new Dish("White", Bowl));
	drying.push_back(new Dish("Asian", Plate));
	drying.push_back(new Dish("Asian", Bowl));
	drying.push_back(new Dish("Spring", Plate));
	drying.push_back(new Dish("White", Dessert));

	Restaurant r(&clean, NULL, &drying);

	r.storeDryDishes("Asian", Plate);
	ASSERT_EQUAL(5, r.getCleanDishStack("Asian", Plate).size());

	r.storeDryDishes("White", Bowl);
	ASSERT_EQUAL(1, r.getCleanDishStack("White", Bowl).size());

	r.storeDryDishes("Asian", Plate);
	ASSERT_EQUAL(5, r.getCleanDishStack("Asian", Plate).size());

	r.storeDryDishes("White", Plate);
	ASSERT_EQUAL(0, r.getCleanDishStack("White", Plate).size());

	ASSERT_EQUAL(3, r.getCleanDishStack("Spring", Dessert).size());

}

// Restaurant::setupTable()
void test_E_() {

	stack<Dish*> st1;
	st1.push(new Dish("Asian", Plate));
	st1.push(new Dish("Asian", Plate));
	st1.push(new Dish("Asian", Plate));
	stack<Dish*> st2;
	st2.push(new Dish("Asian", Bowl));
	st2.push(new Dish("Asian", Bowl));
	st2.push(new Dish("Asian", Bowl));
	st2.push(new Dish("Asian", Bowl));
	st2.push(new Dish("Asian", Bowl));
	stack<Dish*> st3;
	st3.push(new Dish("White", Plate));
	st3.push(new Dish("White", Plate));
	st3.push(new Dish("White", Plate));
	st3.push(new Dish("White", Plate));
	st3.push(new Dish("White", Plate));
	st3.push(new Dish("White", Plate));
	st3.push(new Dish("White", Plate));
	vector< stack<Dish*> > clean;
	clean.push_back(st1);
	clean.push_back(st2);
	clean.push_back(st3);

	Restaurant r(&clean, NULL, NULL);

	int table0_size = 5;
	r.addTable(table0_size);

	vector<Dish*> dishes;
	dishes.push_back(new Dish("Spring", Dessert));
	dishes.push_back(new Dish("Spring", Dessert));
	dishes.push_back(new Dish("Spring", Dessert));
	dishes.push_back(new Dish("Spring", Dessert));
	Table t1(4);
	t1.putOn(dishes);
	r.addTable(t1);

	ASSERT_THROWS(r.setupTable(0, "Asian"), Restaurant::NotEnoughDishesException);
	ASSERT_EQUAL(3, r.getCleanDishStack("Asian", Plate).size());

	int n = r.getCleanDishStack("White", Plate).size();
	r.setupTable(0, "White");
	n -= r.getCleanDishStack("White", Plate).size();
	ASSERT_EQUAL(table0_size, n);
	Table t0_changed = r.getTable(0);
	ASSERT_EQUAL("White", t0_changed.getCollection());
	vector< stack<Dish*> > places = t0_changed.getPlaces();
	for(vector< stack<Dish*> >::const_iterator it = places.begin(); it != places.end(); ++it) {
		ASSERT_EQUAL(1, (*it).size());
		ASSERT_EQUAL("White", (*it).top()->getCollection());
		ASSERT_EQUAL(Plate, (*it).top()->getType());
	}
	ASSERT_EQUAL(3, r.getCleanDishStack("Asian", Plate).size());

	ASSERT_THROWS(r.setupTable(1, "Asian"), Restaurant::TableNotReadyException);
	ASSERT_EQUAL(3, r.getCleanDishStack("Asian", Plate).size());

	r.setupTable(2, "White");

}


// Restaurant::pickupAndGroupDryDishes()
void test_F_() {

	list<Dish*> drying;
	drying.push_back(new Dish("Spring", Bowl));
	drying.push_back(new Dish("Asian", Plate));
	drying.push_back(new Dish("White", Bowl));
	drying.push_back(new Dish("Asian", Plate));
	drying.push_back(new Dish("Asian", Bowl));
	drying.push_back(new Dish("Spring", Plate));
	drying.push_back(new Dish("White", Bowl));
	drying.push_back(new Dish("White", Dessert));
	drying.push_back(new Dish("White", Bowl));

	Restaurant r(NULL, NULL, &drying);

	list<Dish*> dry_grouped = r.pickupAndGroupDryDishes();

	ASSERT_EQUAL(drying.size(), dry_grouped.size());
	ASSERT_EQUAL(0, r.getDrying().size());

//	for(list<Dish*>::iterator it = dry_grouped.begin(); it != dry_grouped.end(); ++it) {
//		cout << (*it)->getCollection() << " " << (*it)->getType() << endl;
//	}

	list<Dish*>::iterator it = dry_grouped.begin();
	while(it != dry_grouped.end()) {
		Dish* d = *it;
		// check existence in drying list
		list<Dish*>::iterator it2 = drying.begin();
		while(it2 != drying.end() && !(*(*it2) == *(*it))) {
			++it2;
		}
		ASSERT_EQUAL(false, it2 == drying.end());
		drying.erase(it2);

		// skip consecutive equal dishes
		it2 = it;
		while(it2 != dry_grouped.end() && *(*it2) == *d) {
			++it2;
		}
		it = it2;

		// check that no more equal dishes follow
		while(it2 != dry_grouped.end()) {
			ASSERT_EQUAL(false, *(*it2) == *d);
			++it2;
		}
	}

	Restaurant r2;
	r2.pickupAndGroupDryDishes();
	ASSERT_EQUAL(0, r2.getDrying().size());

}

// Restaurant::storeGroupedDishes()
void test_G_() {

	stack<Dish*> st1;
	st1.push(new Dish("Asian", Plate));
	st1.push(new Dish("Asian", Plate));
	st1.push(new Dish("Asian", Plate));
	stack<Dish*> st2;
	st2.push(new Dish("Asian", Bowl));
	st2.push(new Dish("Asian", Bowl));
	stack<Dish*> st3;
	st3.push(new Dish("White", Dessert));
	st3.push(new Dish("White", Dessert));
	st3.push(new Dish("White", Dessert));
	stack<Dish*> st4;
	st4.push(new Dish("Spring", Dessert));
	st4.push(new Dish("Spring", Dessert));
	vector< stack<Dish*> > clean;
	clean.push_back(st1);
	clean.push_back(st2);
	clean.push_back(st3);
	clean.push_back(st4);

	Restaurant r(&clean, NULL, NULL);

	list<Dish*> dry_grouped;
	dry_grouped.push_back(new Dish("Spring", Bowl));
	dry_grouped.push_back(new Dish("Asian", Plate));
	dry_grouped.push_back(new Dish("Asian", Plate));
	dry_grouped.push_back(new Dish("White", Bowl));
	dry_grouped.push_back(new Dish("White", Bowl));
	dry_grouped.push_back(new Dish("White", Bowl));
	dry_grouped.push_back(new Dish("Asian", Bowl));
	dry_grouped.push_back(new Dish("Spring", Plate));
	dry_grouped.push_back(new Dish("White", Dessert));

	ASSERT_EQUAL(6, r.storeGroupedDishes(dry_grouped));

	ASSERT_EQUAL(1, r.getCleanDishStack("Spring", Bowl).size());
	ASSERT_EQUAL(5, r.getCleanDishStack("Asian", Plate).size());
	ASSERT_EQUAL(3, r.getCleanDishStack("White", Bowl).size());
	ASSERT_EQUAL(3, r.getCleanDishStack("Asian", Bowl).size());
	ASSERT_EQUAL(1, r.getCleanDishStack("Spring", Plate).size());
	ASSERT_EQUAL(4, r.getCleanDishStack("White", Dessert).size());
	ASSERT_EQUAL(2, r.getCleanDishStack("Spring", Dessert).size());

}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(test_A_));
	s.push_back(CUTE(test_B_));
	s.push_back(CUTE(test_C_));
	s.push_back(CUTE(test_D_));
	s.push_back(CUTE(test_E_));
	s.push_back(CUTE(test_F_));
	s.push_back(CUTE(test_G_));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AEDA 2015/2016 - Avaliacao CI3- 25/nov - Testes Unitarios Estudantes");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}

