
#include "animal.h"

int Animal::maisJovem = 100;

Animal::Animal(string nome, int idade)
{
	this-> nome = nome;
	this->idade = idade;
	vet = 0;
	if(idade < maisJovem)
		maisJovem = idade;
}

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const{
	return idade;
}

int Animal::getMaisJovem() {
	return maisJovem;
}

string Animal::getInfo() {
	stringstream a;
	a << nome << ", " << idade;
	if (vet != NULL)
		a << ", " << vet->getNome() << ", " << vet->getCod();
	return a.str();
}

void Animal::setVeterinario(Veterinario *v){
	this->vet = v;
}

Veterinario * Animal::getVet(){
	return vet;
}

Cao::Cao(string nome, int idade, string raca):Animal(nome, idade)
{
	this ->raca = raca;
}

bool Cao::eJovem() const {
	if (idade < 5)
		return true;
	else
		return false;
}

Voador::Voador(int vmax, int amax)
{
	velocidade_max = vmax;
	altura_max = amax;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax):Animal(nome, idade), Voador(vmax, amax) {}

bool Morcego::eJovem() const {
	if (idade < 4)
		return true;
	else
		return false;
}
