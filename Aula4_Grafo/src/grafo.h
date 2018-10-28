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
	No(N inf) {
		info = inf;
	}
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
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

// excecao  ArestaRepetida
template <class N>
class ArestaRepetida
{
public:
   N info1, info2;
   ArestaRepetida(N inf1, N inf2) { info1=inf1; info2=inf2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &a)
{ out << "Aresta repetida: " << a.info1 << " , " << a.info2; return out; }

// excecao  ArestaInexistente
template <class N>
class ArestaInexistente
{
public:
   N info1, info2;
   ArestaInexistente(N inf1, N inf2) { info1=inf1; info2=inf2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &a)
{ out << "Aresta inexistente: " << a.info1 << " , " << a.info2; return out; }

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

// IMPLEMENTACAO METODOS CLASSE GRAFO


/* Exercicio a) */

// Construtor
template <class N, class A>
Grafo<N,A>::Grafo() {}

// Destrutor
template <class N, class A>
Grafo<N,A>::~Grafo() {

	/* NAO TENHO A CERTEZA SE FUNCIONA
	for (size_t i = 0; i < nos.size(); i++) {
		delete *nos[i];
	}
	*/

	typename vector< No<N,A>*>::const_iterator it; // Apenas define o iterador
	for (it = nos.begin(); it != nos.end(); it++) {
		delete *it; // Apaga o conteudo de nos
	}
}

template <class N, class A>
int Grafo<N,A>::numNos() const {
	return nos.size();
}

template <class N, class A>
int Grafo<N,A>::numArestas() const {
	int numA = 0;

    typename vector< No<N,A> *>::const_iterator it;

    // Percorre o vetor nos, que e um vetor de vetores (arestas)
	for (it = nos.begin(); it != nos.end(); it++) {
		numA += (*it)->arestas.size();
	}

	/*
	for (size_t i = 0; i < nos.size(); i++) {
		n
		numA += nos[i]->arestas.size();
	}
	*/

	return numA;
}

/* Exercicio b) */

// inserir No
template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirNo(const N &dados) {
    typename vector< No<N,A> *>::const_iterator it;

    // Percorre o vetor nos a ver se ha dados repetidos
	for (it = nos.begin(); it != nos.end(); it++) {
		if((*it)->info == dados)
			throw NoRepetido<N>(dados);
	}
	No<N, A> *no1 = new No<N, A>(dados);
	nos.push_back(no1);
	return *this;
}

/* Exercicio c) */

// inserir Aresta
template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
    typename vector< No<N,A> *>::const_iterator it;
    typename vector< Aresta<N,A> >::iterator ita;
    bool encontrouInicio = false;
    bool encontrouFim = false;

	No<N,A> *noInicio_apt=NULL;
	No<N,A> *noFim_apt=NULL;

    // Percorre o vetor nos a ver se ha dados repetidos
	for (it = nos.begin(); it != nos.end(); it++) {
		// procura no vetor de nos, o no em que info == inicio
		if((*it)->info == inicio) {
			encontrouInicio = true;
			noInicio_apt = *it;
			//verifica se o vetor de arestas ja tem uma aresta para o destino = fim
			for (ita = (*it)->arestas.begin(); ita != (*it)->arestas.end(); ita++) {
				if (ita->destino->info == fim)
					throw ArestaRepetida<N> (inicio, fim);
			}
		}
		else if ((*it)->info == fim) {
			encontrouFim = true;
			noFim_apt=*it;
			if (encontrouInicio==true)
				break;
		}
	}

	// Nao encontrando um dos nos lanca excecao tipo NoInexistente
	if (!encontrouInicio) throw NoInexistente<N>(inicio);
	if (!encontrouFim) throw NoInexistente<N>(fim);

	// cria uma nova Aresta
	Aresta<N,A> aresta1(noFim_apt, val);
	// insere o objecto no vector de arestas do no
	noInicio_apt->arestas.push_back(aresta1);

	return *this;
}

// valor Aresta
template <class N, class A>
A & Grafo<N, A>::valorAresta(const N &inicio, const N &fim) {
    typename vector< No<N,A> *>::const_iterator it;
    typename vector< Aresta<N,A> >::iterator ita;

	// procura no vetor de nos, o no em que info == inicio
	for (it = nos.begin(); it != nos.end(); it++) {
		if((*it)->info == inicio) {
			// verifica se o vetor de arestas tem uma aresta para o destino == fim
			for (ita = (*it)->arestas.begin(); ita != (*it)->arestas.end(); ita++) {
				if (ita->destino->info == fim)
					return ita->valor; // Encontrou o No
			}
			// Nao encontrou a aresta
			throw ArestaInexistente<N> (inicio, fim);
		}
	}
	// Nao encontrou o No
	throw NoInexistente<N>(inicio);
}

// Eliminar Aresta
template <class N, class A>
Grafo<N, A> & Grafo<N, A>::eliminarAresta(const N &inicio, const N &fim) {
    typename vector< No<N,A> *>::const_iterator it;
    typename vector< Aresta<N,A> >::iterator ita;

	// procura no vetor de nos, o no em que info == inicio
	for (it = nos.begin(); it != nos.end(); it++) {
		if((*it)->info == inicio) {
			// verifica se o vetor de arestas tem uma aresta para o destino == fim
			for (ita = (*it)->arestas.begin(); ita != (*it)->arestas.end(); ita++) {
				if (ita->destino->info == fim) {
					(*it)->arestas.erase(ita);
					return *this; // Encontrou o No
				}
			}
			// Nao encontrou a aresta
			throw ArestaInexistente<N> (inicio, fim);
		}
	}
	// Nao encontrou o No
	throw NoInexistente<N>(inicio);

	return *this;
}

// Imprimir
template <class N, class A>
void Grafo<N, A>::imprimir(std::ostream &os) const {
	typename vector< No<N,A> *>::const_iterator it;
	typename vector< Aresta<N,A> >::const_iterator ita;

	for (it = nos.begin(); it != nos.end(); it++) {
		os << "( " << (*it)->info;
		for (ita = (*it)->arestas.begin(); ita != (*it)->arestas.end(); ita++) {
			os << "[ " << ita->destino->info << " " << ita->valor << "] ";
		}
		os << ") ";
	}
}

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N, A> &g)
{
   g.imprimir(out);
   return out;
}
