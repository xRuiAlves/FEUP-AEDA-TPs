#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "AfterSalesService.h"
#include "Purchase.h"
#include <math.h>

using namespace std;

// Purchase::createArticle()
void test_A_() {

	Purchase p1(12345);

	Article* a1 = p1.createArticle(11111, false, false);
	ASSERT_EQUAL(false, a1 == NULL);
	ASSERT_EQUAL(p1.getClient(), a1->getClient());
	ASSERT_EQUAL(11111, a1->getBarCode());
	ASSERT_EQUAL(false, a1->getPresent());
	ASSERT_EQUAL(false, a1->getDeliverHome());

	Article* a2 = p1.createArticle(22222, false, true);
	ASSERT_EQUAL(false, a2 == NULL);
	ASSERT_EQUAL(p1.getClient(), a2->getClient());
	ASSERT_EQUAL(22222, a2->getBarCode());
	ASSERT_EQUAL(false, a2->getPresent());
	ASSERT_EQUAL(true, a2->getDeliverHome());

	Article* a3 = p1.createArticle(33333, true, false);
	ASSERT_EQUAL(false, a3 == NULL);
	ASSERT_EQUAL(p1.getClient(), a3->getClient());
	ASSERT_EQUAL(33333, a3->getBarCode());
	ASSERT_EQUAL(true, a3->getPresent());
	ASSERT_EQUAL(false, a3->getDeliverHome());

	Article* a4 = p1.createArticle(44444, true, true);
	ASSERT_EQUAL(false, a4 == NULL);
	ASSERT_EQUAL(p1.getClient(), a4->getClient());
	ASSERT_EQUAL(44444, a4->getBarCode());
	ASSERT_EQUAL(true, a4->getPresent());
	ASSERT_EQUAL(true, a4->getDeliverHome());

}

// Purchase::putInBag()
void test_B_() {

	Purchase p1(12345);

	for(unsigned int i = 1; i < 50; i++) {
		Article* a1 = new Article(p1.getClient(), i);
		p1.putInBag(a1);
		list< stack<Article*> > bags1 = p1.getBags();
		ASSERT_EQUAL(ceil((float) i/Purchase::BAG_SIZE), bags1.size());

		list< stack<Article*> >::iterator it = bags1.begin();
		for(unsigned j = 0; j < bags1.size()-1; j++, it++) {
			ASSERT_EQUAL((unsigned int) Purchase::BAG_SIZE, it->size());
		}
		ASSERT_EQUAL((i-1)%Purchase::BAG_SIZE + 1, it->size());
	}

}

// Purchase::popPresents()
void test_C_() {

	list< stack<Article*> > bs;

	int npresents=0, counter=0;
	for(unsigned int i = 0; i < 10; i++) {
		stack<Article*> bag;
		for(unsigned int j = 0; j < Purchase::BAG_SIZE; j++) {
			Article* a = new Article(12345, counter);
			if(counter%2 == 0) {
				a->setPresent(true);
				++npresents;
			}
			++counter;
			bag.push(a);
		}
		bs.push_back(bag);
	}

	Purchase p1(12345, bs);
	vector<Article*> as = p1.popPresents();

	ASSERT_EQUAL(25, as.size());
	for(vector<Article*>::size_type i = 0; i < as.size(); i++) {
		ASSERT_EQUAL(true, as[i]->getPresent());
		ASSERT_EQUAL(0, as[i]->getBarCode()%2);
	}

	bs = p1.getBags();
	ASSERT_EQUAL(10, bs.size());
	int articles_in_stack = 3;
	counter--;
	for(list< stack<Article*> >::reverse_iterator it = bs.rbegin(); it != bs.rend(); it++) {
		ASSERT_EQUAL(articles_in_stack, it->size());
		articles_in_stack = (articles_in_stack == 2) ? 3 : 2;
		while(!it->empty()) {
			ASSERT_EQUAL(false, it->top()->getPresent());
			ASSERT_EQUAL(counter, it->top()->getBarCode());
			counter -= 2;
			it->pop();
		}
	}

}

// AfterSalesService::pickPresentsFromTable()
void test_D_() {

	vector<Article*> as1;
	as1.push_back(new Article(12345, 0));
	as1.push_back(new Article(12345, 0));
	as1.push_back(new Article(23456, 0));
	as1.push_back(new Article(12345, 0));
	as1.push_back(new Article(23456, 0));
	as1.push_back(new Article(34567, 0));
	as1.push_back(new Article(34567, 0));
	as1.push_back(new Article(12345, 0));
	as1.push_back(new Article(23456, 0));

	AfterSalesService ass(0);
	ass.dropPresentsOnTable(as1);
	as1 = ass.pickPresentsFromTable(12345);
	ASSERT_EQUAL(4, as1.size());
	for(vector<Article*>::iterator it = as1.begin(); it != as1.end(); it++) {
		ASSERT_EQUAL(12345, (*it)->getClient());
	}
	as1 = ass.getPresentsTable();
	ASSERT_EQUAL(5, as1.size());
	for(vector<Article*>::iterator it = as1.begin(); it != as1.end(); it++) {
		ASSERT_EQUAL(false, (*it)->getClient() == 12345);
	}

}

