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

bool PalavraSignificado::operator == (const PalavraSignificado &ps1) const {
	if (this->palavra == ps1.palavra)
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
	PalavraSignificado palavraParaEncontrar(palavra, "");
	PalavraSignificado palavraSignificadoEncontrado = this->palavras.find(palavraParaEncontrar);
	PalavraSignificado palavraNaoEncontrada("", "");
	BSTItrIn<PalavraSignificado> it(palavras);
	/* Nao encontrou */
	if (palavraNaoEncontrada == palavraSignificadoEncontrado) {
		string palavraAntes="", significadoAntes="";
		while (!it.isAtEnd() && it.retrieve().getPalavra() < palavra) {
			palavraAntes = it.retrieve().getPalavra();
			significadoAntes = it.retrieve().getSignificado();
			it.advance();
		}
		string palavraApos="", significadoApos="";
		if (!it.isAtEnd()) {
			palavraApos = it.retrieve().getPalavra();
			significadoApos = it.retrieve().getSignificado();
		}
		throw PalavraNaoExiste(palavraAntes, significadoAntes, palavraApos, significadoApos);
	}
	else
		return palavraSignificadoEncontrado.getSignificado();
}


bool Dicionario::corrige(string palavra, string significado)
{
	PalavraSignificado palavraSignificadoEncontrado = this->palavras.find(PalavraSignificado(palavra, ""));
	BSTItrIn<PalavraSignificado> it(palavras);
	/* Nao encontrou */
	if (PalavraSignificado("", "") == palavraSignificadoEncontrado) {
		palavras.insert(PalavraSignificado(palavra, significado));
		return false;
	}
	else {
		palavras.remove(PalavraSignificado(palavra, "")); /* Remove palavra existente */
		palavraSignificadoEncontrado.setSignificado(significado); /* Muda o significado */
		palavras.insert(palavraSignificadoEncontrado); /* Insere a palavra com o novo significado */
		return true;
	}
}


void Dicionario::imprime() const
{
	/* palavras => BST<PalavrasSignificado> */
	BSTItrIn<PalavraSignificado> it(palavras);
	while (!it.isAtEnd()) {
		cout << it.retrieve().getPalavra() << endl;
		cout << it.retrieve().getSignificado() << endl;
		it.advance();
	}
}
