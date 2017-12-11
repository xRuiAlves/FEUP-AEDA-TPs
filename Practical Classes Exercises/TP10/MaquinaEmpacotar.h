/*
 * MaquinaEmpacotar.h
 */

#ifndef MAQUINAEMPACOTAR_H_
#define MAQUINAEMPACOTAR_H_

#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include "Caixa.h"
using namespace std;

typedef priority_queue<Objeto> HEAP_OBJS;
typedef priority_queue<Caixa> HEAP_CAIXAS;

class MaquinaEmpacotar {
	HEAP_OBJS objetos;
	HEAP_CAIXAS caixas;
	unsigned capacidadeCaixas;
public:
	MaquinaEmpacotar(int capCaixas = 10);
	unsigned numCaixasUsadas();
	unsigned addCaixa(Caixa& cx);
	HEAP_OBJS getObjetos() const;
	HEAP_CAIXAS getCaixas() const;

	unsigned carregaPaletaObjetos(vector<Objeto> &objs);
	Caixa procuraCaixa(Objeto& obj);
	unsigned empacotaObjetos();
	string imprimeObjetosPorEmpacotar() const;
	Caixa caixaMaisObjetos() const;
	class MaquinaSemCaixas{};
};

#endif /* MAQUINAEMPACOTAR_H_ */
