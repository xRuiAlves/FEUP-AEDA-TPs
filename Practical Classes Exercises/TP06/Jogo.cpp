/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <sstream>
using namespace std;


unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  int pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{}

Jogo::Jogo(list<Crianca>& lc2)
{
	criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return criancas;
}


string Jogo::escreve() const
{
	ostringstream oss;
	for (list<Crianca>::const_iterator it = criancas.begin() ; it != criancas.end() ; it++){
		oss << it->escreve() << '\n';
	}

	return oss.str();
}


Crianca& Jogo::perdeJogo(string frase)
{
	unsigned int numeroPalavras = numPalavras(frase);
	unsigned int numAdvances;
	list<Crianca>::iterator it;

	// Repeat until there is only one child left -> the losing one
	while (criancas.size() > 1){
		numAdvances = (numeroPalavras-1)%criancas.size();
		it = criancas.begin();
		while(numAdvances>0){
			it++;
			numAdvances--;
		}
		criancas.erase(it);
	}

	return criancas.front();
}


list<Crianca>& Jogo::inverte()
{
	criancas.reverse();
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	// a alterar
	list<Crianca> criancasRemovidas;
	list<Crianca>::iterator itAux;

	for (list<Crianca>::iterator it = criancas.begin() ; it != criancas.end() ; ){
		if(it->getIdade() > id){				// Age superior to ID
			criancasRemovidas.push_back(*it);	// Add it to removed children list
			itAux = it;							// Preserve the iterator, so it doesn't get lost on erasing
			itAux++;
			criancasRemovidas.erase(it);
			it=itAux;							// Assign to it the correct iterator value
		}
		else
			it++;
	}

	return criancasRemovidas;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	criancas = l1;
}


bool Jogo::operator==(Jogo& j2)
{
	list<Crianca> criancasJogo2 = j2.getCriancasJogo();

	if(criancas.size() != criancasJogo2.size())	// Different size --> Can't be equal
		return false;

	list<Crianca>::iterator it1 = criancas.begin();
	list<Crianca>::iterator it2 = criancasJogo2.begin();

	while( it1 != criancas.end()){
		if ( !((*it1) == (*it2)) )		// If children are different return false
			return false;

		// Increment the iterators;
		it1++;
		it2++;
	}

	// All equal!
	return true;
}


list<Crianca> Jogo::baralha() const
{
	Crianca temp;
	list<Crianca> criancasBaralhadas = criancas;
	list<Crianca>::iterator it;
	list<Crianca>::iterator itAux;
	list<Crianca>::iterator itF = criancasBaralhadas.end();
	itF--;

	int numOfIterations = (rand()%6) + 5;	// Random number of iteration from 5 to 10

	for (unsigned int i=0 ; i<numOfIterations ; i++){
		for (it = criancasBaralhadas.begin() ; it != itF ; it++){
			if ( (rand()%2) == 0 ){ //50% of times
				// Swap children
				itAux = it;
				itAux++;
				temp = (*it);
				(*it) = (*itAux);
				(*itAux) = temp;
			}
		}
	}


	return criancasBaralhadas;
}
