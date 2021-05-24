#pragma once

#include <string>

using namespace std;


class Ventas
{
private:
public:
	void ingresarCliente(string nombre/*, string apellidos, string nit, char genero, string telefono, string correo*/);
};

inline void Ventas::ingresarCliente(string nombre/*, string apellidos, string nit, char genero, string telefono, string correo*/) {
	cout << "Funcion de prueba de ingreso de cliente " << nombre << endl;
	system("pause");
}
