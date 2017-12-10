#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	// Find if "num" is contained in "numeros"
	std::unordered_set<unsigned>::const_iterator it = numeros.find(num);

	// Return true if it's contained , false otherwise
	return (it != numeros.end());
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	// Clear numeros
	numeros.clear();

	for(unsigned int i=0 ; i<valores.size() ; i++){
		// Check if we already got to the bet requested size
		if (numeros.size() == n)
			break;

		// Add the number to the bet, if it is not there yet
		if (!contem(valores.at(i))){
			numeros.insert(valores.at(i));
		}
	}
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	unsigned certos = 0;

	// Search if they are all contained
	for(auto it=sorteio.begin() ; it!=sorteio.end() ; it++){
		if(contem(*it)){
			certos ++;
		}
	}

	return certos;
}




