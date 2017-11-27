#include "Jogo.h"



BinaryTree<Circulo> Jogo::iniciaJogo(int pos,int niv, vector<int> &pontos, vector<bool> &estados){
	Circulo c1(pontos[pos],estados[pos]);

	if (niv==0)
		return BinaryTree<Circulo>(c1);

	BinaryTree<Circulo> filhoEsq = iniciaJogo(2*pos+1,niv-1,pontos, estados);
	BinaryTree<Circulo> filhoDir = iniciaJogo(2*pos+2,niv-1,pontos, estados);

	return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}


ostream &operator << (ostream &os, Circulo &c1)
{
	// a alterar
	return os;
}



Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados){
	jogo=iniciaJogo(0,niv,pontos,estados);
}


string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> it(jogo);
	Circulo circle;
	string game;
	string t = "true" , f = "false";

	// Iterate though the tree (by level) and add the info. to the string
	while (!it.isAtEnd()){
		circle = it.retrieve();

		game += to_string(circle.getPontuacao()) + "-";
		game += (circle.getEstado() ? t : f) + "-";
		game += to_string(circle.getNVisitas()) + "\n";

		it.advance();
	}

	return game;
}


int Jogo::jogada()
{
	int score = 1;

	BTItrLevel<Circulo> it(jogo);
	int n = 1;

	while(!it.isAtEnd()){
		Circulo & circle = it.retrieve();	// Analise the current node

		if (circle.getPontuacao() != n){	// Not the node we are looking for
			it.advance();
			continue;
		}

		// It is the node we are analising!

		if (circle.getEstado())	// Check which node to analise next!
			n = n*2 + 1;
		else
			n *= 2;


		score = circle.getPontuacao();	// Update the score!
		circle.mudaEstado();			// Change the state!
		circle.incNVisitas();			// Increment the number of visits!

		it.advance();
	}


	return score;
}



int Jogo::maisVisitado()
{
	int num = 0;
	BTItrLevel<Circulo> it(jogo);

	// Check for empty tree
	if (it.isAtEnd())
		return 0;

	// Skip the root, as requested in the exercise description
	it.advance();

	// Iterate though the tree to find the most visited node
	while (!it.isAtEnd()){
		if (it.retrieve().getNVisitas() > num)
			num = it.retrieve().getNVisitas();

		it.advance();
	}

	return num;
}




