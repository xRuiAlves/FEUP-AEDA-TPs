/*
 * Crianca.cpp
 *
 */

#include "Crianca.h"

Crianca::Crianca(): nome(""), idade(0)
{}

Crianca::Crianca(string nm, unsigned id): nome(nm), idade(id)
{}

Crianca::Crianca(const Crianca& c1)
{
	this->nome = c1.nome;
	this->idade = c1.idade;
}

string Crianca::getNome() const
{
	return this->nome;
}

unsigned Crianca::getIdade() const
{
	return this->idade;
}

bool Crianca::operator==(const Crianca& c2) const
{
	return( this->nome == c2.nome && this->idade == c2.idade);
}


string Crianca::escreve() const
{
	stringstream oss;
	oss << nome << " : " << idade;
	return oss.str();
}


