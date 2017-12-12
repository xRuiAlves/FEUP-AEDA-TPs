/*
 * Film.cpp
 */
#include "Film.h"


Film::Film(string tit, list<string> a): title(tit), actors(a)
{}

Film::Film(string tit): title(tit)
{}

Film::~Film()
{ }

string Film::getTitle() const
{ return title; }

list<string> Film::getActors() const
{ return actors; }

void Film::addActor(string actorName)
{ actors.push_back(actorName); }


