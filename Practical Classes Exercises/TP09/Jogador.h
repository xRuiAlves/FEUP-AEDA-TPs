#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "Aposta.h"
#include <string>

using namespace std;


//A ALTERAR!!
struct apostaHash
{
	int operator() (const Aposta & ap) const
	{
		return 0;
	}
	
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
		tabHInt t1 = ap1.getNumeros();
		tabHInt t2 = ap2.getNumeros();

		// If they have diff. sizes, they cannot be equal
		if (t1.size() != t2.size())
			return false;

		// See if the bets match!
		return (ap1.calculaCertos(t2) == t1.size());
	}
};

typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;


class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
