/*
 * FilmTime.h
 */
#ifndef SRC_FILMTIME_H_
#define SRC_FILMTIME_H_

#include "Film.h"

using namespace std;


class FilmTime {
	unsigned hour;
	Film *film;
	unsigned roomID;
public:
	FilmTime(unsigned h, Film *f, unsigned id);
	virtual ~FilmTime();
	unsigned getHour() const;
	unsigned getRoomID() const;
	Film* getFilm() const;
	void setFilm(Film* f);
	void setHour(unsigned new_hour) { hour = new_hour; }
	bool operator == (const FilmTime &ft) const;

	bool operator<(const FilmTime & ft1) const;  //TODO: Implement a correct version of the operator
};


#endif /* SRC_FILMTIME_H_ */
