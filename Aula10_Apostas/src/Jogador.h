#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "Aposta.h"
#include <string>

using namespace std;


//A ALTERAR!!
struct apostaHash {
	/* função de hash */
	int operator() (const Aposta & ap) const {
		return ap.somaNumeros();
	}
	/* função de igualdade */
	bool operator() (const Aposta & ap1, const Aposta & ap2) const {
		// 2 apostas sao diferentes se tiverem tamanhos diferentes
		if (ap1.tamanho() != ap2.tamanho())
			return false;
		// comparamos se ap1 tem os mesmos numeros que ap2
		unsigned numIguais = ap1.calculaCertos(ap2.getNumeros());
		if (numIguais == ap1.tamanho())
			return true;
		else
			return false;
	}
};

typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;


class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
