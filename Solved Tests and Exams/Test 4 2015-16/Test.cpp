#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "CinemaFinder.h"

void test_a1() {
	Cinema c1("NS",0,5);

	Film *f1 = new Film("The Last Witch Hunter");
	Film *f2 = new Film("Bridge of Spie");
	Film *f3 = new Film("Hotel Transylvania");
	Film *f4 = new Film("The Good Dinosaur");

	Film *f0=NULL;
	unsigned hf = 20;

	Film *f = c1.filmAtHour(hf);
	ASSERT_EQUAL(f0,f);

	c1.addFilmTime(FilmTime(20,f1,1));

	f = c1.filmAtHour(hf);
	ASSERT_EQUAL(f1,f);
	hf=19;
	f = c1.filmAtHour(hf);
	ASSERT_EQUAL(f0,f);

	c1.addFilmTime(FilmTime(22,f2,1));
	c1.addFilmTime(FilmTime(18,f3,1));
	c1.addFilmTime(FilmTime(15,f4,1));

	hf=18;
	f = c1.filmAtHour(hf);
	ASSERT_EQUAL(f3,f);
	ASSERT_EQUAL(18,hf);

	hf=23;
	f = c1.filmAtHour(hf);
	ASSERT_EQUAL(f2,f);
	ASSERT_EQUAL(22,hf);

	hf=11;
	f = c1.filmAtHour(hf);
	ASSERT_EQUAL(f0,f);
}


void test_a2() {
	Cinema c1("NS",0,5);

	Film *f1 = new Film("The Last Witch Hunter");
	Film *f2 = new Film("Bridge of Spie");
	Film *f3 = new Film("Hotel Transylvania");
	Film *f4 = new Film("The Good Dinosaur");

	bool res = c1.modifyHour(15,3,20);
	ASSERT_EQUAL(false,res);

	c1.addFilmTime(FilmTime(15,f1,3));
	c1.addFilmTime(FilmTime(20,f3,3));
	c1.addFilmTime(FilmTime(15,f2,2));
	c1.addFilmTime(FilmTime(18,f4,3));

	res = c1.modifyHour(15,3,20);
	ASSERT_EQUAL(false, res);

	res = c1.modifyHour(10,3,12);
	ASSERT_EQUAL(false, res);

	BST<FilmTime> timet1 = c1.getTimetable();
	FilmTime ft1 = timet1.findMin();
	ASSERT_EQUAL(f2, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f1, ft1.getFilm());

	res = c1.modifyHour(15,3,19);
	ASSERT_EQUAL(true, res);

	timet1 = c1.getTimetable();
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f2, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f4, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f1, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f3, ft1.getFilm());
	timet1.remove(ft1);
	ASSERT_EQUAL(true, timet1.isEmpty());
}


void test_a3() {
	Cinema c1("NS",0,3);

	Film *f1 = new Film("The Last Witch Hunter");
	Film *f2 = new Film("Bridge of Spie");
	Film *f3 = new Film("Hotel Transylvania");
	Film *f4 = new Film("The Good Dinosaur");

	unsigned room1 = c1.addFilm(f2,15);
	ASSERT_EQUAL(1, room1);

	room1 = c1.addFilm(f2,10);
	ASSERT_EQUAL(1, room1);

	room1 = c1.addFilm(f1,18);
	ASSERT_EQUAL(1, room1);

	room1 = c1.addFilm(f3,10);
	ASSERT_EQUAL(2, room1);

	room1 = c1.addFilm(f4,10);
	ASSERT_EQUAL(3, room1);

	room1 = c1.addFilm(f1,10);
	ASSERT_EQUAL(0, room1);

	BST<FilmTime> timet1 = c1.getTimetable();
	FilmTime ft1 = timet1.findMin();
	ASSERT_EQUAL(f2, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f3, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f4, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f2, ft1.getFilm());
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	ASSERT_EQUAL(f1, ft1.getFilm());
	timet1.remove(ft1);
	ASSERT_EQUAL(true, timet1.isEmpty());
}


