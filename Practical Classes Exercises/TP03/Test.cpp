#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <string>
#include "grafo.h"

void test_a_ConstrutorNosArestas() {
	Grafo<string,int> g;
	ASSERT_EQUAL(0, g.numNos());
	ASSERT_EQUAL(0, g.numArestas());
}

void test_b_InserirNo() {
	Grafo<string,int> f;
	f.inserirNo("A");
	f.inserirNo("B");
	f.inserirNo("C");
	ASSERT_EQUAL(3, f.numNos());

	ASSERT_THROWS(f.inserirNo("B"), NoRepetido<string>);
	try {
		f.inserirNo("B");
	}
	catch (NoRepetido<string> &e) {
		ostringstream ostr;
		ostr << e;
		string str = "No repetido: B";
		ASSERT_EQUAL(str, ostr.str());
	}
	f.inserirNo("D");
	f.inserirNo("E");
	ASSERT_EQUAL(5, f.numNos());
}

void test_c_InserirAresta() {
	Grafo<string,int> f;
	f.inserirNo("A");
	f.inserirNo("B");
	f.inserirNo("C");
	f.inserirNo("D");
	f.inserirNo("E");
	f.inserirAresta("A", "B", 5);
	f.inserirAresta("A", "C", 8);
	f.inserirAresta("B", "D", 9);
	f.inserirAresta("C", "D", 3);
	f.inserirAresta("C", "E", 4);
	f.inserirAresta("D", "E", 2);
	f.inserirAresta("D", "B", 11);
	ASSERT_EQUAL(7, f.numArestas());
	ASSERT_THROWS(f.inserirAresta("D", "B", 12), ArestaRepetida<string>);
	try {
		f.inserirAresta("D", "B", 12);
	}
	catch (ArestaRepetida<string> &e) {
		ostringstream ostr;
		ostr << e;
		string str = "Aresta repetida: D , B";
		ASSERT_EQUAL(str, ostr.str());
	}

	ASSERT_THROWS(f.inserirAresta("F", "B", 11), NoInexistente<string>);
	try {
		f.inserirAresta("F", "B", 11);
	}
	catch (NoInexistente<string> &e) {
		ostringstream ostr1;
		ostr1 << e;
		string str1 = "No inexistente: F";
		ASSERT_EQUAL(str1, ostr1.str());
	}

	ASSERT_EQUAL(7, f.numArestas());
}

void test_d_ValorAresta() {
	Grafo<string,int> f;
	f.inserirNo("A");
	f.inserirNo("B");
	f.inserirNo("C");
	f.inserirNo("D");
	f.inserirNo("E");
	f.inserirAresta("A", "B", 5);
	f.inserirAresta("A", "C", 8);
	f.inserirAresta("B", "D", 9);
	f.inserirAresta("C", "D", 3);
	f.inserirAresta("C", "E", 4);
	f.inserirAresta("D", "E", 2);
	f.inserirAresta("D", "B", 11);
	f.valorAresta("A", "B") = 15;
	ASSERT_EQUAL(15, f.valorAresta("A", "B"));
	ASSERT_THROWS(f.valorAresta("A", "A"), ArestaInexistente<string>);
	try {
		f.valorAresta("A", "A");
	}
	catch (ArestaInexistente<string> &e) {
		//cout << "Apanhou excecao " << e << endl;
		ostringstream ostr;
		ostr << e;
		string str = "Aresta inexistente: A , A";
		ASSERT_EQUAL(str, ostr.str());
	}

	ASSERT_THROWS(f.valorAresta("F", "B"), NoInexistente<string>);
	try {
		f.valorAresta("F", "B");
	}
	catch (NoInexistente<string> &e) {
		//cout << "Apanhou excecao " << e << endl;
		ostringstream ostr1;
		ostr1 << e;
		string str1 = "No inexistente: F";
		ASSERT_EQUAL(str1, ostr1.str());
	}
}

