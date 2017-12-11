#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <vector>
#include <string>

#include "MaquinaEmpacotar.h"



void test_a_CarregaObjetos() {
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 11));
	objetos.push_back(Objeto(3, 17)); objetos.push_back(Objeto(4, 3));
	objetos.push_back(Objeto(5, 9)); objetos.push_back(Objeto(6, 4));
	objetos.push_back(Objeto(7, 2)); objetos.push_back(Objeto(8, 12));
	objetos.push_back(Objeto(9, 7)); objetos.push_back(Objeto(10, 1));

	for(unsigned i = 0; i < objetos.size(); i++) cout << objetos[i] << endl;

	MaquinaEmpacotar maquina;
	int objsCarregados = maquina.carregaPaletaObjetos(objetos);
	int objsIgnorados  = objetos.size();
	ASSERT_EQUAL(7, objsCarregados);
	ASSERT_EQUAL(3, objsIgnorados);
	ASSERT_EQUAL(5,maquina.getObjetos().top().getID());
}


void test_b_ProcuraCaixa() {
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 5));
	objetos.push_back(Objeto(3, 8)); objetos.push_back(Objeto(4, 1));
	objetos.push_back(Objeto(5, 4)); objetos.push_back(Objeto(6, 6));
	objetos.push_back(Objeto(7, 1)); objetos.push_back(Objeto(8, 4));

	Caixa::resetID();

	Caixa c1(10); //7
	c1.addObjeto( objetos[0] );
	c1.addObjeto( objetos[1] );
	Caixa c2(10); //8
	c2.addObjeto( objetos[2] );

	MaquinaEmpacotar maquina;
	maquina.addCaixa( c1 );
	maquina.addCaixa( c2 );

	cout << "Carga livre em C" << c1.getID() << ": " << c1.getCargaLivre() << endl; //3
	cout << "Carga livre em C" << c2.getID() << ": " << c2.getCargaLivre() << endl; //2

	ASSERT_EQUAL(2, maquina.numCaixasUsadas()); // 8 7
	ASSERT_EQUAL(2,maquina.getCaixas().top().getCargaLivre());

	Caixa cx = maquina.procuraCaixa( objetos[3] );
	cx.addObjeto( objetos[3] );
	maquina.addCaixa( cx );
	//cout << "Carga livre em C" << cx.getID() << ": " << cx.getCargaLivre() << endl;
	ASSERT_EQUAL(2, maquina.numCaixasUsadas()); // 9 7
	ASSERT_EQUAL(1,maquina.getCaixas().top().getCargaLivre());

	cx = maquina.procuraCaixa( objetos[4] );
	cx.addObjeto( objetos[4] );
	maquina.addCaixa( cx );
	cout << "Carga livre em C" << cx.getID() << ": " << cx.getCargaLivre() << endl;
	ASSERT_EQUAL(3, maquina.numCaixasUsadas()); // 9 7 4
	ASSERT_EQUAL(1,maquina.getCaixas().top().getCargaLivre());

	cx = maquina.procuraCaixa( objetos[5] );
	cx.addObjeto( objetos[5] );
	maquina.addCaixa( cx );
	cout << "Carga livre em C" << cx.getID() << ": " << cx.getCargaLivre() << endl;
	ASSERT_EQUAL(3, maquina.numCaixasUsadas()); // 10 9 7
	ASSERT_EQUAL(0,maquina.getCaixas().top().getCargaLivre());

	cx = maquina.procuraCaixa( objetos[6] );
	cx.addObjeto( objetos[6] );
	maquina.addCaixa( cx );
	cout << "Carga livre em C" << cx.getID() << ": " << cx.getCargaLivre() << endl;
	ASSERT_EQUAL(3, maquina.numCaixasUsadas()); // 10 10 7
	HEAP_CAIXAS caixas = maquina.getCaixas();
	caixas.pop();
	ASSERT_EQUAL(0,caixas.top().getCargaLivre());

	cx = maquina.procuraCaixa( objetos[7] );
	cx.addObjeto( objetos[7] );
	maquina.addCaixa( cx );
	cout << "Carga livre em C" << cx.getID() << ": " << cx.getCargaLivre() << endl;
	ASSERT_EQUAL(4, maquina.numCaixasUsadas()); // 10 10 7 6
	caixas = maquina.getCaixas();
	caixas.pop(); caixas.pop();
	ASSERT_EQUAL(3,caixas.top().getCargaLivre());
}


