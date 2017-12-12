/*
 * FilmTime.cpp
 */
#include "FilmTime.h"


FilmTime::FilmTime(unsigned h, Film *f, unsigned id): hour(h), film(f), roomID(id)
{}

FilmTime::~FilmTime() { }

unsigned FilmTime::getHour() const
{ return hour; }

unsigned FilmTime::getRoomID() const
{ return roomID; }

Film* FilmTime::getFilm() const
{ return film; }

void FilmTime::setFilm(Film* f)
{ film = f; }

bool FilmTime::operator == (const FilmTime &ft) const
{ return (film==ft.film && hour==ft.hour && roomID==ft.roomID); }


// TODO

bool FilmTime::operator<(const FilmTime & ft1) const
{
	if (hour == ft1.hour){
		return (roomID < ft1.roomID);
	}
	else
		return (hour < ft1.hour);
}




