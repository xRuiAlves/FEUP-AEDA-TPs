#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Mail.h"
#include "Postman.h"
#include "PostOffice.h"
#include <vector>
#include <string>
using namespace std;

template <class T>
unsigned int numberDifferent (const vector<T> & v1){
	unsigned int counter = 0;
	bool foundRepetition;

	for (unsigned int i=0 ; i< v1.size() ; i++){
		foundRepetition = false;	// Reset the found repetition flag

		for (unsigned int j=i+1 ; j<v1.size() ; j++){
			if(v1.at(i) == v1.at(j)){	// found a repetition! Set the flag and break the loop
				foundRepetition = true;
				break;
			}
		}

		if(!foundRepetition)	// If no repetition was found, increment the counter
			counter++;
	}

	return counter;
}

void test_a() {
	vector<int> v1;
	v1.push_back(10); v1.push_back(8);
	v1.push_back(12); v1.push_back(8);
	ASSERT_EQUAL(3, numberDifferent(v1));
	vector<string> v2;
	v2.push_back("ola"); v2.push_back("ola");
	ASSERT_EQUAL(1, numberDifferent(v2));
	v2.push_back("rio"); v2.push_back("arvore");
	v2.push_back("sol"); v2.push_back("sol");
	ASSERT_EQUAL(4, numberDifferent(v2));
}

void test_b() {
	PostOffice po;
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));
	Postman p2;
	p2. setName("paulo");
	p2.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p2.addMail(new RegularMail("luis", "maria","8600-306", 67));
	p2.addMail(new RegularMail("carla", "lara","7100-514", 67));
	Postman p3;
	p3.setName("fernando");
	p3.addMail(new RegularMail("manuel", "ana","3330-454", 33));
	po.addPostman(p1);
	po.addPostman(p2);
	po.addPostman(p3);

	vector <Mail *> mailP = po.removePostman("paulo");
	ASSERT_EQUAL(3, mailP.size());
	ASSERT_EQUAL(2,po.getPostman().size());

	mailP.clear();
	mailP = po.removePostman("sergio");
	ASSERT_EQUAL(0, mailP.size());

	mailP.clear();
	mailP = po.removePostman("fernando");
	ASSERT_EQUAL(1, mailP.size());

	mailP.clear();
	mailP = po.removePostman("joao");
	ASSERT_EQUAL(2, mailP.size());

	ASSERT_EQUAL(0,po.getPostman().size());
}

void test_c() {
	RegularMail m1("manuel", "ana","3330-454", 33);
	RegularMail m2("ana", "rui","4400-146", 550);
	GreenMail m3("maria", "luis","2520-110", "bag");
	GreenMail m4("carla", "lara","7100-514", "envelope");

	ASSERT_EQUAL(75, m1.getPrice());
	ASSERT_EQUAL(325, m2.getPrice());
	ASSERT_EQUAL(200, m3.getPrice());
	ASSERT_EQUAL(80, m4.getPrice());
}

void test_d() {
	PostOffice po("3100-000", "4409-999");
	po.addMailToSend(new RegularMail("manuel", "ana","3330-454", 33));
	po.addMailToSend(new RegularMail("ana", "rui","4400-146", 550));
	po.addMailToSend(new GreenMail("maria", "luis","2520-110", "bag"));
	po.addMailToSend(new GreenMail("carla", "lara","7100-514", "envelope"));

	unsigned int bal = 0;
	vector<Mail *> mailToOtherPO = po.endOfDay(bal);
	ASSERT_EQUAL(680, bal);
	ASSERT_EQUAL(2,mailToOtherPO.size());
	ASSERT_EQUAL(2,po.getMailToDeliver().size());
	ASSERT_EQUAL(0,po.getMailToSend().size());

	PostOffice po2("3100-000", "4409-999");
	po2.addMailToSend(new RegularMail("rita", "joana","5200-514", 120));

	mailToOtherPO = po2.endOfDay(bal);
	ASSERT_EQUAL(140, bal);
	ASSERT_EQUAL(1,mailToOtherPO.size());
	ASSERT_EQUAL(0,po2.getMailToDeliver().size());
	ASSERT_EQUAL(0,po2.getMailToSend().size());
}

void test_e() {
	Postman p1("joao");
	Postman p2("rui");
	Postman p3("paulo");

	ASSERT_EQUAL(1, p1.getID());
	ASSERT_EQUAL(2, p2.getID());
	ASSERT_EQUAL(3, p3.getID());
}

void test_f() {
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));

	Postman p2;
	p2. setName("paulo");
	p2.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p2.addMail(new RegularMail("carla", "lara","7100-514", 67));
	p2.addMail(new RegularMail("luis", "maria","8600-306", 67));

	ASSERT_EQUAL(true, p1<p2);
	ASSERT_EQUAL(false, p2<p1);

	p1.addMail(new RegularMail("joana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("rita", "joana","5200-514", 120));
	p1.addMail(new RegularMail("maria", "lara","7100-514", 67));

	p2.addMail(new RegularMail("maria", "lara","8600-306", 67));

	ASSERT_EQUAL(false, p1<p2);
	ASSERT_EQUAL(true, p2<p1);
}

void test_g() {
	PostOffice po;
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));
	Postman p2;
	p2. setName("paulo");
	Postman p3;
	p3.setName("fernando");
	p3.addMail(new RegularMail("manuel", "ana","3330-454", 33));
	po.addPostman(p1);
	po.addPostman(p2);
	po.addPostman(p3);

	Postman px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"paulo");
	ASSERT_EQUAL(1,px.getMail().size());

	ASSERT_THROWS(po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"luis"), NoPostmanException);

	try {
		px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"joao");
		ASSERT_EQUAL(3,px.getMail().size());
		px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"ricardo");
	}
	catch(NoPostmanException &e) {
		ASSERT_EQUAL("ricardo", e.getName());
	}

	px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"fernando");
	ASSERT_EQUAL(2,px.getMail().size());
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a));
	s.push_back(CUTE(test_b));
	s.push_back(CUTE(test_c));
	s.push_back(CUTE(test_d));
	s.push_back(CUTE(test_e));
	s.push_back(CUTE(test_f));
	s.push_back(CUTE(test_g));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2016/2017 - Componente Individual 1 - Testes Unitarios Estudantes");
}

int main(){
    runSuite();
    return 0;
}

