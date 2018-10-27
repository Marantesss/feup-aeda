#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;

bool InfoCartao::operator == (const InfoCartao &ic1) const {
	return (ic1.nome == nome);
}

bool InfoCartao::operator < (const InfoCartao &ic1) const {
	if (ic1.frequencia < frequencia)
		return true;
	else if ((ic1.frequencia == frequencia) && (ic1.nome > nome))
		return true;
	else
		return false;
}

ClienteNaoExistente::ClienteNaoExistente(string nome) {
	this->nome = nome;
}

string ClienteNaoExistente::getNome() const {
	return this->nome;
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia++;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const {
	if (posicaoCliente(nome) == -1)
		throw ClienteNaoExistente(nome);
	else
		return clientes[posicaoCliente(nome)].frequencia;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia() {
	insertionSort(clientes);
}

// alterado
int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	InfoCartao cliente;
	cliente.nome = nome;
	return sequentialSearch(clientes, cliente);
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2) {
	vector<string> nomeClientes;
	for (size_t i = 0; i > clientes.size(); i++) {
		if (clientes[i].frequencia >= n1 && clientes[i].frequencia <= n2) {
			nomeClientes.push_back(clientes[i].nome);
		}
	}
	return nomeClientes;
}
