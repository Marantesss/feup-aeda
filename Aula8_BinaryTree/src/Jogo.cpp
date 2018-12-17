#include "Jogo.h"
#include <sstream>

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}


ostream &operator << (ostream &os, Circulo &c1)
{
	string estado = "false";
	if (c1.estado)
		estado="true";
	os << c1.pontuacao << "-" << estado  << "-" << c1.nVisitas << "\n";
	return os;
}


/*
 * se o estado é igual a falso, a bola vai para a esquerda
 * se é igual a verdadeiro, a bola vai para a direita
 **/
BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int nivel, vector<int> &pontos, vector<bool> &estados) {
	Circulo c1(pontos[pos], estados[pos]);
	/* Chegou ao fim */
	if (nivel == 0)
		return BinaryTree<Circulo>(c1);
	BinaryTree<Circulo> filhoEsq = iniciaJogo(2*pos+1, nivel-1, pontos, estados);
	BinaryTree<Circulo> filhoDir = iniciaJogo(2*pos+2, nivel-1, pontos, estados);
	return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}


Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados) {
	jogo=iniciaJogo(0, niv, pontos, estados);
}


string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> it(jogo);
	stringstream ss;
	while (!it.isAtEnd()) {
		ss << it.retrieve();
		it.advance();
	}
	return ss.str();
}


int Jogo::jogada()
{
	int pos = 1; /* Posicao da raiz = 1 */
	BTItrLevel<Circulo> it(jogo);
	int pontuacao = 0;
	if (it.isAtEnd()) return pontuacao;
	while (!it.isAtEnd()) {
		Circulo &c = it.retrieve();
		int n;
		if (it.retrieve().getEstado()) n = pos + 1;
		else n = pos;
		c.mudaEstado();
		c.incVisitas();
		pontuacao = c.getPontuacao();
		int i = 0;
		while (!it.isAtEnd() && i < n) {
			i++;
			it.advance();
		}
		pos += n;
	}
	return pontuacao;
}



int Jogo::maisVisitado()
{
	BTItrLevel<Circulo> it(jogo);
	if (it.isAtEnd()) return 0;
	it.advance(); /* Ignorar a Raiz */
	int nVisitas = it.retrieve().getNVisitas();
	it.advance();
	while (!it.isAtEnd()) {
		if (nVisitas < it.retrieve().getNVisitas())
			nVisitas = it.retrieve().getNVisitas();
		it.advance();
	}
	return nVisitas;
}




