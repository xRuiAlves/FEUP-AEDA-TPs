#ifndef APOSTA_H_
#define APOSTA_H_

#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

typedef unordered_set<unsigned> tabHInt;


class Aposta
{
	tabHInt numeros;
public:
	Aposta() {};
	void geraAposta(const vector<unsigned> &valores, unsigned n=6);
	bool contem(unsigned num) const;
	unsigned calculaCertos(const tabHInt & sorteio) const;
	tabHInt getNumeros() const { return numeros; }
};	


#endif /*APOSTA_H_*/
