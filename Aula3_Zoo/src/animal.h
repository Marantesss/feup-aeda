#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
using namespace std;

class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	Animal(string nome, int idade);
	virtual ~Animal(){};
	string getNome() const;
	int getIdade() const;
	static int getMaisJovem();
	void setVeterinario(Veterinario *v);
	Veterinario * getVet();
	virtual bool eJovem() const = 0;
	virtual string getInformacao(){return NULL;};
};



class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	bool eJovem() const;
	string getInformacao();
	//completar
};



class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
	virtual ~Voador(){};
	int getVelocidade() const;
	int getAltura() const;
	virtual string getInformacao(){return NULL;};
	//completar
};



class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	bool eJovem() const;
	string getInformacao();
	//completar
};


#endif /* SRC_ANIMAL_H_ */
