#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) { info = inf; }
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(ostream &os) const;
};

template <class N, class A> 
ostream & operator<<(ostream &out, const Grafo<N,A> &g);

template <class N, class A> // Construtor
Grafo<N,A>::Grafo() {}

template <class N, class A> // Destrutor
Grafo<N,A>::~Grafo()
{
	for (size_t i = 0; i < nos.size(); i++) {
		nos.at(i)->arestas.clear(); // Apaga as arestas
		nos.at(i)->info.clear();
	}
	nos.clear(); // Apaga os nos
}

template <class N, class A>
int Grafo<N,A>::numNos() const
{
	return nos.size();
}

template <class N, class A>
int Grafo<N,A>::numArestas() const
{
	int num = 0;
	for (size_t i = 0; i < nos.size(); i++) {
		num += nos.at(i)->arestas.size();
	}
	return num;
}

// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};

template <class N>
ostream & operator<<(ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }

template <class N, class A>
Grafo <N,A> & Grafo<N,A>::inserirNo(const N &dados)
{
	for (size_t i = 0; i < nos.size(); i++) {
		if (dados == nos.at(i)->info)
			throw NoRepetido<N>(dados);
	}
	No<N, A> *novoNo = new No<N, A>(dados); // Criar novo no
	nos.push_back(novoNo); // Inserir o novo no
	return *(this);
}

// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) { info = inf; }
};
template <class N>
ostream & operator<<(ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template <class N, class A>
Grafo <N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val)
{
	return *(this);
}
