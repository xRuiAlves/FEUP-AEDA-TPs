#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].frequencia++;
	clientes[pos].presente = true;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}


int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	for (unsigned int i=0 ; i<clientes.size() ; i++){
		if(clientes.at(i).nome == nome){
			return i;		// Client was found!
		}
	}

	// Client not found
	return -1;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const{
	int index = posicaoCliente(nome);

	if(index == -1){	// Client not found
		throw (ClienteNaoExistente(nome));
	}
	else{				// Client found
		return clientes.at(index).frequencia;
	}
}

void ParqueEstacionamento::ordenaClientesPorFrequencia(){
	insertionSort(clientes);	// Sort the clients
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2){
	// Sort clients by frequency
	ordenaClientesPorFrequencia();

	vector<string> clientesGama;

	// Get clientes with n1 <= freq <= n2
	for (unsigned int i=0 ; i<clientes.size() ; i++){
		if((clientes.at(i).frequencia >= n1) && (clientes.at(i).frequencia <= n2)){
			clientesGama.push_back(clientes.at(i).nome);
		}
		else
			break;	// Sorted by freq, so break after getting one out of range
	}

	return clientesGama;
}

// Auxiliary functions for sorting clients by name
bool compararClientesNome(const InfoCartao &ic1, const InfoCartao &ic2){
	return (ic1.nome < ic2.nome);
}

void ParqueEstacionamento::ordenaClientesPorNome(){
	sort(clientes.begin(),clientes.end(),compararClientesNome);
}

ostream & operator<<(ostream & os, const ParqueEstacionamento & pe){
	vector<InfoCartao> clientes = pe.getClientes();	// Get the clients

	// Print'em all
	for(unsigned int i=0 ; i<clientes.size() ; i++){
		os << clientes.at(i).nome << " - " << ((clientes.at(i).presente) ? "Presentes" : "Nao presente") << " - " << clientes.at(i).frequencia << endl;
	}

	return os;
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const{
	if(p >= clientes.size()){
		throw (PosicaoNaoExistente(p));
	}
	else {
		return clientes.at(p);
	}
}
