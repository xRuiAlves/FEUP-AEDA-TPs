/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"
#include <set>
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	vector<Objeto>::iterator it;

	for(it=objs.begin() ; it!=objs.end() ; ){
		cout << it->getID() << endl;
		if (it->getPeso() <= capacidadeCaixas){
			objetos.push(*it);
			objs.erase(it);
		}
		else
			it ++;
	}

	return objetos.size();
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	// Temporary vector to hold the boxes
	vector<Caixa> tempVec;

	while(!caixas.empty()){
		Caixa box_aux = caixas.top();
		caixas.pop();

		if (box_aux.getCargaLivre() >= obj.getPeso()){	// Found one!

			for(unsigned int i=0 ; i<tempVec.size() ; i++){
				caixas.push(tempVec.at(i));
			}

			return box_aux;
		}
		else
			tempVec.push_back(box_aux);
	}

	// Put them back into the priority queue
	for(unsigned int i=0 ; i<tempVec.size() ; i++){
		caixas.push(tempVec.at(i));
	}

	// Return a new box
	return (Caixa(capacidadeCaixas));


}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	// Set to save all the unique ids
	set<unsigned> ids;

	while(!objetos.empty()){
		Objeto obj = objetos.top();
		objetos.pop();

		Caixa caixaAux = procuraCaixa(obj);	// Find the best suited box for the object
		ids.insert(caixaAux.getID());
		caixaAux.addObjeto(obj);
		caixas.push(caixaAux);
	}

	return ids.size();
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	if (objetos.empty())
		return "Nao ha objetos!\n";

	stringstream stream;

	HEAP_OBJS aux = objetos;

	while(!aux.empty()){
		stream << aux.top();
		stream << '\n';
		aux.pop();
	}

	return stream.str();
}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	if(caixas.empty())
		throw (MaquinaSemCaixas());

	Caixa aux , box;
	unsigned maxNum = 0;
	HEAP_CAIXAS auxHeap = caixas;

	while(!auxHeap.empty()){
		aux = auxHeap.top();

		if (aux.getSize() >= maxNum){
			maxNum = aux.getSize();
			box = aux;
		}

		auxHeap.pop();
	}



	return box;
}



