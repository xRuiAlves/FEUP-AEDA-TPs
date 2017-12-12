/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;
	list<string> aux;

	for (auto it = films.begin() ; it != films.end() ; it++){
		aux = it->film->getActors();
		for (auto it2 = aux.begin() ; it2!=aux.end() ; it2++){
			if (actorName == (*it2)){
				res.push_back(it->film->getTitle());
			}
		}
	}

	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	for (auto it=films.begin() ; it!=films.end() ; it++){
		if (it->film->getTitle() == filmTitle){
			FilmPtr fptr;
			fptr.film = it->film;
			films.erase(it);
			fptr.film->addActor(actorName);
			films.insert(fptr);
			return;
		}
	}

	Film* newfilme = new Film(filmTitle);
	newfilme->addActor(actorName);
	FilmPtr fptr;
	fptr.film = newfilme;
	films.insert(fptr);
}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	priority_queue<Cinema> aux = cinemas;
	list<string> services;

	while(!aux.empty()){
		Cinema c = aux.top();
		aux.pop();

		services=c.getServices();

		for(auto it=services.begin() ; it!=services.end() ; it++){
			if( (*it) == service1){
				return c.getName();
			}
		}

	}


	return "";
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {

	if(cinemas.empty())
		throw (CinemaNotFound());

	Cinema c = cinemas.top();

	if(c.getDistance() >= maxDistance)
		throw (CinemaNotFound());

	// Checks
	cinemas.pop();
	c.addService(service1);
	cinemas.push(c);

}
