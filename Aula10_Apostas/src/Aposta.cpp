#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const {
	tabHInt::const_iterator it = numeros.find(num);
	if (it == numeros.end())
		return false;
	else
		return true;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n) {
	numeros.clear(); /* clears all previous bets numbers */
	unsigned nonRepeatedValues = 0;
	for (unsigned i = 0; nonRepeatedValues < n; i++) {
		pair<tabHInt::iterator, bool> num = numeros.insert(valores[i]);
		if (num.second)
			nonRepeatedValues++;
	}

}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const {
	unsigned certos = 0;
	tabHInt::const_iterator it;
	for (it = sorteio.begin(); it != sorteio.end(); it++) {
		if(contem(*it))
			certos++;
	}
	return certos;
}

unsigned Aposta::somaNumeros() const {
	unsigned soma = 0;
	tabHInt::const_iterator it;
	for (it = numeros.begin(); it != numeros.end(); it++) {
		soma += *it;
	}
	return soma;
}

unsigned Aposta::tamanho() const {
	return numeros.size();
}
