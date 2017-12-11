#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Book.h"
#include "User.h"
#include "ReadingClub.h"

#include <vector>
#include <iostream>
using namespace std;

void test_A_() {

	vector<Book*> books;
	books.push_back(new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 2016));
	books.push_back(new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 1994));
	books.push_back(new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 2016));
	books.push_back(new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 1994));
	books.push_back(new Book("Data Structures and Algorithms", "Narasimha Karumanchi", 2011));
	books.push_back(new Book("Data Structures and Algorithms", "Hemant Jain", 2011));
	books.push_back(new Book("Data Structures and Algorithms", "Mark Allen Weiss", 2012));
	books.push_back(new Book("Data Structures and Algorithms", "Mark Allen Weiss", 2001));
	books.push_back(new Book("Data Structures and Algorithms", "Harry Hariom Choudhary", 2014));
	books.push_back(new Book("Data Structures and Algorithms", "Robert Lafore", 2002));
	books.push_back(new Book("Data Structures and Algorithms", "Mark Allen Weiss", 2001));
	books.push_back(new Book("Data Structures and Algorithms", "Harry Hariom Choudhary", 2015));
	books.push_back(new Book("Data Structures and Algorithms", "Robert Lafore", 2002));
	books.push_back(new Book("Data Structures and Algorithms", "Mark Allen Weiss", 2020));

	ReadingClub club(books);

	club.generateCatalog();

	BookCatalogItem bci1 = club.getCatalogItem("Artificial Intelligence", "Stuart Russell and Peter Norvig");
	ASSERT_EQUAL(4, bci1.getItems().size());
	BookCatalogItem bci2 = club.getCatalogItem("Data Structures and Algorithms", "Harry Hariom Choudhary");
	ASSERT_EQUAL(2, bci2.getItems().size());
	BookCatalogItem bci3 = club.getCatalogItem("Data Structures and Algorithms", "Mark Allen Weiss");
	ASSERT_EQUAL(4, bci3.getItems().size());

}

void test_B_() {

	Book* bPtr1 = new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 2016);
	Book* bPtr2 = new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 1994);
	Book* bPtr3 = new Book("Data Structures and Algorithms", "Narasimha Karumanchi", 2011);

	User* u1 = new User("Joao", "joao@gmail.com");
	bPtr2->setReader(u1);
	u1->addReading(bPtr2->getTitle(), bPtr2->getAuthor());

	User* u2 = new User("Maria", "maria@gmail.com");
	bPtr3->setReader(u2);
	u2->addReading(bPtr3->getTitle(), bPtr3->getAuthor());

	ReadingClub club;

	club.addCatalogItem(bPtr1);
	club.addCatalogItem(bPtr2);
	club.addCatalogItem(bPtr3);

	vector<Book*> av1 = club.getAvailableItems(bPtr1);
	ASSERT_EQUAL(1, av1.size());
	vector<Book*> av2 = club.getAvailableItems(bPtr2);
	ASSERT_EQUAL(1, av2.size());
	vector<Book*> av3 = club.getAvailableItems(bPtr3);
	ASSERT_EQUAL(0, av3.size());

}

void test_C_() {

	vector<Book*> books;
	Book* bPtr1 = new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 2016);
	Book* bPtr2 = new Book("Artificial Intelligence", "Stuart Russell and Peter Norvig", 1994);
	Book* bPtr3 = new Book("Data Structures and Algorithms", "Narasimha Karumanchi", 2011);
	Book* bPtr4 = new Book("Easy Cooking", "Master Chef", 2013);

	User* u1 = new User("Joao", "joao@gmail.com");
	User* u2 = new User("Maria", "maria@gmail.com");

	ReadingClub club;

	club.addCatalogItem(bPtr1);
	club.addCatalogItem(bPtr2);
	club.addCatalogItem(bPtr3);


	bool loan1 = club.borrowBookFromCatalog(bPtr4, u1);
	ASSERT_EQUAL(false, loan1);


	bool loan2 = club.borrowBookFromCatalog(bPtr3, u1);
	ASSERT_EQUAL(true, loan2);
	ASSERT_EQUAL("Joao", bPtr3->getReader()->getName());

	bool loan3 = club.borrowBookFromCatalog(bPtr3, u2);
	ASSERT_EQUAL(false, loan3);
	ASSERT_EQUAL("Joao", bPtr3->getReader()->getName());

	bool loan4 = club.borrowBookFromCatalog(bPtr1, u2);
	ASSERT_EQUAL(true, loan4);
	ASSERT_EQUAL("Maria", bPtr1->getReader()->getName());
}

