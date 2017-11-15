#ifndef PERFORMANCE_H_
#define PERFORMANCE_H_
#include <iostream>
#include <cstdlib>
#include "cycle.h"

using namespace std;

/**
 * Function that returns true if a sequence of numbers
 * corresponds to a constant function
 * @param y_el[] the array of ints to be considered
 * @param size the number of elements in the array
 * @param var a variação (+/-) aceitável
 * @return true if corresponds to a constant function
 */
bool isConstant(const unsigned int y_el[], const int size, const int var) {

	// Esta abordagem verifica as diferenças entre cada elemento
	// bastando uma das diferenças ser superior ao intervalo
	// para não considerar constante
	int primDif = 0; // para ser constante o valor de referencia da diferença entre elementos deverá ser zero
	//cout << "primDif = " << primDif << endl;
	int dif = 0;
	for (int i = 1; i < size; i++) {
		dif = (y_el[i] - y_el[i-1]);
		//cout << "dif = " << dif << endl;
		//cout << "primdif-var = " << primDif-var << "primdif+var = " << primDif+var << endl;
		if (dif<(primDif-var) || dif>primDif+var) return false;
	}
	return true;

/*
	// Esta abordagem usa o valor médio da leitura
	// e considera constante se estiver dentro do intervalo definido
	int primDif = 0; // para ser constante o valor de referencia da diferença entre elementos deverá ser zero
	cout << "primDif = " << primDif << endl;
	int soma = 0;
	int dif = 0;
	for (int i = 1; i < size; i++) {
		dif = (y_el[i] - y_el[i-1]);
		soma = soma + dif;
		cout << "dif = " << dif << endl;
		cout << "soma = " << soma << endl;
	}
	int media = soma/(size-1);
	cout << "media = " << soma/(size-1) << " primdif-var = " << primDif-var << " primdif+var = " << primDif+var << endl;
	return (media >= primDif-var && media <= primDif+var);
*/
}

/**
 * Function that returns true if a sequence of numbers
 * corresponds to a linear function
 * @param y_el[] the array of ints to be considered
 * @param size the number of elements in the array
 * @param var a variação (+/-) aceitável
 * @return true if corresponds to a linear function
 */
bool isLinear(const unsigned int y_el[], const int size, const int var) {

	// Esta abordagem usa os valores médios

	// Para saber se é linear, basta calcular as primeiras diferenças
	// entre elementos consecutivos, somar essas diferenças e dividir pelo número
	// de elementos -1.
	// O resultado terá de estar dentro do intervalo pretendido

	// Primeiro, verificar se é não é constante
	if (isConstant(y_el, size, var)) return false;
	// Agora que sabemos que não é constante
	int soma = 0;
	int primDif = y_el[1]-y_el[0];
	//cout << "primDif = " << primDif << endl;
	for (int i = 1; i < size; i++) {
		soma = soma + (y_el[i] - y_el[i-1]);
		//cout << "soma = " << soma << endl;
	}

	//
	int media = soma/(size-1);
	//cout << "media = " << soma/(size-1) << " primdif-var = " << primDif-var << " primdif+var = " << primDif+var << endl;
	return (media >= primDif-var && media <= primDif+var);
}

/**
 * Function that returns true if a sequence of numbers
 * corresponds to a quadratic function
 * @param y_el[] the array of ints to be considered
 * @param size the number of elements in the array
 * @param var a variação (+/-) aceitável
 * @return true if corresponds to a quadratic function
 */