void test_b1() {
	CinemaFinder cf1;

	list<string> actors1;
	actors1.push_back("Vin Diesel"); actors1.push_back("Rose Leslie"); actors1.push_back("Elijah Wood");
	list<string> actors2;
	actors2.push_back("Tom Hanks"); actors2.push_back("Mark Rylance"); actors2.push_back("Scott Shepherd");
	actors2.push_back("Amy Ryan"); actors2.push_back("Sebastian Koch"); actors2.push_back("Alan Alda");
	list<string> actors3;
	actors3.push_back("Amy Ryan");

	Film *f1 = new Film("The Last Witch Hunter", actors1);
	Film *f2 = new Film("Bridge of Spie", actors2);
	Film *f3 = new Film("Hotel Transylvania", actors3);
	Film *f4 = new Film("The Good Dinosaur");

	list<string> res;

	res = cf1.filmsWithActor("Vin Diesel");
	ASSERT_EQUAL(0, res.size());

	cf1.addFilm(f1);
	cf1.addFilm(f2);
	cf1.addFilm(f3);
	cf1.addFilm(f4);

	res = cf1.filmsWithActor("Tom Hanks");
	ASSERT_EQUAL(1, res.size());
	ASSERT_EQUAL("Bridge of Spie", res.front());

	res = cf1.filmsWithActor("Amy Ryan");
	ASSERT_EQUAL(2, res.size());

	string s1,s2;
	if (res.front()=="Bridge of Spie") { s1=res.front(); s2=res.back(); }
	else { s1=res.back(); s2=res.front(); }
	ASSERT_EQUAL("Bridge of Spie", s1);
	ASSERT_EQUAL("Hotel Transylvania", s2);

	res=cf1.filmsWithActor("Daniel Craig");
	ASSERT_EQUAL(0, res.size());
}


void test_b2() {
	CinemaFinder cf1;

	list<string> actors1;
	actors1.push_back("Vin Diesel"); actors1.push_back("Rose Leslie"); actors1.push_back("Elijah Wood");
	list<string> actors2;
	actors2.push_back("Tom Hanks"); actors2.push_back("Mark Rylance"); actors2.push_back("Scott Shepherd");
	actors2.push_back("Amy Ryan"); actors2.push_back("Sebastian Koch"); actors2.push_back("Alan Alda");

	Film *f2 = new Film("Bridge of Spie", actors2);
	Film *f4 = new Film("The Good Dinosaur");


	cf1.addActor("Hotel Transylvania", "Daniel Craig");
	ASSERT_EQUAL(1,cf1.getFilms().size());

	cf1.addFilm(f2);
	cf1.addFilm(f4);
	ASSERT_EQUAL(3,cf1.getFilms().size());

	cf1.addActor("Bridge of Spie", "Daniel Craig");
	ASSERT_EQUAL(3,cf1.getFilms().size());

	FilmPtr fxPtr;
	fxPtr.film=f2;
	tabHFilm tabf = cf1.getFilms();
	ASSERT_EQUAL(7, tabf.find(fxPtr)->film->getActors().size());
}


void test_c1() {
	CinemaFinder cf1;

	ASSERT_EQUAL("", cf1.nearestCinema("estacionamento"));

	Cinema c1("NS", 20, 4);
	c1.addService("estacionamento");
	c1.addService("restauração");
	c1.addService("comercio");

	Cinema c2("Arrabida", 10, 4);
	c2.addService("estacionamento");

	Cinema c3("PN", 20, 4);
	c3.addService("estacionamento");
	c3.addService("restauração");

	Cinema c4("GS", 8, 4);

	cf1.addCinema(c1);
	cf1.addCinema(c2);
	cf1.addCinema(c3);
	cf1.addCinema(c4);

	ASSERT_EQUAL("Arrabida", cf1.nearestCinema("estacionamento"));
	ASSERT_EQUAL(4, cf1.getCinemas().size());

	ASSERT_EQUAL("NS", cf1.nearestCinema("comercio"));
	ASSERT_EQUAL(4, cf1.getCinemas().size());
}


void test_c2() {
	CinemaFinder cf1;

	ASSERT_THROWS(cf1.addServiceToNearestCinema("diversao",10), CinemaFinder::CinemaNotFound);

	Cinema c1("NS", 20, 4);
	c1.addService("estacionamento");
	c1.addService("restauração");
	c1.addService("comercio");

	Cinema c2("Arrabida", 12, 4);
	c2.addService("estacionamento");

	Cinema c3("PN", 20, 4);
	c3.addService("estacionamento");
	c3.addService("restauração");

	Cinema c4("GS", 8, 4);

	cf1.addCinema(c1);
	cf1.addCinema(c2);
	cf1.addCinema(c3);
	cf1.addCinema(c4);

	cf1.addServiceToNearestCinema("diversao",10);
	ASSERT_EQUAL(4, cf1.getCinemas().size());
	c1= cf1.getCinemas().top();
	ASSERT_EQUAL("GS",c1.getName());
	ASSERT_EQUAL(1,c1.getServices().size());

	ASSERT_THROWS(cf1.addServiceToNearestCinema("diversao",4), CinemaFinder::CinemaNotFound);
	ASSERT_EQUAL(4, cf1.getCinemas().size());
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a1));
	s.push_back(CUTE(test_a2));
	s.push_back(CUTE(test_a3));
	s.push_back(CUTE(test_b1));
	s.push_back(CUTE(test_b2));
	s.push_back(CUTE(test_c1));
	s.push_back(CUTE(test_c2));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2015/2016 - Avaliação - 16/dez - Testes Unitarios Estudantes");
}

int main(){
    runSuite();
    return 0;
}



