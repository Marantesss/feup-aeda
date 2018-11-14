#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"
#include <time.h>       /* time */

using namespace std;


Cliente::Cliente() {
	  /* initialize random seed: */
	  srand (time(NULL));
	  /* generate secret number between 1 and 5: */
	  this->numPresentes = rand() % 5 + 1;

}


int Cliente::getNumPresentes() const {
	return this->numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	this->clientes_atendidos = 0;
	this->tempo_atual = 0;
	this->prox_saida = 0;
	/* initialize random seed: */
	srand (time(NULL));
	/* generate secret number between 20 and 5: */
	this->prox_chegada = rand() % 20 + 1;

}      


void Balcao:: proximoEvento()
{
	// a alterar
}


void Balcao::chegada()
{
	//... cria cliente
	Cliente c;

	//... insere na fila
	clientes.push(c);

	//... gerar aleatoriamente o novo tempo de chegada do proximo cliente
	/* initialize random seed: */
	srand (time(NULL));
	/* generate secret number between 20 and 5: */
	this->prox_chegada = rand() % 20 + 1;

	//... atualizar tempo de saida
	if (clientes.size() == 1) {
		this->prox_saida = this->tempo_atual + c.getNumPresentes() * this->tempo_embrulho;
	}

	//... escrever no monitor
	cout << "chegou novo cliente com " << c.getNumPresentes() << " presentes" << endl;

}   


void Balcao::saida()
{
	this->getProxCliente();

}


int Balcao::getTempoAtual() const {
	return this->tempo_atual;
}


int Balcao::getProxChegada() const {
	return this->prox_chegada;
}

int Balcao::getClientesAtendidos() const {
	return this->clientes_atendidos;
}

int Balcao::getTempoEmbrulho() const {
	return this->tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return this->prox_saida;
}

Cliente & Balcao::getProxCliente() {
	if(!clientes.empty()) {
		return this->clientes.front();
	}
	else
		throw(FilaVazia());
}

ostream & operator << (ostream & out, const Balcao & b1)
{
	// a alterar
     return out;
}
