#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Jogo.h"
#include "Dicionario.h"
#include <fstream>


void test_1a_CriaDicionario(){
	ifstream fich;
    fich.open("/home/rui/eclipse-workspace/AEDA 2017-18/src/TP08/dic.txt");
	ASSERTM("Erro ao Abrir o Ficheiro", fich);
	Dicionario d1;
	d1.lerDicionario(fich);
	fich.close();
	BST<PalavraSignificado> arvPals = d1.getPalavras();
	ASSERT_EQUAL(false, arvPals.isEmpty());
	BSTItrIn<PalavraSignificado> it(arvPals);
	it.advance(); it.advance();
	ASSERT_EQUAL("gato", it.retrieve().getPalavra());
}

void test_1b_ImprimeDicionario(){
	ASSERTM("Este teste n�o falha. Verifique na consola os valores", true);
	ifstream fich;
	fich.open("/home/rui/eclipse-workspace/AEDA 2017-18/src/TP08/dic.txt");
	ASSERTM("Erro ao Abrir o Ficheiro", fich);
	Dicionario d1;
	d1.lerDicionario(fich);
	fich.close();
	d1.imprime();
}

void test_1c_ConsultaDicionario(){
	ifstream fich;
	fich.open("/home/rui/eclipse-workspace/AEDA 2017-18/src/TP08/dic.txt");
	ASSERTM("Erro ao Abrir o Ficheiro", fich);
	Dicionario d1;
	d1.lerDicionario(fich);
	fich.close();
	ASSERT_EQUAL("mamifero felino", d1.consulta("gato"));
	ASSERT_THROWS(d1.consulta("rio"), PalavraNaoExiste);
	try {
		string signf=d1.consulta("janela");
	}
	catch (PalavraNaoExiste &e) {
		cout << "Apanhou excep��o: PalavraNaoExiste" << endl;
		ASSERT_EQUAL("ilha", e.getPalavraAntes());
		ASSERT_EQUAL("porcao de terra emersa rodeada de agua", e.getSignificadoAntes());
		ASSERT_EQUAL("macaco", e.getPalavraApos());
		ASSERT_EQUAL("mamifero da ordem dos primatas", e.getSignificadoApos());
	}
}

void test_1d_CorrigeDicionario(){
	ifstream fich;
	fich.open("/home/rui/eclipse-workspace/AEDA 2017-18/src/TP08/dic.txt");
	ASSERTM("Erro ao Abrir o Ficheiro", fich);
	Dicionario d1;
	d1.lerDicionario(fich);
	fich.close();
	ASSERT_EQUAL(true,d1.corrige("morango","fruto vermelho"));
	ASSERT_EQUAL("fruto vermelho", d1.consulta("morango"));
	ASSERT_EQUAL(false,d1.corrige("esquilo","pequeno mamifero roedor de cauda longa"));
	BST<PalavraSignificado> arvPals=d1.getPalavras();
	BSTItrIn<PalavraSignificado> it(arvPals);
	it.advance(); it.advance();
	ASSERT_EQUAL("esquilo", it.retrieve().getPalavra());
	ASSERT_EQUAL("pequeno mamifero roedor de cauda longa", d1.consulta("esquilo"));
}


void test_2a_InicioJogo(){
	vector<int> pontos;
	vector<bool> estados;
	pontos.push_back(1); pontos.push_back(2); pontos.push_back(3);
	pontos.push_back(4); pontos.push_back(5); pontos.push_back(6); pontos.push_back(7);
	estados.push_back(true); estados.push_back(false); estados.push_back(false);
	estados.push_back(false); estados.push_back(false); estados.push_back(true); estados.push_back(false);
    Jogo jogo1(2, pontos,estados);
    ASSERT_EQUAL(1, jogo1.getJogo().getRoot().getPontuacao());
}