void test_D_() {

	User u1("Tiago", "t.silva@gmail.com");
	User u2("Tiago", "t.silva@gmail.com");
	User u3("Pedro", "pedro@gmail.com");
	User u4("ana", "ana@gmail.com");
	User u5("Maria", "maria.castro@gmail.com");
	User u6("Tiago", "tiago@gmail.com");

	ReadingClub rc1;
	rc1.addUserRecord(&u1);
	vector<UserRecord> ur1 = rc1.getUserRecords();
	ASSERT_EQUAL(1, ur1.size());
	ASSERT_EQUAL("t.silva@gmail.com", ur1[0].getEMail());

	rc1.addUserRecord(&u2);
	ur1 = rc1.getUserRecords();
	ASSERT_EQUAL(1, ur1.size());

	rc1.addUserRecord(&u3);
	rc1.addUserRecord(&u4);
	rc1.addUserRecord(&u5);
	ur1 = rc1.getUserRecords();
	ASSERT_EQUAL(4, ur1.size());

	rc1.addUserRecord(&u6);
	ur1 = rc1.getUserRecords();
	ASSERT_EQUAL(5, ur1.size());

}

void test_E_() {

	User u1("Tiago", "t.silva@gmail.com");
	vector<UserRecord> urs1;
	urs1.push_back(UserRecord(&u1));

	ReadingClub rc1;
	rc1.setUserRecords(urs1);

	rc1.changeUserEMail(&u1, "tiago.sousa@gmail.com");

	urs1 = rc1.getUserRecords();
	ASSERT_EQUAL("tiago.sousa@gmail.com", urs1[0].getEMail());


	vector<UserRecord> urs2;
	User u2("Pedro", "pedro@gmail.com");
	User u3("Ana", "ana@gmail.com");

	urs2.push_back(UserRecord(&u1));
	urs2.push_back(UserRecord(&u2));
	urs2.push_back(UserRecord(&u3));

	ReadingClub rc2;
	rc2.setUserRecords(urs2);

	rc2.changeUserEMail(&u3, "a.gomes@gmail.com");

	urs2 = rc2.getUserRecords();

	for(int i = 0; i < urs2.size(); i++) {
		if(urs2[i].getName() == "Ana") ASSERT_EQUAL("a.gomes@gmail.com", urs2[i].getEMail());
	}

}

void test_F_() {

	User u0("Tiago", "tiago@gmail.com");
	User u1("Joao", "joao@gmail.com");
	User u2("Maria", "maria@gmail.com");
	User u3("Pedro", "pedro@gmail.com");
	User u4("ana", "ana@gmail.com");
	User u5("Miguel", "miguel@gmail.com");

	u1.addReading("The Lord of the Rings", "John R. R. Tolkien");
	u1.addReading("On The Shoulders Of Giants", "Stephen Hawking");
	u1.addReading("Divina Comedia", "Dante Alighieri");
	u1.addReading("Artificial Intelligence", "Stuart Russell and Peter Norvig");

	u2.addReading("Artificial Intelligence", "Kevin Warwick");
	u2.addReading("The Universe in a Nutshell", "Stephen Hawking");

	u3.addReading("Artificial Intelligence", "Kevin Warwick");
	u3.addReading("On The Shoulders Of Giants", "Stephen Hawking");
	u3.addReading("Divina Comedia", "Dante Alighieri");
	u3.addReading("Artificial Intelligence", "Stuart Russell and Peter Norvig");
	u3.addReading("The Philosopher's Stone", "Joanne K. Rowling");

	u5.addReading("Data Structures and Algorithms", "Mark Allen Weiss");
	u5.addReading("Mathematical Analysis", "Vladimir A. Zorich and Roger Cooke");

	vector<User> candidates_0;
	candidates_0.push_back(u0);

	vector<User> candidates_2;
	candidates_2.push_back(u2);
	candidates_2.push_back(u5);

	vector<User> candidates_5;
	candidates_5.push_back(u1);
	candidates_5.push_back(u2);
	candidates_5.push_back(u3);
	candidates_5.push_back(u4);
	candidates_5.push_back(u5);

	ReadingClub rc1;
	rc1.addBestReaderCandidates(candidates_5, 5);
	ASSERT_EQUAL(1, rc1.getBestReaderCandidates().size());

	ReadingClub rc2;
	rc2.addBestReaderCandidates(candidates_0, 2);
	ASSERT_EQUAL(0, rc2.getBestReaderCandidates().size());

	ReadingClub rc3;
	rc3.addBestReaderCandidates(candidates_5, 3);
	ASSERT_EQUAL(2, rc3.getBestReaderCandidates().size());

	vector<User> candidates_a;
	candidates_a.push_back(u1);
	candidates_a.push_back(u3);

	vector<User> candidates_b;
	u3.endReading();
	candidates_b.push_back(u1);
	candidates_b.push_back(u3);

	ReadingClub rc4;
	rc4.addBestReaderCandidates(candidates_a, 5);
	ASSERT_EQUAL(1, rc4.getBestReaderCandidates().size());

	ReadingClub rc5;
	rc5.addBestReaderCandidates(candidates_b, 5);
	ASSERT_EQUAL(1, rc5.getBestReaderCandidates().size());

}


