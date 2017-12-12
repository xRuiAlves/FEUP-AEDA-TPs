/*
 * Cinema.h
 */

#ifndef SRC_CINEMA_H_
#define SRC_CINEMA_H_

#include <string>
#include "BST.h"
#include "FilmTime.h"

using namespace std;

class Cinema {
	string name;
	unsigned distance;
	unsigned numberOfRooms;
	list<string> services;
	BST<FilmTime> timetable;
public:
	Cinema(string nm, unsigned d, unsigned nr);
	Cinema(string nm, unsigned d, unsigned nr, list<string> ls);
	virtual ~Cinema();
	string getName() const;
	unsigned getDistance() const;
	list<string> getServices() const;
	BST<FilmTime> getTimetable() const;
	void addService(string service1);
	void addFilmTime(const FilmTime &ft1);

	bool operator<(const Cinema & c1) const;  //TODO: Implement a correct version of the operator
	Film *filmAtHour(unsigned &h1) const;
	bool modifyHour(unsigned h1, unsigned room1, unsigned h2);
	unsigned addFilm(Film *f1, unsigned h1);
};





#endif /* SRC_CINEMA_H_ */
