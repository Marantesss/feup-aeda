/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"


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
	// TODO
	return 0;
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	// TODO
	Caixa cx;
	return cx;
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	// TODO
	return 0;
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	// TODO
	return "";
}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	// TODO
	Caixa cx;
	return cx;
}



