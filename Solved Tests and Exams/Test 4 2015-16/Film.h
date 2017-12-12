/*
 * Film.h
 */
#ifndef SRC_FILM_H_
#define SRC_FILM_H_

#include <string>
#include <list>

using namespace std;


class Film {
	string title;
	list<string> actors;
public:
	Film(string tit, list<string> a);
	Film(string tit);
	virtual ~Film();
	string getTitle() const;
	list<string> getActors() const;
	void addActor(string actorName);
};

struct FilmPtr {
	Film *film;
};




#endif /* SRC_FILM_H_ */