void test_e_EliminarAresta() {
	Grafo<string,int> f;
	f.inserirNo("A");
	f.inserirNo("B");
	f.inserirNo("C");
	f.inserirNo("D");
	f.inserirNo("E");
	f.inserirAresta("A", "B", 5);
	f.inserirAresta("A", "C", 8);
	f.inserirAresta("B", "D", 9);
	f.inserirAresta("C", "D", 3);
	f.inserirAresta("C", "E", 4);
	f.inserirAresta("D", "E", 2);
	f.inserirAresta("D", "B", 11);
	ASSERT_EQUAL(7, f.numArestas());
	f.eliminarAresta("D", "E");
	ASSERT_EQUAL(6, f.numArestas());
	ASSERT_THROWS(f.eliminarAresta("D", "F"), NoInexistente<string>);
	try {
		f.eliminarAresta("A", "A");
	}
	catch (ArestaInexistente<string> &e) {
		//cout << "Apanhou excecao " << e << endl;
		ostringstream ostr;
		ostr << e;
		string str = "Aresta inexistente: A , A";
		ASSERT_EQUAL(str, ostr.str());
	}

	ASSERT_THROWS(f.eliminarAresta("F", "B"), NoInexistente<string>);
	try {
		f.eliminarAresta("F", "B");
	}
	catch (NoInexistente<string> &e) {
		//cout << "Apanhou excecao " << e << endl;
		ostringstream ostr1;
		ostr1 << e;
		string str1 = "No inexistente: F";
		ASSERT_EQUAL(str1, ostr1.str());
	}

	ASSERT_EQUAL(6, f.numArestas());
}

void test_f_ImprimirGrafo() {
	Grafo<string,int> f;
	f.inserirNo("A");
	f.inserirNo("B");
	f.inserirNo("C");
	f.inserirNo("D");
	f.inserirNo("E");
	f.inserirAresta("A", "B", 5);
	f.inserirAresta("A", "C", 8);
	f.inserirAresta("B", "D", 9);
	f.inserirAresta("C", "D", 3);
	f.inserirAresta("C", "E", 4);
	f.inserirAresta("D", "E", 2);
	f.inserirAresta("D", "B", 11);
	ASSERT_EQUAL(7, f.numArestas());
	ostringstream ostr;
	f.imprimir(ostr);
	string str = "( A[ B 5] [ C 8] ) ( B[ D 9] ) ( C[ D 3] [ E 4] ) ( D[ E 2] [ B 11] ) ( E) ";
	cout << str.c_str()<<endl;
	ASSERT_EQUAL(str, ostr.str());

}

void test_g_OperadorSaida() {
	Grafo<string,int> f;
	f.inserirNo("A");
	f.inserirNo("B");
	f.inserirNo("C");
	f.inserirNo("D");
	f.inserirNo("E");
	f.inserirAresta("A", "B", 5);
	f.inserirAresta("A", "C", 8);
	f.inserirAresta("B", "D", 9);
	f.inserirAresta("C", "D", 3);
	f.inserirAresta("C", "E", 4);
	f.inserirAresta("D", "E", 2);
	f.inserirAresta("D", "B", 11);
	ASSERT_EQUAL(7, f.numArestas());
	ostringstream ostr;
	ostr << f;
	string str = "( A[ B 5] [ C 8] ) ( B[ D 9] ) ( C[ D 3] [ E 4] ) ( D[ E 2] [ B 11] ) ( E) ";
	ASSERT_EQUAL(str, ostr.str());
}

void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_ConstrutorNosArestas));
	s.push_back(CUTE(test_b_InserirNo));
	s.push_back(CUTE(test_c_InserirAresta));
	s.push_back(CUTE(test_d_ValorAresta));
	s.push_back(CUTE(test_e_EliminarAresta));
	s.push_back(CUTE(test_f_ImprimirGrafo));
	s.push_back(CUTE(test_g_OperadorSaida));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2017/2018 - Aula Pratica 3");
}


int main(){
    runSuite();
    return 0;
}



