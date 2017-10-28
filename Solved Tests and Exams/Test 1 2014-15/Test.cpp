#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Escritorio.h"

void test_a_ImpressorasSemResponsavel() {
	Escritorio e1;
	Impressora *imp1 = new ImpressoraPB("PBa", 2014, 25);   //codigo, ano, numPaginasToner
	Impressora *imp2 = new ImpressoraCores("Ca", 2014, 50);   //codigo, ano, numPaginasToner
	Impressora *imp3 = new ImpressoraPB("PBb", 2014, 100);   //codigo, ano, numPaginasToner
	Impressora *imp4 = new ImpressoraPB("PBc", 2014, 20);   //codigo, ano, numPaginasToner
	Impressora *imp5 = new ImpressoraCores("Cb", 2014, 100);   //codigo, ano, numPaginasToner
	Impressora *imp6 = new ImpressoraCores("Cc", 2014, 15);   //codigo, ano, numPaginasToner
	e1.adicionaImpressora(imp1);
	e1.adicionaImpressora(imp2);
	e1.adicionaImpressora(imp3);
	e1.adicionaImpressora(imp4);
	e1.adicionaImpressora(imp5);
	e1.adicionaImpressora(imp6);

	ASSERT_EQUAL(6, e1.numImpressorasSemResponsavel());

	Funcionario fa("fA");
	fa.adicionaImpressora(imp1);
	fa.adicionaImpressora(imp2);
	e1.adicionaFuncionario(fa);

	Funcionario fb("fB");
	e1.adicionaFuncionario(fb);

	ASSERT_EQUAL(4,e1.numImpressorasSemResponsavel());

	Funcionario fc("fC");
	fc.adicionaImpressora(imp4);
	e1.adicionaFuncionario(fc);

	ASSERT_EQUAL(3,e1.numImpressorasSemResponsavel());

	Funcionario fd("fD");
	fd.adicionaImpressora(imp5);
	fd.adicionaImpressora(imp6);
	fd.adicionaImpressora(imp3);
	e1.adicionaFuncionario(fd);

	ASSERT_EQUAL(0, e1.numImpressorasSemResponsavel());
}



void test_b_RetiraImpressoras() {
	Escritorio e1;
	Impressora *imp1 = new ImpressoraPB("PBa", 2011, 100);   //codigo, ano, numPaginasToner
	Impressora *imp2 = new ImpressoraCores("Ca", 2010, 100);   //codigo, ano, numPaginasToner
	Impressora *imp3 = new ImpressoraPB("PBb", 2008, 100);   //codigo, ano, numPaginasToner
	Impressora *imp4 = new ImpressoraPB("PBc", 2013, 100);   //codigo, ano, numPaginasToner
	Impressora *imp5 = new ImpressoraPB("PBd", 2011, 100);   //codigo, ano, numPaginasToner

	vector<Impressora *> res;
	res = e1.retiraImpressoras(2012);
	ASSERT_EQUAL (0, res.size());

	e1.adicionaImpressora(imp1);
	e1.adicionaImpressora(imp2);
	e1.adicionaImpressora(imp3);
	e1.adicionaImpressora(imp4);
	e1.adicionaImpressora(imp5);

	res = e1.retiraImpressoras(2009);
	ASSERT_EQUAL(1, res.size());
	ASSERT_EQUAL("PBb", res[0]->getCodigo());
	ASSERT_EQUAL(4,e1.getImpressoras().size());

	res = e1.retiraImpressoras(2012);
	ASSERT_EQUAL (3, res.size());
	ASSERT_EQUAL(1,e1.getImpressoras().size());
	ASSERT_EQUAL("PBc", e1.getImpressoras()[0]->getCodigo());
}



