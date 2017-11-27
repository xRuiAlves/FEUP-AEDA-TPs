#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	return (palavra < ps1.palavra);
}


bool PalavraSignificado::operator == (const PalavraSignificado &ps1) const
{
	return (palavra == ps1.palavra);
}


void Dicionario::lerDicionario(ifstream &fich)
{
	string palavra, significado;

	while (getline(fich, palavra)){	// Get the word

		getline(fich, significado);	// Get the meaning

		// Remove the '\r' character from each string -> .txt files suck :(
		if(palavra.at(palavra.size()-1) == '\r')
			palavra.erase(palavra.size()-1);
		if(significado.at(significado.size()-1) == '\r')
			significado.erase(significado.size()-1);

		// Form a new word and add it
		PalavraSignificado ps(palavra,significado);
		palavras.insert(ps);

	}
}


string Dicionario::consulta(string palavra) const
{
	BSTItrIn<PalavraSignificado> it(palavras);
	PalavraSignificado palavraAnterior("","");
	PalavraSignificado palavraAux("","");

	// Iterate though the dic.
	while(!it.isAtEnd()){

		palavraAux = it.retrieve();

		if (it.retrieve().getPalavra() == palavra){		// Found it!
			return (palavraAux.getSignificado());
		}
		else if (palavraAux.getPalavra() > palavra){		// Was supposed to be here, if existant!
			throw (PalavraNaoExiste(palavraAnterior,palavraAux));
		}

		palavraAnterior = it.retrieve();

		it.advance();
	}

	throw PalavraNaoExiste(palavraAnterior,PalavraSignificado("",""));	// Wasn't found!
}


bool Dicionario::corrige(string palavra, string significado)
{
	// Search for the word
	BSTItrIn<PalavraSignificado> it(palavras);

	while (!it.isAtEnd()){
		if (it.retrieve().getPalavra() == palavra){	// Already exists! Remove it, change the meaning, and insert it back. Then , return true
			palavras.remove(PalavraSignificado(palavra,""));
			palavras.insert(PalavraSignificado(palavra,significado));
			return true;
		}

		it.advance();
	}

	// Wasn't found -> does not exist -> add it and return false
	palavras.insert(PalavraSignificado(palavra,significado));
	return false;
}


void Dicionario::imprime() const
{
	BSTItrIn<PalavraSignificado> it(palavras);

	while (!it.isAtEnd()){
		cout << it.retrieve().getPalavra() << '\n' << it.retrieve().getSignificado() << '\n';
		it.advance();
	}
}
