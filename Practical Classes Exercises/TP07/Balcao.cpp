#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() : numPresentes((rand()%5) + 1) { }

int Cliente::getNumPresentes() const { return numPresentes;}

Balcao::Balcao(int te)
	: tempo_embrulho(te) , tempo_atual(0) , prox_chegada((rand()%20) + 1) , prox_saida(0) , clientes_atendidos(0) { }

void Balcao:: proximoEvento()
{
	if (tempo_atual == 0){		// The first time an event is procced, make something happen!
		chegada();
		tempo_atual = ((prox_saida < prox_chegada) ? prox_saida : prox_chegada);
		return;
	}

	if(prox_chegada < prox_saida){		// prox_chegada is going to happen first than prox_saida!
		chegada();
		tempo_atual = prox_chegada;
	}
	else{								// prox_saida is going to happen first than prox_chegada!
		tempo_atual = prox_saida;
		saida();
	}
}

void Balcao::chegada() {
	// Create client
	Cliente c1;

	// Randomly generate prox_chegada [1..20]
	prox_chegada = tempo_atual + (rand()%20) + 1;

	// Update prox_saida, if needed
	if (clientes.empty())
		prox_saida = tempo_atual + c1.getNumPresentes() * tempo_embrulho;

	// Insert the new client in the queue
	clientes.push(c1);

	// Print the info.
	cout << "tempo= " << tempo_atual << "\nchegou novo cliente com " << c1.getNumPresentes() << " presentes\n";
}   

void Balcao::saida()
{
	// Try to get the next client
	Cliente c;
	try{
		c = getProxCliente();
	}
	catch(FilaVazia &e){
		cout << e.getMsg();
		prox_saida = 0;
		return;
	}

	// Remove the first client in the queue
	clientes.pop();

	// Up prox_saida
	prox_saida = tempo_atual + c.getNumPresentes() * tempo_embrulho;

	// Update the number of clients that have been there
	clientes_atendidos++;

	// Print the info
	cout << "tempo= " << tempo_atual << "\nSaiu um cliente e chegou novo cliente com " << c.getNumPresentes() << " presentes\n";
}

int Balcao::getTempoAtual() const { return tempo_atual; }

unsigned int Balcao::getTamanhoFila() const { return clientes.size(); }

int Balcao::getProxChegada() const { return prox_chegada; }

ostream & operator << (ostream & out, const Balcao & b1){
	out << "Numero clientes atendidos: " << b1.getClientesAtendidos() << '\n';
	out << "Numero de clientes em espera: " << b1.getTamanhoFila() << '\n';

	return out;
}

int Balcao::getTempoEmbrulho() const { return tempo_embrulho; }

int Balcao::getProxSaida() const { return prox_saida; }

int Balcao::getClientesAtendidos() const { return clientes_atendidos; }

Cliente & Balcao::getProxCliente() {
	if (clientes.empty())			// Queue is empty
		throw (FilaVazia("Fila Vazia"));

	// Return the queue's front
	return clientes.front();
}

      
