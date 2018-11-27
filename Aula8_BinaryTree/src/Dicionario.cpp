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
	// a alterar
	return true;
}


void Dicionario::lerDicionario(ifstream &fich)
{
	// a alterar
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
