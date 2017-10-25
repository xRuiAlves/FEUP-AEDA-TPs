#ifndef PARQUE_H_
#define PARQUE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InfoCartao {
public:
	string nome;
	bool presente;
	int frequencia;
	bool operator == (const InfoCartao &ic1) const{ return (frequencia == ic1.frequencia); }
	bool operator < (const InfoCartao &ic1) const{
		if (frequencia == ic1.frequencia){
			return (nome < ic1.nome);
		}
		else
			return (ic1.frequencia < frequencia);
	}
};

class ParqueEstacionamento {
	unsigned int vagas;
	const unsigned int lotacao;
	vector<InfoCartao> clientes;
	unsigned int numClientes;
	const unsigned int numMaximoClientes;
public:
	ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli);
	~ParqueEstacionamento();
	vector<InfoCartao> getClientes() const;
	bool adicionaCliente(const string & nome);
	bool retiraCliente(const string & nome);
	bool entrar(const string & nome);
	bool sair(const string & nome);
	unsigned int getNumLugares() const;
	unsigned int getNumLugaresOcupados() const;
	int posicaoCliente(const string & nome) const;
	friend ostream & operator<<(ostream & os, const ParqueEstacionamento & pe);
	int getFrequencia(const string &nome) const;
	InfoCartao getClienteAtPos(vector<InfoCartao>::size_type p) const;
	void ordenaClientesPorFrequencia();
	void ordenaClientesPorNome();
	vector<string> clientesGamaUso(int n1, int n2);
};

class ClienteNaoExistente{
private:
	string nome;
public:
	ClienteNaoExistente(const string &nome) { this->nome = nome; }
	string getNome(){ return nome; }
};

class PosicaoNaoExistente{
private:
	int valor;
public:
	PosicaoNaoExistente(int valor) { this->valor = valor; }
	int getValor(){ return valor; }
};

#endif /*PARQUE_H_*/
