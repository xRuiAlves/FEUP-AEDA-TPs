/*
 * Caixa.h
 */

#ifndef SRC_CAIXA_H_
#define SRC_CAIXA_H_

#include <stack>
#include <iostream>
using namespace std;

class Objeto {
	unsigned id;
	unsigned peso;
public:
	Objeto(unsigned idObj, unsigned pesoObj);
	unsigned getID() const;
	unsigned getPeso() const;
	friend ostream& operator<<(ostream& os, Objeto obj);

	bool operator<(const Objeto& o1) const;
};


typedef stack<Objeto> STACK_OBJS;

class Caixa {
	STACK_OBJS objetos;
	unsigned id;
	unsigned capacidade;
	unsigned cargaLivre;
	static unsigned ultimoId;
public:
    Caixa(unsigned cap=10);
    unsigned getID() const;
    unsigned getCargaLivre() const;
    void addObjeto(Objeto& obj);
    static void resetID();
    unsigned getSize() const;

    string imprimeConteudo() const;
	bool operator<(const Caixa& c1) const;

};

#endif /* SRC_CAIXA_H_ */
