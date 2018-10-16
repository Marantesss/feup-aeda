
#include "veterinario.h"

Veterinario::Veterinario(string nome, int cod)
{
	this->nome = nome;
	codOrdem = cod;
}

string Veterinario::getNome() const {
	return nome;
}

long Veterinario::getCod() const {
	return codOrdem;
}
