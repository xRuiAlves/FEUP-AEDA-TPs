#include "Jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
	apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;

	for (auto it=apostas.begin() ; it!=apostas.end() ; it++){
		if (it->contem(num))
			count ++;
	}

	return count;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;

	for (auto it=apostas.begin() ; it!=apostas.end() ; it++){
		if (it->calculaCertos(sorteio) > 3)
			money.insert(*it);
	}

	return money;
}
