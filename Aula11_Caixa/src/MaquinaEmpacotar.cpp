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
	vector<Objeto>::iterator it;
	for (it = objs.begin(); it != objs.end(); it++) {
		if (it->getPeso() < this->capacidadeCaixas) {
			objetos.push(*it);
			objs.erase(it);
			it--;
		}
	}
	return objetos.size();
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	/* Para guardar as caixas que vamos fazendo pop */
	vector<Caixa> tmp;
	Caixa cx;

	/* Procura na caixa mais cheia para a mais vazia */
	while (!this->caixas.empty()) {
		cx = this->caixas.top();
		this->caixas.pop();
		/* Encontrou */
		if (cx.getCargaLivre() >= obj.getPeso()) {
			/* Coloca de volta na priority_queue todas as caixas que retirou */
			for (unsigned i = 0; i < tmp.size(); i++) {
				caixas.push(tmp[i]);
			}
			return cx;
		}
		else
			tmp.push_back(cx);
	}
	/* Nao encontrou */
	/* Coloca de volta na priority_queue todas as caixas que retirou */
	for (unsigned i = 0; i < tmp.size(); i++) {
		caixas.push(tmp[i]);
	}
	return Caixa(this->capacidadeCaixas);
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	while(!this->objetos.empty()) {
		Objeto o = objetos.top();
		objetos.pop();
		/* Proura a caixa com capacidade suficiente para adicionar um objeto
		 * S nao encontrar, e criada uma nova (ver procuraCaixa) */
		Caixa c = procuraCaixa(o);
		c.addObjeto(o);
		caixas.push(c);
	}
	return caixas.size();
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	stringstream ss;
	if (objetos.empty())
		ss << "Nao ha objetos!\n";
	else {
		HEAP_OBJS buffer = objetos;
		while( !buffer.empty() ) {
			Objeto obj = buffer.top();
			buffer.pop();
			ss << obj << endl;
		}
	}
	return ss.str();
}

Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	Caixa caixaMaisObj;
	if (caixas.empty())
		throw(MaquinaSemCaixas());
	else {
		HEAP_CAIXAS buffer = caixas;
		caixaMaisObj = buffer.top();
		buffer.pop();
		while( !buffer.empty() ) {
			if(caixaMaisObj.getSize() < buffer.top().getSize())
				caixaMaisObj = buffer.top();
			buffer.pop();
		}
	}
	return caixaMaisObj;
}