// AfterSalesService::sortArticles()
void test_E_() {

	AfterSalesService ass(0);
	Article* a;

	vector<Article*> as1;
	a = new Article(12345, 1); // client 12345, present 1
	as1.push_back(a);
	a = new Article(12345, 2); // client 12345, present 2
	as1.push_back(a);
	a = new Article(12345, 3); // client 12345, present 3
	as1.push_back(a);
	a = new Article(12345, 4); // client 12345, present 4
	as1.push_back(a);
	a = new Article(12345, 5); // client 12345, present 5
	a->setDeliverHome(true);
	as1.push_back(a);
	ass.dropPresentsOnTable(as1);

	vector<Article*> as2;
	a = new Article(23456, 6); // client 23456, present 1
	as2.push_back(a);
	a = new Article(23456, 7); // client 23456, present 2
	a->setDeliverHome(true);
	as2.push_back(a);
	ass.dropPresentsOnTable(as2);

	vector<Article*> as3;
	a = new Article(34567, 8); // client 34567, present 1
	as3.push_back(a);
	a = new Article(34567, 9); // client 34567, present 2
	as3.push_back(a);
	a = new Article(34567, 10); // client 34567, present 3
	a->setDeliverHome(true);
	as3.push_back(a);
	a = new Article(34567, 11); // client 34567, present 4
	as3.push_back(a);
	ass.dropPresentsOnTable(as3);

	ass.sortArticles();

	as1 = ass.getPresentsTable();
	ASSERT_EQUAL(11, as1.size());
	long bar_codes[] = {1,2,3,6,8,4,9,5,7,10,11};
	unsigned int i = 0;
	for(vector<Article*>::iterator it = as1.begin(); it != as1.end(); it++, i++) {
		ASSERT_EQUAL(bar_codes[i], (*it)->getBarCode());
	}

}


// AfterSalesService::enqueueArticles()
void test_F_() {

	vector<Article*> as1;
	as1.push_back(new Article(12345, 1));
	as1.push_back(new Article(12345, 2));
	as1.push_back(new Article(23456, 3));
	as1.push_back(new Article(12345, 4));
	as1.push_back(new Article(23456, 5));
	as1.push_back(new Article(34567, 6));
	as1.push_back(new Article(34567, 7));
	as1.push_back(new Article(12345, 8));
	as1.push_back(new Article(23456, 9));

	AfterSalesService ass1(7);
	ass1.dropPresentsOnTable(as1);
	ass1.enqueueArticles();
	ASSERT_EQUAL(7, ass1.getToWrap().size());
	ASSERT_EQUAL(1, ass1.getToWrap().front()->getBarCode());
	ASSERT_EQUAL(7, ass1.getToWrap().back()->getBarCode());
	ASSERT_EQUAL(2, ass1.getPresentsTable().size());
	ASSERT_EQUAL(8, ass1.getPresentsTable()[0]->getBarCode());
	ASSERT_EQUAL(9, ass1.getPresentsTable()[1]->getBarCode());

	AfterSalesService ass2(10);
	ass2.dropPresentsOnTable(as1);
	ass2.enqueueArticles();
	ASSERT_EQUAL(9, ass2.getToWrap().size());
	ASSERT_EQUAL(1, ass2.getToWrap().front()->getBarCode());
	ASSERT_EQUAL(9, ass2.getToWrap().back()->getBarCode());
	ASSERT_EQUAL(0, ass2.getPresentsTable().size());

	AfterSalesService ass3(15);
	ass3.dropPresentsOnTable(as1);
	ass3.enqueueArticles();
	ass3.dropPresentsOnTable(as1);
	ass3.enqueueArticles();
	ASSERT_EQUAL(15, ass3.getToWrap().size());
	ASSERT_EQUAL(1, ass3.getToWrap().front()->getBarCode());
	ASSERT_EQUAL(6, ass3.getToWrap().back()->getBarCode());
	ASSERT_EQUAL(3, ass3.getPresentsTable().size());
	ASSERT_EQUAL(7, ass3.getPresentsTable()[0]->getBarCode());
	ASSERT_EQUAL(8, ass3.getPresentsTable()[1]->getBarCode());
	ASSERT_EQUAL(9, ass3.getPresentsTable()[2]->getBarCode());

}

// AfterSalesService::wrapNext()
void test_G_() {

	queue<Article*> tw;
	Article* a1 = new Article(12345, 1);
	a1->setDeliverHome(true);
	tw.push(a1);
	Article* a2 = new Article(12345, 2);
	a2->setDeliverHome(false);
	tw.push(a2);

	AfterSalesService ass1(7, tw);
	a1 = ass1.wrapNext();
	ASSERT_EQUAL(true, a1 == NULL);
	ASSERT_EQUAL(1, ass1.getToWrap().size());
	ASSERT_EQUAL(2, ass1.getToWrap().front()->getBarCode());
	ASSERT_EQUAL(1, ass1.getToDeliver().size());
	ASSERT_EQUAL(1, ass1.getToDeliver().front()->getBarCode());
	a1 = ass1.wrapNext();
	ASSERT_EQUAL(false, a1 == NULL);
	ASSERT_EQUAL(2, a1->getBarCode());
	ASSERT_EQUAL(0, ass1.getToWrap().size());
	ASSERT_EQUAL(1, ass1.getToDeliver().size());
	a1 = ass1.wrapNext();
	ASSERT_EQUAL(true, a1 == NULL);

}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(test_A_));
	s.push_back(CUTE(test_B_));
	s.push_back(CUTE(test_C_));
	s.push_back(CUTE(test_D_));
	s.push_back(CUTE(test_E_));
	s.push_back(CUTE(test_F_));
	s.push_back(CUTE(test_G_));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AEDA 2016/2017 - Avaliacao CI2- 23/nov - Testes Unitarios Estudantes");
}

int main(int argc, char const *argv[]){
	runAllTests(argc,argv);
    return 0;
}

