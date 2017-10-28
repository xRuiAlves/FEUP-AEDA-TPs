/*
 * Escritorio.h
 *
 *  Created on: Oct 4, 2015
 *      Author: arocha
 */

#ifndef ESCRITORIO_H_
#define ESCRITORIO_H_

#include <vector>
#include <string>
using namespace std;


class Documento {
  int numPaginas;
  float pPreto, pAmarelo;
public:
   Documento(int nPag, float pP, float pA);
   ~Documento();
   int getNumPaginas() const;
   float getPercentagemPreto() const;
   float getPercentagemAmarelo() const;
};

Documento & operator+(const Documento &d1, const Documento &d2);

class Impressora {
protected:
  const string codigo;
  const int ano;
  vector<Documento> docsImpressos;
public:
	Impressora(string cod, int a);
	virtual ~Impressora();
	string getCodigo() const;
	int getAno() const;
	vector<Documento> getDocumentosImpressos() const;
	virtual bool imprime(Documento doc1) = 0;
	virtual int getNumPaginasImprimir() const = 0;
	virtual string getTipo() const = 0;
};

class ImpressoraPB: public Impressora {
  int numPagImprimir;
public:
   ImpressoraPB(string cod, int a, int toner);
   int getNumPaginasImprimir() const;
   bool imprime(Documento doc1);
   string getTipo() const { return "PB"; }
};

class ImpressoraCores: public Impressora {
  float numPagImprimirPreto;
  float numPagImprimirAmarelo;
public:
   ImpressoraCores(string cod, int a, int toner);
   int getNumPaginasImprimir() const;
   bool imprime(Documento doc1);
   string getTipo() const { return "Cores"; }
};

class Funcionario {
  string codigo;
  vector<Impressora *> impressoras;
public:
  Funcionario(string cod);
  ~Funcionario();
  string getCodigo() const;
  void adicionaImpressora(Impressora *i1);
  vector<Impressora *> getImpressoras() const;
	// �
};

class Escritorio {
  vector<Impressora *> impressoras;
  vector<Funcionario> funcionarios;
public:
  Escritorio();
  ~Escritorio();
  void adicionaImpressora(Impressora *i1);
  void adicionaFuncionario(Funcionario f1);
  vector<Impressora *> getImpressoras() const;
  int numImpressorasSemResponsavel() const;
  vector<Impressora *> retiraImpressoras(int ano1);
  Impressora * imprimeDoc(Documento doc1) const;
  vector<Impressora *> tonerBaixo() const;
  string operator()(const string & codigo) const;
};






#endif /* ESCRITORIO_H_ */
