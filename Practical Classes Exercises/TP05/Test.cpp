#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "parque.h"


void test_a_Pesquisa() {
	ParqueEstacionamento p1(10,20);
	p1.adicionaCliente("Joao Santos");
	p1.adicionaCliente("Pedro Morais");
	p1.adicionaCliente("Rui Silva");
	p1.adicionaCliente("Susana Costa");
	p1.adicionaCliente("Maria Tavares");
	ASSERT_EQUAL(0, p1.posicaoCliente("Joao Santos"));
	ASSERT_EQUAL(4, p1.posicaoCliente("Maria Tavares"));
	ASSERT_EQUAL(1, p1.posicaoCliente("Pedro Morais"));
	ASSERT_EQUAL(-1, p1.posicaoCliente("Tiago Tavares"));
}

void test_b_UtilizacaoParque() {
	ParqueEstacionamento p1(10,20);
	p1.adicionaCliente("Joao Santos");
	p1.adicionaCliente("Pedro Morais");
	p1.adicionaCliente("Rui Silva");
	p1.adicionaCliente("Susana Costa");
	p1.adicionaCliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	ASSERT_EQUAL(3, p1.getFrequencia("Rui Silva"));
	ASSERT_EQUAL(1, p1.getFrequencia("Pedro Morais"));
	ASSERT_EQUAL(0, p1.getFrequencia("Joao Santos"));
	ASSERT_THROWS(p1.getFrequencia("Tiago Silva"), ClienteNaoExistente);
	try {
		p1.getFrequencia("Tiago Silva");
	}
	catch (ClienteNaoExistente &e) {
		cout << "Apanhou excecao. Cliente nao existente: " << e.getNome() << endl;
		ASSERT_EQUAL("Tiago Silva", e.getNome());
	}
}

void test_c_OrdenaFrequencia() {
	ParqueEstacionamento p1(10,20);
	p1.adicionaCliente("Joao Santos");
	p1.adicionaCliente("Pedro Morais");
	p1.adicionaCliente("Rui Silva");
	p1.adicionaCliente("Susana Costa");
	p1.adicionaCliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	// Joao Santos: frequencia 0
	// Pedro Morais: frequencia 1
	// Maria Tavares: frequencia 2
	// Susana Costa: frequencia 2
	// Rui Silva: frequencia 3
	p1.ordenaClientesPorFrequencia();
	InfoCartao ic1=p1.getClientes()[2];
	ASSERT_EQUAL("Susana Costa", ic1.nome);
	ASSERT_EQUAL(2, ic1.frequencia);
	InfoCartao ic2=p1.getClientes()[0];
	ASSERT_EQUAL("Rui Silva", ic2.nome);
	ASSERT_EQUAL(3, ic2.frequencia);
}

void test_d_GamasUso() {
	ParqueEstacionamento p1(10,20);
	p1.adicionaCliente("Joao Santos");
	p1.adicionaCliente("Pedro Morais");
	p1.adicionaCliente("Rui Silva");
	p1.adicionaCliente("Susana Costa");
	p1.adicionaCliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	// Joao Santos: frequencia 0
	// Pedro Morais: frequencia 1
	// Maria Tavares: frequencia 2
	// Susana Costa: frequencia 2
	// Rui Silva: frequencia 3
	vector<string> clientes = p1.clientesGamaUso(2,3);
	ASSERT_EQUAL(3,clientes.size());
	ASSERT_EQUAL("Rui Silva", clientes[0]);
	ASSERT_EQUAL("Maria Tavares", clientes[1]);
	ASSERT_EQUAL("Susana Costa", clientes[2]);
}


void test_e_OrdenaNome() {
	ParqueEstacionamento p1(10,20);
	p1.adicionaCliente("Joao Santos");
	p1.adicionaCliente("Pedro Morais");
	p1.adicionaCliente("Rui Silva");
	p1.adicionaCliente("Susana Costa");
	p1.adicionaCliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	p1.ordenaClientesPorNome();
	InfoCartao ic1=p1.getClientes()[2];
	ASSERT_EQUAL("Pedro Morais", ic1.nome);
	InfoCartao ic2=p1.getClientes()[0];
	ASSERT_EQUAL("Joao Santos", ic2.nome);
}

void test_f_InfoClientes() {
	ParqueEstacionamento p1(10,20);
	p1.adicionaCliente("Joao Santos");
	p1.adicionaCliente("Pedro Morais");
	p1.adicionaCliente("Rui Silva");
	p1.adicionaCliente("Susana Costa");
	p1.adicionaCliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.entrar("Rui Silva");
	p1.entrar("Susana Costa");
	ASSERTM("Este teste nunca falha! VERIFICAR informação escrita no monitor", true);
	cout << p1;
	InfoCartao ic=p1.getClienteAtPos(2);
	ASSERT_EQUAL("Rui Silva", ic.nome);
	ASSERT_THROWS(p1.getClienteAtPos(6), PosicaoNaoExistente);
	try {
		p1.getClienteAtPos(6);
	}
	catch (PosicaoNaoExistente &e) {
		ASSERTM("Este teste nunca falha. Verifique no monitor a informacao", true);
		cout << "Apanhou excecao. Posicao nao existente:" << e.getValor() << endl;
		ASSERT_EQUAL(6, e.getValor());
	}
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_Pesquisa));
	s.push_back(CUTE(test_b_UtilizacaoParque));
	s.push_back(CUTE(test_c_OrdenaFrequencia));
	s.push_back(CUTE(test_d_GamasUso));
	s.push_back(CUTE(test_e_OrdenaNome));
	s.push_back(CUTE(test_f_InfoClientes));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2017/2018 - Aula Pratica 5");
}

int main(){

    runSuite();
    return 0;
}