void test_c_ImprimeDoc() {
	 Documento docPB1(100, 1, 0);  //numPaginas, pPreto, PAmarelo
	 Documento docPB2(40, 1, 0);  //numPaginas, pPreto, PAmarelo
	 Documento docC1(90, 0.8, 0.2);  //numPaginas, pPreto, PAmarelo
	 Documento docC2(90, 0.2, 0.8);  //numPaginas, pPreto, PAmarelo

	 ImpressoraPB impPB("PBa", 2014, 200);   //codigo, ano, numPaginasToner
	 ImpressoraCores impC("Ca", 2014, 100);   //codigo, ano, numPaginasToner

	 ASSERT_EQUAL(true,impPB.imprime(docC1));
	 ASSERT_EQUAL(110,impPB.getNumPaginasImprimir());
	 ASSERT_EQUAL(true,impPB.imprime(docPB1));
	 ASSERT_EQUAL(false,impPB.imprime(docPB2));
	 ASSERT_EQUAL(2,impPB.getDocumentosImpressos().size());
	 ASSERT_EQUAL(10,impPB.getNumPaginasImprimir());

	 ASSERT_EQUAL(true,impC.imprime(docPB2));
	 ASSERT_EQUAL(60,impC.getNumPaginasImprimir());
	 ASSERT_EQUAL(false,impC.imprime(docPB1));
	 ASSERT_EQUAL(1,impC.getDocumentosImpressos().size());
	 ASSERT_EQUAL(true,impC.imprime(docC2));
	 ASSERT_EQUAL(2,impC.getDocumentosImpressos().size());
	 ASSERT_EQUAL(28,impC.getNumPaginasImprimir());
	 ASSERT_EQUAL(false,impC.imprime(docC1));
}



void test_d_ImpressoraImpressaoDoc() {
	Escritorio e1;
	Impressora *imp1 = new ImpressoraPB("PBa", 2014, 100);   //codigo, ano, numPaginasToner
	Impressora *imp2 = new ImpressoraCores("Ca", 2014, 200);   //codigo, ano, numPaginasToner
	Impressora *imp3 = new ImpressoraPB("PBb", 2014, 200);   //codigo, ano, numPaginasToner
	e1.adicionaImpressora(imp1);
	e1.adicionaImpressora(imp2);
	e1.adicionaImpressora(imp3);

	Documento docPB1(120, 1, 0);  //numPaginas, pPreto, PAmarelo
	Documento docC1(300, 0.3, 0.7);  //numPaginas, pPreto, PAmarelo
	Documento docC2(200, 0.8, 0.2);  //numPaginas, pPreto, PAmarelo
	Documento docPB2(70, 1, 0);  //numPaginas, pPreto, PAmarelo

	Impressora *res =e1.imprimeDoc(docC1);
	ASSERT_EQUAL("inexistente",res->getCodigo());

	res =e1.imprimeDoc(docC2);
	ASSERT_EQUAL("Ca",res->getCodigo());
	ASSERT_EQUAL(1, res->getDocumentosImpressos().size());

	res =e1.imprimeDoc(docPB2);
	ASSERT_EQUAL("PBa",res->getCodigo());
	ASSERT_EQUAL(1, res->getDocumentosImpressos().size());


	res =e1.imprimeDoc(docPB2);
	ASSERT_EQUAL("PBb",res->getCodigo());
	ASSERT_EQUAL(1, res->getDocumentosImpressos().size());

	res =e1.imprimeDoc(docPB2);
	ASSERT_EQUAL("PBb",res->getCodigo());
	ASSERT_EQUAL(2, res->getDocumentosImpressos().size());

	res =e1.imprimeDoc(docPB2);
	ASSERT_EQUAL("inexistente",res->getCodigo());
}



