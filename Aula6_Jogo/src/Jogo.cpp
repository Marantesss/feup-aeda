/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <iostream>
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

	while(criancas.size() != 1) {
		for (int n = this->numPalavras(frase); n > 1; n--) {
			if (it == it_end)
				it = criancas.begin();
			else
				it++;
		}
		cout << criancas.size() << endl;
		cout << "Sai: " <<  it->escreve() << endl;
		it = criancas.erase(it);
	}

	return *it;
}


list<Crianca>& Jogo::inverte()
{
	criancas.reverse();
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	// a alterar
	list<Crianca> res;
	return res;
}

bool Jogo::operator==(Jogo& j2)
{
	// a alterar
	return true;
}


list<Crianca> Jogo::baralha() const
{
	// a alterar
	list<Crianca> res;
	return res;
}
