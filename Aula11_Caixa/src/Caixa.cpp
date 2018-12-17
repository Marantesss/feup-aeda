/*
 * Caixa.cpp
 */

#include "Caixa.h"


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

unsigned Caixa::ultimoId = 1;


/* a implementar pelos estudantes */

bool Objeto::operator<(const Objeto& o1) const {
	if (this->peso < o1.peso)
		return true;
	else
		return false;
}

bool Caixa::operator<(const Caixa& c1) const {
	/* A caixa com menos carga livre está em primeiro lugar na priority_queue */
	return cargaLivre > c1.cargaLivre;
}


string Caixa::imprimeConteudo() const {
	stringstream ss;
	if( objetos.empty() ) ss << "Caixa " << id << " vazia!" << endl;
	else {
		STACK_OBJS buffer = objetos;
		ss << "C" << id << "[";
		while( !buffer.empty() ) {
			Objeto obj = buffer.top();
			buffer.pop();
			ss << " " << obj;
		}
		ss << " ]";
	}
	return ss.str();
}


