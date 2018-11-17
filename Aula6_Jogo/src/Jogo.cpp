/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <iostream>
#include <time.h>
using namespace std;

unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  unsigned pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{
	list<Crianca> c; // empty list
	this->criancas = c;
}

Jogo::Jogo(list<Crianca>& lc2)
{
	this->criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return this->criancas;
}

void Jogo::setCriancasJogo(const list<Crianca>& l1) {
	this->criancas = l1;
}

string Jogo::escreve() const
{
	stringstream oss;
	list<Crianca>::const_iterator it;
	for (it = criancas.begin(); it != criancas.end(); it++) {
		oss << it->escreve() << endl; // = (*it).escreve();
	}

	return oss.str();
}


Crianca& Jogo::perdeJogo(string frase)
{
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator it_end = criancas.end();
	int numPalavrasFrase = this->numPalavras(frase) - 1;
	int numCriancas, ultimaVolta;
	while(criancas.size() > 1) {
		numCriancas = this->criancas.size();
		ultimaVolta = numPalavrasFrase%numCriancas;	// Evita voltas
		for (int i = 0; i < ultimaVolta; i++) {
			it++;
			if (it == it_end)
				it = criancas.begin();
		}
		cout << "Sai: " <<  it->escreve() << endl;
		it = criancas.erase(it);
		if (it == it_end)
			it = criancas.begin();
	}

	return *it;
}


list<Crianca>& Jogo::inverte()
{
	//... o QUE ELES QUEREM
	/*
	list<Crianca> l1;
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator ite = criancas.end();
	while ( it != ite )
	{
		Crianca *c=new Crianca(*it);
		l1.push_front(*c);
		it ++;
	}
	criancas = l1;
	*/

	//... O QUE AS PESSOAS NORMAIS FAZEM
	this->criancas.reverse();
	return this->criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> returnList;
	list<Crianca>::iterator it = criancas.begin();
	// list<Crianca>::iterator it_end = criancas.end();
	int numCriancas = this->criancas.size();
	for (int i = 0; i < numCriancas; i++) {
		if (it->getIdade() > id) {
			returnList.push_back(*it);
			it = criancas.erase(it);
		}
		else {
			it++;
		}
	}
	return returnList;
}

bool Jogo::operator==(Jogo& j2)
{
	if (this->criancas.size() != j2.criancas.size()) {
		return false;
	}

	list<Crianca>::iterator it = this->criancas.begin();
	list<Crianca>::iterator it_end = this->criancas.end();
	list<Crianca>::iterator it2 = j2.criancas.begin();

	for (/* nada */; it != it_end; it++, it2++) {
		if (!(*it == *it2)) { // usa-se !(==) porque o operador != nao esta definido
			return false;
		}
	}

	return true;
}


list<Crianca> Jogo::baralha() const
{
	list<Crianca> returnList;
	list<Crianca> trocaCriancas = this->criancas;

	int rPos;

	/* initialize random seed: */
	srand(time(NULL) );

	while( !trocaCriancas.empty() ){
		/* generate a random position: */
		rPos = rand() % trocaCriancas.size();
		list<Crianca>::iterator it = trocaCriancas.begin();
		for(int i = 0; i < rPos; i++, it++);	// incrementa o it nPos vezes
		returnList.push_back(*it);				// adiciona ao returnList
		trocaCriancas.erase(it);				// essa crianca já esta escolhida
	}

	return returnList;
}