void test_2b_EscreveJogo(){
	vector<int> pontos;
	vector<bool> estados;
	pontos.push_back(1); pontos.push_back(2); pontos.push_back(3);
	pontos.push_back(4); pontos.push_back(5); pontos.push_back(6);
	pontos.push_back(7); pontos.push_back(8); pontos.push_back(9);
	pontos.push_back(10); pontos.push_back(11); pontos.push_back(12);
	pontos.push_back(13); pontos.push_back(14); pontos.push_back(15);
	estados.push_back(true); estados.push_back(false); estados.push_back(false);
	estados.push_back(false); estados.push_back(false); estados.push_back(true);
	estados.push_back(false); estados.push_back(true); estados.push_back(true);
	estados.push_back(true); estados.push_back(true); estados.push_back(true);
	estados.push_back(true); estados.push_back(true); estados.push_back(true);
    Jogo jogo1(3, pontos,estados);
    string jogoStr="1-true-0\n2-false-0\n3-false-0\n4-false-0\n5-false-0\n6-true-0\n7-false-0\n8-true-0\n9-true-0\n10-true-0\n11-true-0\n12-true-0\n13-true-0\n14-true-0\n15-true-0\n";
    ASSERT_EQUAL(jogoStr, jogo1.escreveJogo());
}

void test_2c_FazJogada(){
	vector<int> pontos;
	vector<bool> estados;
	pontos.push_back(1); pontos.push_back(2); pontos.push_back(3);
	pontos.push_back(4); pontos.push_back(5); pontos.push_back(6);
	pontos.push_back(7); pontos.push_back(8); pontos.push_back(9);
	pontos.push_back(10); pontos.push_back(11); pontos.push_back(12);
	pontos.push_back(13); pontos.push_back(14); pontos.push_back(15);
	estados.push_back(true); estados.push_back(false); estados.push_back(false);
	estados.push_back(false); estados.push_back(false); estados.push_back(true);
	estados.push_back(false); estados.push_back(true); estados.push_back(true);
	estados.push_back(true); estados.push_back(true); estados.push_back(true);
	estados.push_back(true); estados.push_back(true); estados.push_back(true);
    Jogo jogo1(3, pontos,estados);
    ASSERT_EQUAL(13, jogo1.jogada());
    ASSERT_EQUAL(8,jogo1.jogada());
}

void test_2d_MaisVisitado(){
	vector<int> pontos;
	vector<bool> estados;
	pontos.push_back(1); pontos.push_back(2); pontos.push_back(3);
	pontos.push_back(4); pontos.push_back(5); pontos.push_back(6);
	pontos.push_back(7); pontos.push_back(8); pontos.push_back(9);
	pontos.push_back(10); pontos.push_back(11); pontos.push_back(12);
	pontos.push_back(13); pontos.push_back(14); pontos.push_back(15);
	estados.push_back(true); estados.push_back(false); estados.push_back(false);
	estados.push_back(false); estados.push_back(false); estados.push_back(true);
	estados.push_back(false); estados.push_back(true); estados.push_back(true);
	estados.push_back(true); estados.push_back(true); estados.push_back(true);
	estados.push_back(true); estados.push_back(true); estados.push_back(true);
	Jogo jogo1(3, pontos,estados);
	jogo1.jogada(); jogo1.jogada(); jogo1.jogada();
	ASSERT_EQUAL(2, jogo1.maisVisitado());
	jogo1.jogada(); jogo1.jogada(); jogo1.jogada();jogo1.jogada();
	ASSERT_EQUAL(4, jogo1.maisVisitado());
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_1a_CriaDicionario));
	s.push_back(CUTE(test_1b_ImprimeDicionario));
	s.push_back(CUTE(test_1c_ConsultaDicionario));
	s.push_back(CUTE(test_1d_CorrigeDicionario));
	s.push_back(CUTE(test_2a_InicioJogo));
	s.push_back(CUTE(test_2b_EscreveJogo));
	s.push_back(CUTE(test_2c_FazJogada));
	s.push_back(CUTE(test_2d_MaisVisitado));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2017/2018 - Aula Pratica 8");
}

int main(){
    runSuite();
    return 0;
}



