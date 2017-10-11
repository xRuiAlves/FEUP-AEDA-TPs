#include <iostream>
#include <vector>

using namespace std;

/**
 * Vers�o da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
    bool noExiste(const N &dados) const;
    int indiceNo(const N &dados) const;
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template <class N>
class ArestaRepetida{
public:
	N info1;
	N info2;
	ArestaRepetida(N inf1, N inf2){
		info1 = inf1;
		info2 = inf2;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar)
{ out << "Aresta repetida: " << ar.info1 << " , " << ar.info2; }

template <class N>
class ArestaInexistente{
public:
	N info1;
	N info2;
	ArestaInexistente(N inf1, N inf2){
		info1 = inf1;
		info2 = inf2;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai)
{ out << "Aresta inexistente: " << ai.info1 << " , " << ai.info2; }

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


template <class N, class A>
Grafo<N,A>::Grafo(){

}

template <class N, class A>
Grafo<N,A>::~Grafo(){
	for(unsigned int i=0 ; i<nos.size() ; i++){
		delete nos.at(i);
	}
}

template <class N, class A>
int Grafo<N,A>::numNos() const{
	return nos.size();
}

template <class N, class A>
int Grafo<N,A>::numArestas() const{
	unsigned int counter = 0;
	for(unsigned int i=0 ; i<nos.size() ; i++){
		counter+=nos.at(i)->arestas.size();
	}
	return counter;
}

template <class N, class A>
bool Grafo<N,A>::noExiste(const N &dados) const{
	for(unsigned int i=0 ; i<nos.size() ; i++){
		if(nos.at(i)->info == dados){
			return true;		// existe
		}
	}

	return false;		// nao exite
}

template <class N, class A>
int Grafo<N,A>::indiceNo(const N &dados) const{
	for(int i=0 ; i<nos.size() ; i++){
		if(nos.at(i)->info == dados){		// found it!
			return i;
		}
	}

	return -1;			// não foi encontrado
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados){
	// check for existance
	if(noExiste(dados)){
		throw (NoRepetido<N>(dados));		// thorw the exception and return the graph un-altered
	}

	nos.push_back(new No<N,A>(dados));
	return *this;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){

	//obter indices
	int indiceInicio = indiceNo(inicio);
	int indiceFim = indiceNo(fim);

	// verificar se não existem
	if(indiceInicio == -1)
		throw (NoInexistente<N>(inicio));
	if(indiceFim == -1)
		throw (NoInexistente<N>(fim));

	// verificar se aresta existe
	for(unsigned int i=0 ; i<nos.at(indiceInicio)->arestas.size() ; i++){
		if(nos.at(indiceInicio)->arestas.at(i).destino->info == fim){
			throw (ArestaRepetida<N>(inicio,fim));
		}
	}

	// adicionar aresta
	nos.at(indiceInicio)->arestas.push_back(Aresta<N,A>(nos.at(indiceFim), val));
	return *this;

}

template <class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim){
	// obter indices
	int indiceInicio = indiceNo(inicio);
	int indiceFim = indiceNo(fim);

	// verificar se não existem
	if(indiceInicio == -1)
		throw (NoInexistente<N>(inicio));
	if(indiceFim == -1)
		throw (NoInexistente<N>(fim));

	// procurar a aresta e retornar o valor pedido
	for(unsigned int i=0 ; i<nos.at(indiceInicio)->arestas.size() ; i++){
		if(nos.at(indiceInicio)->arestas.at(i).destino == nos.at(indiceFim)){	// found it!
			return nos.at(indiceInicio)->arestas.at(i).valor;
		}
	}

	// nao foi encontrada, lançar exceção
	throw (ArestaInexistente<N>(inicio,fim));

}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim){
	// obter indices
	int indiceInicio = indiceNo(inicio);
	int indiceFim = indiceNo(fim);

	// verificar se não existem
	if(indiceInicio == -1)
		throw (NoInexistente<N>(inicio));
	if(indiceFim == -1)
		throw (NoInexistente<N>(fim));

	// eliminar a aresta caso esta exista
	for(unsigned int i=0 ; i<nos.at(indiceInicio)->arestas.size() ; i++){
		if(nos.at(indiceInicio)->arestas.at(i).destino == nos.at(indiceFim)){	// found it!
			nos.at(indiceInicio)->arestas.erase(nos.at(indiceInicio)->arestas.begin()+i);
			return *this;
		}
	}

	// nao foi encontrada, lançar exceção
	throw (ArestaInexistente<N>(inicio,fim));
}

template <class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const{
	for(unsigned int i=0 ; i<nos.size() ; i++){
		os << "( " << nos.at(i)->info;
		for(unsigned int j=0 ; j<nos.at(i)->arestas.size() ; j++){
			os << "[ " << nos.at(i)->arestas.at(j).destino->info << " " << nos.at(i)->arestas.at(j).valor << "] ";
		}
		os << ") ";
	}
}

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g)
{ g.imprimir(out); }