bool isQuadratic(const unsigned int y_el[], const int size, const int var) {

	// Esta abordagem usa os valores médios

	// Para saber se é quadratica, primeiro garantir que não é constante nem linear.
	// Depois, Calcular as segundas diferenças entre elementos consecutivos, somar essas diferenças e dividir pelo número
	// de elementos -2.
	// O resultado terá de ser igual à diferença da primeira segunda-diferença
	//
	//
	// Primeiro, verificar se é não é constante (de notar que não é suficiente comparar com Linear, pois não ser linear
	// pode significar que é constante)
	if (isConstant(y_el, size, var)) return false;
	// Segundo, verificar se é não é linear
	if (isLinear(y_el, size, var)) return false;
	// Criar um array para guardar os valores das primeiras diferenças
	int y_el_prim_dif[size-1];
	// Calcular as primeiras diferenças e guardá-las no array
	for (int i = 1; i < size; i++ ) {
		y_el_prim_dif[i-1] = (y_el[i] - y_el[i-1]);
	}
	// Agora calcular as segundas-diferenças
	int soma = 0;
	int primDif = y_el_prim_dif[1]-y_el_prim_dif[0];

	for (int i = 1; i < size-1; i++) {
		soma = soma + (y_el_prim_dif[i] - y_el_prim_dif[i-1]);
	}
	//
	int media = soma/(size-2);
	return (media >= primDif-var && media <= primDif+var);

}

/**
 * Function that returns true if a sequence of numbers
 * corresponds to a cubic function
 * @param y_el[] the array of ints to be considered
 * @param size the number of elements in the array
 * @param var a variação (+/-) aceitável
 * @return true if corresponds to a cubic function
 */
bool isCubic(const unsigned int y_el[], const int size, const int var) {

	// Esta abordagem usa os valores médios

	// Para saber se é cubica, primeiro garantir que não é constante nem linear nem quadratica.
	// Depois, Calcular as terceiras diferenças entre elementos consecutivos, somar essas diferenças e dividir pelo número
	// de elementos -3.
	// O resultado terá de ser igual à diferença da primeira segunda-diferença
	//
	//
	// Primeiro, verificar se é não é constante (de notar que não é suficiente comparar com Linear, pois não ser linear
	// pode significar que é constante)
	if (isConstant(y_el, size, var)) return false;
	// Segundo, verificar se é não é linear
	if (isLinear(y_el, size, var)) return false;
	// Terceiro, verificar se é não é quadratica
	if (isQuadratic(y_el, size, var)) return false;
	// Criar um array para guardar os valores das primeiras diferenças
	int y_el_prim_dif[size-1];
	// Calcular as primeiras diferenças e guardá-las no array
	for (int i = 1; i < size; i++ ) {
		y_el_prim_dif[i-1] = (y_el[i] - y_el[i-1]);
	}
	// Criar um array para guardar os valores das segundas diferenças
	int y_el_sec_dif[size-2];
	// Calcular as segundas diferenças e guardá-las no array
	for (int y = 1; y < size-1; y++ ) {
		y_el_sec_dif[y-1] = (y_el_prim_dif[y] - y_el_prim_dif[y-1]);
	}
	// Agora calcular as terceiras-diferenças
	int soma = 0;
	int primDif = y_el_sec_dif[1]-y_el_sec_dif[0];

	for (int z = 1; z < size-2; z++) {
		soma = soma + (y_el_sec_dif[z] - y_el_sec_dif[z-1]);
	}
	//
	int media = soma/(size-3);
	return (media >= primDif-var && media <= primDif+var);

}

/**
 * Function that returns true if a sequence of numbers
 * corresponds to an exponential function
 * @param y_el[] the array of ints to be considered
 * @param size the number of elements in the array
 * @param var a variação (+/-) aceitável
 * @return true if corresponds to an exponential function
 */
bool isExponential(const unsigned int y_el[], const int size, const int var) {

	// Esta abordagem usa os valores médios

	// Para saber se é exponencial, basta calcular as primeiras divisoes
	// entre elementos consecutivos, somar essas diferenças e dividir pelo número
	// de elementos -1.
	// O resultado terá de ser igual ao valor da primeira divisão

	int soma = 0;
	int primDiv = y_el[1]/y_el[0];
	for (int i = 1; i < size; i++) {
		soma = soma + (y_el[i] / y_el[i-1]);
	}
	//
	int media = soma/(size-1);
	return (media >= primDiv-var && media <= primDiv+var);
}

/**
 * Função para devolver a diferença entre dois ticks
 * @param te  tick de fim
 * @param ts  tick de inicio
 * @return a diferença
 */
unsigned int getElapsed(ticks te, ticks ts) {
	return ( (int)te - (int)ts )/1000;
}


#endif /* PERFORMANCE_H_ */
