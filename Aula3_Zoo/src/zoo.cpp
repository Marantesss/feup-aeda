#include "zoo.h"


int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
	this->animais.push_back(a1);
}

string Zoo::getInformacao() const {
	stringstream a;
	string s;
	for (Animal *an: animais) {
		s = an->getInformacao();
		a << s << endl;
	}
	return a.str();
}

bool Zoo::animalJovem(string nomeA) {
	for (size_t i = 0 ; i < animais.size(); i++) {
		if(animais[i]->getNome() == nomeA && animais[i]->eJovem())
			return true;
	}
	return false;
}

void Zoo::alocaVeterinarios(istream &isV) {
	string nome, cod;

	// Aloca os veterinarios no vetor veterinarios
	while(!isV.eof()) {
		getline(isV,nome);
		getline(isV, cod);
		Veterinario *v = new Veterinario(nome, stoi(cod));
		veterinarios.push_back(v);
	}

	// Distribui os veterinários uniformemente pelos animais do zoo.
	int j = 0;
	for (size_t i = 0; i < animais.size(); i++) {
		animais[i]->setVeterinario(veterinarios[j]);
		j++;
		j = j % veterinarios.size();
	}
}

bool Zoo::removeVeterinario (string nomeV) {
	if(!procuraVeterinario(nomeV))
		return false;

	unsigned int pos;

	// Apaga o Vet do vetor veterinarios
	for (size_t i = 0; i < veterinarios.size(); i++) {
		if (veterinarios[i]->getNome() == nomeV) {
			veterinarios.erase(veterinarios.begin() + i);
			pos = i;
		}
	}

	// Alocando para o Vet seguinte
	if (pos == veterinarios.size())
		pos = 0;

	for (size_t i = 0; i < animais.size(); i++) {
		if (animais[i]->getVet()->getNome() == nomeV)
			animais[i]->setVeterinario(veterinarios[pos]);
	}

	return true;
}

bool Zoo::procuraVeterinario (string nomeV) {
	for (size_t i = 0 ; i < veterinarios.size(); i++) {
		if(veterinarios[i]->getNome() == nomeV)
			return true;
	}
	return false;
}

bool Zoo::operator < (Zoo& zoo2) const {
	int z1 = 0, z2 = 0;
	for (size_t i = 0; i < animais.size(); i++) {
			z1 += animais[i]->getIdade();
	}

	for (size_t i = 0; i < zoo2.animais.size(); i++) {
			z2 += zoo2.animais[i]->getIdade();
	}

	/*
	for (Animal *a:animais) {
		z1 += a->getIdade();
	}

	for (Animal *a:zoo2.animais) {
		z2 += a->getIdade();
	*/

	return z1 < z2;
}

