#include "Parque.h"
#include <vector>

using namespace std;

unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
	return numMaximoClientes;
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):lotacao(lot), numMaximoClientes(nMaxCli)
{ // :lotacao(lot) forma de inicializar variaveis const
	vagas = lot;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
	for (size_t i = 0; i < clientes.size(); i++ ) { // unsigned int i pq clientes.size() e unsigned
		if (clientes.at(i).nome == nome)
			return i;
	}
	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
	if (lotacao == clientes.size()) // Se lotacao for igual ao numero de clientes
		return false;
	InfoCartao c1; // Cria InfoCartao vazia
	c1.nome = nome; // Adiciona nome
	c1.presente = false; // Adiciona presente
	clientes.push_back(c1); // Coloca no final do vetor clientes
	return true;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	for(size_t i = 0; i < clientes.size(); i++)
		if(clientes.at(i).nome == nome && vagas > 0 && clientes.at(i).presente == false){
			clientes.at(i).presente=true;
			vagas--;
			return true;
		}
	return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for(size_t i = 0; i < clientes.size(); i++)
			if(clientes.at(i).nome == nome && clientes.at(i).presente == false){
				clientes.erase(clientes.begin()+i); // Apaga elemento de indice i
				return true;
			}
		return false;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	for(size_t i = 0; i < clientes.size(); i++)
		if(clientes.at(i).nome == nome && clientes.at(i).presente){
			clientes.at(i).presente=false;
			vagas++;
			return true;
		}
	return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return (lotacao-vagas);
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
	return (clientes.size());
}
