#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "StackExt.h"
#include "Balcao.h"
#include "exceptions.h"
#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include "performance.h"

using namespace std;


void test_1_StackExt_FindMin() {
//	StackExt<int> s1;
//	// Teste ao empty()
//	ASSERT_EQUAL(true, s1.empty());
//	// Teste ao push() e top()
// 	s1.push(6);
//	s1.push(4);
//	s1.push(7);
//	s1.push(2);
//	s1.push(5);
//	ASSERT_EQUAL(5, s1.top());
//	// Teste ao pop() e top()
//	s1.pop();
//	s1.pop();
//	ASSERT_EQUAL(7, s1.top());
//
//	// Testar findMin()
//	ASSERT_EQUAL(4, s1.findMin());
//	s1.push(3);
//	s1.push(2);
//	ASSERT_EQUAL(2, s1.findMin());
//
//	// Agora testar findMin() para saber se executa em tempo constante
//	// preparar Stack removendo todos os elementos
//	s1.pop();
//	s1.pop();
//	s1.pop();
//	s1.pop();
//	s1.pop();
//	ASSERT_EQUAL(true, s1.empty());
//
//	// preparar dados para teste TEMPO EXECUCAO
//	int size = 9;
//	unsigned int elapsedTime[size];
//	int x_el[] = {5000000,6000000,7000000,8000000,9000000,10000000,11000000,12000000,13000000};
//	int random_int;
//	ticks tstart;
//	ticks tend;
//
//	for (int i = 0; i < size; i++) {
//		// encher stack com numero de elementos indicados pelo x_el
//		for (int z = 1; z <= x_el[i]; z++) {
//			random_int = rand() % 1000 + 1;
//			s1.push(random_int);
//		}
//		// agora contar tempo invocando o metodo
//		tstart = getticks(); // inicio contagem ticks
//		s1.findMin(); // este ee constante
//		tend = getticks(); // fim da contagem ticks
//		// colocar valor no array de elapsedTime
//		elapsedTime[i] = getElapsed(tend,tstart);
//		// retirar da stack os numeros la colocados
//		for (int z = 1; z <= x_el[i]; z++) {
//			s1.pop();
//		}
//	}
//	// Verifica se executa em TEMPO CONSTANTE
//	// NOTA: o parametro com valor 10 significa que sao considerados constantes valores no intervalo [-10, 10]
//	ASSERT_EQUAL(true, isConstant(elapsedTime, size, 10));
}

void test_2a_ConstructorCliente(){
    srand(time(NULL));
    Cliente c;
    ASSERT((c.getNumPresentes()>0 && c.getNumPresentes()<=5));
}

void test_2b_ConstructorBalcao(){
    srand(time(NULL));
    Balcao b;
    ASSERT_EQUAL(0, b.getClientesAtendidos());
    ASSERT_EQUAL(2, b.getTempoEmbrulho());
    ASSERT_EQUAL(0, b.getTempoAtual());
    ASSERT((b.getProxChegada()>0 && b.getProxChegada() <= 20));
    ASSERT_EQUAL(0, b.getProxSaida());
	ASSERT_THROWS(b.getProxCliente(), FilaVazia);
	try {
		b.getProxCliente();
	}
	catch (FilaVazia &e) {
		cout << "Apanhou excecao. FilaVazia: " << e.getMsg() << endl;
		ASSERT_EQUAL("Fila Vazia", e.getMsg());
	}
}

void test_2c_ChegadaBalcao(){
    Balcao b;
    ASSERTM("Este teste nao falha. Verifique se na consola aparece (x varia entre 1 e 5): tempo= 0\nchegou novo cliente com x presentes", true);
    b.chegada();
    //
    // Agora que se invocou o metodo chegada, verifica-se se fez correctamente alguns dos requisitos
    //
    ASSERT_EQUAL(0, b.getTempoAtual());
    ASSERT((b.getProxCliente().getNumPresentes()>0 && b.getProxCliente().getNumPresentes()<=5));
    ASSERT((b.getProxChegada()>0 && b.getProxChegada() <= 20));
    ASSERT((b.getProxSaida()>=2 && b.getProxSaida() <= 10)); // entre [0+1*2, 0+5*2]
}

void test_2d_SaidaBalcao(){
    Balcao b;
    // Simula a chegada de um cliente
    b.chegada();
    b.chegada();

    b.saida();
    // Agora que se invocou o metodo saida, verifica se fez corretamente alguns dos requisitos
    ASSERT_EQUAL(0, b.getTempoAtual());
    ASSERT((b.getProxSaida()>=2 && b.getProxSaida() <= 10)); // entre [0+1*2, 0+5*2]
    b.saida();
    try {
		b.getProxCliente();
	}
	catch (FilaVazia &e) {
		cout << "Apanhou excecao. FilaVazia: " << e.getMsg() << endl;
		ASSERT_EQUAL("Fila Vazia", e.getMsg());
	}
}

void test_2e_ProximoEvento(){
	ASSERTM("Este teste nao falha. Verifique na consola os valores", true);
	Balcao b;
    b.proximoEvento();
    cout << "01: " << "Clientes atendidos: " << b.getClientesAtendidos() << " Tempo actual: " << b.getTempoAtual() << " Prox chegada: " << b.getProxChegada() << " Prox Saida: " << b.getProxSaida() << endl;
    b.proximoEvento();
    cout << "02: " << "Clientes atendidos: " << b.getClientesAtendidos() << " Tempo actual: " << b.getTempoAtual() << " Prox chegada: " << b.getProxChegada() << " Prox Saida: " << b.getProxSaida() << endl;
    b.proximoEvento();
    cout << "03: " << "Clientes atendidos: " << b.getClientesAtendidos() << " Tempo actual: " << b.getTempoAtual() << " Prox chegada: " << b.getProxChegada() << " Prox Saida: " << b.getProxSaida() << endl;
    b.proximoEvento();
    cout << "04: " << "Clientes atendidos: " << b.getClientesAtendidos() << " Tempo actual: " << b.getTempoAtual() << " Prox chegada: " << b.getProxChegada() << " Prox Saida: " << b.getProxSaida() << endl;
}

void test_2f_Operador() {
    ASSERTM("Este teste nao falha. Verifique na consola os valores", true);
	Balcao b;
    b.proximoEvento();
    b.proximoEvento();
    b.proximoEvento();
    b.proximoEvento();
    cout << b << endl;
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_1_StackExt_FindMin));
	s.push_back(CUTE(test_2a_ConstructorCliente));
	s.push_back(CUTE(test_2b_ConstructorBalcao));
	s.push_back(CUTE(test_2c_ChegadaBalcao));
	s.push_back(CUTE(test_2d_SaidaBalcao));
	s.push_back(CUTE(test_2e_ProximoEvento));
	s.push_back(CUTE(test_2f_Operador));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2017/2018 - Aula Pratica 7");
}

int main(){
    runSuite();
    return 0;
}

