#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli){
	vagas = lotacao;
}

unsigned int ParqueEstacionamento::getNumLugares() const{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
	return numMaximoClientes;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	return (lotacao - vagas);
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size();
}

int ParqueEstacionamento::posicaoCliente(const string& nome) const{
	for(int i=0 ; i<clientes.size() ; i++){
		if(nome==clientes.at(i).nome)
			return i;		// cliente foi encontrado!
	}

	return -1; // cliente nao foi encontrado
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){
	if(clientes.size()<numMaximoClientes){
		clientes.push_back(InfoCartao(nome,false));
		return true;
	}
	else {
		return false;
	}
}

bool ParqueEstacionamento::entrar(const string & nome){
	int posCliente = posicaoCliente(nome);
	if (posCliente == -1)	// cliente nao foi encontrado
		return false;
	else if(clientes.at(posCliente).presente==true)	// cliente encontra-se já estacionado
		return false;
	else if(vagas==0)	// o parque já está cheio
		return false;
	else{
		vagas--;	// menos uma vaga no parque
		clientes.at(posCliente).presente=true;	// o cliente encontra-se agora estacionado
		return true;
	}
}

bool ParqueEstacionamento::retiraCliente(const string & nome){
	int posCliente = posicaoCliente(nome);
	if (posCliente == -1)	// cliente nao foi encontrado
		return false;
	else if(clientes.at(posCliente).presente==true)	// cliente encontra-se estacionado, nao pode ser removido
		return false;
	else{
		clientes.erase(clientes.begin()+posCliente);	// remove o cliente do vetor de clientes
		return true;
	}
}

bool ParqueEstacionamento::sair(const string & nome){
	int posCliente = posicaoCliente(nome);
	if (posCliente == -1)	// cliente nao foi encontrado
		return false;
	else if(clientes.at(posCliente).presente==false)	// cliente não está estacionado no parque
		return false;
	else{
		vagas++;	// mais uma vaga no parque!
		clientes.at(posCliente).presente = false;	// o cliente encontra-se agora fora do parque
		return true;
	}
}

const ParqueEstacionamento& ParqueEstacionamento::operator+=(const ParqueEstacionamento & p2){
	
	for (int i=0 ; i<p2.clientes.size() ; i++)
		adicionaCliente(p2.clientes.at(i).nome);

	return *this;
}


