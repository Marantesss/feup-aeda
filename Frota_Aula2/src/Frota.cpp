#include "Frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1)
{
	veiculos.push_back(v1); // Apenas preciso de escrever v1
}

int Frota::numVeiculos() const
{
	return veiculos.size();
}

int Frota::menorAno() const
{
	int ano;
	if (veiculos.size() == 0)
		return 0;
	else
		ano = veiculos.at(0)->getAno();
	for(unsigned int i = 1; i < veiculos.size(); i++) {
		if (ano > veiculos.at(i)->getAno())
			ano = veiculos.at(i)->getAno();
	}
	return ano;
}