void test_e_TonerBaixo() {
	Escritorio e1;
	Impressora *imp1 = new ImpressoraPB("PBa", 2014, 25);   //codigo, ano, numPaginasToner
	Impressora *imp2 = new ImpressoraCores("Ca", 2014, 50);   //codigo, ano, numPaginasToner
	Impressora *imp3 = new ImpressoraPB("PBb", 2014, 100);   //codigo, ano, numPaginasToner
	Impressora *imp4 = new ImpressoraPB("PBc", 2014, 20);   //codigo, ano, numPaginasToner
	Impressora *imp5 = new ImpressoraCores("Cb", 2014, 100);   //codigo, ano, numPaginasToner
	Impressora *imp6 = new ImpressoraCores("Cc", 2014, 15);   //codigo, ano, numPaginasToner

	vector<Impressora *> res;
	res = e1.tonerBaixo();
	ASSERT_EQUAL(0,res.size());

	e1.adicionaImpressora(imp1);
	e1.adicionaImpressora(imp2);
	e1.adicionaImpressora(imp3);

	res = e1.tonerBaixo();
	ASSERT_EQUAL(1,res.size());
	ASSERT_EQUAL("PBa", res[0]->getCodigo());

	e1.adicionaImpressora(imp4);
	e1.adicionaImpressora(imp5);
	e1.adicionaImpressora(imp6);

	res = e1.tonerBaixo();
	ASSERT_EQUAL(3,res.size());
	ASSERT_EQUAL(true, (res[0]->getCodigo()=="PBc" || res[1]->getCodigo()=="PBc" || res[2]->getCodigo()=="PBc"));
	ASSERT_EQUAL(true, (res[0]->getCodigo()=="Cc" || res[1]->getCodigo()=="Cc" || res[2]->getCodigo()=="Cc"));
}



void test_f_OperadorMais() {
	Documento d1(30,1,0);
	Documento d2(70,0.8,0.2);

	Documento dx=d1+d2;
	ASSERT_EQUAL(100,dx.getNumPaginas());
	ASSERT_EQUAL_DELTA(0.86,dx.getPercentagemPreto(),0.01);
	ASSERT_EQUAL_DELTA(0.14,dx.getPercentagemAmarelo(),0.01);

	Documento d3(50,1,0);
	Documento dy=d1+d3;
	ASSERT_EQUAL(80,dy.getNumPaginas());
	ASSERT_EQUAL_DELTA(1,dy.getPercentagemPreto(),0.01);
	ASSERT_EQUAL_DELTA(0,dy.getPercentagemAmarelo(),0.01);
}



void test_g_OperadorFuncao() {
	Escritorio e1;
	Impressora *imp1 = new ImpressoraPB("PBa", 2014, 25);   //codigo, ano, numPaginasToner
	Impressora *imp2 = new ImpressoraCores("Ca", 2014, 50);   //codigo, ano, numPaginasToner
	Impressora *imp3 = new ImpressoraPB("PBb", 2014, 100);   //codigo, ano, numPaginasToner
	Impressora *imp4 = new ImpressoraPB("PBc", 2014, 20);   //codigo, ano, numPaginasToner
	Impressora *imp5 = new ImpressoraCores("Cb", 2014, 100);   //codigo, ano, numPaginasToner

	Funcionario fa("fA");
	fa.adicionaImpressora(imp1);
	fa.adicionaImpressora(imp2);

	Funcionario fb("fB");
	fb.adicionaImpressora(imp3);

	Funcionario fc("fC");
	fc.adicionaImpressora(imp4);
	fc.adicionaImpressora(imp5);

	e1.adicionaFuncionario(fa);
	e1.adicionaFuncionario(fb);
	e1.adicionaFuncionario(fc);

	//////////////////////////////////////////////////////////////
	//					>>>>	WARNING		<<<<				//
	//															//
	// ESQUECERAM-SE DE ADICIONAR AS IMPRESSORAS À IMPRESA!!!	//
	//															//
	//////////////////////////////////////////////////////////////

	e1.adicionaImpressora(imp1);
	e1.adicionaImpressora(imp2);
	e1.adicionaImpressora(imp3);
	e1.adicionaImpressora(imp4);
	e1.adicionaImpressora(imp5);

	ASSERT_EQUAL("nulo", e1("PBx"));
	ASSERT_EQUAL("fC", e1("Cb"));
}



void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_ImpressorasSemResponsavel));
	s.push_back(CUTE(test_b_RetiraImpressoras));
	s.push_back(CUTE(test_c_ImprimeDoc));
	s.push_back(CUTE(test_d_ImpressoraImpressaoDoc));
	s.push_back(CUTE(test_e_TonerBaixo));
	s.push_back(CUTE(test_f_OperadorMais));
	s.push_back(CUTE(test_g_OperadorFuncao));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA 2015/2016 - Avalia��o - 07/out - Testes Unitarios Estudantes");
}

int main(){
    runSuite();
    return 0;
}

