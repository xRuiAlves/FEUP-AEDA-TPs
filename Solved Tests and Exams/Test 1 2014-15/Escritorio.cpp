#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento & operator+(const Documento &d1, const Documento &d2){

	int numPaginas = d1.getNumPaginas() + d2.getNumPaginas();
	float pAmarelo = (d1.getPercentagemAmarelo()*d1.getNumPaginas() + d2.getPercentagemAmarelo()*d2.getNumPaginas()) / (d1.getNumPaginas() + d2.getNumPaginas());
	float pPreto = (d1.getPercentagemPreto()*d1.getNumPaginas() + d2.getPercentagemPreto()*d2.getNumPaginas()) / (d1.getNumPaginas() + d2.getNumPaginas());

	Documento* d3 = new Documento(numPaginas,pPreto,pAmarelo);

	return (*d3);
}

//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1){
	if (doc1.getNumPaginas() > numPagImprimir) // Nao e possivel imprimir o doc
		return false;

	// E possivel imprimir o doc
	docsImpressos.push_back(doc1);	// Adicionar aos docs impressos
	numPagImprimir -= doc1.getNumPaginas();		// Atualizar o num de paginas que a impressora pode imprimir
	return true;
}

//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1){
	float pAmarelo = doc1.getPercentagemAmarelo();
	float pPreto = doc1.getPercentagemPreto();
	int numPaginas = doc1.getNumPaginas();

	if ((numPaginas*pPreto > numPagImprimirPreto) || (numPaginas*pAmarelo > numPagImprimirAmarelo)) // Nao e possivel imprimir o doc
		return false;

	// E possivel imprimir o doc
	docsImpressos.push_back(doc1);	// Adicionar aos docs impressos
	numPagImprimirAmarelo -= numPaginas*pAmarelo;		// Atualizar o num de paginas a amarelo que a impressora pode imprimir
	numPagImprimirPreto -= numPaginas*pPreto; 			// Atualizar o num de paginas a pretp que a impressora pode imprimir
	return true;
}


//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }


////////////////////////////////////////////////////////////////////////
//    >>>>       WARNING: EXTREME SPAGHETTI CODE !!!!         <<<<    //
////////////////////////////////////////////////////////////////////////
int Escritorio::numImpressorasSemResponsavel() const{
	int counter = 0;	// Contar o nº de impressoras sem responsal
	Impressora* impressora;
	vector<Impressora*> impressorasFunc;
	bool temResponsavel;

	for (unsigned int i=0 ; i<impressoras.size() ; i++){
		temResponsavel = false;
		impressora = impressoras.at(i);

		// Procurar um responsável por esta impressora
		for (unsigned int j=0 ; j<funcionarios.size() ; j++){
			impressorasFunc = funcionarios.at(j).getImpressoras();	// Obter as impressoras à responsabilidade do funcionario
			for (unsigned int k=0 ; k<impressorasFunc.size() ; k++){
				if(impressorasFunc.at(k)->getCodigo() == impressora->getCodigo()){	// Encontramos um functionário encarregue desta impressora, set the flag
					temResponsavel = true;
					break;
				}
			}
			if (temResponsavel)	// Já encontramos um responsavel, nao é necessário encontrar mais
				break;
		}
		if (!temResponsavel)	// Esta impressora  nao tinha responsável, incrementar contador
			counter++;
	}

	return counter;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1){
	vector<Impressora*> impressorasRemovidas;

	for (unsigned int i=0 ; i<impressoras.size() ; i++){
		if (impressoras.at(i)->getAno() < ano1){	// Found one!
			impressorasRemovidas.push_back(impressoras.at(i));
			impressoras.erase(impressoras.begin()+i);	// Remove-la
			i--;
		}
	}

	return impressorasRemovidas;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const{
	for (unsigned int i=0 ; i<impressoras.size() ; i++){
		if(impressoras.at(i)->imprime(doc1))	// Esta consegue imprimir! Retornar a referencia da mesma
			return impressoras.at(i);
	}

	// Nao foi encontrada nenhuma que conseguisse imprimir, retornar impressora qualquer com codigo "inexistente"
	return (new ImpressoraPB("inexistente",0,0));
}

vector<Impressora *> Escritorio::tonerBaixo() const{
	string tipo;
	vector<Impressora*> impressorasBaixo;

	for (unsigned int i=0 ; i<impressoras.size() ; i++){
		tipo = impressoras.at(i)->getTipo();
		// Impressoras a cores
		if (tipo == "Cores"){
			if (impressoras.at(i)->getNumPaginasImprimir() < 20)
				impressorasBaixo.push_back(impressoras.at(i));
		}
		// Impressoras a preto e branco
		else{
			if (impressoras.at(i)->getNumPaginasImprimir() < 30)
				impressorasBaixo.push_back(impressoras.at(i));
		}
	}

	return impressorasBaixo;
}

string Escritorio::operator()(const string & codigo) const{
	// Procurar a impressora
	int indexImpressora = -1;

	for (unsigned int i=0 ; i<impressoras.size() ; i++){
		if (impressoras.at(i)->getCodigo() == codigo){		// Found it!
			indexImpressora = i;
			break;
		}
	}

	if (indexImpressora == -1)	// Impressora nao encontrada
		return "nulo";

	// Procurar o funcionário encarregue desta impressora
	vector<Impressora*> impressorasFunc;

	for (unsigned int i=0 ; i<funcionarios.size() ; i++){
		impressorasFunc = funcionarios.at(i).getImpressoras();
		// Procurar por esta impressora
		for (unsigned int j=0 ; j<impressorasFunc.size() ; j++){
			if (impressorasFunc.at(j)->getCodigo() == codigo)
				return funcionarios.at(i).getCodigo();			// Found him!
		}
	}

	return "nulo";	// Nenhum foi encontrado
}
