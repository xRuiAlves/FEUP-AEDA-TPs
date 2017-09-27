#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <string>
#include "Parque.h"


 void test_1a_AbrirParque() {
	ParqueEstacionamento p1(4, 6);
	// Testa se o parque foi aberto com a lota��o indicada
	ASSERT_EQUAL(4, p1.getNumLugares());
	// Testa se o parque foi aberto com o n�mero m�ximo de clientes indicado
	ASSERT_EQUAL(6, p1.getNumMaximoClientes());
}


void test_1b_AdicionarCliente() {
	ParqueEstacionamento p1(3, 5);
	// Testa se deixa adicionar um novo cliente
	ASSERT_EQUAL(true, p1.adicionaCliente("Joao"));
	p1.adicionaCliente("Antonio");
	p1.adicionaCliente("Rui");
	p1.adicionaCliente("Maria");
	p1.adicionaCliente("Clara");
	// Testa se recusa novo cliente quando numero m�ximo de clientes foi atingido
	ASSERT_EQUAL(false, p1.adicionaCliente("Paula"));
	// Testa se retorna a posi��o correcta do cliente
	ASSERT_EQUAL(1, p1.posicaoCliente("Antonio"));
	// Testa se retorna -1 caso o cliente n�o exista
	ASSERT_EQUAL(-1, p1.posicaoCliente("Joana"));
}


void test_1c_EntrarParque() {
	ParqueEstacionamento p1(3, 5);
	p1.adicionaCliente("Joao");
	p1.adicionaCliente("Maria");
	p1.adicionaCliente("Antonio");
	p1.adicionaCliente("Rui");
	// Testa se deixa entrar no parque um cliente existente
	ASSERT_EQUAL(true, p1.entrar("Maria"));
	// Testa se n�o deixa entrar no parque um cliente que n�o existe
	ASSERT_EQUAL(false, p1.entrar("Paula"));
	// Testa se n�o dexia entrar em cliente que j� l� est�
	ASSERT_EQUAL(false, p1.entrar("Maria"));
	p1.entrar("Joao");
	p1.entrar("Antonio");
	// Testa se n�o deixa entrar quando a lota��o est� completa
	ASSERT_EQUAL(false, p1.entrar("Rui"));
}


void test_1d_RetirarCliente() {
	ParqueEstacionamento p1(3, 5);
	p1.adicionaCliente("Joao");
	p1.adicionaCliente("Maria");
	p1.adicionaCliente("Antonio");
	p1.entrar("Maria");
	// Testa se n�o deixa remover cliente que est� dentro do parque
	ASSERT_EQUAL(false, p1.retiraCliente("Maria"));
	// Testa se deixa remover cliente que est� fora do parque
	ASSERT_EQUAL(true, p1.retiraCliente("Antonio"));
	// Testa se nao deixa remover cliente que nao existe
	ASSERT_EQUAL(false, p1.retiraCliente("Ana"));
}


void test_1e_SairParque() {
	ParqueEstacionamento p1(3, 5);
	p1.adicionaCliente("Joao");
	p1.adicionaCliente("Maria");
	p1.adicionaCliente("Rui");
	p1.entrar("Maria");
	p1.entrar("Joao");
	p1.entrar("Rui");
	// Testa se um cliente estacionado no parque, sai.
	ASSERT_EQUAL(true, p1.sair("Maria"));
	// Testa se n�o deixa sair um cliente que n�o est� estacionado.
	ASSERT_EQUAL(false, p1.sair("Maria"));
	// Testa se n�o deixa sair um cliente que n�o existe.
	ASSERT_EQUAL(false, p1.sair("Antonio"));
}


void test_1f_LugaresLotacaoParque() {
	ParqueEstacionamento p1(3, 5);
	p1.adicionaCliente("Joao");
	p1.adicionaCliente("Maria");
	p1.adicionaCliente("Antonio");
	p1.entrar("Maria");
	p1.entrar("Antonio");
	// Testa se Lotacao do parque est� correcta
	ASSERT_EQUAL(3, p1.getNumLugares());
	// Testa se o numero de viaturas presentes no parque est� correcto
	ASSERT_EQUAL(2, p1.getNumLugaresOcupados());
	// Testa se o o n�mero de clientes registados no parque est� correcto
	ASSERT_EQUAL(3, p1.getNumClientesAtuais());
}


void test_1g_OperadorSoma() {
	ParqueEstacionamento p1(5, 8);
	ParqueEstacionamento p2(10, 18);
	p1.adicionaCliente("Joao");
	p1.adicionaCliente("Maria");
	p1.adicionaCliente("Antonio");
	p1.adicionaCliente("Rui");
	p2.adicionaCliente("Rita");
	p2.adicionaCliente("Vasco");

	p1 += p2;
	// Testa se o o n�mero de clientes registados no parque est� correcto
	ASSERT_EQUAL(6, p1.getNumClientesAtuais());

	ParqueEstacionamento p3(10, 18);
	p3.adicionaCliente("Pedro");
	p3.adicionaCliente("Ana");
	p3.adicionaCliente("Carlos");

	p1 += p3;
	// Testa se o o n�mero de clientes registados no parque est� correcto
	ASSERT_EQUAL(8, p1.getNumClientesAtuais());

	// Testa se retorna a posi��o correcta do cliente
	ASSERT_EQUAL(4, p1.posicaoCliente("Rita"));
	ASSERT_EQUAL(-1, p1.posicaoCliente("Carlos"));
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_1a_AbrirParque));
	s.push_back(CUTE(test_1b_AdicionarCliente));
	s.push_back(CUTE(test_1c_EntrarParque));
	s.push_back(CUTE(test_1d_RetirarCliente));
	s.push_back(CUTE(test_1e_SairParque));
	s.push_back(CUTE(test_1f_LugaresLotacaoParque));
	s.push_back(CUTE(test_1g_OperadorSoma));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s,"AEDA 2017/2018 - Aula Pratica 1" );
}


int main(){
    runSuite();
}



