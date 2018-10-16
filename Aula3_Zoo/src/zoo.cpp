#include "zoo.h"


int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *al) {
	animais.push_back(al);
}

string Zoo::getInformacao() const {
	stringstream a;
	string s;
	for (Animal *an: animais) {
		s = an->getInfo();
		a << s << endl;
	}
	return a.str();
}

bool Zoo::animalJovem(string nomeA) {
	for (Animal *an: animais) {
		if (an->getNome() == nomeA && an->eJovem())
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
	int i = 0;
	for (Animal * a:animais) {
		a->setVeterinario(veterinarios[i]);
		i++;
		i = i % veterinarios.size();
	}
}

bool Zoo::removeVeterinario (string nomeV) {
	Veterinario * temp = NULL;
	vector <Veterinario *>::const_iterator next;

	// Apaga o veterinarios com o nome nomeV do vector veterinarios
	for (Veterinario *v:veterinarios) {
		if (v->getNome() == nomeV) {
			temp = v;
			next = find(veterinarios.begin(), veterinarios.end(), temp);
			veterinarios.erase(next);
			break;
		}
	}

	if (temp == NULL)
		return false;

	if (next >= veterinarios.end()) {
		next = veterinarios.begin();
	}

	for (Animal *a:animais) {
		if (a->getVet()->getNome() == nomeV)
			a->setVeterinario((*next));
	}
	return true;
}

bool Zoo::operator < (Zoo& zoo2) const {
	int z1 = 0, z2 = 0;
	for (Animal *a:animais) {
		z1 += a->getIdade();
	}
	for (Animal *a:zoo2.animais) {
		z2 += a->getIdade();
	}
	return z1 < z2;
}
