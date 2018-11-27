#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	if (this->palavra < ps1.palavra)
		return true;
	else
		return false;
}


void Dicionario::lerDicionario(ifstream &fich)
{
	string palavra, significado;
	while(!fich.eof()) {
		getline(fich, palavra);	// reads file from ifstream fich
		getline(fich, significado);	// reads file from ifstream fich
		PalavraSignificado PS(palavra, significado);
		palavras.insert(PS);
	}
	return;
}


string Dicionario::consulta(string palavra) const
{
     // a alterar
	return "";
}


bool Dicionario::corrige(string palavra, string significado)
{
	// a alterer
		return true;
}


void Dicionario::imprime() const
{
	// a alterar
     return;
}
