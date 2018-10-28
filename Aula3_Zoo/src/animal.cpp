#include "animal.h"

// Classe Animal
int Animal::maisJovem = 999999;

Animal::Animal(string nome, int idade) {
	this->nome = nome;
	this->idade = idade;
	this->vet = NULL;
	if (Animal::maisJovem > idade)
		Animal::maisJovem = idade;
}

string Animal::getNome() const {
	return this->nome;
}

int Animal::getIdade() const {
	return this->idade;
}

int Animal::getMaisJovem() {
	return Animal::maisJovem;
}

void Animal::setVeterinario(Veterinario *v) {
	this->vet = v;
}

Veterinario * Animal::getVet() {
	return this->vet;
}

// Classe Cao:Animal
Cao::Cao(string nome, int idade, string raca): Animal(nome, idade) {
	this->raca = raca;
}

bool Cao::eJovem() const {
	if (this->idade < 5)
		return true;
	else
		return false;
}

string Cao::getInformacao() {
	stringstream a;
	if (vet != NULL)
		a << nome << ", " << idade << ", " << vet->getNome() << ", " << vet->getCod() << ", " << raca;
	else
		a << nome << ", " << idade << ", " << raca;
	return a.str();
}

// Classe Voador
Voador::Voador(int vmax, int amax) {
	this->velocidade_max = vmax;
	this->altura_max = amax;
}

int Voador::getVelocidade() const {
	return this->velocidade_max;
}

int Voador::getAltura() const {
	return this->altura_max;
}

// Classe morcego:Animal, Voador
Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome, idade), Voador(vmax, amax) {}

bool Morcego::eJovem() const {
	if (this->idade < 4)
		return true;
	else
		return false;
}

string Morcego::getInformacao() {
	stringstream a;
	a << nome << ", " << idade << ", " << this->getVelocidade() << ", " << this->getAltura();
	if (vet != NULL)
		a << ", " << vet->getNome() << ", " << vet->getCod();
	return a.str();
}
