/*
 * Caixa.cpp
 */

#include "Caixa.h"
#include <sstream>


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

unsigned Caixa::ultimoId = 1;


/* a implementar pelos estudantes */

bool Objeto::operator<(const Objeto& o1) const {
	return (peso < o1.peso);
}

bool Caixa::operator<(const Caixa& c1) const {
	return (cargaLivre > c1.cargaLivre);
}


string Caixa::imprimeConteudo() const {
	if (objetos.empty())
		return ("Caixa " + to_string(id) + " vazia!\n");

	stringstream stream;
	stream << "C" + to_string(id) + "[ ";

	STACK_OBJS aux = objetos;

	while(!aux.empty()){
		Objeto obj = aux.top();
		aux.pop();
		stream << obj << " ";
	}

	stream << "]";

	return stream.str();

}