void test_c_EmpacotaObjetos() {
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 11));
	objetos.push_back(Objeto(3, 17)); objetos.push_back(Objeto(4, 3));
	objetos.push_back(Objeto(5, 9)); objetos.push_back(Objeto(6, 4));
	objetos.push_back(Objeto(7, 2)); objetos.push_back(Objeto(8, 12));
	objetos.push_back(Objeto(9, 7)); objetos.push_back(Objeto(10, 10));
	objetos.push_back(Objeto(11, 10)); objetos.push_back(Objeto(12, 1));

	Caixa::resetID();

	MaquinaEmpacotar maquina;

	ASSERT_EQUAL(9, maquina.carregaPaletaObjetos(objetos));
	ASSERT_EQUAL(3, objetos.size());
	ASSERT_EQUAL(5, maquina.empacotaObjetos());

	HEAP_CAIXAS caixas = maquina.getCaixas();
	ASSERT_EQUAL(0,caixas.top().getCargaLivre()); caixas.pop();
	ASSERT_EQUAL(0,caixas.top().getCargaLivre()); caixas.pop();
	ASSERT_EQUAL(0,caixas.top().getCargaLivre()); caixas.pop();
	ASSERT_EQUAL(0,caixas.top().getCargaLivre()); caixas.pop();
	ASSERT_EQUAL(2,caixas.top().getCargaLivre());
}


void test_d_ObjetosPorEmpacotar() {
	MaquinaEmpacotar maquina;

	ASSERT_EQUAL("Nao ha objetos!\n", maquina.imprimeObjetosPorEmpacotar());

	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 12));
	objetos.push_back(Objeto(3, 8)); objetos.push_back(Objeto(4, 1));

	ASSERT_EQUAL(3, maquina.carregaPaletaObjetos(objetos));
	string objsPorEmpacotar = maquina.imprimeObjetosPorEmpacotar();
	cout << objsPorEmpacotar;
	ASSERT_EQUAL("O3: 8\nO1: 2\nO4: 1\n", maquina.imprimeObjetosPorEmpacotar());

	ASSERT_EQUAL(2, maquina.empacotaObjetos());

	ASSERT_EQUAL("Nao ha objetos!\n", maquina.imprimeObjetosPorEmpacotar());
}


void test_e_ConteudoCaixa() {
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); 	objetos.push_back(Objeto(2, 5));

	Caixa::resetID();

	Caixa c1(10);
	ASSERT_EQUAL("Caixa 1 vazia!\n", c1.imprimeConteudo());

	c1.addObjeto( objetos[0] );
	c1.addObjeto( objetos[1] );

	ASSERT_EQUAL("C1[ O2: 5 O1: 2 ]", c1.imprimeConteudo());
}


void test_f_CaixaMaisObjetos() {
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 11));
	objetos.push_back(Objeto(3, 17)); objetos.push_back(Objeto(4, 3));
	objetos.push_back(Objeto(5, 9)); objetos.push_back(Objeto(6, 4));
	objetos.push_back(Objeto(7, 2)); objetos.push_back(Objeto(8, 12));
	objetos.push_back(Objeto(9, 7)); objetos.push_back(Objeto(10, 10));
	objetos.push_back(Objeto(11, 10)); objetos.push_back(Objeto(12, 1));

	Caixa cx;
	Caixa::resetID();

	MaquinaEmpacotar maquina;

	ASSERT_THROWS(maquina.caixaMaisObjetos(), MaquinaEmpacotar::MaquinaSemCaixas);
	try {
		cx = maquina.caixaMaisObjetos();
	}
	catch(MaquinaEmpacotar::MaquinaSemCaixas &msc) {
		ASSERTM("Este teste nunca falha! VERIFICAR informacao escrita no monitor", true);
	}

	ASSERT_EQUAL(9, maquina.carregaPaletaObjetos(objetos));
	ASSERT_EQUAL(3, objetos.size());
	ASSERT_EQUAL(5, maquina.empacotaObjetos());

	cx = maquina.caixaMaisObjetos();
	ASSERT_EQUAL(5, cx.getID());
	ASSERT_EQUAL("C5[ O1: 2 O7: 2 O6: 4 ]", cx.imprimeConteudo());
}



void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_CarregaObjetos));
	s.push_back(CUTE(test_b_ProcuraCaixa));
	s.push_back(CUTE(test_c_EmpacotaObjetos));
	s.push_back(CUTE(test_d_ObjetosPorEmpacotar));
	s.push_back(CUTE(test_e_ConteudoCaixa));
	s.push_back(CUTE(test_f_CaixaMaisObjetos));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2017/2018 - Aula Pratica 10");
}

int main(){
    runSuite();
    return 0;
}



