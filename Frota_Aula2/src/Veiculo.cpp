#include "Veiculo.h"
#include <iostream>

using namespace std;
// So para o commit
Veiculo::Veiculo(string mc, int m, int a)
{
	marca = mc;
	mes = m;
	ano = a;
}

string Veiculo::getMarca() const
{
	return marca;
}

int Veiculo::getAno() const
{
	return ano;
}

int Veiculo::info() const
{
	cout << "Marca: " << marca << endl;
	cout << "Mes: " << mes << endl;
	cout << "Ano: " << ano << endl;
	return 3;
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc, m, a)
{
	combustivel = c;
	cilindrada = cil;
}

string Motorizado::getCombustivel() const
{
	return combustivel;
}

int Motorizado::info() const
{
	cout << "Marca: " << marca << endl;
	cout << "Mes: " << mes << endl;
	cout << "Ano: " << ano << endl;
	cout << "Combustivel: " << combustivel << endl;
	cout << "Cilindrada: " << cilindrada << endl;
	return 5;
}

Automovel::Automovel(string mc, int m, int a, string c, int cil): Motorizado(mc, m, a, c, cil) {}

int Automovel::info() const
{
	cout << "Marca: " << marca << endl;
	cout << "Mes: " << mes << endl;
	cout << "Ano: " << ano << endl;
	cout << "Combustivel: " << combustivel << endl;
	cout << "Cilindrada: " << cilindrada << endl;
	return 5;
}

Camiao::Camiao(string mc, int m, int a,string c, int cil,int cm): Motorizado(mc, m, a, c, cil)
{
	carga_maxima = cm;
}

int Camiao::info() const
{
	cout << "Marca: " << marca << endl;
	cout << "Mes: " << mes << endl;
	cout << "Ano: " << ano << endl;
	cout << "Combustivel: " << combustivel << endl;
	cout << "Cilindrada: " << cilindrada << endl;
	cout << "Carga Maxima: " << carga_maxima << endl;
	return 6;
}

Bicicleta::Bicicleta(string mc, int m, int a,string t): Veiculo(mc, m, a)
{
	tipo = t;
}

int Bicicleta::info() const
{
	return 4;
}
