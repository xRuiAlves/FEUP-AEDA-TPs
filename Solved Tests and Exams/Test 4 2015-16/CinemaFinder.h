/*
 * CinemaFinder.h
 */

#ifndef SRC_CINEMAFINDER_H_
#define SRC_CINEMAFINDER_H_

#include <tr1/unordered_set>
#include "Cinema.h"
#include "Film.h"

using namespace std;


struct hFilmPtr {
	int operator()(const FilmPtr & f1) const{
		return f1.film->getTitle().size();
	}
	bool operator()(const FilmPtr & f1, const FilmPtr & f2) const {
		return (f1.film->getTitle() == f2.film->getTitle());
	}
};

typedef tr1::unordered_set<FilmPtr, hFilmPtr, hFilmPtr> tabHFilm;

class CinemaFinder {
	priority_queue<Cinema> cinemas;
	tabHFilm films;
public:
	CinemaFinder();
	virtual ~CinemaFinder();
	tabHFilm getFilms() const;
	priority_queue<Cinema> getCinemas() const;
	void addFilm(Film *f1);
	void addCinema(const Cinema &c1);
	//
	list<string> filmsWithActor(string actorName) const;
	void addActor(string filmTitle, string actorName);
	string nearestCinema(string service1) const;
	void addServiceToNearestCinema(string service1, unsigned maxDistance);

	class CinemaNotFound {};
};

#endif /* SRC_CINEMAFINDER_H_ */