void test_G_() {

	User u0("Tiago", "tiago@gmail.com");
	User u1("Joao", "joao@gmail.com");
	User u2("Maria", "maria@gmail.com");
	User u3("Pedro", "pedro@gmail.com");
	User u4("ana", "ana@gmail.com");
	User u5("Miguel", "miguel@gmail.com");
	User u6("Hugo", "hugo@gmail.com");

	u1.addReading("The Lord of the Rings", "John R. R. Tolkien");
	u1.addReading("On The Shoulders Of Giants", "Stephen Hawking");
	u1.addReading("Divina Comedia", "Dante Alighieri");
	u1.addReading("Artificial Intelligence", "Stuart Russell and Peter Norvig");

	u2.addReading("Artificial Intelligence", "Kevin Warwick");
	u2.addReading("The Universe in a Nutshell", "Stephen Hawking");

	u3.addReading("Artificial Intelligence", "Kevin Warwick");
	u3.addReading("On The Shoulders Of Giants", "Stephen Hawking");
	u3.addReading("Divina Comedia", "Dante Alighieri");
	u3.addReading("Artificial Intelligence", "Stuart Russell and Peter Norvig");
	u3.addReading("The Philosopher's Stone", "Joanne K. Rowling");

	u5.addReading("Data Structures and Algorithms", "Mark Allen Weiss");
	u5.addReading("Mathematical Analysis", "Vladimir A. Zorich and Roger Cooke");

	u6.addReading("On The Shoulders Of Giants", "Stephen Hawking");

	User champion("","");

	priority_queue<User> candidates_a;
	ReadingClub rc1;
	rc1.setBestReaderCandidates(candidates_a);
	ASSERT_EQUAL(0, rc1.awardReaderChampion(champion));


	priority_queue<User> candidates_b;
	candidates_b.push(u2);
	candidates_b.push(u5);
	candidates_b.push(u6);

	ReadingClub rc2;
	rc2.setBestReaderCandidates(candidates_b);
	ASSERT_EQUAL(0, rc2.awardReaderChampion(champion));

	priority_queue<User> candidates_c;
	candidates_c.push(u1);
	candidates_c.push(u2);
	candidates_c.push(u3);

	ReadingClub rc3;
	rc3.setBestReaderCandidates(candidates_c);
	ASSERT_EQUAL(3, rc3.awardReaderChampion(champion));
	ASSERT_EQUAL("Pedro", champion.getName());

	priority_queue<User> candidates_d;
	candidates_d.push(u2);
	candidates_d.push(u6);

	ReadingClub rc4;
	rc4.setBestReaderCandidates(candidates_d);
	ASSERT_EQUAL(2, rc4.awardReaderChampion(champion));
	ASSERT_EQUAL("Maria", champion.getName());

}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_A_));
	s.push_back(CUTE(test_B_));
	s.push_back(CUTE(test_C_));
	s.push_back(CUTE(test_D_));
	s.push_back(CUTE(test_E_));
	s.push_back(CUTE(test_F_));
	s.push_back(CUTE(test_G_));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



