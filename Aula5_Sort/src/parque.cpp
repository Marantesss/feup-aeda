#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>
#include <algorithm>

using namespace std;

bool InfoCartao::operator == (const InfoCartao &ic1) const {
	if (this->nome == ic1.nome)
		return true;
	else
		return false;
}

bool InfoCartao::operator < (const InfoCartao &ic1) const {
	if (frequencia > ic1.frequencia) // > porque queremos por ordem decrescente de frequencia
		return true;
	else if (frequencia < ic1.frequencia)
		return false;
	else
		return (nome < ic1.nome); // mas queremos ordem crescente de nomes caso a frequencia seja igual
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const {
	return clientes;
}


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
	clientes[pos].frequencia++; // adicionado
	vagas--;
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

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	InfoCartao inf1;
	inf1.nome = nome;
	int pos = sequentialSearch(clientes, inf1);
	return pos;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const {
	int pos = posicaoCliente(nome);
	if (pos == -1) {
		throw ClienteNaoExistente(nome);
	}
	return clientes[pos].frequencia;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia() {
	insertionSort(clientes);
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2) {
	ordenaClientesPorFrequencia();
	vector<string> nomes;
	for (unsigned int i=0; i < clientes.size(); i++) {
		if (clientes[i].frequencia < n1)
	      	break;
	    if (clientes[i].frequencia <= n2)
	       	nomes.push_back(clientes[i].nome);
	}
	return nomes;
}

bool compNome(const InfoCartao &c1, const InfoCartao &c2) {
	return c1.nome < c2.nome;
}

void ParqueEstacionamento::ordenaClientesPorNome() {
	sort(clientes.begin(), clientes.end(), compNome);
}
